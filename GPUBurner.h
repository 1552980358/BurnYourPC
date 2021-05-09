#ifndef BURNYOURPC_GPUBURNER_H
#define BURNYOURPC_GPUBURNER_H

#include <string>
using std::string;

#include <boost/compute.hpp>

#include "Burner.h"

class GPUBurner: public Burner {

private:

    boost::compute::device _device{};

    int _compute_unit = 0;

    string _input{};

public:

    explicit GPUBurner(const boost::compute::device&);

    void menu() override;

    void prepare() override;

    void burn() override;

};


#endif //BURNYOURPC_GPUBURNER_H
