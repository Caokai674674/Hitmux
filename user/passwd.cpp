#ifndef PASSWD_CPP
#define PASSWD_CPP

#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

std::string hitmux_input_passwd() {
    std::string password = "";

#ifdef _WIN32
    const int ENTER_KEY = 13;
    auto isBackspace = [](int ch) { return ch == 8; };
#else
    const int ENTER_KEY = '\n';
    auto isBackspace = [](int ch) { return ch == 8 || ch == 127; };
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

    while (true) {
        int ch;
#ifdef _WIN32
        ch = getch();
#else
        ch = getchar();
#endif
        if (ch == ENTER_KEY) {
            break;
        } else if (isBackspace(ch)) {
            if (!password.empty()) {
                password.erase(password.size() - 1);
                std::cout << "\b \b" << std::flush;
            }
        } else {
            password += static_cast<char>(ch);
            std::cout << "*" << std::flush;
        }
    }

#ifndef _WIN32
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    cout << endl;
    return password;
}

#endif