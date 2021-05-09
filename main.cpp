#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;

#include <boost/compute.hpp>
namespace compute = boost::compute;

#include "Burner.h"
#include "CPUBurner.h"
#include "utils.h"

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
    return 0;
}

void init_welcome() {
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

Burner *menu() {
    cout << LINUX_TERMINAL_BOLDCYAN << "- MAKE IT" << LINUX_TERMINAL_RESET << LINUX_TERMINAL_BOLDBLUE << " STRESSFUL" << LINUX_TERMINAL_RESET << LINUX_TERMINAL_BOLDCYAN << "-" << LINUX_TERMINAL_RESET << endl
         << "==============================" << endl
         << "= 1) CPU" << endl
         << "= 2) GPU (In developing)  " << endl
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
            default:
                return nullptr;
        }
    }
}

