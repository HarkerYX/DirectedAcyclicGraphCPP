Project 2: Topological Sorting

Group Member: Guy (solo)
Extra Credit Implemented: Adjacency List Representation


This project was developed in CLion (2020.2.5) using C++17.

You can open and run this directly in CLion or compile and run by the following:

1. Unzip the project

2. Take the folder that you unzipped and transfer it to blue (or somewhere that you have a compiler on-hand)

3. cd into the main project folder on blue

4. Compile with the following command: g++ -std=c++17 *.cpp

5. Run the program with the following command, passing in the input file as an argument: ./a.out <nameOfInputFile>
    -Examples: ./a.out data3.txt
               ./a.out ./data/data3.txt

6. Relevant output is sent to both std::out and to an output file named to reflect the input file (i.e. "data2.txt" would produce a "outdata2.txt" file)

7. The program will ask the user if they'd like to output the adjacency list representation to a text file, if so it is sent to Graph.txt

NOTE: Each of the output files for the data that's been provided is in the outputFiles folder. Subsequent data files will be generated in whatever folder you have the input files in.