#ifndef TESTFIBONACCI_FIBONACCIHEAP_H
#define TESTFIBONACCI_FIBONACCIHEAP_H
#include "FibonacciNode.h"
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

namespace lyj
{
    template<class T>
    class FibonacciHeap
    {
    public:
        FibonacciHeap()
                : minNode(nullptr), numOfNodes(0)
        {
        }

        ~FibonacciHeap()
        {
        }

        void insert(T val);
        void fibonacciLink(FibonacciNode<T> *biggerNode, FibonacciNode<T> *smallerNode);
        void extractMin();
        void consolidate();
        void cut(FibonacciNode<T> *node, FibonacciNode<T> *parentNode);
        void cascadingCut(FibonacciNode<T> *node);
        void decreaseKey(FibonacciNode<T> *found, T val);
        void findAndDecreaseKey(FibonacciNode<T> *min, T oldVal, T newVal);
        void del(T val);

        void display();
        FibonacciNode<T>* getMin()
        {
            return minNode;
        }

    private:
        FibonacciNode<T> *minNode;
        int numOfNodes;
    };

    template<class T>
    void FibonacciHeap<T>::display()
    {
        if (minNode == NULL)
        {
            std::cout << "The heap is empty" << std::endl;
            return;
        }

        std::cout << "The root nodes of the heap are: ";
        FibonacciNode<T> *curNode = minNode;
        do {
            std::cout << curNode->data << " ";
            curNode = curNode->right;
        } while (curNode != minNode);

        std::cout << std::endl;
        std::cout << "The heap has " << numOfNodes << " nodes. " << std::endl;
    }

    template<class T>
    void FibonacciHeap<T>::del(T val)
    {
        if (minNode == NULL)
        {
            std::cout << "The heap is empty" << std::endl;
            return;
        }

        findAndDecreaseKey(minNode, val, INT32_MIN); //works only for int?
        extractMin();
        std::cout << "Node deleted" << std::endl;
    }

    //Find a node with a specific key and decrease its value
    template<class T>
    void FibonacciHeap<T>::findAndDecreaseKey(FibonacciNode<T> *curNode, T oldVal, T newVal)
    {
        if (curNode == NULL)
        {
            return;
        }

        curNode->visited == 'Y';
        if (curNode->data == oldVal)
        {
            decreaseKey(curNode, newVal);
        }

        // also find in child
        if (curNode->child != NULL)
        {
            findAndDecreaseKey(curNode->child, oldVal, newVal);
        }

        if (curNode->right->visited != 'Y')
        {
            findAndDecreaseKey(curNode->right, oldVal, newVal);
        }

        curNode->visited = 'N';
    }

    //decrease the key value of a node
    template<class T>
    void FibonacciHeap<T>::decreaseKey(FibonacciNode<T> *node, T val)
    {
        if (node == NULL)
        {
            std::cout << "Node not found" << std::endl;
            return;
        }

        node->data = val;
        FibonacciNode<T> *parentNode = node->parent;
        if (parentNode != NULL && node->data < parentNode->data)
        {
            cut(node, parentNode);
            cascadingCut(parentNode);
        }

        if (node->data < minNode->data)
        {
            minNode = node;
        }
    }

    //cascading cut to ensure that parent nodes lose a child only once
    template<class T>
    void FibonacciHeap<T>::cascadingCut(FibonacciNode<T> *node)
    {
        FibonacciNode<T>  *parentNode = node->parent;
        if (parentNode != NULL)
        {
            if (node->mark == 'W')
            {
                node->mark = 'B';
            }
            else //cut only nodes which are not in rootList and colored black
            {
                cut(node, parentNode);
                cascadingCut(parentNode);
            }
        }
    }

    // cut a node from its parent and move it to the root list
    template<class T>
    void FibonacciHeap<T>::cut(FibonacciNode<T> *node, FibonacciNode<T> *parentNode)
    {
        if (node->right == node)
        {
            parentNode->child = nullptr;
        }
        else
        {
            node->left->right = node->right;
            node->right->left = node->left;
            if (parentNode->child == node)
            {
                parentNode->child = node->right;
            }
        }

        parentNode->degree--;

        //insert to left of minNode
        node->left = minNode->left;
        node->right = minNode;
        minNode->left->right = node;
        minNode->left = node;

        node->parent = NULL;
        node->mark = 'W'; //?what for
    }

    template<class T>
    void FibonacciHeap<T>::consolidate()
    {
        int maxDegree = static_cast<int>(log2(numOfNodes)) + 1;
        std::vector<FibonacciNode<T>*> degreeTable(maxDegree, NULL);

        std::vector<FibonacciNode<T>*> rootList;
        FibonacciNode<T>* currentNode = minNode;
        do
        {
            rootList.push_back(currentNode) ;
            currentNode = currentNode->right;
        } while (currentNode != minNode);

        for (auto it = rootList.begin(); it != rootList.end(); ++it)
        {
            int degree = (*it)->degree;
            while (degreeTable[degree] != NULL)
            {
                FibonacciNode<T>* otherNode = degreeTable[degree];
                if (otherNode->data < (*it)->data) //make the smaller be the child
                {
                    std::swap(*it, otherNode);
                }
                fibonacciLink(otherNode, *it);
                degreeTable[degree] = NULL;

                //degree of root increase by 1, also need to check unicity
                ++degree;
            }

            degreeTable[degree] = *it;
        }

        //update the minNode
        for (auto it = degreeTable.begin(); it != degreeTable.end(); ++it)
        {
            if (*it != NULL
                && (minNode == NULL || (*it)->data < minNode->data))
            {
                minNode = *it;
            }
        }

    }

    template<class T>
    void FibonacciHeap<T>::extractMin()
    {
        if (minNode == NULL)
        {
            std::cout << "The heap is empty" << std::endl;
            return;
        }

        // move all children of minNode to rootList
        FibonacciNode<T>* extractedNode = minNode;
        if (extractedNode->child != NULL)
        {
            FibonacciNode<T>* child = extractedNode->child;
            do
            {
                FibonacciNode<T> *nextChild = child->right;
                minNode->left->right = child;
                child->right = minNode;
                child->left = minNode->left;
                minNode->left = child;
                child->parent = nullptr;
                child = nextChild;
            } while(child != extractedNode->child);
        }

        // remove from rootList
        extractedNode->left->right = extractedNode->right;
        extractedNode->right->left = extractedNode->left;

        if (extractedNode == extractedNode->right)
        {
            minNode = NULL;
        }
        else
        {
            minNode = extractedNode->right;
            consolidate();
        }

        numOfNodes--;
        delete extractedNode;
    }

    template<class T>
    void FibonacciHeap<T>::fibonacciLink(FibonacciNode<T> *biggerNode, FibonacciNode<T> *smallerNode)
    {
        biggerNode->left->right = smallerNode->right;
        biggerNode->right->left = smallerNode->left;

        biggerNode->parent = smallerNode;
        if (smallerNode->child == NULL)
        {
            smallerNode->child = biggerNode;
            biggerNode->right = biggerNode;
            biggerNode->left = biggerNode;
        }
        else //insert to left. why?
        {
            biggerNode->right = smallerNode->child;
            biggerNode->left = smallerNode->child->left;
            smallerNode->child->left->right = biggerNode;
            smallerNode->child->left = biggerNode;
        }

        smallerNode->degree++;
        biggerNode->mark = 'W'; //for what?
    }

    template<class T>
    void FibonacciHeap<T>::insert(T key)
    {
        FibonacciNode<T> *node = new FibonacciNode<T>(key);

        if (minNode == NULL)
        {
            minNode = node;
        }
        else
        {
            // insert to left
            (minNode->left)->right = node;
            minNode->left = node;
            node->left = minNode->left;
            node->right = minNode;

            if (node->data < minNode->data)
            {
                minNode = node;
            }
        }

        ++numOfNodes;
    }
}


#endif //TESTFIBONACCI_FIBONACCIHEAP_H
