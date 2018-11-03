//
//  coreMods.cpp
//  
//
//  Created by Hallowizer on 11/2/18.
//
//

#include <list>

#include "../../api/apiCoreMods.hpp";
#include "coreMods.hpp"

using namespace std;

static list<modTransformer> transformers;

void setupCoreMods(void) {
    
}

static void registerTransformer(modTransformer transformer) {
    transformers.push_back(transformer);
}

char *transformMod(char *name, char *bytes) {
    for (list<modTransformer>::iterator iter = transformers.begin(); iter != transformers.end(); iter++)
        bytes = (*iter)(name, bytes);
    
    return bytes;
}
