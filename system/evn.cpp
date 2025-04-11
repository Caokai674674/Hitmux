#ifndef EVN_CPP
#define EVN_CPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "../const.cpp"
#include "fs.cpp"

using namespace std;

string hitmux_get_evn(int num) {
    string evn_file = init_dir + "hitmux.evn";
    ifstream evn_stream(evn_file.c_str());
    string line;
    string all[MAX_EVN];
    for(int i=0; i<MAX_EVN; i++) {
        getline(evn_stream, line);
        all[i] = line;
    }
    evn_stream.close();
    if (num >= 0 && num < MAX_EVN) {
        return all[num];
    }
    else {
        return "";
    }
}

bool hitmux_set_evn(int num, const string& env) {
    string evn_file = init_dir + "hitmux.evn";
    ifstream infile(evn_file.c_str());
    if (!infile) {
        cerr << "Failed to open file: " << evn_file << std::endl;
        log("Set environment failed: Failed to open file: " + evn_file, 2);
        return false;
    }
    vector<string> lines;
    string line;
    int temp = -1;
    while (getline(infile, line)) {
        lines.push_back(line);
        temp++;
    }
    infile.close();
    if (temp >= MAX_EVN) {
        cerr << "Too many environments. Maximum is " << MAX_EVN << std::endl;
        return false;
    }
    if (num > 5 && num < MAX_EVN) {
        lines.insert(lines.begin() + num, env);
    } else {
        cerr << "Invalid environment number: " << num << " (The number must be between 6 and " << MAX_EVN << ")" << std::endl;
        return false;
    }

    ofstream outfile(evn_file.c_str(), std::ofstream::trunc);
    if (!outfile) {
        cerr << "Failed to open file: " << evn_file << std::endl;
        log("Set environment failed: Failed to open file: " + evn_file, 2);
        return false;
    }

    for (const auto& l : lines) {
        outfile << l << "\n";
    }
    outfile.close();
}

#endif