/*
 * main.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: hallowizer
 */

#include <stdio.h>

#include <iostream>
#include <string>

#include "binaryRemover.hpp"
#include "labelProcessor.hpp"
#include "writeFormatter.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc < 2) {
		cerr << "Usage: processasm <source> <destination>\n";
		return 1;
	}
	
	FILE *src = fopen(argv[0], "r");
	FILE *target = fopen(argv[1], "w");
	
	string contents = readNoBinary(src);
	contents = processLabels(contents);
	contents = format(contents);
	
	fprintf(target, contents.c_str());
	
	fclose(src);
	fclose(target);
	
	cout << "Processed assembly file.";
	return 0;
}
