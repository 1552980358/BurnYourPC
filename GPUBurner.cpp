#include "GPUBurner.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <vector>
using std::vector;
#include <chrono>
using namespace std::chrono;

#include <boost/compute.hpp>

#include "utils.h"

// Remove following 3 comment line if [multiple definition of "windows_console_handle"] error thrown
// #ifdef WINDOWS_SYSTEM
// extern HANDLE windows_console_handle; // NOLINT(readability-redundant-declaration)
// #endif

GPUBurner::GPUBurner(const boost::compute::device& device) {
    _device = device;
}

void GPUBurner::menu() {
#ifdef WINDOWS_SYSTEM
    // HANDLE windows_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDRED);
#else
    cout << LINUX_TERMINAL_BOLDRED;
#endif

    cout << "This test is still in development. Running will be DANGEROUS!" << endl;

#ifdef WINDOWS_SYSTEM
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
#else
    cout << LINUX_TERMINAL_RESET;
#endif

    cout << "Input \"YES\" to continue" << endl
         << "$> ";
    getline(cin, _input);
}

void GPUBurner::prepare() {
    if (_input != "YES") {
        return;
    }
    cout << "<Press any key to continue...>";
    getchar();
}

void GPUBurner::burn() {

    if (_input != "YES") {
        return;
    }


}


