//
//  stackDigger.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/11/18.
//
//

#include "stackDigger.hpp"
#include "rbpLocator.hpp"

// TBD
#define MEMORY_SIZE

static void *stackStart;

void initStackDigger(void) {
	char dummy;
	char *addr = &dummy;
	
	addr += MEMORY_SIZE;
	stackStart = addr;
}

void *getStackStart(void) {
    return stackStart;
}
