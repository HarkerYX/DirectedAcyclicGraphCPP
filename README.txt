This project was developed in CLion (2020.2.5) using C++17.


You can run this directly in CLion or compile on blue with the following:

1. Unzip the project

2. Take the folder that you unzipped and transfer it to blue

3. cd into the folder on blue

4. Compile with the following command: g++ -std=c++17 *.cpp

5. Run the program with the following command: ./a.out

6. User will be prompted to enter the name of the file they wish to read from, extension not included
    -Example: Say I have the file "data2.txt" in the data folder, I'd enter 'data2' as my input to read from that file.
    -Note: The file that you choose MUST be in the 'data' directory!

7. Relevant output is sent to both std::out and to an output file named to reflect the input file (i.e. "data2.txt" would produce a "data2Output.txt" file)
