#include "FibonacciNode.h"
#include "FibonacciHeap.h"

int main(int argc, char** argv)
{
    std::cout << "Creating an initial heap" << std::endl;
    lyj::FibonacciHeap<int> *fh = new lyj::FibonacciHeap<int>();
    fh->insert(5);
    fh->insert(2);
    fh->insert(8);
    fh->display();

    std::cout << "Extracting the minimum node" << std::endl;
    fh->extractMin();
    fh->display();

    std::cout << "Decreasing value of 8 to 7" << std::endl;
    fh->findAndDecreaseKey(fh->getMin(), 8, 7);
    fh->display();

    std::cout << "Deleting the node with value 7" << std::endl;
    fh->del(7);
    fh->display();

}