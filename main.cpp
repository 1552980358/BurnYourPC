#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;

#include <boost/compute.hpp>
namespace compute = boost::compute;

#include "utils.h"
#include "Burner.h"
#include "CPUBurner.h"
#include "GPUBurner.h"

// Remove following 3 comment line if [multiple definition of "windows_console_handle"] error thrown
// #ifdef WINDOWS_SYSTEM
// extern HANDLE windows_console_handle; // NOLINT(readability-redundant-declaration)
// #endif

void init_welcome();
Burner *menu();

int main() {
    init_welcome();
    auto *burner = menu();
    if (!burner) {
        return 1;
    }
    burner->menu();
    burner->prepare();
    burner->burn();

    cout << "<Press any key to continue...>";
    getchar();

    return 0;
}

void init_welcome_win() {
    // HANDLE windows_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cout << "Welcome to ";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDRED);
    cout << "BurnYourPC";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
    cout << '!' << endl
         << "=====|Software|=====" << endl
         << "OS Name:  ";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDBLUE);
    cout << get_os_name();
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
    cout << endl
         << "Compiler: ";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDBLUE);
    cout << get_compiler();
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
    cout << endl
         << "=====|Hardware|=====" << endl
         << "CPU:      ";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDBLUE);
    cout << get_cpu_info();
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
    cout << endl;
    auto devices = compute::system::devices();
    for (auto &device : devices) {
        cout << "OpenCL:   ";
        SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDBLUE);
        cout << device.name();
        SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
        cout << " by ";
        SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDRED);
        cout << device.vendor();
        SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
        cout << " with ";
        SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDYELLOW);
        cout << device.version();
        SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
        cout << endl;
    }
    cout << "====================" << endl
         << endl;
}

void init_welcome_linux() {
    cout << "Welcome to " << LINUX_TERMINAL_BOLDRED << "BurnYourPC" << LINUX_TERMINAL_RESET << '!' << endl
         << "=====|Software|=====" << endl
         << "OS Name:  " << LINUX_TERMINAL_BOLDBLUE << get_os_name() << LINUX_TERMINAL_RESET << endl
         << "Compiler: " << LINUX_TERMINAL_BOLDBLUE << get_compiler() << LINUX_TERMINAL_RESET << endl
         << "=====|Hardware|=====" << endl
         << "CPU:      " << LINUX_TERMINAL_BOLDBLUE << get_cpu_info() << LINUX_TERMINAL_RESET << endl;
    auto devices = compute::system::devices();
    for (auto &device : devices) {
        cout << "OpenCL:   " << LINUX_TERMINAL_BOLDBLUE << device.name() << LINUX_TERMINAL_RESET
             << " by " << LINUX_TERMINAL_BOLDRED << device.vendor() << LINUX_TERMINAL_RESET
             << " with " << LINUX_TERMINAL_BOLDYELLOW << device.version() << LINUX_TERMINAL_RESET << endl;
    }
    cout << "====================" << endl
         << endl;
}

void init_welcome() {
#ifdef _WIN32
    init_welcome_win();
#elif _WIN64
    init_welcome_win();
#else
    init_welcome_linux();
#endif
}

Burner *menu() {
#ifdef WINDOWS_SYSTEM
    // HANDLE windows_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDCYAN);
    cout << "- MAKE IT";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDRED);
    cout << " STRESSFUL";
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDCYAN);
    cout << "-" << endl;
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
#else
    cout << LINUX_TERMINAL_BOLDCYAN << "- MAKE IT" << LINUX_TERMINAL_RESET << LINUX_TERMINAL_BOLDBLUE << " STRESSFUL" << LINUX_TERMINAL_RESET << LINUX_TERMINAL_BOLDCYAN << "-" << LINUX_TERMINAL_RESET << endl;
#endif
    cout << "==============================" << endl
         << "= 1) CPU" << endl
         << "= 2) GPU" << endl
         << "= 3) RAM (In developing)" << endl
         << "= 4) Hard Disk (In developing)" << endl
         << "==============================" << endl
         << "$> ";

    string input;
    while (true) {
        getline(cin, input);
        if (input.size() != 1) {
            continue;
        }
        switch (input[0]) {
            case '1':
                return new CPUBurner();
            case '2':
                return new GPUBurner(compute::system::default_device());
            default:
                return nullptr;
        }
    }
}

