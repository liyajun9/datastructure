#ifndef TESTMAXHEAP_QUEUE_H
#define TESTMAXHEAP_QUEUE_H
#include <iostream>

namespace lyj
{
    template<class T>
    class queue
    {
    public:
        virtual ~queue() {}
        virtual bool empty() const  = 0;
        virtual int size() const = 0;
        virtual T& front() const = 0;
        virtual T& back() const  = 0;
        virtual void pop() = 0;
        virtual void push(const T& theElement) = 0;
    };
}

#endif //TESTMAXHEAP_QUEUE_H
