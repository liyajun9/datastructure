#ifndef TESTMAXHEAP_BINARYTREENODE_H
#define TESTMAXHEAP_BINARYTREENODE_H
#include <iostream>

namespace lyj {
    template <class T> struct binaryTreeNode
    {
        T element;
        binaryTreeNode<T> *leftChild,   //left subtree
                          *rightChild;  //right subtree

        binaryTreeNode()
        {
            leftChild = rightChild = NULL;
        }

        binaryTreeNode(const T& theElement) : element(theElement)
        {
            leftChild = rightChild = NULL;
        }

        binaryTreeNode(const T& theElement,
                       binaryTreeNode *theLeftChild,
                       binaryTreeNode *theRightChild) : element(theElement)
        {
            leftChild = theLeftChild;
            rightChild = theRightChild;
        }
    };
}
#endif //TESTMAXHEAP_BINARYTREENODE_H
