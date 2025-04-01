#ifndef MANAGE_CPP
#define MANAGE_CPP

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include "../const.cpp"
#include "../system/time.cpp"
#include "../system/fs.cpp"
#include "../system/safe/sha256.cpp"
#include "passwd.cpp" 
using namespace std;

int hitmux_login(){
    string username, password;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    password = hitmux_input_passwd();

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


bool hitmux_deluser(string username) {  
    if (username.empty()){
        cout << "Deleteuser: Username cannot be empty" << endl;
        return 0;
    }
    ifstream file(init_file.c_str());
    if (!file.is_open()) {
        cout << "Deleteuser: Error: Could not open file: " << init_file << endl;
        log("Deleteuser: Could not open file: " + init_file,2);
        return 0;
    }

    string line;
    string stored_hash = "";
    string new_file_content = "";
    bool user_found = false;
    while (getline(file, line)) {
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string file_username = line.substr(0, pos);
            if (file_username == username) {
                stored_hash = line.substr(pos + 1);
            } else {
                new_file_content += line + "\n";
            }
        }
    }
    file.close();
    if (!user_found) {
        cout << "Error: User not found :" << username << endl;
        return 0;
    }
    string password;
    cout << "Please input the password for user " << username << ":" << endl;
    password = hitmux_input_passwd();

    string input_hash = sha256(password);

    if (input_hash != stored_hash) {
        cout << "Error: Incorrect password" << endl;
        log("Delete user: Incorrect password for user " + username,0);
        return 0;
    }

    ofstream new_file(init_file.c_str());
    new_file << new_file_content;
    new_file.close();

    cout << "User deleted successfully" << endl;
    log("Delete user: " + username + " deleted successfully",0);
    return 1;
}

bool hitmux_adduser(string username){
    string  password;
    if (username.empty()){
        cout << "Adduser: Username cannot be empty" << endl;
        return 0;
    }
    for(int i=0;i<username.length();i++){
        if(username[i] == ':'){
            printf("Invalid username\n");
            return 0;
        }
    }
    
    printf("Password:");
    password = hitmux_input_passwd();
    for(int i=0;i<password.length();i++){
        if(password[i] == ':'){
            printf("Invalid password\n");
            return 0;
        }
    }
    ofstream install_system(init_file.c_str(),ios::app);
    if (!install_system.is_open()) {
        cout << "Error: Could not open file: " << init_file << endl;
        log("Adduser: Could not open file: " + init_file,2);
        return 0;
    }
    install_system << username <<":"<< sha256(password) << "\n";
    install_system.close();
    cout << "User added successfully" << endl;
    log("Adduser: " + username + " added successfully",0);
    return 1;
}

#endif