#include "plugin.h"
#include <iostream>

using namespace std;


void f1() {
    printf("Hello, world!\n");     
}


extern "C" {
    FunctionMap* register_functions() {
        FunctionMap* funcs = new FunctionMap();
        (*funcs)["helloword"] = f1;
        return funcs;
    }
}

