#ifndef TESTMAXHEAP_CHANGELENGTH1D_H
#define TESTMAXHEAP_CHANGELENGTH1D_H
#include <iostream>
#include <exception>

namespace lyj
{
    template<class T>
    void changeLength1D(T*& a, int oldLength, int newLength)
    {
        if (newLength < 0)
            throw std::exception();

        T* temp = new T[newLength];
        int number = std::min(oldLength, newLength);
        copy(a, a + number, temp);
        delete [] a;
        a = temp;
    }
}
#endif //TESTMAXHEAP_CHANGELENGTH1D_H
