#ifndef BURNYOURPC_GPUPIFLOATBURNER_H
#define BURNYOURPC_GPUPIFLOATBURNER_H

#include "GPUBurnerTask.h"

class GPUPiFloatBurner: public GPUBurnerTask {

public:

    explicit GPUPiFloatBurner(compute::device &);

    void prepare() override;

    void burn() override;

    void recycle() override;

};


#endif //BURNYOURPC_GPUPIFLOATBURNER_H
