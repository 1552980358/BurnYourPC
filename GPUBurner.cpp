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

#include <boost/compute.hpp>

#include "utils.h"

GPUBurner::GPUBurner(const boost::compute::device& device) {
    _device = device;
    _compute_unit = (int) device.compute_units();
}

void GPUBurner::menu() {
#ifdef WINDOWS_SYSTEM
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WIN_CONSOLE_BOLDRED);
#else
    cout << LINUX_TERMINAL_BOLDRED;
#endif
    cout << "This test is still in development. Running will be DANGEROUS!" << endl;
#ifdef WINDOWS_SYSTEM
    SetConsoleTextAttribute(hConsole, WIN_CONSOLE_RESET);
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

struct pi_struct {
    double pi{};
};

auto make_pi_structs(int size) {
    vector<pi_struct> structs(size);
    std::generate(structs.begin(), structs.end(), []() {
        return pi_struct{ 0 };
    });
    return structs;
}

BOOST_COMPUTE_ADAPT_STRUCT(pi_struct, pi_struct, (pi));

BOOST_COMPUTE_FUNCTION(double, get_pi, (pi_struct var_pi_struct), {
            for (int i = 1; i < INT_MAX; ++i) {
                var_pi_struct.pi += (double) ((i % 2) ? 1 : -1) * (1 / (2 * (double) i + 1));
            }
            return var_pi_struct.pi;
        });

void GPUBurner::burn() {

    if (_input != "YES") {
        return;
    }

    boost::compute::context context(_device);
    boost::compute::command_queue queue(context, _device);

    vector<pi_struct> cpu_structs = make_pi_structs(_compute_unit);
    boost::compute::vector<pi_struct> gpu_structs(cpu_structs.size(), context);
    boost::compute::copy(cpu_structs.begin(), cpu_structs.end(), gpu_structs.begin(), queue);
    boost::compute::vector<double> gpu_pi(cpu_structs.size(), context);
    boost::compute::transform(gpu_structs.begin(), gpu_structs.end(), gpu_pi.begin(), get_pi, queue);
    vector<double> cpu_pi(gpu_pi.size());
    boost::compute::copy(gpu_pi.begin(), gpu_pi.end(), cpu_pi.begin(), queue);

}


