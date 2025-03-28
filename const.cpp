#ifndef CONST_H
#define CONST_H

#include <string>
using namespace std;
const int MAX_PARAMS_INITIAL = 10;
const string Hitmux_Version="3.0.0-beta";
#ifdef _WIN32
    const string init_file="C:\\Users\\Public\\Hitmux\\init.txt";
    const string init_dir="C:\\Users\\Public\\Hitmux";

    const string log_file="C:\\Users\\Public\\Hitmux\\log.txt";
    const string log_dir="C:\\Users\\Public\\Hitmux";

    const string config_file="C:\\Users\\Public\\Hitmux\\config.txt";
    const string config_dir="C:\\Users\\Public\\Hitmux";
#else
    const string init_file="/etc/hitmux/init.txt";
    const string init_dir="/etc/hitmux";

    const string log_file="/var/log/hitmux/log.txt";
    const string log_file="/var/log/hitmux";

    
    const string config_file="/etc/hitmux/config.txt";
#endif

const string prompt="Hitmux >> ";

#endif