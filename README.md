# AI_Cube_A_star
Relation between Time and Distance for a A* in a Cube implemented in C++.

## Getting Started

Clone the repository, compile and run it.

### Clone

```
git clone https://github.com/EduardoCulau/AI_Cube_A_star.git
```

### Compile

Enter the project directory and run the make command below.
The parameter PRINT define if the program must to print (verbose) the execution or not.

```
make -j -C src/ PRINT=0

or

make -j -C src/ PRINT=1
```

### Run

The executable has 4 parameters as following in the below table:

  Parameter   |         Meaning
------------- | --------------------------
-c            | Size of the cube NxNxN
-o            | Percentage of obstructions
-r            | Routes to be commputed
-t            | Number of threads
-f            | Exit file with results
-h            | Help

One example is:

```
./bin/cube -c 5 -o 50 -r 1000 -t 4 -f results.csv
```

For a fast test, is possible to run with the make command as follow below but only with -c 3 -o 3 -r 1 -t 1 -f ../bin/results.csv.

```
make runTest -C src/
```

### Extract Results

After run the code you can generate a grath with the results (Avg Time vs Distance).
Todo that you need to edit the [computeCube.py)](../blob/master/computeCube.py).

You need to change the following parameter, matching with you use in the execution:

*CUBE_SIZE 
*OBSTRUCTIONS 
*ROUTES  
*THREADS 
*PRE_COMPUTED_FILE

And you can change the thresold that make the average:

*MIN_REPETITION

After that, you can run the python script and get the grath.
An example is:

![alt text](https://github.com/EduardoCulau/AI_Cube_A_star/blob/master/results/grath_20_30_240000.png)
