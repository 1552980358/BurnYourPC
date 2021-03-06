#ifndef BURNYOURPC_GPUBURNERTASK_H
#define BURNYOURPC_GPUBURNERTASK_H

#include <chrono>
using namespace std::chrono;

#include <boost/compute.hpp>

namespace compute = boost::compute;

class GPUBurnerTask {

private:

    milliseconds _start_milliseconds{};

    milliseconds _end_milliseconds{};

protected:

    void *_cpu_input = nullptr;

    void *_gpu_input = nullptr;

    void *_cpu_output = nullptr;

    void *_gpu_output = nullptr;

    compute::command_queue *_queue = nullptr;

    compute::context *_context = nullptr;

    int _compute_unit{};

public:

    explicit GPUBurnerTask(compute::device &);

    virtual void prepare();

    virtual void burn();

    virtual void recycle() = 0;

    long long get_time_spend_milliseconds();

};


#endif //BURNYOURPC_GPUBURNERTASK_H
