#ifndef TESTMAXHEAP_BINARYTREE_H
#define TESTMAXHEAP_BINARYTREE_H
#include <functional>
#include <iostream>

namespace lyj
{
    template<class T>
    class binaryTree
    {
    public:
        virtual ~binaryTree() {}
        virtual bool empty() const = 0;
        virtual int size() const  = 0;
        virtual void preOrder(void (*) (T*)) = 0;
        virtual void inOrder(void (*) (T*)) = 0;
        virtual void postOrder(void (*) (T*)) = 0;
        virtual void levelOrder(void (*) (T*)) = 0;
    };
}
#endif //TESTMAXHEAP_BINARYTREE_H
