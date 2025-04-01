#ifndef FS2_CPP
#define FS2_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm> // 用于 std::find
namespace fs = std::filesystem;

void handle_error(const std::string& msg) {
    std::cerr << "error: " << msg << std::endl;
}

bool hitmux_cp(const std::vector<std::string>& parameter) {
    // 分离选项和路径
    std::vector<std::string> options;
    std::vector<std::string> paths;
    for (const auto& p : parameter) {
        if (!p.empty() && p[0] == '-') {
            options.push_back(p);
        } else {
            paths.push_back(p);
        }
    }
    bool recursive = std::find(options.begin(), options.end(), "-r") != options.end();
    if (paths.size() < 2) {
        handle_error("cp: missing source and destination operands");
        return false;
    }
    fs::path dst(paths.back());
    bool dst_is_dir = fs::exists(dst) && fs::is_directory(dst);
    if (paths.size() == 2) {
        fs::path src(paths[0]);
        if (fs::is_directory(src) && !recursive) {
            handle_error("cp: omitting directory '" + src.string() + "' (use -r)");
            return false;
        }
        try {
            if (dst_is_dir) {
                fs::path target = dst / src.filename();
                if (fs::is_directory(src)) {
                    fs::copy(src, target, fs::copy_options::recursive);
                } else {
                    fs::copy(src, target);
                }
            } else {
                if (fs::is_directory(src)) {
                    handle_error("cp: cannot copy directory to file");
                    return false;
                } else {
                    fs::copy(src, dst);
                }
            }
            return true;
        } catch (const fs::filesystem_error& e) {
            handle_error(e.what());
            return false;
        }
    } else {
        if (!dst_is_dir) {
            handle_error("cp: target must be a directory for multiple sources");
            return false;
        }
        bool success = true;
        for (size_t i = 0; i < paths.size() - 1; ++i) {
            fs::path src(paths[i]);
            if (fs::is_directory(src) && !recursive) {
                handle_error("cp: omitting directory '" + src.string() + "' (use -r)");
                success = false;
                continue;
            }
            fs::path target = dst / src.filename();
            try {
                if (fs::is_directory(src)) {
                    fs::copy(src, target, fs::copy_options::recursive);
                } else {
                    fs::copy(src, target);
                }
            } catch (const fs::filesystem_error& e) {
                handle_error(e.what());
                success = false;
            }
        }
        return success;
    }
}

bool hitmux_mv(const std::vector<std::string>& parameter) {
    if (parameter.size() < 2) {
        handle_error("mv: missing source and destination operands");
        return false;
    }
    fs::path dst(parameter.back());
    bool dst_is_dir = fs::exists(dst) && fs::is_directory(dst);
    if (parameter.size() == 2) {
        fs::path src(parameter[0]);
        try {
            if (dst_is_dir) {
                fs::path target = dst / src.filename();
                fs::rename(src, target);
            } else {
                fs::rename(src, dst);
            }
            return true;
        } catch (const fs::filesystem_error& e) {
            handle_error(e.what());
            return false;
        }
    } else {
        if (!dst_is_dir) {
            handle_error("mv: target must be a directory for multiple sources");
            return false;
        }
        bool success = true;
        for (size_t i = 0; i < parameter.size() - 1; ++i) {
            fs::path src(parameter[i]);
            fs::path target = dst / src.filename();
            try {
                fs::rename(src, target);
            } catch (const fs::filesystem_error& e) {
                handle_error(e.what());
                success = false;
            }
        }
        return success;
    }
}

bool hitmux_rm(const std::vector<std::string>& parameter) {
    std::vector<std::string> options;
    std::vector<std::string> paths;
    for (const auto& p : parameter) {
        if (!p.empty() && p[0] == '-') {
            options.push_back(p);
        } else {
            paths.push_back(p);
        }
    }
    bool recursive = std::find(options.begin(), options.end(), "-r") != options.end();
    if (paths.empty()) {
        handle_error("rm: missing operand");
        return false;
    }
    bool success = true;
    for (const auto& p : paths) {
        fs::path path(p);
        try {
            if (fs::is_directory(path)) {
                if (recursive) {
                    fs::remove_all(path);
                } else {
                    handle_error("rm: cannot remove '" + p + "': is a directory (use -r)");
                    success = false;
                }
            } else {
                fs::remove(path);
            }
        } catch (const fs::filesystem_error& e) {
            handle_error(e.what());
            success = false;
        }
    }
    return success;
}

bool hitmux_cat(const std::vector<std::string>& parameter) {
    std::vector<std::string> options;
    std::vector<std::string> paths;
    for (const auto& p : parameter) {
        if (!p.empty() && p[0] == '-') {
            options.push_back(p);
        } else {
            paths.push_back(p);
        }
    }
    bool number_lines = std::find(options.begin(), options.end(), "-n") != options.end();
    if (paths.empty()) {
        handle_error("cat: missing operand");
        return false;
    }
    bool success = true;
    for (const auto& p : paths) {
        fs::path path(p);
        if (!fs::exists(path) || !fs::is_regular_file(path)) {
            handle_error("cat: '" + p + "': no such file or not a regular file");
            success = false;
            continue;
        }
        std::ifstream file(path);
        if (!file.is_open()) {
            handle_error("cat: '" + p + "': cannot open file");
            success = false;
            continue;
        }
        if (number_lines) {
            std::string line;
            int line_num = 1;
            while (std::getline(file, line)) {
                std::cout << line_num << " " << line << std::endl;
                line_num++;
            }
        } else {
            std::cout << file.rdbuf();
        }
        file.close();
    }
    return success;
}

bool hitmux_ls(const std::vector<std::string>& parameter) {
    std::vector<std::string> options;
    std::vector<std::string> paths;
    for (const auto& p : parameter) {
        if (!p.empty() && p[0] == '-') {
            options.push_back(p);
        } else {
            paths.push_back(p);
        }
    }
    bool show_all = std::find(options.begin(), options.end(), "-a") != options.end();
    if (paths.empty()) {
        paths.push_back(fs::current_path().string());
    }
    bool success = true;
    for (const auto& p : paths) {
        fs::path path(p);
        if (!fs::exists(path) || !fs::is_directory(path)) {
            handle_error("ls: '" + path.string() + "': no such directory");
            success = false;
            continue;
        }
        for (const auto& entry : fs::directory_iterator(path)) {
            std::string filename = entry.path().filename().string();
            if (!show_all && !filename.empty() && filename[0] == '.') {
                continue;
            }
            std::cout << filename << std::endl;
        }
    }
    return success;
}

bool hitmux_mkdir(const std::vector<std::string>& parameter) {
    if (parameter.empty()) {
        handle_error("mkdir: missing operand");
        return false;
    }
    bool success = true;
    for (const auto& p : parameter) {
        fs::path path(p);
        try {
            fs::create_directories(path);
        } catch (const fs::filesystem_error& e) {
            handle_error(e.what());
            success = false;
        }
    }
    return success;
}

bool hitmux_touch(const std::vector<std::string>& parameter) {
    std::vector<std::string> options;
    std::vector<std::string> paths;

    for (const auto& arg : parameter) {
        if (!arg.empty() && arg[0] == '-') {
            options.push_back(arg);
        } else {
            paths.push_back(arg);
        }
    }

    bool no_create = std::find(options.begin(), options.end(), "-c") != options.end();

    if (paths.empty()) {
        std::cerr << "touch: missing file operand" << std::endl;
        return false;
    }

    bool success = true;
    for (const auto& path_str : paths) {
        fs::path path(path_str);

        if (fs::exists(path)) {
            std::ofstream file(path, std::ios::app);
            if (!file.is_open()) {
                std::cerr << "touch: cannot touch '" << path_str << "': permission denied" << std::endl;
                success = false;
            }
            file.close();
        } else if (!no_create) {
            std::ofstream file(path);
            if (!file.is_open()) {
                std::cerr << "touch: cannot create '" << path_str << "': permission denied" << std::endl;
                success = false;
            }
            file.close();
        }
    }
    return success;
}
#endif