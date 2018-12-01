//
//  launcher.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/3/18.
//
//

#include <iostream>

#include <common/relauncher/relauncher.hpp>

static void returned(void);

int main(int argc, char **argv) {
    relaunch(argc, argv);
    
    // Should not reach here.
    returned();
    return 1;
}

static void returned(void) {
	cerr << "MinecraftBlacksmith somehow returned from the relauncher.";
}
