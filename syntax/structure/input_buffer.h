//
// Created by enderqiu on 2018/9/19.
//

#ifndef VSLC_INPUT_BUFFER_H
#define VSLC_INPUT_BUFFER_H

#include <vector>
#include <iostream>

#include "symbol.h"
#include "../../utils/shortcuts.h"


using namespace std;

class InputBuffer {
private:
    vector<Symbol> symbols;
    unsigned long index = 0;
    unsigned long len = 0;
public:
    InputBuffer() = default;
    explicit InputBuffer(vector<Symbol> symbols);
    Symbol present();
    void next();
    bool is$();  // end of input
    void reset();
};


#endif //VSLC_INPUT_BUFFER_H
