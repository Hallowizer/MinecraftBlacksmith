//
//  launchHandler.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/11/18.
//
//

#include "stackDigger.hpp"

void entry() {
    void *stackStart = digToMain(2);
    
    char ***p_argv = (char ***) (stackStart-sizeof(char **));
    int *p_argc = (int *) (p_argv-sizeof(int));
    
    int argc = *p_argc;
    char **argv = *p_argv;
    relaunch(argc, argv);
}
