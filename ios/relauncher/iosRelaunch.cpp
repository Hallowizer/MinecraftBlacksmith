//
//  iosRelaunch.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/11/18.
//
//

#include <common/relauncher/relauncher.hpp>
#include "stackDigger.hpp"

// TBD
#define MAIN_OFFSET

char *findMinecraft(void) {
    void *stackStart = digToMain(3); // 4 stack frames in, but skip the last Minecraft frame.
    void **p_retAddr = (void **) (stackStart-sizeof(void *));
    
    void *retAddr = *p_retAddr;
    return (char *) (retAddr-MAIN_OFFSET);
}

string mainName(void) {
    return "bmlReentry";
}
