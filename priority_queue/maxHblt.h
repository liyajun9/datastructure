#ifndef TESTMAXHEAP_MAXHBLT_H
#define TESTMAXHEAP_MAXHBLT_H
#include "maxPriorityQueue.h"
#include "../binaryTree/linkedBinaryTree.h"

namespace lyj {

template<class T>
class maxHblt : public maxPriorityQueue<T>, public linkedBinaryTree<std::pair<int, T> >
{
public:
    using linkedBinaryTree<std::pair<int, T>>::treeSize;
    using linkedBinaryTree<std::pair<int, T>>::root;
    using linkedBinaryTree<std::pair<int, T>>::postOrder;
    using linkedBinaryTree<std::pair<int, T>>::erase;

    virtual bool empty() const
    {
        return treeSize == 0;
    }

    virtual int size() const
    {
        return treeSize;
    }

    virtual const T& top()
    {
        if (treeSize == 0)
            throw std::exception();
        return root->element.second;
    }

    virtual void pop();

    virtual void push(const T& theElement);

    void initialize(T*, int);

    void meld(maxHblt<T>& theHblt)
    {
        meld(root, theHblt.root);
        treeSize += theHblt.treeSize;
        theHblt.root = NULL;
        theHblt.treeSize = 0;
    }

    void output()
    {
        postOrder(hbltOutput);
        std::cout << std::endl;
    }

private:
    void meld(binaryTreeNode<std::pair<int, T>>* &, binaryTreeNode<std::pair<int, T>>* &);

    static void hbltOutput(binaryTreeNode<std::pair<int, T>> *t)
    {
        std::cout << t->element.second << ' ';
    }

};

//meld 2 maxHblt, return pointer to new root in x
/* recurse route:
 * 1. simplest case:        a node and null. - do not need to update s value after meld since s value is 0
 * 2. the 2nd simplest case:2 nodes without any child(left child is null after meld) - need to update s value to 1 after meld
 *     note: left child wouldn't be null while right child is not null since it's leftist tree's property
 * 3. other case:           s value of x is right child's s value + 1 ?? yes, for leftist property, right child has the short s value
 */
template<class T>
void maxHblt<T>::meld(binaryTreeNode<std::pair<int, T>>* &x, binaryTreeNode<std::pair<int, T>>* &y)
{
    //check empty tree
    if (y == NULL)
        return;

    if (x == NULL)
    {
        x = y;
        return;
    }

    //neither is empty
    //determine the new root before meld, let the max one as it(keep max heap), by convention as left one.
    if (x->element.second < y->element.second)
    {
        std::swap(x, y);
    }

    meld(x->rightChild, y);
    //so right child is not null

    if (x->leftChild == NULL)
    {
        x->leftChild = x->rightChild;
        x->rightChild = NULL;
        x->element.first = 1; //new root's s value is 1 now
    }
    else
    {
        if (x->leftChild->element.first < x->rightChild->element.first)
        {
            std::swap(x->leftChild, x->rightChild);
        }
        x->element.first = x->rightChild->element.first + 1;
    }

}

template<class T>
void maxHblt<T>::push(const T& theElement)
{
    //create tree with one node
    binaryTreeNode<std::pair<int, T>> *q = new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElement)); //s value of leaf node is 1

    //meld q and original tree
    meld(root, q);
    treeSize++;
}

template<class T>
void maxHblt<T>::pop()
{
    if (root == NULL)
        throw std::exception();

    binaryTreeNode<std::pair<int, T>> *left = root->leftChild,
                                      *right = root->rightChild;

    delete root;
    root = left;
    meld(root, right);
    treeSize--;
}

//initialize hblt with theElements[1:theSize+1]
//初始化
//theElement: 待初始化数组, 只取从索引1开始的元素. why? 可能是为了使用maxHeap? maxHeap是由数组实现,且只使用从1开始的元素
//theSize:    要初始化进去的元素个数
template<class T>
void maxHblt<T>::initialize(T *theElements, int theSize)
{
    arrayQueue<binaryTreeNode<std::pair<int, T>> *> q(theSize);
    erase();

    //initialize queue of trees
    for (int i = 1; i <= theSize; i++)
    {
        //create trees with one node each
        q.push(new binaryTreeNode<std::pair<int, T>>(std::pair<int, T>(1, theElements[i])));
    }

    //repeatedly meld from queue
    for (int i = 1; i < theSize; i++)
    {
        //pop and meld two trees from queue
        binaryTreeNode<std::pair<int, T>> *b = q.front();
        q.pop();
        binaryTreeNode<std::pair<int, T>> *c = q.front();
        q.pop();
        meld(b, c);

        //dont forget to put melded tree on queue again
        q.push(b);
    }

    if (theSize > 0)
        root = q.front();
    treeSize = theSize;
}

}
#endif //TESTMAXHEAP_MAXHBLT_H
