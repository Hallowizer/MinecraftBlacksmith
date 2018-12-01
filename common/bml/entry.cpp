/*
 * entry.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: hallowizer
 */

#include <stdlib.h>
#include <stdio.h>

#include "entry.hpp"
#include "commonHandlerTable.hpp"
#include <common/relauncher/relauncher.hpp>
#include <common/relauncher/coreMods.hpp>

typedef void (*HandlerInitFunc)(BmlCommonHandler);

BmlCommonHandler enter(void) {
	FILE *file = fopen((getRelauncherGameDir() + "blacksmith/bml").c_str(), "r");
	HandlerInitFunc init = loadSym(file, "initFunctionTable");
	
	BmlCommonHandler handler = (BmlCommonHandler) malloc(sizeof(struct BmlFunctionTable));
	init(handler);
	
	fclose(file);
	return handler;
}
