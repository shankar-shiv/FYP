

import numpy as np
import matplotlib.pyplot as plt
import pathlib
from ecgdetectors import Detectors
import sys
import wfdb
from scipy.signal import butter, lfilter, freqz, hilbert
import peakutils
from hrv import HRV
import psutil

record = wfdb.rdsamp('mitdb/100')
annotation = wfdb.rdann('mitdb/100', 'atr')
lead_I = record[0][:, 0]


def process_ecg(data, threshold=0.15):
    transformed = np.abs(hilbert(np.gradient(data)))
    return peakutils.indexes(transformed, thres=0.1,  min_dist=100)


import numpy as np
import pywt
import scipy.signal as signal


class Detectors:
    """ECG heartbeat detection algorithms
    General useage instructions:
    r_peaks = detectors.the_detector(ecg_in_samples)
    The argument ecg_in_samples is a single channel ECG in volt
    at the given sample rate.
    """

    def __init__(self, sampling_frequency = False):
        """
        The constructor takes the sampling rate in Hz of the ECG data.
        The constructor can be called without speciying a sampling rate to
        just access the detector_list, however, detection won't
        be possible.
        """

        ## Sampling rate
        self.fs = sampling_frequency

        ## This is set to a positive value for benchmarking
        self.engzee_fake_delay = 0

        ## 2D Array of the different detectors: [[description,detector]]
        self.detector_list = [
            ["Kalidas & Tamil (Wavelet transform)",self.swt_detector],
            ["Engzee",self.engzee_detector],
            ["WQRS",self.wqrs_detector]
        ]

    def get_detector_list(self):
        """
        Returns a 2D array of the different detectors in the form:
        [[description1,detector1],[description2,detector2], ...]
        where description is a string and detector a function pointer
        to the detector. Use this for benchmarking to loop through
        detectors.
        """
        return self.detector_list

    
    def engzee_detector(self, unfiltered_ecg):
        """
        C. Zeelenberg, A single scan algorithm for QRS detection and
        feature extraction, IEEE Comp. in Cardiology, vol. 6,
        pp. 37-42, 1979 with modifications A. Lourenco, H. Silva,
        P. Leite, R. Lourenco and A. Fred, “Real Time
        Electrocardiogram Segmentation for Finger Based ECG
        Biometrics”, BIOSIGNALS 2012, pp. 49-54, 2012.
        """
                
        f1 = 48/self.fs
        f2 = 52/self.fs
        b, a = signal.butter(4, [f1*2, f2*2], btype='bandstop')
        filtered_ecg = signal.lfilter(b, a, unfiltered_ecg)

        diff = np.zeros(len(filtered_ecg))
        for i in range(4, len(diff)):
            diff[i] = filtered_ecg[i]-filtered_ecg[i-4]

        ci = [1,4,6,4,1]        
        low_pass = signal.lfilter(ci, 1, diff)

        low_pass[:int(0.2*self.fs)] = 0
      
        ms200 = int(0.2*self.fs)
        ms1200 = int(1.2*self.fs)        
        ms160 = int(0.16*self.fs)
        neg_threshold = int(0.01*self.fs)

        M = 0
        M_list = []
        neg_m = []
        MM = []
        M_slope = np.linspace(1.0, 0.6, ms1200-ms200)

        QRS = []
        r_peaks = []

        counter = 0

        thi_list = []
        thi = False
        thf_list = []
        thf = False
        newM5 = False

        for i in range(len(low_pass)):

            # M
            if i < 5*self.fs:
                M = 0.6*np.max(low_pass[:i+1])
                MM.append(M)
                if len(MM)>5:
                    MM.pop(0)

            elif QRS and i < QRS[-1]+ms200:

                newM5 = 0.6*np.max(low_pass[QRS[-1]:i])

                if newM5>1.5*MM[-1]:
                    newM5 = 1.1*MM[-1]

            elif newM5 and QRS and i == QRS[-1]+ms200:
                MM.append(newM5)
                if len(MM)>5:
                    MM.pop(0)    
                M = np.mean(MM)    
            
            elif QRS and i > QRS[-1]+ms200 and i < QRS[-1]+ms1200:

                M = np.mean(MM)*M_slope[i-(QRS[-1]+ms200)]

            elif QRS and i > QRS[-1]+ms1200:
                M = 0.6*np.mean(MM)

            M_list.append(M)
            neg_m.append(-M)


            if not QRS and low_pass[i]>M:
                QRS.append(i)
                thi_list.append(i)
                thi = True
            
            elif QRS and i > QRS[-1]+ms200 and low_pass[i]>M:
                QRS.append(i)
                thi_list.append(i)
                thi = True

            if thi and i<thi_list[-1]+ms160:
                if low_pass[i]<-M and low_pass[i-1]>-M:
                    #thf_list.append(i)
                    thf = True
                    
                if thf and low_pass[i]<-M:
                    thf_list.append(i)
                    counter += 1
                
                elif low_pass[i]>-M and thf:
                    counter = 0
                    thi = False
                    thf = False
            
            elif thi and i>thi_list[-1]+ms160:
                    counter = 0
                    thi = False
                    thf = False                                        
            
            if counter>neg_threshold:
                unfiltered_section = unfiltered_ecg[thi_list[-1]-int(0.01*self.fs):i]
                r_peaks.append(self.engzee_fake_delay+
                               np.argmax(unfiltered_section)+thi_list[-1]-int(0.01*self.fs))
                counter = 0
                thi = False
                thf = False

        # removing the 1st detection as it 1st needs the QRS complex amplitude for the threshold
        r_peaks.pop(0)
        return r_peaks

    
    
    
    def swt_detector(self, unfiltered_ecg, MWA_name='cumulative'):
        """
        Stationary Wavelet Transform 
        based on Vignesh Kalidas and Lakshman Tamil. 
        Real-time QRS detector using Stationary Wavelet Transform 
        for Automated ECG Analysis. 
        In: 2017 IEEE 17th International Conference on 
        Bioinformatics and Bioengineering (BIBE). 
        Uses the Pan and Tompkins thresolding.
        """
        
        maxQRSduration = 0.150 #sec
        swt_level=3
        padding = -1
        for i in range(1000):
            if (len(unfiltered_ecg)+i)%2**swt_level == 0:
                padding = i
                break

        if padding > 0:
            unfiltered_ecg = np.pad(unfiltered_ecg, (0, padding), 'edge')
        elif padding == -1:
            print("Padding greater than 1000 required\n")    

        swt_ecg = pywt.swt(unfiltered_ecg, 'db3', level=swt_level)
        swt_ecg = np.array(swt_ecg)
        swt_ecg = swt_ecg[0, 1, :]

        squared = swt_ecg*swt_ecg

        N = int(maxQRSduration*self.fs)
        mwa = MWA_from_name(MWA_name)(squared, N)
        mwa[:int(maxQRSduration*self.fs*2)] = 0

        filt_peaks = panPeakDetect(mwa, self.fs)
        
        return filt_peaks


    def wqrs_detector(self, unfiltered_ecg):
        """
        based on W Zong, GB Moody, D Jiang 
        A Robust Open-source Algorithm to Detect Onset and Duration of QRS
        Complexes 
        In: 2003 IEEE
        """
        def butter_lowpass_filter(data, cutoff):
            nyq = 0.5 * self.fs
            order = 2

            normal_cutoff = cutoff / nyq
            
            b, a = signal.butter(order, normal_cutoff, btype='low', analog=False)
            y = signal.lfilter(b, a, data)
            return y

        def length_transfrom(x, w):
            tmp = []
            for i in range(w, len(x)):
                chunk = x[i-w:i]
                ll = np.sum(
                    np.sqrt( np.power(1/self.fs,2)*np.ones(w-1) + np.power(np.diff(chunk),2) )
                )
                tmp.append(ll)
            l = [tmp[0]]*w
            
            return l+tmp
        
        def threshold(x):
            peaks = []
            u = MWA_convolve(x, 10*self.fs)
            for i in range(len(x)):
                if (len(peaks) == 0 or i > peaks[-1]+(self.fs*0.35)) and x[i] > u[i]:
                    peaks.append(i)
            return peaks
        
        y = butter_lowpass_filter(unfiltered_ecg, 15)
        y = length_transfrom(y, int(np.ceil(self.fs*0.13)))
        return threshold(y)

def MWA_from_name(function_name):
    if function_name == "cumulative":
        return MWA_cumulative
    elif function_name == "convolve":
        return MWA_convolve
    elif function_name == "original":
        return MWA_original
    else: 
        raise RuntimeError('invalid moving average function!')

#Fast implementation of moving window average with numpy's cumsum function 
def MWA_cumulative(input_array, window_size):
    
    ret = np.cumsum(input_array, dtype=float)
    ret[window_size:] = ret[window_size:] - ret[:-window_size]
    
    for i in range(1,window_size):
        ret[i-1] = ret[i-1] / i
    ret[window_size - 1:]  = ret[window_size - 1:] / window_size
    
    return ret

#Original Function 
def MWA_original(input_array, window_size):

    mwa = np.zeros(len(input_array))
    mwa[0] = input_array[0]
    
    for i in range(2,len(input_array)+1):
        if i < window_size:
            section = input_array[0:i]
        else:
            section = input_array[i-window_size:i]        
        
        mwa[i-1] = np.mean(section)

    return mwa

#Fast moving window average implemented with 1D convolution 
def MWA_convolve(input_array, window_size):
    
    ret = np.pad(input_array, (window_size-1,0), 'constant', constant_values=(0,0))
    ret = np.convolve(ret,np.ones(window_size),'valid')
    
    for i in range(1,window_size):
        ret[i-1] = ret[i-1] / i
    ret[window_size-1:] = ret[window_size-1:] / window_size
    
    return ret


def normalise(input_array):

    output_array = (input_array-np.min(input_array))/(np.max(input_array)-np.min(input_array))

    return output_array


def panPeakDetect(detection, fs):    

    min_distance = int(0.25*fs)

    signal_peaks = [0]
    noise_peaks = []

    SPKI = 0.0
    NPKI = 0.0

    threshold_I1 = 0.0
    threshold_I2 = 0.0

    RR_missed = 0
    index = 0
    indexes = []

    missed_peaks = []
    peaks = []

    for i in range(1,len(detection)-1):
        if detection[i-1]<detection[i] and detection[i+1]<detection[i]:
            peak = i
            peaks.append(i)

            if detection[peak]>threshold_I1 and (peak-signal_peaks[-1])>0.3*fs:
                    
                signal_peaks.append(peak)
                indexes.append(index)
                SPKI = 0.125*detection[signal_peaks[-1]] + 0.875*SPKI
                if RR_missed!=0:
                    if signal_peaks[-1]-signal_peaks[-2]>RR_missed:
                        missed_section_peaks = peaks[indexes[-2]+1:indexes[-1]]
                        missed_section_peaks2 = []
                        for missed_peak in missed_section_peaks:
                            if missed_peak-signal_peaks[-2]>min_distance and signal_peaks[-1]-missed_peak>min_distance and detection[missed_peak]>threshold_I2:
                                missed_section_peaks2.append(missed_peak)

                        if len(missed_section_peaks2)>0:
                            signal_missed = [detection[i] for i in missed_section_peaks2]
                            index_max = np.argmax(signal_missed)
                            missed_peak = missed_section_peaks2[index_max]
                            missed_peaks.append(missed_peak)
                            signal_peaks.append(signal_peaks[-1])
                            signal_peaks[-2] = missed_peak   

            else:
                noise_peaks.append(peak)
                NPKI = 0.125*detection[noise_peaks[-1]] + 0.875*NPKI

            threshold_I1 = NPKI + 0.25*(SPKI-NPKI)
            threshold_I2 = 0.5*threshold_I1

            if len(signal_peaks)>8:
                RR = np.diff(signal_peaks[-9:])
                RR_ave = int(np.mean(RR))
                RR_missed = int(1.66*RR_ave)

            index = index+1      
    
    signal_peaks.pop(0)

    return signal_peaks


fs = 360
detectors = Detectors(fs)


#Uncomment the line you want to use and comment the others 

r_peaks = detectors.swt_detector(lead_I)
#r_peaks = detectors.engzee_detector(lead_I) 
#r_peaks = detectors.wqrs_detector(lead_I) 
#r_peaks = process_ecg(lead_I)

print(f'{len(r_peaks)} Peaks')
print(psutil.cpu_times())
print(f'CPU Usage: {psutil.cpu_percent(interval= None)}%')

