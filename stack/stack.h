//
// Created by ralph on 4/26/20.
//

#ifndef DATASTRUCTURE_STACK_H
#define DATASTRUCTURE_STACK_H

#include "../vector/vector.h"
#include <iostream>

template <typename T>
class Stack : public Vector<T>{
public:
    void push(const T& e) {
        this->insert(this->_size, e);
    }

    void push(T&& e ) {
        this->insert(this->_size, std::move(e));
    }

    T pop() {
        return this->remove(this->_size - 1);
    }

    T& top() {
        return (*this)[this->_size - 1];
    }

    const T& top() const {
        return this[0];
    }

};

std::string radixConvert(int num, int radix){
    std::string sNum;
    char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    Stack<char> stack;
    while(num){
        stack.push(digit[num % radix]);
        num /= radix;
    }
    int size = stack.size();
    while(size--){
        sNum.append(1, stack.pop());
    }
    return sNum;
}


#endif //DATASTRUCTURE_STACK_H
