import os
import csv
import numpy as np
import matplotlib.pyplot as plt

MIN_REPETITION = 50;

CUBE_SIZE    = 20;
OBSTRUCTIONS = 30;
ROUTES       = 240_000;
THREADS      = 8;
FILE         = "./results/results.csv"

#Combine the arguments
#executable = "./bin/cube" + "-c " + CUBE_SIZE + "-o " + OBSTRUCTIONS + "-r " + ROUTES + "-t " + THREADS + "-f " + FILE;
#print(executable);

#Call the executable
#os.system(executable);

#Pre computed file
PRE_COMPUTED_FILE = "./results/results_compact_20_30_240000.csv"

#Define the data list
data = []

#Open the csvFile
with open(PRE_COMPUTED_FILE, 'r') as csvFile:
	readCSV = csv.reader(csvFile, delimiter=';');
	#Get the data
	print("CSV Data");
	for row in readCSV:
		data.append((int(row[0]), int(row[1]), float(row[2])));
		print(data[-1]);

#Cut the zeros and cost with less than the minimun repetition from back to front. Equal of data[-1:]
for i in range(len(data)-1, -1, -1):
        if data[i][0] == 0 or data[i][1] < MIN_REPETITION:
                data.pop(i);

#Print the filtered data and get cost and time.
print("\n\nFiltered Data");
cost = []; avg_time = [];
for r in data:
        print(r);
        #Get cost and time from data
        cost.append(r[0]); avg_time.append(r[2]*1000);

#Plot
plt.plot(cost, avg_time, cost, avg_time,'r.')
plt.xlabel('Distance (manhattan)')
plt.ylabel('Average Time (ms)')
plt.title('Average time VS Distance\n' + "Cube=" + str(CUBE_SIZE) + " | Obst=" + str(OBSTRUCTIONS) + "% | Routes=" + str(ROUTES));
plt.grid(True);
plt.show();

                

