//
//  coreMods.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef coreMods_h
#define coreMods_h

#include <string>
#include <vector>

struct ModBytecode {
	std::string modid;
	std::vector<char> bytes;
};

typedef void (*ModTransformer)(ModBytecode&);

class CoreMod {
public:
	virtual ~CoreMod() {
		// NOOP
	}

	virtual ModTransformer *getTransformers() {
		return NULL;
	}

	virtual int getTransformerCount() {
		return 0;
	}
};

#endif /* coreMods_h */
