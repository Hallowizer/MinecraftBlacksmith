//
//  patcher.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include "patcher.hpp"
#include "patchApplier.hpp"

using namespace std;

static void applyPatch(vector<char>&);
static void differentBinary(void);

struct patchHeader {
    int srcLength;
    int checksum;
    int patchLength;
};

static char *binpatchFile;
static bool ignoreDiscrepancies;

void init(char *gameDir, bool ignorePatchDiscrepancies) {
    ignoreDiscrepancies = ignorePatchDiscrepancies;
}

void patchTransform(ModBytecode& bytecode) {
    if (bytecode.modid != "minecraft")
        return;
    
    applyPatch(bytecode.bytes);
}

static void applyPatch(vector<char>& bytes) {
    FILE *file = fopen(binpatchFile, "r");
    
    struct patchHeader *header = malloc(sizeof(struct patchHeader));
    fread(header, sizeof(struct patchHeader), 1, file);
    
    if (bytes.size() != header->srcLength)
    	differentBinary();
    
    int a = 1;
    int b = 0;
    int i;
    
    for (i = 0; i < header->srcLength; i++) { // Adler 32 hash
        a += bytes[i];
        b += a;
    }
    
    if (header->checksum != b)
    	differentBinary();
    
    patch(bytes, file);
    fclose(file);
}

static void differentBinary(void) {
	cerr << "There is a binary discrepancy between the expected and actual Minecraft binary. Did you modify Minecraft?\n";
	
	if (ignoreDiscrepancies)
		cerr << "BML will ignore this error. This may result in an invalid patched binary.";
	else {
		cerr << "The game will exit, because this is a severe error. Please get a clean binary.";
		exit(1);
	}
}
