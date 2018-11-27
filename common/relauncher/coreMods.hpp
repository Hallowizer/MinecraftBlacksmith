//
//  coreMods.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef coreMods_hpp
#define coreMods_hpp

#include <string>

// API functions
void setupCoreMods(char *);
char *transformMod(char *, char *, int *);

//  Processor dependent functions
void *loadSym(FILE *, std::string);

#endif /* coreMods_hpp */
