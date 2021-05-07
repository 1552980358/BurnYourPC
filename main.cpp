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

    cout << "Welcome to " << BOLDRED << "BurnYourPC" << RESET << '!' << endl
         << "=====|Software|=====" << endl
         << "OS Name:  " << BOLDBLUE << get_os_name() << RESET << endl
         << "Compiler: " << BOLDBLUE << get_compiler() << RESET << endl
         << "=====|Hardware|=====" << endl
         << "CPU:      " << BOLDBLUE << get_cpu_info() << RESET << endl;
    auto devices = compute::system::devices();
    for (auto &device : devices) {
        cout << "OpenCL:   " << BOLDBLUE << device.name() << RESET << " by " << BOLDRED << device.vendor() << RESET << " with " << BOLDYELLOW << device.version() << RESET << endl;
    }
    cout << "====================" << endl
         << endl;
}

Burner *menu() {
    cout << BOLDCYAN << "- MAKE IT" << RESET << BOLDBLUE << " STRESSFUL" << RESET << BOLDCYAN << "-" << RESET << endl
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

