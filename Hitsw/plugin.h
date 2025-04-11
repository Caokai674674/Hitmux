#ifndef PLUGIN_H
#define PLUGIN_H

#include <string>
#include <functional>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using CommandFunction = std::function<void()>;
using FunctionMap = std::map<std::string, CommandFunction>;

extern "C" {
    FunctionMap* register_functions();
}

std::string H_get_evn(int num) {
#ifdef _WIN32
    std::ifstream ifile("C:\\Users\\Public\\Hitmux\\hitmux.env");
#else 
    std::ifstream ifile("/etc/hitmux/hitmux.env");
#endif
    if (!ifile.is_open()) {
        std::cerr << "Error: Cannot open environment file: " ;
#ifdef _WIN32
        std::cerr << "C:\\Users\\Public\\Hitmux\\hitmux.env" << std::endl;
#else
        std::cerr << "/etc/hitmux/hitmux.env" << std::endl;
#endif
        return "";
    }
    std::string line,temp;
    for (int i = 0; i < num; i++) {
        std::getline(ifile,temp);
    }
    std::getline(ifile, line);
    return line;
}

#endif