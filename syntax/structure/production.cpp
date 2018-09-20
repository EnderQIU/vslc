//
// Created by enderqiu on 2018/9/19.
//

#include <utility>
#include <cstdarg>
#include <iostream>

#include "production.h"

using namespace std;

Production::Production(Symbol left, vector<Symbol> right) {
    this->left = std::move(left);
    this->right = std::move(right);
}

void Production::display() {
    cout<<this->left.getDisplay()<<" -> ";
    for(Symbol s: this->right) cout<<s.getDisplay();
    cout<<endl;
}
