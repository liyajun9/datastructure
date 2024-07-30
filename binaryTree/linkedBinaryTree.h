#ifndef TESTMAXHEAP_LINKEDBINARYTREE_H
#define TESTMAXHEAP_LINKEDBINARYTREE_H
#include <iostream>
#include "binaryTree.h"
#include "../queue/arrayQueue.h"
#include "binaryTreeNode.h"
//#include <booster>

template<class K, class E>
std::ostream& operator<<(std::ostream& out, const std::pair<K, E>& x)
{
    out << x.first << " " << x.second;
    return out;
}

namespace lyj
{
    template<class T>
    class linkedBinaryTree : public binaryTree<binaryTreeNode<T>>
    {
    public:
        linkedBinaryTree()
        {
            root = NULL;
            treeSize = 0;
        }

        ~linkedBinaryTree()
        {
            erase();
        }

        bool empty() const
        {
            return treeSize == 0;
        }

        int size() const
        {
            return treeSize;
        }

        T* rootElement() const
        {
            if (treeSize == 0)
                return NULL;
            else
                return &root->element;
        }

        void makeTree(const T& element, linkedBinaryTree<T>& left, linkedBinaryTree<T>& right)
        {
            root = new binaryTreeNode<T>(element, left.root, right.root);
            treeSize = left.treeSize + right.treeSize + 1;

            //deny access from trees left and right
            left.root = right.root = NULL;
            left.treeSize = right.treeSize = 0;
        }

        linkedBinaryTree<T>& removeLeftSubtree()
        {
            if (treeSize == 0)
                throw std::exception();

            //detach the left subtree and save in leftSubtree
            linkedBinaryTree<T> leftSubtree;
            leftSubtree.root = root->leftChild;
            count = 0;
            leftSubtree.treeSize = CountNodes(leftSubtree.root);
            root->leftChild = NULL;
            treeSize -= leftSubtree.treeSize;

            return leftSubtree;
        }

        linkedBinaryTree<T>& removeRightSubtree()
        {
            if (treeSize == 0)
                throw std::exception();

            //detach the right subtree and save in rightSubtree
            linkedBinaryTree<T> rightSubtree;
            rightSubtree.root = root->rightChild;
            count = 0;
            rightSubtree.treeSize = CountNodes(rightSubtree.root);
            root->rightChild = NULL;
            treeSize -= rightSubtree.treeSize;

            return rightSubtree;
        }

        // traverse with custom function
        void preOrder(void(*theVisit)(binaryTreeNode<T>*))
        {
            visit = theVisit;
            preOrder(root);
        }
        void inOrder(void(*theVisit)(binaryTreeNode<T>*))
        {
            visit = theVisit;
            inOrder(root);
        }
        void postOrder(void(*theVisit)(binaryTreeNode<T>*))
        {
            visit = theVisit;
            postOrder(root);
        }

        void levelOrder(void(*theVisit)(binaryTreeNode<T>*))
        {
            arrayQueue<binaryTreeNode<T>*> q;
            binaryTreeNode<T> *t = root;
            while (t != NULL)
            {
                theVisit(t); //visit t

                //put t's children on queue
                if (t->leftChild != NULL)
                    q.push(t->leftChild);
                if (t->rightChild != NULL)
                    q.push(t->rightChild);

                //get next node to visit
                try {
                    t = q.front();
                }
                catch(...)
                {
                    return;
                }
                q.pop();
            }
        }

        //traverse with static member output
        void preOrderOutput()
        {
            preOrder(output);
            std::cout << std::endl;
        }

        void inOrderOutput()
        {
            inOrder(output);
            std::cout << std::endl;
        }

        void postOrderOutput()
        {
            postOrder(output);
            std::cout << std::endl;
        }

        void levelOrderOutput()
        {
            levelOrder(output);
            std::cout << std::endl;
        }

        void erase()
        {
            postOrder(dispose);
            root = NULL;
            treeSize = 0;
        }

        int height() const
        {
            return height(root);
        }

    protected:
        binaryTreeNode<T> *root;    //pointer to root
        int treeSize;               //number of nodes in tree

        static void (*visit)(binaryTreeNode<T>*); //visit function
        static int count;           //used to count nodes in a subtree
        static void preOrder(binaryTreeNode<T> *t)
        {
            if (t != NULL)
            {
                linkedBinaryTree<T>::visit(t);
                preOrder(t->leftChild);
                preOrder(t->rightChild);
            }
        }
        static void inOrder(binaryTreeNode<T> *t)
        {
            if (t != NULL)
            {
                inOrder(t->leftChild);
                linkedBinaryTree<T>::visit(t);
                inOrder(t->rightChild);
            }
        }
        static void postOrder(binaryTreeNode<T> *t)
        {
            if (t != NULL)
            {
                postOrder(t->leftChild);
                postOrder(t->rightChild);
                linkedBinaryTree<T>::visit(t);
            }

        }

        static void CountNodes(binaryTreeNode<T> *t)
        {
            visit = addToCount;
            count = 0;
            preOrder(t);
        }
        static void dispose(binaryTreeNode<T> *t)
        {
            delete t;
        }
        static void output(binaryTreeNode<T> *t)
        {
            std::cout << t->element << ' ' << std::endl;
        }
        static void addToCount(binaryTreeNode<T> *t)
        {
            count++;
        }
        static int height(binaryTreeNode<T> *t)
        {
            if (t == NULL)
                return 0;

            int hl = height(t->leftChild); //height of left
            int hr = height(t->rightChild);//height of right
            if (hl > hr)
                return ++hl;
            else
                return ++hr;
        }
    };

    //    template<typename T>
//    void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*) = linkedBinaryTree<T>::output;
    template<typename T>
    void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*) = nullptr;

    //以下应该是可行的,但提示内部编译器错误template<T> void (*linkedBinaryTree<T>::visit)(binaryTreeNode<T>*)
//    template<> void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
//    void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<int>*);
//    template<> void (*linkedBinaryTree<std::pair<int, int>>::visit)(binaryTreeNode<std::pair<int, int>>*);
//    template<> void (*linkedBinaryTree<std::pair<const int, char>>::visit)(binaryTreeNode<std::pair<const int, char>>*);
//    template<> void (*linkedBinaryTree<std::pair<const int, int>>::visit)(binaryTreeNode<std::pair<const int, int>>*);


    //return null if no root.otherwise, return pointer to a root element
//    template<class T>
//    T* linkedBinaryTree<T>::rootElement() const
//    {
//        if (treeSize == 0)
//            return NULL;
//        else
//            return &root->element;
//    }

    //combine left, right, and element to make new tree.
    //left, right, and this must be different trees
    //create combined tree
//    template<class T>
//    void linkedBinaryTree<T>::makeTree(const T &element, linkedBinaryTree<T> &left, linkedBinaryTree<T> &right)
//    {
//        root = new binaryTreeNode<T>(element, left.root, right.root);
//        treeSize = left.treeSize + right.treeSize + 1;
//
//        //deny access from trees left and right
//        left.root = right.root = NULL;
//        left.treeSize = right.treeSize = 0;
//    }

    //remove and return the left subtree
//    template<class T>
//    linkedBinaryTree<T>& linkedBinaryTree<T>::removeLeftSubtree()
//    {
//        if (treeSize == 0)
//            throw std::exception();
//
//        //detach the left subtree and save in leftSubtree
//        linkedBinaryTree<T> leftSubtree;
//        leftSubtree.root = root->leftChild;
//        count = 0;
//        leftSubtree.treeSize = CountNodes(leftSubtree.root);
//        root->leftChild = NULL;
//        treeSize -= leftSubtree.treeSize;
//
//        return leftSubtree;
//    }

    //remove and return the right subtree
//    template<class T>
//    linkedBinaryTree<T>& linkedBinaryTree<T>::removeRightSubtree()
//    {
//        if (treeSize == 0)
//            throw std::exception();
//
//        //detach the right subtree and save in rightSubtree
//        linkedBinaryTree<T> rightSubtree;
//        rightSubtree.root = root->rightChild;
//        count = 0;
//        rightSubtree.treeSize = CountNodes(rightSubtree.root);
//        root->rightChild = NULL;
//        treeSize -= rightSubtree.treeSize;
//
//        return rightSubtree;
//    }

    //Preorder traversal
//    template<class T>
//    void linkedBinaryTree<T>::preOrder(binaryTreeNode<T> *t)
//    {
//        if (t != NULL)
//        {
//            linkedBinaryTree<T>::visit(t);
//            preOrder(t->leftChild);
//            preOrder(t->rightChild);
//        }
//    }

    //Inorder traversal
//    template<class T>
//    void linkedBinaryTree<T>::inOrder(binaryTreeNode<T> *t)
//    {
//        if (t != NULL)
//        {
//            inOrder(t->leftChild);
//            linkedBinaryTree<T>::visit(t);
//            inOrder(t->rightChild);
//        }
//    }

    //Postorder traversal
//    template<class T>
//    void linkedBinaryTree<T>::postOrder(binaryTreeNode<T> *t)
//    {
//        if (t != NULL)
//        {
//            postOrder(t->leftChild);
//            preOrder(t->rightChild);
//            linkedBinaryTree<T>::visit(t);
//        }
//    }

    //Left-order traversal
//    template <class T>
//    void linkedBinaryTree<T>::levelOrder(void (*theVisit)(binaryTreeNode<T> *))
//    {
//        arrayQueue<binaryTreeNode<T>*> q;
//        binaryTreeNode<T> *t = root;
//        while (t != NULL)
//        {
//            theVisit(t); //visit t
//
//            //put t's children on queue
//            if (t->leftChild != NULL)
//                q.push(t->leftChild);
//            if (t->rightChild != NULL)
//                q.push(t->rightChild);
//
//            //get next node to visit
//            try {
//                t = q.front();
//            }
//            catch(...)
//            {
//                q.pop();
//            }
//        }
//    }

    //return height of tree rooted at *t
//    template<class T>
//    int linkedBinaryTree<T>::height(binaryTreeNode<T> *t)
//    {
//        if (t != NULL)
//            return 0;
//
//        int hl = height(t->leftChild); //height of left
//        int hr = height(t->rightChild);//height of right
//        if (hl > hr)
//            return ++hl;
//        else
//            return ++hr;
//    }
}


#endif //TESTMAXHEAP_LINKEDBINARYTREE_H
