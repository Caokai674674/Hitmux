#ifndef SW_CPP
#define SW_CPP

#include <string>
#include <cstdlib>
#include <vector>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dirent.h>
#endif

std::string get_sw_folder() {
        std::string home_dir;
    #ifdef _WIN32
        char* user_profile = std::getenv("USERPROFILE");
        if (user_profile != nullptr) {
            home_dir = user_profile;
        } else {
            home_dir = "";
        }
        return home_dir + "\\hitsw\\";
    #else
        char* home = std::getenv("HOME");
        if (home != nullptr) {
            home_dir = home;
        } else {
            home_dir = "";
        }
        return home_dir + "/hitsw/";
    #endif
}

std::vector<std::string> list_sw(const std::string& folder) {
    std::vector<std::string> files;

    #ifdef _WIN32
        WIN32_FIND_DATA find_data;
        HANDLE hFind = FindFirstFile((folder + "\\*").c_str(), &find_data);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (!(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                    files.push_back(folder + "\\" + find_data.cFileName);
                }
            } while (FindNextFile(hFind, &find_data));
            FindClose(hFind);
        }
    #else
        DIR* dir = opendir(folder.c_str());
        if (dir != nullptr) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_type == DT_REG) {
                    files.push_back(folder + "/" + entry->d_name);
                }
            }
            closedir(dir);
        }
    #endif

        return files;
}

#endif