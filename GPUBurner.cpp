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

#define GPU_BURN_TYPE_PI_DOUBLE 1

// Remove following 3 comment line if [multiple definition of "windows_console_handle"] error thrown
// #ifdef WINDOWS_SYSTEM
// extern HANDLE windows_console_handle; // NOLINT(readability-redundant-declaration)
// #endif

GPUBurner::GPUBurner(const boost::compute::device& device) {
    _device = device;
}

void GPUBurner::menu() {
    cout << "=|BURN-GPU|====================" << endl
         << "= 1) Calculate Pi in Double Precision" << endl
         << "===============================" << endl
         << "$> ";
    string input;
    getline(cin, input);
    if (input.empty()) {
        return;
    }
    _type = input[0] - 48;
}

void GPUBurner::prepare() {
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
    string input;
    cout << "Input \"YES\" to continue" << endl
         << "$> ";
    getline(cin, input);
    _input = input == "YES";
    if (!_input) {
        return;
    }
    cout << "<Press any key to continue...>";
    getchar();
}

void GPUBurner::burn() {
    if (!_input) {
        return;
    }
}


