#include "Burner.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

void Burner::menu() {
    cout << "===============================" << endl
         << "$> ";
    string input;
    getline(cin, input);
    if (input.empty()) {
        return;
    }
    _type = input[0] - 48;
}

void Burner::prepare() {
    cout << "<Press any key to continue...>";
    getchar();
}

int Burner::get_type() const {
    return _type;
}
