//
//  coreMods.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <list>
#include <string>

using namespace std;

#include "../../api/apiCoreMods.hpp"
#include "coreMods.hpp"
#include "../patcher/patcher.hpp"

#define COREMOD_TYPE 1

typedef coreMod (*cmInitFunc)(void);

static void discoverCoreMods(string);
static void processFile(string, string, string);
static void loadCoreMod(cmInitFunc);

static list<modTransformer> transformers;

void setupCoreMods(char *gameDir) {
    registerTransformer(patchTransform);
    
    discoverCoreMods(gameDir);
}

static void discoverCoreMods(string gameDir) {
    string modDir = gameDir + "mods/";
    
    DIR *dir = opendir(modDir);
    struct dirent *member;
    struct stat *sb = (struct stat *) malloc(sizeof(struct stat));
    
    if (dir) {
        while ((member = readdir(dir)) != NULL)
            if (stat(modDir + member->d_name, sb) == 0 && S_ISREG(sb->st_mode))
                processFile(modDir + member->d_name, member->d_name);
    }
    
    closeDir(dir);
    
    free(sb);
}

static void processFile(string gameDir, string name, string singleName) {
    FILE *fp = fopen(name, "r");
    
    char type;
    fscanf(fp, "%c", &type);
    
    if (type != COREMOD_TYPE)
        return;
    
    string tmpModDir = gameDir + "blacksmith/tmp/mods/";
    
    int len;
    fscanf(fp, "%d", &len);
    
    char *bytes = malloc(len);
    fread(bytes, 1, len, fp);
    
    fclose(fp);
    
    fp = fopen(tmpModDir + singleName);
    fprintf(fp, bytes);
    free(bytes);
    
    cmInitFunc init = (cmInitFunc) loadSym(fp, "blacksmith_reserved_initCoreMod");
    loadCoreMod(init);
}

static void loadCoreMod(cmInitFunc init) {
    
}

static void registerTransformer(modTransformer transformer) {
    transformers.push_back(transformer);
}

char *transformMod(char *name, char *bytes) {
    for (list<modTransformer>::iterator iter = transformers.begin(); iter != transformers.end(); iter++)
        bytes = (*iter)(name, bytes);
    
    return bytes;
}
