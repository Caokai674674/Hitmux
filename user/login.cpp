#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include "../const.cpp"
#include "../system/time.cpp"
#include "../system/fs.cpp"
#include "../system/safe/sha256.cpp"
using namespace std;

int hitmux_login(){
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream file(init_file.c_str());
    if (!file.is_open()) {
        cout << "Error: Could not open file: " << init_file << endl;
        log("Error: Could not open file: " + init_file,2);
        return 2;
    }

    string line;
    string stored_password = "";
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string file_username = line.substr(0, pos);
            if (file_username == username) {
                stored_password = line.substr(pos + 1);
                break;
            }
        }
    }
    file.close();
    if (stored_password == sha256(password)) {
        cout << "Authentication successful" << endl;
        return 0;
    } else {
        cout << "Wrong password, wait 3 seconds and try again" << endl;
        chrono::seconds duration(3);
        this_thread::sleep_for(duration);
        return 1;
    }
}

void hitmux_add(){
    printf("Please input your username and password\n");
    printf("Username:");
    string username, password;
        cin >> username;
        for(int i=0;i<username.length();i++){
            if(username[i] == ':'){
                printf("Invalid username\nPlease input your username again:\n");
                break;
            }
        }
    
    printf("Password:");
        cin >> password;
        for(int i=0;i<password.length();i++){
            if(password[i] == ':'){
                printf("Invalid password\nPlease input your password again:\n");
                break;
            }
        }
    
    ofstream install_system(init_file.c_str(),ios::app);
    install_system << username <<":"<< sha256(password) << "\n";
    install_system.close();
    cout << "User added successfully" << endl;
    return;
}

#endif