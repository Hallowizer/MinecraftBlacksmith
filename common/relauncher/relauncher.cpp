//
//  relauncher.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#include <stdlib.h>

#include "relauncher.hpp"
#include "coreMods.hpp"

static MainFunc findMain(char *, int);

static string gameDir;

void relaunch(int argc, char **argv) {
    gameDir = findGameDir(argc, argv);
    setupCoreMods(gameDir);
    
    int length = 0;
    char *minecraftBytes = findMinecraft(&length);

    int transformedLength = length;
    char *transformedBytes = transformMod("Minecraft", minecraftBytes, &transformedLength);
    
    MainFunc minecraftMain = findMain(transformedBytes, transformedLength);
    int exitCode = minecraftMain(argc, argv, enter);
    
    exit(exitCode);
}

static MainFunc findMain(char *minecraftBytes, int length) {
    char *name = mainName();
    return findMainFunc(name, minecraftBytes, length);
}

string getRelauncherGameDir() {
	return gameDir;
}
