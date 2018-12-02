/*
 * main.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: hallowizer
 */

#include <stdio.h>

#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include "binaryRemover.hpp"
#include "labelProcessor.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " <source> <destination>\n";
		return 1;
	}
	
	try {
		cout << "Opening files.\n";
		ifstream src(argv[1]);
		ofstream target(argv[2]);
		
		cout << "Reading source file.\n";
		string contents = readNoBinary(src);
		
		cout << "Processing labels.\n";
		contents = processLabels(contents);
		
		cout << "Writing target file.\n";
		target << contents;
		
		cout << "Processed assembly file.\n";
		return 0;
	} catch (const exception& e) {
		cerr << "Something went horribly wrong.\n";
		cerr << e.what() << "\n";
		return 1;
	}
}
