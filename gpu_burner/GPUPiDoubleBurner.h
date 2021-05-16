#ifndef BURNYOURPC_GPUPIDOUBLEBURNER_H
#define BURNYOURPC_GPUPIDOUBLEBURNER_H

#include "GPUBurnerTask.h"

class GPUPiDoubleBurner: public GPUBurnerTask {

public:

    explicit GPUPiDoubleBurner(compute::device &);

    void prepare() override;

    void burn() override;

    void recycle() override;

};


#endif //BURNYOURPC_GPUPIDOUBLEBURNER_H
