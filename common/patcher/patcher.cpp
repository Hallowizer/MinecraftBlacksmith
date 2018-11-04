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

using namespace std;

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

char *patchTransform(char *name, char *bytes) {
    if (strcmp(name, "Minecraft") != 0)
        return bytes;
    
    return applyPatch(bytes);
}

static char *applyPatch(char *bytes) {
    FILE *file = fopen(binpatchFile);
    struct patchHeader *header = malloc(sizeof(struct patchHeader));
    fread(header, sizeof(struct patchHeader), 1, file);
    
    int a = 1;
    int b = 0;
    int i;
    
    for (i = 0; i < header->srcLength; i++) {
        a += bytes[i];
        b += a;
    }
    
    if (header->checksum != b) {
        cerr << "There is a binary discrepancy between the expected and actual Minecraft binary. Did you modify Minecraft?";
        
        if (ignoreDiscrepancies)
            cerr << "BML will ignore this error. This may result in an invalid patched binary.";
        else {
            cerr << "The game will exit, because this is a severe error. Please get a clean binary.";
            exit(1);
        }
    }
    
    return patch(bytes, file, patchHeader->patchLength);
}
