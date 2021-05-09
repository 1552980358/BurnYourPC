#ifndef BURNYOURPC_CPUBURNER_H
#define BURNYOURPC_CPUBURNER_H

#include <pthread.h>
#include "Burner.h"

class CPUBurner: public Burner {

private:
    int _cpu_max_thread = 0;
    pthread_t *_threads = nullptr;

    int _type = 0;

public:

    CPUBurner();

    void burn() override;

    void menu() override;

    void prepare() override;

    [[nodiscard]] int get_type() const;

};

#endif //BURNYOURPC_CPUBURNER_H
