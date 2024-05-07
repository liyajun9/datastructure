#include "maxHeap.h"
#include <iostream>
#include <vector>

void traverseMaxHeap(lyj::maxHeap<int>& theHeap)
{
    auto size = theHeap.size();
    for (auto i = 0; i < size; ++i)
    {
        if (i != 0)
            std::cout << ", ";
        std::cout << theHeap.top();
        theHeap.pop();
    }
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    //initialize
    std::vector<int> origVec = {-1, 3, 5, 6, 7, 20, 8, 2, 9, 12, 15, 30, 17};
    lyj::maxHeap<int> theMaxHeap(16);
    theMaxHeap.initialize(origVec);
    traverseMaxHeap(theMaxHeap);

    //push
    theMaxHeap.initialize(origVec);
    theMaxHeap.push(-4);
    theMaxHeap.push(-8);
    theMaxHeap.push(12);
    theMaxHeap.push(200);
    theMaxHeap.push(-9);
    traverseMaxHeap(theMaxHeap);

    //pop
    theMaxHeap.initialize(origVec);
    theMaxHeap.pop();
    theMaxHeap.pop();
    theMaxHeap.pop();
    traverseMaxHeap(theMaxHeap);
}