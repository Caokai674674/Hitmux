#ifndef SW_CPP
#define SW_CPP

#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "evn.cpp"

using namespace std;

bool hitmux_install_sw(vector<string> str) {
    if (str.size() == 0) {
        cout << "No input file.\n";
        return false;
    }
    else if (str.size() > 1) {
        cout << "Too many input files.\n";
        return false;
    }
    else {
        string cmd;
#ifdef _WIN32
        string dest = hitmux_get_evn(1) + "\\lib" + str[0] + ".dll";
        cmd = "mkdir " + hitmux_get_evn(1) + " " + hitmux_get_evn(2) + " " + hitmux_get_evn(3) + " " + hitmux_get_evn(4) + " && copy lib" + str[0] + ".dll " + dest;
#else
        string dest = hitmux_get_evn(1) + "/lib" + str[0] + ".so";
        cmd = "mkdir -p " + hitmux_get_evn(1) + " " + hitmux_get_evn(2) + " " + hitmux_get_evn(3) + " " + hitmux_get_evn(4) + " && cp lib" + str[0] + ".so " + dest;
#endif
        cout<<hitmux_get_evn(1)<<endl<<cmd<<endl;
        if (system(cmd.c_str()) == 0) {
            return true;
        }
        else {
            cout << "Installation failed.\n";
            return false;
        }
    }
}

bool hitmux_uninstall_sw(vector<string> str) {
    cout << "Not implemented yet.\n";
    return false;
}

bool hitmux_build_sw(vector<string> str) {
    string cmd;
#ifdef _WIN32
    if (str.size() == 0){
        cout <<"No input file.\n";
        return false;
    }
    else if (str.size() < 2) {
        cmd = "g++ -shared -fPIC -O2 -o lib" + str[0] + ".dll " + str[0] + ".cpp";
    }
    else {
        cmd = "g++ -o lib" + str[0] + ".dll " + str[0] + ".cpp";
        for (int i = 1; i < str.size(); i++) {
            cmd += " " + str[i];
        }
    }
    system(cmd.c_str());
    return true;
#else
    if (str.size() == 0){
        cout <<"No input file.\n";
        return false;
    }
    else if (str.size() < 2) {
        cmd = "g++ -shared -fPIC -O2 -o lib" + str[0] + ".so " + str[0] + ".cpp";
    }
    else {
        cmd = "g++ -o lib" + str[0] + ".so " + str[0] + ".cpp";
        for (int i = 1; i < str.size(); i++) {
            cmd += " " + str[i];
        }
    }
    system(cmd.c_str());
    return true;
#endif
}

#endif