#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <filesystem>
#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>
#else
    #include <dlfcn.h>
    #include <unistd.h>
#endif

#include "const.cpp"
#include "system/init.cpp"
#include "user/login.cpp"
#include "system/time.cpp"
#include "system/fs.cpp"
#include "system/sw.cpp"

using namespace std;

using CommandFunction = std::function<void(const std::vector<std::string>&)>;
using FunctionMap = std::map<std::string, CommandFunction>;

map<string, CommandFunction> global_commands;
vector<void*> plugin_handles;

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

void load_all_plugins(const string& plugin_dir) {
    if (!filesystem::exists(plugin_dir)) {
        cout << "Plugin directory '" << plugin_dir << "' not found." << endl;
        return;
    }

    for (const auto& entry : filesystem::directory_iterator(plugin_dir)) {
        string path = entry.path().string();
        if ((path.size() >= 4 && path.compare(path.size() - 4, 4, ".dll") == 0) ||
            (path.size() >= 3 && path.compare(path.size() - 3, 3, ".so") == 0)) {
            void* handle = load_lib(path);
            if (handle) {
                plugin_handles.push_back(handle);
                using GetFuncsType = FunctionMap* (*)();
#ifdef _WIN32
                GetFuncsType get_funcs = reinterpret_cast<GetFuncsType>(
                    GetProcAddress(static_cast<HMODULE>(handle), "register_functions"));
#else
                GetFuncsType get_funcs = reinterpret_cast<GetFuncsType>(
                    dlsym(handle, "register_functions"));
#endif
                if (get_funcs) {
                    FunctionMap* funcs = get_funcs();
                    if (funcs) {
                        for (const auto& [cmd, func] : *funcs) {
                            global_commands[cmd] = func;
                        }
                        delete funcs;
                    } else {
                        cout << path << ": register_functions returned nullptr" << endl;
                    }
                } else {
                    cout << path << ": failed to find register_functions" << endl;
                }
            }
        }
    }
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

    load_all_plugins("plugins");
    cout<<"enter any key to continue."<<endl;
    getchar();
    string input;
//    cout << prompt;

    while (true) {
        getline(cin, input);
        if (input.empty()) {
            cout << prompt;
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

        if (command == "echo") {
            if (!params.empty()) {
                cout << params[0] << endl;
            }
        } else if (command == "help") {
            showHelp();
        } else if (command == "adduser") {
            hitmux_add();
        } else if (command == "cd") {
            if (params.empty()) {
                cout << "cd: missing operand" << endl;
            } else if (params.size() == 1) {
                if (cd_path(params[0])) {
                    cout << "cd: No such directory: " << params[0] << endl;
                }
            } else {
                cout << "cd: Too many arguments." << endl;
            }
        } else if (global_commands.count(command)) {
            global_commands[command](params);
        } else {
            cout << command << ": command not found" << endl;
        }
        cout << prompt;
    }

    for (void* handle : plugin_handles) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
#else
        dlclose(handle);
#endif
    }
    return 0;
}