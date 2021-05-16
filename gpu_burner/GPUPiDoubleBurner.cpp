#include "GPUPiDoubleBurner.h"


GPUPiDoubleBurner::GPUPiDoubleBurner(compute::device &device) : GPUBurnerTask(device) {}

void GPUPiDoubleBurner::prepare() {
    GPUBurnerTask::prepare();
}

void GPUPiDoubleBurner::burn() {
    GPUBurnerTask::burn();
}

void GPUPiDoubleBurner::recycle() {

}
