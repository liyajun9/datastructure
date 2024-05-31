#include "linkedBinaryTree.h"
#include <iostream>

#define TEST_LINKEDBINARYTREE

int main(void)
{
#ifdef TEST_LINKEDBINARYTREE
    lyj::linkedBinaryTree<int> a,x,y,z;
    y.makeTree(1, a, a);
    z.makeTree(2, a, a);
    x.makeTree(3, y, z);
    y.makeTree(4, x, a);

    std::cout << "Number of nodes = ";
    std::cout << y.size() << std::endl;

    std::cout << "height = ";
    std::cout << y.height() << std::endl;

    std::cout << "Preorder sequence is " << std::endl;
    y.preOrderOutput();

    std::cout << "Inorder sequence is " << std::endl;
    y.inOrderOutput();

    std::cout << "Postorder sequence is " << std::endl;
    y.postOrderOutput();

    std::cout << "Levelorder sequence is " << std::endl;
    y.levelOrderOutput();
#endif

    return 0;
}