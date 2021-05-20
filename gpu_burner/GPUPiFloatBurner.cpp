#include "GPUPiFloatBurner.h"

#include "GPUPiFloatBurner.h"
#include <vector>
using std::vector;

GPUPiFloatBurner::GPUPiFloatBurner(compute::device &device) : GPUBurnerTask(device) {}

struct pi_float_struct {
    float pi{};
};

BOOST_COMPUTE_ADAPT_STRUCT(pi_float_struct, pi_float_struct, (pi));

BOOST_COMPUTE_FUNCTION(float, get_pi_float, (pi_float_struct var_pi_struct), {
    for (int i = 1; i < INT_MAX; ++i) {
        var_pi_struct.pi += (float) ((i % 2) ? 1 : -1) * (1 / (2 * (float) i + 1));
    }
    return var_pi_struct.pi;
});

vector<pi_float_struct> get_pi_float_structs(const int &size);

void GPUPiFloatBurner::prepare() {
    auto cpu_input = get_pi_float_structs(_compute_unit);
    _gpu_input = new compute::vector<pi_float_struct>(cpu_input.size(), *_context);
    compute::copy(cpu_input.begin(), cpu_input.end(), ((vector<pi_float_struct> *) _gpu_input)->begin(), *_queue);
    _gpu_output = new compute::vector<float>(cpu_input.size(), *_context);
    _cpu_output = new vector<float>(cpu_input.size());
    GPUBurnerTask::prepare();
}

void GPUPiFloatBurner::burn() {
    compute::transform(
            ((compute::vector<pi_float_struct> *) _gpu_input)->begin(),
            ((compute::vector<pi_float_struct> *) _gpu_input)->end(),
            ((compute::vector<float> *) _gpu_output)->begin(),
            get_pi_float,
            *_queue
    );
    compute::copy(
            ((compute::vector<float> *) _gpu_output)->begin(),
            ((compute::vector<float> *) _gpu_output)->end(),
            ((vector<float> *) _cpu_output)->begin(),
            *_queue
    );
    GPUBurnerTask::burn();
}

void GPUPiFloatBurner::recycle() {
    delete (compute::vector<pi_float_struct> *) _gpu_input;
    delete (compute::vector<float> *) _gpu_output;
    delete (vector<float> *) _cpu_output;
    delete _context;
    delete _queue;
}

vector<pi_float_struct> get_pi_float_structs(const int &size) {
    vector<pi_float_struct> pi_structs(size);
    std::generate(pi_structs.begin(), pi_structs.end(), []() {
        return pi_float_struct{ 0 };
    });
    return pi_structs;
}