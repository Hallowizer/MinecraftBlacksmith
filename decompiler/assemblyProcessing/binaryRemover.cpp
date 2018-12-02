/*
 * binaryRemover.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: hallowizer
 */

#include <limits>
#include <iostream>

#include "binaryRemover.hpp"

#define LAST_LABEL 0x1426371aa

string readNoBinary(istream& in) {
	string word;
	char character;
	
	long label;
	size_t end;
	
	string contents = "";
	
	// Skip 3 lines.
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	in.ignore(numeric_limits<streamsize>::max(), '\n');
	
	while (label != LAST_LABEL) {
		in >> word;
		
		if (word == "Disassembly") { // Section header
			in.ignore(numeric_limits<streamsize>::max(), '\n');
			in >> word;
			
			// And copy it over.
			contents += word;
			contents += "\n";
			
			continue;
		}
		
		try {
			label = stol(word, NULL, 16); // Skips the colon
		} catch (const exception&) {
			contents += word;
			contents += "\n";
			continue;
		}
		
		try {
			for (;;) { // Skip binary numbers.
				in >> word;
				stoi(word, &end, 16);
			}
		} catch (const exception&) {
			// NOOP
		}
		
		contents += to_string(label);
		contents += ":\n";
		
		contents += word;
		contents += " ";
		
		string text;
		getline(in, text);
		contents += text;
		contents += "\n";
	}
	
	return contents;
}
