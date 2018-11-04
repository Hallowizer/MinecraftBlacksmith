//
//  relauncher.cpp
//  
//
//  Created by Hallowizer on 11/2/18.
//
//

#include <stdlib.h>

#include "relauncher.hpp"
#include "coreMods.hpp"

static mainFunc findMain(char *);

void relaunch(int argc, char **argv) {
    char *gameDir = findGameDir(argc, argv);
    setupCoreMods(gameDir);
    
    char *minecraftBytes = findMinecraft();
    char *transformedBytes = transformMod("Minecraft", minecraftBytes);
    
    mainFunc minecraftMain = findMain(transformedBytes);
    int exitCode = minecraftMain(argc, argv);
    
    exit(exitCode);
}

static mainFunc findMain(char *minecraftBytes) {
    char *name = mainName();
    return findMainFunc(name, minecraftBytes);
}
