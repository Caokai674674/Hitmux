#define HITMUX

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <filesystem>
#include <cstdlib>
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
#else
    #include <dlfcn.h>
    #include <unistd.h>
#endif

#include "const.cpp"
#include "system/init.cpp"
#include "user/manage.cpp"
#include "system/time.cpp"
#include "system/fs.cpp"
#include "system/sw.cpp"
#include "system/fs2.cpp"

using namespace std;

using CommandFunction = std::function<void(const std::vector<std::string>&)>;
using FunctionMap = std::map<std::string, CommandFunction>;

map<string, CommandFunction> global_commands;
map<string, void*> plugin_handles;

bool cd_path(const string& path) {
    return chdir(path.c_str()) != 0;
}

void showHelp() {
    cout << "This is Hitmux system shell.\n"
         << "By CaoKai in China, 2025.\n"
         << "Connect with me: hitmux674@gmail.com\n"
         << "Source code: https://github.com/CaoKai674674/hitmux\n";
}

void* load_lib(const string& path) {
#ifdef _WIN32
    HMODULE handle = LoadLibrary(path.c_str());
    if (!handle) {
        cout << "Failed to load " << path << ": command not found" << endl;
        return nullptr;
    }
    return handle;
#else
    void* handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        cout << "Failed to load " << path << ": " << dlerror() << endl;
        return nullptr;
    }
    return handle;
#endif
}

CommandFunction load_command_function(const string& command) {
    string plugin_name;
#ifdef _WIN32
    plugin_name = "lib" + command + ".dll";
#else
    plugin_name = "lib" + command + ".so";
#endif
    string plugin_path = init_dir + plugin_name;

    if (!filesystem::exists(plugin_path)) {
        cout << command << ": command not found" << endl;
        return nullptr;
    }

    if (plugin_handles.find(command) == plugin_handles.end()) {
        void* handle = load_lib(plugin_path);
        if (!handle) {
            return nullptr;
        }
        plugin_handles[command] = handle;
    }

    void* handle = plugin_handles[command];
    using GetFuncsType = FunctionMap* (*)();
#ifdef _WIN32
    GetFuncsType get_funcs = reinterpret_cast<GetFuncsType>(
        GetProcAddress(static_cast<HMODULE>(handle), "register_functions"));
#else
    GetFuncsType get_funcs = reinterpret_cast<GetFuncsType>(
        dlsym(handle, "register_functions"));
#endif
    if (!get_funcs) {
        cout << "Failed to find register_functions in " << plugin_name << endl;
        return nullptr;
    }

    FunctionMap* funcs = get_funcs();
    if (!funcs || funcs->find(command) == funcs->end()) {
        cout << command << ": command not found in plugin" << endl;
        delete funcs;
        return nullptr;
    }

    CommandFunction func = (*funcs)[command];
    delete funcs;
    return func;
}

int main() {
    system_init();
    printf("Welcome to Hitmux!\n");
    while (true) {
        int temp = hitmux_login();
        if (temp == 0) break;
        else if (temp == 1) continue;
        else if (temp == 2) {
            getchar();
            return 0;
        }
    }
    string input;
    while (true) {
        // cout << prompt1 << hitmux_pwd() << prompt2;
        getline(cin, input);
        if (input.empty()) {
            cout << prompt1 << hitmux_pwd() << prompt2;
            continue;
        }
        stringstream ss(input);
        string command;
        ss >> command;

        vector<string> params;
        string arg;
        while (ss >> arg) {
            params.push_back(arg);
        }
        {   //Processing command
            if (command == "exit") {
                exit(0);
            }
            else if (command == "echo") {
                if (!params.empty()) {
                    cout << params[0] << endl;
                }
            } 
            else if (command == "help") {
                showHelp();
            }
            else if (command == "adduser") {
                if (params.size() > 1) cout << "Too many arguments." << endl;
                else hitmux_adduser(params[0]);
            } 
            else if (command == "deluser") {
                if (params.size() > 1) cout << "Too many arguments." << endl;
                else hitmux_deluser(params[0]);
            }
            else if (command == "pwd") {
                cout << hitmux_pwd() << endl;
            }
            else if (command == "ls") {
                hitmux_ls(params);
            }
            else if (command == "cp") {
                hitmux_cp(params);
            }
            else if (command == "mv") {
                hitmux_mv(params);
            }
            else if (command == "rm") {
                hitmux_rm(params);
            }
            else if (command == "cat") {
                hitmux_cat(params);
            }
            else if (command == "mkdir") {
                hitmux_mkdir(params);
            }
            else if (command == "time") {
                cout << showtime() << endl;
            }
            else if (command == "touch") {
                hitmux_touch(params);
            }
            else if (command == "cd") {
                if (params.empty()) {
                    cout << "cd: missing operand" << endl;
                } else if (params.size() == 1) {
                    if (cd_path(params[0])) {
                        cout << "cd: No such directory: " << params[0] << endl;
                    }
                } else {
                    cout << "cd: Too many arguments." << endl;
                }
            }

            else if (command == "sw"){
                if (params.size() < 2) {
                    cout << "sw: missing operand" << endl;
                }
                else if (params[0] == "install"){
                    // params.erase(params.begin());
                    // hitmux_install_sw(params);
                    cout << "sw: install command is not supported yet." << endl;
                    cout << "Please copy the software package to the "+ init_dir +" directory and run the command" << endl;
                }
                else if (params[0] == "uninstall"){
                    params.erase(params.begin());
                    hitmux_uninstall_sw(params);
                }
                else if (params[0] == "build"){
                    params.erase(params.begin());
                    hitmux_build_sw(params);
                }
                else {
                    cout << "sw: invalid operand: "<< params[0] << endl;
                }
            }
            else if (global_commands.find(command) != global_commands.end()) {
                global_commands[command](params);
            } else {
                CommandFunction func = load_command_function(command);
                if (func) {
                    func(params);
                    global_commands[command] = func;
                }
            }
            cout << prompt1 << hitmux_pwd() << prompt2;
        }
    }

    for (auto& pair : plugin_handles) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(pair.second));
#else
        dlclose(pair.second);
#endif
    }
    return 0;
}