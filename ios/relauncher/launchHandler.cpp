//
//  launchHandler.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/11/18.
//
//

#include "../../common/relauncher/relauncher.hpp"
#include "stackDigger.hpp"

void entry(void) {
    void *stackStart = digToMain(2);
    
    void **retAddr = (void **) (stackStart-sizeof(void *));
    char ***p_argv = (char ***) (retAddr-sizeof(char **));
    int *p_argc = (int *) (p_argv-sizeof(int));
    
    int argc = *p_argc;
    char **argv = *p_argv;
    relaunch(argc, argv);
}