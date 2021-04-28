//
// Created by blithepan on 2021/4/27.
//

#ifndef SELFGTEST_LOGPRINT_H
#define SELFGTEST_LOGPRINT_H
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>
#include <stdarg.h>  // For va_start, etc.

using namespace std;

#ifdef STD_UNIT_TEST
#define  ZONE_INFO 0

void LogOut(const string &str){
    cout << str << endl;
}

std::string LOGMSG(int logleve, const std::string fmt_str, ...) {
    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt_str.c_str());
        va_start(ap, fmt_str);
        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    LogOut(formatted.get());
    return std::string(formatted.get());
}
#endif

#endif //SELFGTEST_LOGPRINT_H
