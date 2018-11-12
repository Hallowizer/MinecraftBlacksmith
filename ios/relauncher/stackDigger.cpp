//
//  stackDigger.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/11/18.
//
//

#include "stackJumper.hpp"
#include "rbpLocator.hpp"

// TBD
#define MINECRAFT_FRAME_COUNT

void *digToMain(int extraFrames) {
    void *addr = getRbp();
    int frameCount = MINECRAFT_FRAME_COUNT+extraFrames;
    
    int i;
    for (i = 0; i < frameCount; i++)
        addr = *((void **) addr);
    
    return addr;
}
