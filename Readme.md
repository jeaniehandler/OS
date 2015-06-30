README
Jeanie Handler

CPU.h : Header file for CPU.cpp


CPU.cpp : Contains Instruction execution communicates with Memory by sending an instruction to be fetched then executing accordingly\


Memory.h: Header file for Memory.cpp

Memory.cpp: Initializes itself with the program file and sends the CPU instructions and operands

main.cpp: creates to pipes before forking two processes creating the CPU and Memory which communicate to each other by fetching and executing instructions until the program is complete\


sample1.txt: general set up of how to work the program

sample2.txt: deal with stack more 

sample3.txt: work with interrupt handling

sample4.txt: continued stack handling

sample5.txt: writes the name of the creator of the code


To Run: Have all files in the same directory and type

g++ Memory.cpp CPU.cpp main.cpp

This will compile an a.out executable

depending on system to run the executable type

./a.out sample1.txt 1000

or 

a.out sample2.txt 2000

whichever sample you wish to run replace the second parameter. 

