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

#Open the csvFile
with open(FILE, 'r') as csvFile:
	readCSV = csv.reader(csvFile, delimiter=';');
	for row in readCSV:
		print(row);
