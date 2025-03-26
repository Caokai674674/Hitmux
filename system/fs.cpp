#ifndef _FS_CPP
#define _FS_CPP

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include "time.cpp"
#include "../const.cpp"

using namespace std;
namespace fs = std::filesystem;

void log(string message,int level);

int hitmuix_mkdir(string fspath,int mode) {
    fs::path folderPath = fspath.c_str();

    try {
        if (!fs::exists(folderPath)) {
            if (fs::create_directory(folderPath)) {
                std::cout << " Folder '" << folderPath << "' created successfully." << std::endl;
            } else {
                std::cout << " Folder '" << folderPath << "' creation failed." << std::endl;
                log("Folder creation failed: " + fspath, 2);
            }
        } else {
            if(mode == 1) std::cout << " Folder '" << folderPath << "' already exists." << std::endl;
            else if(mode == 2) {
                std::cout << " Folder '" << folderPath << "' already exists." << std::endl;
                log("Folder already exists: " + fspath, 0);
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        if(mode != -1) log(string("Filesystem error: ") + e.what(), 2);
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        if(mode != -1) log(string("Error: ") + e.what(), 2);
        return 1;
    }

    return 0;
}

bool hitmux_is_dir(string fspath) {
    fs::path folderPath = fspath.c_str();

    if (fs::exists(folderPath) && fs::is_directory(folderPath)) return 1;
    return 0;
}

void log(string message,int level) {
    string level_str;
    if(level==0) {
        level_str="Note";
    }
    if(level==1) {
        level_str="Warning";
    }
    if(level==2) {
        level_str="Error";
    }
    if(!hitmux_is_dir(log_dir)){
        int temp = hitmuix_mkdir(log_dir,-1);
        if(temp!=0) {
            cout << "Failed to create log directory." << endl;
            return;
        }
    }
    ofstream logFile;
    logFile.open(log_file.c_str(), ios::app);
    logFile << showtime() << " [" << level_str << "] " << message << endl;
    logFile.close();
}

#endif