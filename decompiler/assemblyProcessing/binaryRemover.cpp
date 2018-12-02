/*
 * binaryRemover.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: hallowizer
 */

#include "binaryRemover.hpp"

#define LAST_LABEL 0x1426371aa

string readNoBinary(FILE *fp) {
	char *word;
	char character;
	
	int label;
	char *end;
	
	string contents = "";
	
	fscanf(fp, " Minecraft.Windows.exe file format COFF-x86-64 "); // Skip header.
	
	while (label != LAST_LABEL) {
		fscanf(fp, "%s ", &word);
		
		if (strcmp(word, "Disassembly") == 0) { // Section header
			fscanf(fp, "of section %s ", &word, &word); // Skip human text
			fscanf(fp, "%s ", &word); // Take section label.
			
			// And copy it over.
			contents += word;
			contents += "\n";
			
			continue;
		}
		
		label = strtol(word, NULL, 16); // Skips the colon
		
		do { // Skip binary numbers.
			fscanf(fp, "%s ", &word);
			strtol(word, &end, 16);
		} while (end[0] == '\0');
		
		contents += to_string(label);
		contents += ":\n";
		
		do {
			fscanf(fp, "%s%c", &word, &character);
			
			contents += word;
			contents += character;
		} while (character != '\n');
	}
	
	return contents;
}
