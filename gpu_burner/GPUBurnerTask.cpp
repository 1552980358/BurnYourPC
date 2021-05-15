#include "GPUBurnerTask.h"

void GPUBurnerTask::prepare() {
    _start_milliseconds = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

void GPUBurnerTask::burn() {

}
