#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <string>
using std::string;
using std::getline;
#include <cpuid.h>

#include <boost/compute.hpp>
namespace compute = boost::compute;

#include "Burner.h"
#include "CPUBurner.h"
#include "utils.h"

void init_welcome();
string get_cpu_info();
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
    compute::device device = compute::system::default_device();
    cout << "Welcome to " << BOLDRED << "BurnYourPC" << RESET << '!' << endl
         << "=====|Software|=====" << endl
         << "OS Name:  " << BOLDBLUE << get_os_name() << RESET << endl
         << "Compiler: " << BOLDBLUE << get_compiler() << RESET << endl
         << "=====|Hardware|=====" << endl
         << "CPU:      " << BOLDBLUE << get_cpu_info() << RESET << endl
         << "OpenCL:   " << BOLDBLUE << device.name() << RESET << " by " << BOLDRED << device.vendor() << RESET << " with " << BOLDYELLOW << device.version() << RESET << endl
         << "====================" << endl
         << endl;
}

string get_cpu_info() {
    char CPUBrandString[0x40];
    unsigned int CPUInfo[4] = {0,0,0,0};

    __cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    unsigned int nExIds = CPUInfo[0];

    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
        switch (i) {
            case 0x80000002:
                memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
                break;
            case 0x80000003:
                memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
                break;
            case 0x80000004:
                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
                break;
            default:
                break;
        }
    }
    return CPUBrandString;
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

