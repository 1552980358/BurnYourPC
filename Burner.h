#ifndef BURNYOURPC_BURNER_H
#define BURNYOURPC_BURNER_H


class Burner {

public:

    virtual void menu() = 0;

    virtual void prepare() = 0;

    virtual void burn() = 0;

};


#endif //BURNYOURPC_BURNER_H
