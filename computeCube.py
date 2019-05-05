import os
import csv
import numpy as np
import matplotlib.pyplot as plt

CUBE_SIZE    = 20;
OBSTRUCTIONS = 30;
ROUTES		 = 100_000;
THREADS		 = 8;
FILE		 = "./bin/results.csv"

#Combine the arguments
#executable = "./bin/cube" + "-c " + CUBE_SIZE + "-o " + OBSTRUCTIONS + "-r " + ROUTES + "-t " + THREADS + "-f " + FILE;
#print(executable);

#Call the executable
#os.system(executable);

#Pre computed file
PRE_COMPUTED_FILE = "./bin/results_20_30_240000.csv"

#Define the data list
data = []

#Open the csvFile
with open(PRE_COMPUTED_FILE, 'r') as csvFile:
	readCSV = csv.reader(csvFile, delimiter=';');
	c = 0;
	for row in readCSV:
		data.append((int(row[0]), float(row[1])));
		c = c+1; print(c);
