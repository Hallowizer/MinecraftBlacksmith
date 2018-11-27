//
//  relauncher.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef relauncher_hpp
#define relauncher_hpp

#include <string>

using namespace std;

// Typedefs
typedef int (*mainFunc)(int, char **);

// API functions
void relaunch(int, char **);

// Platform dependent functions
char *findGameDir(int, char **);
char *findMinecraft(int *);
string mainName(void);

// Processor dependent functions
mainFunc findMainFunc(string, char *, int);

#endif /* relauncher_hpp */
