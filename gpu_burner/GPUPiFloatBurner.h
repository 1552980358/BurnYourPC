#ifndef BURNYOURPC_GPUPIFLOATBURNER_H
#define BURNYOURPC_GPUPIFLOATBURNER_H

#include "GPUBurnerTask.h"

class GPUPiFloatBurner: public GPUBurnerTask {

private:

    compute::vector<float> *_gpu_output_proc = nullptr;

    compute::vector<float> *_gpu_input_proc_pos = nullptr;

    compute::vector<float> *_gpu_input_proc_neg = nullptr;

    compute::vector<float> *_gpu_output_proc_pos = nullptr;

    compute::vector<float> *_gpu_output_proc_neg = nullptr;

    void *_struct_vector = nullptr;

public:

    explicit GPUPiFloatBurner(compute::device &);

    void prepare() override;

    void burn() override;

    void recycle() override;

};

#endif //BURNYOURPC_GPUPIFLOATBURNER_H
