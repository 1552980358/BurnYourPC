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

struct pi_double_struct {
    double pi{};
};

auto get_pi_double_structs(const int &size) {
    vector<pi_double_struct> structs(size);
    std::generate(structs.begin(), structs.end(), []() {
        return pi_double_struct{ 0 };
    });
    return structs;
}

BOOST_COMPUTE_ADAPT_STRUCT(pi_double_struct, pi_double_struct, (pi));

BOOST_COMPUTE_FUNCTION(double, get_pi_double, (pi_double_struct var_pi_struct), {
            for (int i = 1; i < INT_MAX; ++i) {
                var_pi_struct.pi += (double) ((i % 2) ? 1 : -1) * (1 / (2 * (double) i + 1));
            }
            return var_pi_struct.pi;
        });

void cal_pi_double(boost::compute::context &context, boost::compute::command_queue &queue, const int compute_unit) {
    vector<pi_double_struct> cpu_structs = get_pi_double_structs(compute_unit);
    boost::compute::vector<pi_double_struct> gpu_structs(cpu_structs.size(), context);
    boost::compute::copy(cpu_structs.begin(), cpu_structs.end(), gpu_structs.begin(), queue);
    boost::compute::vector<double> gpu_pi(cpu_structs.size(), context);
    boost::compute::transform(gpu_structs.begin(), gpu_structs.end(), gpu_pi.begin(), get_pi_double, queue);
    vector<double> cpu_pi(gpu_pi.size());
    boost::compute::copy(gpu_pi.begin(), gpu_pi.end(), cpu_pi.begin(), queue);
}

void GPUBurner::burn() {

    if (_input != "YES") {
        return;
    }

    boost::compute::context context(_device);
    boost::compute::command_queue queue(context, _device);

    milliseconds milliseconds_start = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    cal_pi_double(context, queue, (int) _device.compute_units());

    milliseconds milliseconds_stop = duration_cast< milliseconds >(system_clock::now().time_since_epoch());

    cout << "Time spend: " << milliseconds_stop.count() - milliseconds_start.count() << " ms." << endl;

}


