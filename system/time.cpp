#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <string>
using namespace std;

string showtime() {
    time_t now = time(nullptr);
    return ctime(&now);
}

#endif