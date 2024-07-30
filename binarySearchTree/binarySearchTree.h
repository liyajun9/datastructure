#ifndef TESTBINARYTREE_BINARYSEARCHTREE_H
#define TESTBINARYTREE_BINARYSEARCHTREE_H
#include "bsTree.h"
#include "../binaryTree/linkedBinaryTree.h"

namespace lyj
{
    template<class K, class E>
    class binarySearchTree : public bsTree<K, E>,
                             public linkedBinaryTree<std::pair<const K, E>>
    {
    public:
        using linkedBinaryTree<std::pair<const K, E>>::treeSize;
        using linkedBinaryTree<std::pair<const K, E>>::inOrderOutput;
        using linkedBinaryTree<std::pair<const K, E>>::root;

        //methods of dictionary
        bool empty() const
        {
            return treeSize == 0;
        }

        int size() const
        {
            return treeSize;
        }

        std::pair<const K, E>* find(const K& theKey) const;

        void insert(const std::pair<const K, E>& thePair);

        void erase(const K& theKey);

        //additional method of bsTree
        void ascend()
        {
            inOrderOutput();
        }
    };

    //return pointer to matching pair. return NULL if no matching pair.
    template<class K, class E>
    std::pair<const K, E>* binarySearchTree<K, E>::find(const K &theKey) const
    {
        binaryTreeNode<std::pair<const K, E>> *p = root;
        while (p != NULL)
        {
            if (theKey < p->element.first)
            {
                p = p->leftChild;
            }
            else
            {
                if (theKey > p->element.first)
                {
                    p = p->rightChild;
                }
                else
                {
                    return &p->element;
                }
            }
        }

        return NULL;
    }

    //Insert thePair into the tree. overwrite existing pair, if any, with same key.
    //find place to insert
    template<class K, class E>
    void binarySearchTree<K, E>::insert(const std::pair<const K, E>& thePair)
    {
        binaryTreeNode<std::pair<const K, E>> *p = root,
                                            *pp = NULL;

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
                    p->element.second = thePair.second;
                    return;
                }
            }
        }

        //get a node for thePair and attach to pp
        binaryTreeNode<std::pair<const K, E>> *newNode = new binaryTreeNode<std::pair<const K, E>>(thePair);

        if (root == NULL)
        {
            root = newNode;
        }
        else
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

        ++treeSize;
    }

    //delete the pair, if any, whose key equals theKey
    template<class K, class E>
    void binarySearchTree<K, E>::erase(const K& theKey)
    {
        //search for node with key theKey
        binaryTreeNode<std::pair<const K, E>> *p = root,    //target node to be deleted
                                            *pp = NULL;     //it's parent

        while (p != NULL && p->element.first != theKey)
        {
            pp = p;
            if (theKey < p->element.first)
            {
                p = p->leftChild;
            }
            else
            {
                p = p->rightChild;
            }
        }

        if (p == NULL)
            return;

        //2 children. convert to zero or one child case
        //find the largest element in left subtree of p
        if (p->leftChild != NULL && p->rightChild != NULL)
        {
            binaryTreeNode<std::pair<const K, E>> *s = p->leftChild,    //trace the largest element in left subtree
                                                *ps = p;                //parent of s
            while (s->rightChild != NULL)
            {
                ps = s;
                s = s->rightChild;
            }

            //move the largest from s to p, can't do a simple move
            //p->element = s->element as key is const

            //create the new node for the largest node in the left subtree
            binaryTreeNode<std::pair<const K, E>> *q = new binaryTreeNode<std::pair<const K, E>>(s->element, p->leftChild, p->rightChild);

            //place the new node at the position of the target node
            if (pp == NULL)
            {
                root = q;
            }
            else if (p == pp->leftChild)
            {
                pp->leftChild = q;
            }
            else
            {
                pp->rightChild = q;
            }

            //update pp
            if (ps == p)
            {
                pp = q;
            }
            else
            {
                pp = ps;
            }

            //delete the old p, and let the s to be the new p. remark: now q and p both hold the element of the largest node in the left subtree. what need to do next is deleting p.
            //it's converted to the one child case
            delete p;
            p = s;
        }

        // p has at most one child
        //save child pointer in c
        binaryTreeNode<std::pair<const K, E>> *c;
        if (p->leftChild != NULL)
        {
            c = p->leftChild;
        }
        else
        {
            c = p->rightChild;
        }

        //delete p
        if (p == root)
        {
            root  = c;
        }
        else
        {
            if (p == pp->leftChild)
            {
                pp->leftChild = c;
            }
            else
            {
                pp->rightChild = c;
            }
        }

        --treeSize;
        delete p;
    }

}


#endif //TESTBINARYTREE_BINARYSEARCHTREE_H
