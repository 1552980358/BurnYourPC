#ifndef BURNYOURPC_CPUBURNER_H
#define BURNYOURPC_CPUBURNER_H

#include <pthread.h>
#include "Burner.h"

class CPUBurner: public Burner {

private:
    int _cpu_max_thread = 0;
    pthread_t *_threads = nullptr;

public:

    CPUBurner();

    void burn() override;

    void menu() override;

    void prepare() override;

};

#endif //BURNYOURPC_CPUBURNER_H
