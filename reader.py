import wfdb
import csv
import matplotlib.pyplot as plt 
import io 
from PIL import Image 


patient_record1 = wfdb.rdrecord('234')

# Extract patient info, lead names, and ECG data

patient_number = patient_record1.record_name
leads = patient_record1.sig_name
ecg_data = patient_record1.p_signal

# Create CSV
filename = f"{patient_number}.csv"
outfile = open(filename, "w")
out_csv = csv.writer(outfile)

# Write CSV header with lead names
out_csv.writerow(leads)

# Write ECG data to CSV
for row in ecg_data:
    out_csv.writerow(row)

#visualisation
wfdb.plot_wfdb(record=patient_record1) # plots the ECG

