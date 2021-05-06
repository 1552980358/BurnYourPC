#include <iostream>
using std::cout;
using std::to_string;
#include <sstream>
#include "utils.h"

void clear_screen() {
    cout << "\033[2J\033[1;1H";
}

string get_os_name() {
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
#elif __CYGWIN__
    return "Windows Cygwin";
#elif __APPLE__ || __MACH__
    return "Mac OSX";
#elif __linux__
    return "Linux";
#elif __FreeBSD__
    return "FreeBSD";
#elif __unix || __unix__
    return "Unix";
#else
    return "Unknown";
#endif
}

string get_compiler_name() {
#ifdef __clang__
    return "Clang++";
#else
    return "GNU G++";
#endif
}

string ver_string(int a, int b, int c) {
    // std::ostringstream ss;
    // ss << a << '.' << b << '.' << c;
    // return ss.str();
    return to_string(a) + '.' + to_string(b) + '.' + to_string(c);
}

string get_compiler_version() {
#ifdef __clang__
    return ver_string(__clang_major__, __clang_minor__, __clang_patchlevel__);
#else
    return ver_string(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif
}

string get_compiler() {
    return get_compiler_name() + " " + get_compiler_version();
}