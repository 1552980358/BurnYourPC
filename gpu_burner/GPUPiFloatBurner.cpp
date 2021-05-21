#include "GPUPiFloatBurner.h"
#include <vector>
using std::vector;

GPUPiFloatBurner::GPUPiFloatBurner(compute::device &device) : GPUBurnerTask(device) {}

/**
 * struct float_input_struct {
 *     int value{};
 *     int indicator{};
 * };
 **/

/**
 * BOOST_COMPUTE_ADAPT_STRUCT(float_input_struct, float_input_struct, (value, indicator));
 **/

BOOST_COMPUTE_FUNCTION(float, get_pi_float_proc, (int value), {
    return (float) 4 / value;
});

struct pi_struct {
    float pos{};
    float neg{};
};

BOOST_COMPUTE_ADAPT_STRUCT(pi_struct, pi_struct, (pos, neg));

BOOST_COMPUTE_FUNCTION(float, get_pi_out, (pi_struct pi_s), {
    return 4 + pi_s.pos - pi_s.neg;
});

vector<int> *get_pi_float_structs(const int &size);

void GPUPiFloatBurner::prepare() {
    int size = SHRT_MAX;

    auto context = *_context;

    _cpu_input = get_pi_float_structs(size);
    _gpu_input = new compute::vector<int>(size, context);
    _gpu_output = new compute::vector<float>(1, context);
    _cpu_output = new vector<float>(1);

    _gpu_output_proc = new compute::vector<float>(size, context);
    _gpu_input_proc_neg = new compute::vector<float>(context);
    _gpu_input_proc_pos = new compute::vector<float>(context);
    _gpu_output_proc_neg = new compute::vector<float>(size / 2 + 1, context);
    _gpu_output_proc_pos = new compute::vector<float>(size / 2, context);
    _struct_vector = new compute::vector<pi_struct>(context);

    /**
     * auto cpu_input = get_pi_float_structs(_compute_unit);
     * _gpu_input = new compute::vector<float_input_struct>(cpu_input.size(), *_context);
     * compute::copy(cpu_input.begin(), cpu_input.end(), ((vector<float_input_struct> *) _gpu_input)->begin(), *_queue);
     * _gpu_output = new compute::vector<float>(cpu_input.size(), *_context);
     * _cpu_output = new vector<float>(cpu_input.size());
     **/
    GPUBurnerTask::prepare();
}

void GPUPiFloatBurner::burn() {
    auto queue = *_queue;

    auto cpu_input = *((vector<int> *) _cpu_input);
    auto gpu_input = *((compute::vector<int> *) _gpu_input);
    auto gpu_output = *(compute::vector<float> *) _gpu_output;
    auto cpu_output = *(vector<float> *) _cpu_output;

    auto gpu_output_proc = *_gpu_output_proc;

    auto gpu_input_proc_neg = *_gpu_input_proc_neg;
    auto gpu_input_proc_pos = *_gpu_input_proc_pos;
    auto gpu_output_proc_neg = *_gpu_output_proc_neg;
    auto gpu_output_proc_pos = *_gpu_output_proc_pos;

    auto struct_vector = *(compute::vector<pi_struct> *) _struct_vector;

    // Copy
    compute::copy(cpu_input.begin(), cpu_input.end(), gpu_input.begin(), queue);

    // Calculate all procedure values
    compute::transform(
            gpu_input.begin(),
            gpu_input.end(),
            gpu_output_proc.begin(),
            get_pi_float_proc,
            queue
            );

    // Divide into two group
    for (int i = 0; i < cpu_input.size(); ++i) {
        if ((i + 1) % 2 == 1) {
            gpu_input_proc_neg.push_back(gpu_output_proc[i]);
        } else {
            gpu_input_proc_pos.push_back(gpu_output_proc[i]);
        }
    }

    // Calculate addition first
    compute::partial_sum(
            gpu_input_proc_pos.begin(),
            gpu_input_proc_pos.end(),
            gpu_output_proc_pos.begin(),
            queue
            );

    // Calculate subtraction
    compute::partial_sum(
            gpu_input_proc_neg.begin(),
            gpu_input_proc_neg.end(),
            gpu_output_proc_neg.begin(),
            queue
            );

    struct_vector.push_back(pi_struct{ gpu_output_proc_pos.back(), gpu_output_proc_neg.back() });

    compute::transform(
            struct_vector.begin(),
            struct_vector.end(),
            gpu_output.begin(),
            get_pi_out,
            queue
            );

    compute::copy(
            gpu_output.begin(),
            gpu_output.end(),
            cpu_output.begin(),
            queue
            );

    std::cout << cpu_output.back() << std::endl;

    /**
    * compute::transform(
    *        ((compute::vector<float_input_struct> *) _gpu_input)->begin(),
    *        ((compute::vector<float_input_struct> *) _gpu_input)->end(),
    *        ((compute::vector<float> *) _gpu_output)->begin(),
    *        get_pi_float_proc,
    *        *_queue
    * );
    * compute::copy(
    *        ((compute::vector<float> *) _gpu_output)->begin(),
    *        ((compute::vector<float> *) _gpu_output)->end(),
    *        ((vector<float> *) _cpu_output)->begin(),
    *        *_queue
    * );
    **/
    GPUBurnerTask::burn();
}

void GPUPiFloatBurner::recycle() {
    delete (vector<int> *) _cpu_input;
    delete (compute::vector<int> *) _gpu_input;
    delete (compute::vector<float> *) _gpu_output;
    delete (vector<float> *) _cpu_output;
    delete _context;
    delete _queue;

    delete _gpu_output_proc;
    delete _gpu_input_proc_pos;
    delete _gpu_input_proc_neg;
    delete _gpu_output_proc_pos;
    delete _gpu_output_proc_neg;
    delete (vector<pi_struct> *) _struct_vector;

}

vector<int> *get_pi_float_structs(const int &size) {
    auto *inputs = new vector<int>();
    // int i = 0;
    // std::generate(*inputs->begin(), *inputs->end(), [&i]{
    //     return int(2 * i + 1);
    // });
    for (int i = 0; i < size; ++i) {
        inputs->push_back(2 * i + 1);
    }
    return inputs;
}