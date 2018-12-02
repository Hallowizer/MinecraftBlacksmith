/*
 * writeFormatter.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: hallowizer
 */

#include "writeFormatter.hpp"

string format(string input) {
	string output = "";
	
	int i = 1; // Skip first newline character.
	for (; i < input.size(); i++) {
		if (input[i] == '%')
			output += '%';
		
		output += input[i];
	}
	
	return output;
}
