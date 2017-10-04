//
//  main.cpp
//  Near Neighbours
//
//  Created by Hadi on 4/1/13.
//  Copyright (c) 2013 Hadi. All rights reserved.
//

#include "Problem.h"
#include "Solver.h"

string inputFileName = "";
string outputFileName = "";
double radius = -1;

void printUsage(){
    cerr << "Usage:\n\n"
    << "  Near Neighbours [-r rad] [-i input] [-o output]\n\n"
    << "  where:\n"
    << "    r        minimum distance between two points (a positive value)\n"
    << "    input    input file name\n"
    << "    output   output file name\n"
    << endl;
}
void getArguments(int argc, const char **argv)
{
	
	if (argc != 2 * 3 + 1) {
		printUsage();
		exit(-1);
	}
	int i = 1;
	while (i < argc) {
		if (!strcmp(argv[i], "-r")) {
			radius = atof(argv[++i]);
		} else if (!strcmp(argv[i], "-i")) {
			inputFileName = argv[++i];
		} else if (!strcmp(argv[i], "-o")) {
			outputFileName = argv[++i];
		}else {
			printUsage();
            exit(-1);
		}
		i++;
	}
    if (radius <= 0 || inputFileName == "" || outputFileName == "") {
        printUsage();
		exit(-1);
    }
}


int main(int argc,const char** argv)
{
    getArguments(argc, argv);
    new Solver(new Problem(inputFileName), radius, outputFileName);
    return 0;
}

