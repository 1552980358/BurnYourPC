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

#include "utils.h"
#include "gpu_burner/GPUPiDoubleBurner.h"
#include "gpu_burner/GPUPiFloatBurner.h"

#define GPU_BURN_TYPE_PI_DOUBLE 1
#define GPU_BURN_TYPE_PI_FLOAT 2

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
         << "= 2) Calculate Pi in Single Precision" << endl;
    Burner::menu();
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
    Burner::prepare();
}

void GPUBurner::burn() {
    if (!_input) {
        return;
    }
    GPUBurnerTask *burner_task;
    switch (_type) {
        case GPU_BURN_TYPE_PI_DOUBLE:
            burner_task = new GPUPiDoubleBurner(_device);
            break;
        case GPU_BURN_TYPE_PI_FLOAT:
            burner_task = new GPUPiFloatBurner(_device);
            break;
        case BURNER_TYPE_INIT:
        default:
            cout << "Unknown burning method: " << _type << endl;
            return;
    }
    cout << "GPUBurner task preparing..." << endl;
    burner_task->prepare();
    cout << "Now start..." << endl;
    burner_task->burn();
    cout << "GPUBurner task complete." << endl
         << "Time spend: " << burner_task->get_time_spend_milliseconds() << " ms." << endl;
    burner_task->recycle();

    switch (_type) {
        case GPU_BURN_TYPE_PI_DOUBLE:
            delete (GPUPiDoubleBurner *) burner_task;
            break;
        case GPU_BURN_TYPE_PI_FLOAT:
            delete (GPUPiFloatBurner *) burner_task;
            break;
    }
}

#undef GPU_BURN_TYPE_PI_DOUBLE
#undef GPU_BURN_TYPE_PI_FLOAT