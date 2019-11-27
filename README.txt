Readme File for Monitoring Cetacean Mammals Program ( version 1.0 )
created by alm82, 13.12.2017

CONTENTS OF THIS FILE
---------------------
   
 * Introduction
 * List of included files
 * Requirements
 * Usage instructions

INTRODUCTION
------------

 Monitoring Cetacean Mammals Program is actually a set of two programs designed to assist marine biologists
 monitoring Bottlenose Dolphins and Harbour Porpoise in Cardigan Bay.

LIST OF INCLUDED FILES
----------------------
 
 * this README file
 * DesignDescription.pdf - a document with description, explanation and justification of both programs design
 * Screencast.mp4 - video showing both programs being built and running with explanation
 * Part1 - a folder containing source code and makefile for first program as well as some example data to use ( created by Neal Snooke and Dave Price )
   - main.c 
   - CmakeLists.txt
   - cmake-build-debug
 * Part2 - a folder  containing source code and makefile for second program
   - main.cpp
   - Location.cpp
   - Location.h
   - MammalData.cpp
   - MammalData.h
   - CMakeLists.txt
   - cmake-build-debug

REQUIREMENTS
------------

 First program requires following libraries: <stdio.h>, <stdlib.h>, <math.h>, <memory.h>, <stdbool.h>
 Second program requires following libraries: <iostream>, <fstream>, <vector>, <cstdlib>, <cmath>

 Cmake minimum required version is 3.7 for both programs.

USAGE INSTRUCTIONS
------------------
 
 Program 1:

 When asked for names of files containing observers or sightings data use one of provided example files or to use
 different files either move them to the program working directory ( cmake-build-debug ) or specify the path for 
 own files.
 Do not provide the path when asked for target saving file name - this may affect the results of second program.
 Program will save calculated mammal data and print relative path of the file for confirmation.

 Program 2:
 
 Do not provide the path when asked for file with mammals locations - for correct results use name of the file only.
 Results of this program will not be saved - they will be displayed and discarded after user exits.

 



