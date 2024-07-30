#ifndef TESTBINARYTREE_BINARYSEARCHTREEWITHVISIT_H
#define TESTBINARYTREE_BINARYSEARCHTREEWITHVISIT_H
#include "binarySearchTree.h"

namespace lyj
{
    template<class K, class E>
    class binarySearchTreeWithVisit : public binarySearchTree<K, E>
    {
    public:
        using linkedBinaryTree<std::pair<const K, E>>::treeSize;
        using linkedBinaryTree<std::pair<const K, E>>::root;

        void insert(const std::pair<const K, E>&, void(*visit)(E& u));
    };

    //insert thePair into the tree if no matching pair present.
    //visit existing pair, if any, with same key.
    template<class K, class E>
    void binarySearchTreeWithVisit<K, E>::insert(const std::pair<const K, E> &thePair, void (*visit)(E &u))
    {
        binaryTreeNode<std::pair<const K, E>> *p = root,
                                            *pp = 0;

        while (p != NULL)
        {
            pp = p;

            if (thePair.first < p->element.first)
            {
                p = p->leftChild;
            }
            else
            {
                if (thePair.first > p->element.first)
                {
                    p = p->rightChild;
                }
                else
                {
                    visit(p->element.second);
                    return;
                }
            }
        }

        //get a node for thePair and attach to pp
        binaryTreeNode<std::pair<const K, E>> *newNode = new binaryTreeNode<std::pair<const K, E>> (thePair);
        if (root != NULL)
        {
            if (thePair.first < pp->element.first)
            {
                pp->leftChild = newNode;
            }
            else
            {
                pp->rightChild = newNode;
            }
        }
        else
        {
            root = newNode;
        }

        ++treeSize;
    }
}
#endif //TESTBINARYTREE_BINARYSEARCHTREEWITHVISIT_H
