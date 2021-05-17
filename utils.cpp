#include <iostream>
using std::cout;
using std::to_string;
using std::getline;
#include <cpuid.h>
#include <cstring>
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

string get_cpu_info() {
    char cpu_info_char_str[0x40];
    unsigned int cpu_info[4] = {0, 0, 0, 0};

    __cpuid(0x80000000, cpu_info[0], cpu_info[1], cpu_info[2], cpu_info[3]);
    unsigned int nExIds = cpu_info[0];

    memset(cpu_info_char_str, 0, sizeof(cpu_info_char_str));

    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(i, cpu_info[0], cpu_info[1], cpu_info[2], cpu_info[3]);
        switch (i) {
            case 0x80000002:
                memcpy(cpu_info_char_str, cpu_info, sizeof(cpu_info));
                break;
            case 0x80000003:
                memcpy(cpu_info_char_str + 16, cpu_info, sizeof(cpu_info));
                break;
            case 0x80000004:
                memcpy(cpu_info_char_str + 32, cpu_info, sizeof(cpu_info));
                break;
            default:
                break;
        }
    }
    return cpu_info_char_str;
}