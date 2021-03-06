#include "GPUBurnerTask.h"

GPUBurnerTask::GPUBurnerTask(compute::device &device) {
    _context = new compute::context(device);
    _queue = new compute::command_queue(*_context, device);
    _compute_unit = (int) device.compute_units();
}

void GPUBurnerTask::prepare() {
    _start_milliseconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

void GPUBurnerTask::burn() {
    _end_milliseconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

long long GPUBurnerTask::get_time_spend_milliseconds() {
    return  _end_milliseconds.count() - _start_milliseconds.count();
}
