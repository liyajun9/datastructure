#ifndef TESTMAXHEAP_ARRAYQUEUE_H
#define TESTMAXHEAP_ARRAYQUEUE_H
#include "queue.h"

namespace lyj
{
template<class T>
class arrayQueue : public queue<T>
{
public:
    explicit arrayQueue(int initialCapacity = 10);
    ~arrayQueue()
    {
        delete [] queue;
    }

    virtual bool empty() const
    {
        return theFront == theBack;
    }

    int size() const
    {
        return (theBack - theFront + arrayLength) % arrayLength;
    }

    virtual T& front() const //return front element
    {
        if (theFront == theBack)
            throw std::exception();
        return queue[(theFront + 1) % arrayLength]; //有可能越到开头了,所以求模
    }

    virtual T& back() const//return back element
    {
        if (theFront == theBack)
            throw std::exception();
        return queue[theBack];
    }

    virtual void pop() //remove theFront element
    {
        if (theFront == theBack)
            throw std::exception();
        theFront = (theFront + 1) % arrayLength;
        queue[theFront].~T();
    }

    virtual void push(const T& theElement);

private:
    int theFront; //当前队首在数组中的索引.position of 1 counterclockwise from theFront element. sentinel.
    int theBack;  //当前队尾在数组中的索引.position of theBack element
    int arrayLength; //queue capacity
    T *queue;   //element array
};

template<class T>
arrayQueue<T>::arrayQueue(int initialCapacity)
{
    if (initialCapacity < 1)
        throw std::exception();

    arrayLength = initialCapacity;
    queue = new T[arrayLength];
    theFront = 0;
    theBack = 0;
}

template<class T>
void arrayQueue<T>::push(const T& theElement)
{
    //increase array length if necessary
    if ((theBack + 1) % arrayLength == theFront)
    {
        //double array length
        T* newQueue = new T[2 * arrayLength];

        //copy elements into new array
        int start = (theFront + 1) % arrayLength;
        if (start < 2)
        {
            //no wrap around
            std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
        }
        else
        {
            //queue wraps around
            std::copy(queue + start, queue + arrayLength, newQueue);
            std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
        }

        //switch to newQueue and set theFront and theBack
        theFront = 2 * arrayLength - 1;
        theBack = arrayLength - 2; //queue size arrayLength - 1
        arrayLength *= 2;
        queue = newQueue;
    }

    //put theElement at the theBack of the queue
    theBack = (theBack + 1) % arrayLength;
    queue[theBack] = theElement;
}

}

#endif //TESTMAXHEAP_ARRAYQUEUE_H
