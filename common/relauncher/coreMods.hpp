//
//  coreMods.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef coreMods_hpp
#define coreMods_hpp

// API functions
void setupCoreMods(char *);
char *transformMod(char *, char *);

//  Processor dependent functions
void *loadSym(FILE *, string);

#endif /* coreMods_hpp */
