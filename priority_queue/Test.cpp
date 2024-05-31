#include "maxHeap.h"
#include "maxHblt.h"
#include <iostream>
#include <vector>

//#define TEST_MAXHEAP
#define TEST_MAXHBLT

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
#ifdef TEST_MAXHEAP
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
#endif

#ifdef TEST_MAXHBLT
    lyj::maxHblt<int> h, j;
    int a[6] = {0, 7, 9, 1, 8, 11};
    h.initialize(a, 5);
    std::cout << "One tree in postorder is " << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();

    int b[5] = {0, 2, 6, 4, 9};
    j.initialize(b, 4);
    std::cout << "Other tree in postorder is" << std::endl;
    std::cout << "Tree size is " << j.size() << std::endl;
    j.output();

    h.meld(j);
    std::cout << "After medling, the tree in postorder is" << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();

    int w = h.top();
    h.pop();
    int x = h.top();
    h.pop();
    int y = h.top();
    h.pop();
    int z = h.top();
    h.pop();
    std::cout << "After popping four elements, the tree is" << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();
    std::cout << "The popped elements, in order, are" << std::endl;
    std::cout << w << " " << x << " " << y << " " << z << std::endl;

    h.push(10);
    h.push(20);
    h.push(5);
    std::cout << "After push 10, 20, 5, the tree is" << std::endl;
    std::cout << "Leftist tree in postorder" << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();

    h.push(15);
    h.push(30);
    h.push(2);
    std::cout << "After push 15, 30, 2, the tree is" << std::endl;
    std::cout << "Leftist tree in postorder" << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();

    std::cout << "The max element is " << h.top() << std::endl;

    h.pop();
    std::cout << "Popped max element " << std::endl;
    std::cout << "Leftist tree in postorder" << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();

    x = h.top();
    h.pop();
    std::cout << "Popped max element " << std::endl;
    std::cout << "Leftist tree in postorder" << std::endl;
    std::cout << "Tree size is " << h.size() << std::endl;
    h.output();

    while (true)
    {
        try
        {
            x = h.top();
            h.pop();
            std::cout << "Popped" << x << std::endl;
            std::cout << "Tree size is " << h.size() << std::endl;
        }
        catch(...)
        {
            break;
        }
    }

    return 0;
#endif
}