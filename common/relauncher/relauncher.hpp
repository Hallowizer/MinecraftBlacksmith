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

#include <common/bml/entry.hpp>

using namespace std;

// Typedefs
typedef int (*MainFunc)(int, char **, EnterFunc);

// API functions
void relaunch(int, char **);
string getRelauncherGameDir();

// Platform dependent functions
string *findGameDir(int, char **);
string findMinecraft(int *);
string mainName(void);

// Processor dependent functions
MainFunc findMainFunc(string, char *, int);

#endif /* relauncher_hpp */
