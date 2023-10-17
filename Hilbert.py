import os
import wfdb #pip install wfdb
import numpy as np
import matplotlib.pyplot as plt

from scipy.signal import butter, lfilter, freqz, hilbert
import peakutils #pip install peakutils
import pandas as pd

# Loading the dataset
record = wfdb.rdsamp('mitdb/100', sampto=8050)
annotation = wfdb.rdann('mitdb/100', 'atr', sampto=8050)

lead_I = record[0][:, 0]
fs = record[1]['fs']

def process_ecg(data, threshold=0.15):
    transformed = np.abs(hilbert(np.gradient(data)))
    return peakutils.indexes(transformed, thres=0.1,  min_dist=100)

def calculate_metrics(pred, test):
    # Counting the number of hits and misses. 
    # This needs to be developed more rigorous development
    fp, fn = 0, 0
    for p in pred:
        if np.sum(np.abs(p-test)<150)==0:
            fp += 1
    
    for t in test:
        if np.sum(np.abs(t-pred)<150)==0:
            fn += 1
    return fp, fn

'''
def set_threshols_for_subset(subset):
    h = np.abs(hilbert(np.gradient(subset)))
    h = h/np.max(h)
    max_amp = np.max(h)
    rms = np.sqrt(np.mean(np.square(h)))
    if rms>=0.18*max_amp:
        threshold = 0.39*max_amp
    else:
        threshold = 1.6*rms
    
    return threshold, process_ecg(h, threshold=threshold)

subset = lead_I[:1025]
threshold, indxes = set_threshols_for_subset(subset)

h = np.abs(hilbert(np.gradient(subset)))
h = h/np.max(h)

fig, ax = plt.subplots(nrows=2)
ax[0].plot(h)
ax[0].plot([0, 1025], [threshold, threshold], '--r')
ax[1].plot(np.arange(0, 1025), subset)

for pos, sym in zip(annotation.sample, annotation.symbol):
    if pos>len(h):
        break
    else:
        ax[1].plot(pos, lead_I[pos], 'go', markersize=4, markerfacecolor='white')
        ax[1].text(pos+10, lead_I[pos], sym, color='orange')
        
ax[1].plot(indxes, subset[indxes], 'or')
plt.show()
'''


#Testing the algorithm
recnums = ['100', '101', '102', '103', '104', '105', '106', '107',
           '109', '111', '112', '113', '114', '115', '116', '117', '118',
           '119', '121', '122', '123', '124']
data = np.zeros( (len(recnums), 6) )
for idx, recno in enumerate(recnums):
    entire_sample = wfdb.rdsamp('mitdb/'+str(recno)) 
    entire_sample_anon = wfdb.rdann('mitdb/'+str(recno), 'atr')
    
    total_beats = np.sum([(sym!='+')&(sym!='~')&(sym!='"') for sym in entire_sample_anon.symbol])
    test = entire_sample_anon.sample
    
    dat = entire_sample[0][:, 0]
    pred = process_ecg(dat, threshold=0.01)
    
    fp, fn = calculate_metrics(pred, test)
    
    # Adding the results to the data matrix
    data[idx, :] = np.array([recno, total_beats, fp, fn, fp+fn, 100*(fp+fn)/total_beats])

results = pd.DataFrame(
    data=data,
    columns=['tape', 'total_beats', 'FP', 'FN', 'failed_detection_beats', 'failed_detection_percent'])

print('Overall detection error percent: {0:.2f}%'.format(results.failed_detection_beats.sum()/results.total_beats.sum()*100))