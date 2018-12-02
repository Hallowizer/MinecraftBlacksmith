//
//  patcher.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef patcher_hpp
#define patcher_hpp

#include <string>

#include <apiCoreMods.hpp>

using namespace std;

void init(char *);
void patchTransform(ModBytecode&);

#endif /* patcher_hpp */
