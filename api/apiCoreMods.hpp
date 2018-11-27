//
//  coreMods.hpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/2/18.
//
//

#ifndef coreMods_h
#define coreMods_h

typedef char *(*modTransformer)(string, char *, int *);

class coreMod {
public:
	virtual ~coreMod() {
		// NOOP
	}

	virtual modTransformer *getTransformers() {
		return NULL;
	}

	virtual int getTransformerCount() {
		return 0;
	}
};

#endif /* coreMods_h */
