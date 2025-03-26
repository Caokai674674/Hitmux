#include "plugin.h"
#include <iostream>

using namespace std;


void f1() {
    printf("Hello, world!\n");     
}


extern "C" {
    FunctionMap* register_functions() {
        FunctionMap* funcs = new FunctionMap();
        (*funcs)["hello"] = f1;//f1 is function name and hello is the command name.
        return funcs;
    }
}

