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

static char *applyPatch(char *, int *);
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

char *patchTransform(string name, char *bytes, int *len) {
    if (name != "Minecraft")
        return bytes;
    
    return applyPatch(bytes, len);
}

static char *applyPatch(char *bytes, int *len) {
    FILE *file = fopen(binpatchFile, "r");
    struct patchHeader *header = malloc(sizeof(struct patchHeader));
    fread(header, sizeof(struct patchHeader), 1, file);
    
    if ((*len) != header->srcLength)
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
    
    return patch(bytes, file, header->patchLength);
}

static void differentBinary(void) {
	cerr << "There is a binary discrepancy between the expected and actual Minecraft binary. Did you modify Minecraft?";

	if (ignoreDiscrepancies)
		cerr << "BML will ignore this error. This may result in an invalid patched binary.";
	else {
		cerr << "The game will exit, because this is a severe error. Please get a clean binary.";
		exit(1);
	}
}
