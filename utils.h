#ifndef BURNYOURPC_UTILS_H
#define BURNYOURPC_UTILS_H

#include <string>
using std::string;

// The following are LINUX, and MacOS ONLY terminal color codes.
#define LINUX_TERMINAL_RESET   "\033[0m"
#define LINUX_TERMINAL_BLACK   "\033[30m"      /* Black */
#define LINUX_TERMINAL_RED     "\033[31m"      /* Red */
#define LINUX_TERMINAL_GREEN   "\033[32m"      /* Green */
#define LINUX_TERMINAL_YELLOW  "\033[33m"      /* Yellow */
#define LINUX_TERMINAL_BLUE    "\033[34m"      /* Blue */
#define LINUX_TERMINAL_MAGENTA "\033[35m"      /* Magenta */
#define LINUX_TERMINAL_CYAN    "\033[36m"      /* Cyan */
#define LINUX_TERMINAL_WHITE   "\033[37m"      /* White */
#define LINUX_TERMINAL_BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define LINUX_TERMINAL_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define LINUX_TERMINAL_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define LINUX_TERMINAL_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define LINUX_TERMINAL_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define LINUX_TERMINAL_BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define LINUX_TERMINAL_BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define LINUX_TERMINAL_BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// The following are Windows console color codes
#define WIN_CONSOLE_BLACK 0
#define WIN_CONSOLE_BOLDBLUE 1
#define WIN_CONSOLE_BOLDGREEN 2
#define WIN_CONSOLE_BOLDCYAN 3
#define WIN_CONSOLE_BOLDRED 4
#define WIN_CONSOLE_BOLDMAGENTA 5
#define WIN_CONSOLE_BOLDYELLOW 6
#define WIN_CONSOLE_RESET 7
#define WIN_CONSOLE_GRAY 8
#define WIN_CONSOLE_BLUE 9
#define WIN_CONSOLE_GREEN 10
#define WIN_CONSOLE_CYAN 11
#define WIN_CONSOLE_RED 12
#define WIN_CONSOLE_MAGENTA 13
#define WIN_CONSOLE_YELLOW 14
#define WIN_CONSOLE_WHITE 15

/** Check whether the OS is Microsoft Windows **/
#ifdef _WIN32
#define WINDOWS_SYSTEM
#elif _WIN64
#define WINDOWS_SYSTEM
#endif

#ifdef WINDOWS_SYSTEM
#include <windows.h>
static HANDLE windows_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

void clear_screen();

string get_os_name();

string get_compiler();

string get_cpu_info();

#endif //BURNYOURPC_UTILS_H
