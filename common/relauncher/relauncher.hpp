//
//  relauncher.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef relauncher_hpp
#define relauncher_hpp

// Typedefs
typedef int (*mainFunc)(int, char **);

// API functions
void relaunch(int, char **);

// Platform dependent functions
char *findGameDir(int, char **);
char *findMinecraft(void);
char *mainName(void);

// Processor dependent functions
mainFunc findMainFunc(char *name, char *minecraftBytes);

#endif /* relauncher_hpp */
