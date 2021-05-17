#include "GPUPiDoubleBurner.h"
#include <vector>
using std::vector;

GPUPiDoubleBurner::GPUPiDoubleBurner(compute::device &device) : GPUBurnerTask(device) {}

struct pi_double_struct {
    double pi{};
};

vector<pi_double_struct> get_pi_double_structs(const int &size);

void GPUPiDoubleBurner::prepare() {
    auto cpu_input = get_pi_double_structs(_compute_unit);
    _gpu_input = new compute::vector<pi_double_struct>(cpu_input.size(), *_context);
    compute::copy(cpu_input.begin(), cpu_input.end(), ((vector<pi_double_struct> *) _gpu_input)->begin(), *_queue);
    _gpu_output = new compute::vector<double>(cpu_input.size(), *_context);
    _cpu_output = new vector<double>(cpu_input.size());
    GPUBurnerTask::prepare();
}

void GPUPiDoubleBurner::burn() {
    GPUBurnerTask::burn();
}

void GPUPiDoubleBurner::recycle() {

}

vector<pi_double_struct> get_pi_double_structs(const int &size) {
    vector<pi_double_struct> pi_structs(size);
    std::generate(pi_structs.begin(), pi_structs.end(), []() {
        return pi_double_struct{ 0 };
    });
    return pi_structs;
}