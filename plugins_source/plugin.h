#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>
#include <functional>
#include <map>

using CommandFunction = std::function<void()>;
using FunctionMap = std::map<std::string, CommandFunction>;

extern "C" {
    FunctionMap* register_functions();
}

#endif