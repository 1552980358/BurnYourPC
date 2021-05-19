#ifndef BURNYOURPC_BURNER_H
#define BURNYOURPC_BURNER_H

#define BURNER_TYPE_INIT -1

class Burner {

protected:

    int _type = BURNER_TYPE_INIT;

public:

    [[nodiscard]] int get_type() const;

    virtual void menu();

    virtual void prepare() = 0;

    virtual void burn() = 0;

};


#endif //BURNYOURPC_BURNER_H
