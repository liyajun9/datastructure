#include "rbTree.h"

int main(int argc, char** argv)
{
    lyj::rbTree<int> rbtree;

    rbtree.insert(7);
    rbtree.insert(3);
    rbtree.insert(18);
    rbtree.insert(10);
    rbtree.insert(22);
    rbtree.insert(8);
    rbtree.insert(11);
    rbtree.insert(26);
    rbtree.insert(2);
    rbtree.insert(6);
    rbtree.insert(24);
    rbtree.insert(1);
    rbtree.insert(0);

    rbtree.printTree();

    std::cout << "After deleting 18:" << std::endl;
    rbtree.remove(18);
    rbtree.printTree();

    std::cout << "After deleting 11:" << std::endl;
    rbtree.remove(11);
    rbtree.printTree();

    std::cout << "After deleting 26:" << std::endl;
    rbtree.remove(26);
    rbtree.printTree();

    std::cout << "After deleting 8:" << std::endl;
    rbtree.remove(8);
    rbtree.printTree();

    std::cout << "After deleting 3:" << std::endl;
    rbtree.remove(3);
    rbtree.printTree();
}