/*
 * labelProcessor.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: hallowizer
 */

#include "labelProcessor.hpp"

string processLabels(string input) {
	char *text = (char *) malloc(input.size()*sizeof(char));
	strcpy(text, input.c_str());
	
	char *token;
	char *token2;
	
	bool first = true;
	
	string result = "";
	
	while ((token = strtok(first ? text : NULL, " \n")) != NULL) {
		first = false;
		
		size_t len = strlen(token);
		if (token[len-1] != ':') { // Let all instructions through.
			result += token;
			result += ' ';
			continue;
		}
		
		result += '\n'; // At the end of an instruction, or beginning of file.
		
		if (token[0] == '.') { // Let all section labels through.
			result += token;
			result += '\n';
			continue;
		}
		
		token2 = strtok(NULL, " \n");
		if (strcmp(token2, "pushq") == 0) { // Let all function labels through.
			result += "_func_"; // First underscore indicates that this is a function. Second underscore connects the word func to the hex value.
			result += token;
			result += '\n';
			result += token2;
			continue;
		}
	}
	
	free(text);
	return result;
}
