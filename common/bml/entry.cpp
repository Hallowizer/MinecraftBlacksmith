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
	FILE *fp = fopen((getRelauncherGameDir() + "blacksmith/bml").c_str(), "r");
	
	int len;
	fscanf(fp, "%d", &len);
	
	char *bytes = malloc(len);
	fread(bytes, 1, len, fp);
	
	fclose(fp);
	
	char *transformedBytes = transformMod("bml", bytes, &len);
	
	fp = fopen((getRelauncherGameDir() + "blacksmith/temp/bml").c_str(), "r+");
	fwrite(transformedBytes, 1, len, fp);
	HandlerInitFunc init = loadSym(fp, "initFunctionTable");
	
	fclose(fp);
	remove((getRelauncherGameDir() + "blacksmith/temp/bml").c_str());
	
	BmlCommonHandler handler = (BmlCommonHandler) malloc(sizeof(struct BmlFunctionTable));
	init(handler);
	
	fclose(fp);
	return handler;
}
