#ifndef TESTBINARYSEARCHTREE_RBTREE_H
#define TESTBINARYSEARCHTREE_RBTREE_H
#include "rbTreeNode.h"
#include <string>
#include <iostream>

namespace lyj
{
template <class T>
class rbTree
{
public:
    rbTree() : root(nullptr)
    {}

    ~rbTree()
    {
        deleteTree(root);
    }

    void insert(T key);         //insert a value into rb-tree

    void remove(T key);         //remove a value from rb-tree

    void printTree();

private:
    void rotateLeft(rbTreeNode<T>*&);      //left rotation
    void rotateRight(rbTreeNode<T>*&);     //right rotation
    void fixInsert(rbTreeNode<T>*&);       //fixing insertion violation
    void fixDelete(rbTreeNode<T>*&, bool isNull);       //fixing deletion violation

    rbTreeNode<T>* maxValueNode(rbTreeNode<T>*&);                          //find node with minimum value
    void transplantAtCurNode(rbTreeNode<T> *&theRoot, rbTreeNode<T> *&curSubtree, rbTreeNode<T> *&implant);  //transplantAtCurNode nodes in rb tree
    void deleteTree(rbTreeNode<T>*);       //delete all nodes in the rb tree

    void printHelper(rbTreeNode<T>*, std::string, bool);

private:
    rbTreeNode<T> *root;
};

template <class T>
void rbTree<T>::insert(T key)
{
    rbTreeNode<T>* node = new rbTreeNode<T>(key);
    rbTreeNode<T>* parent = nullptr;              //track the insert position
    rbTreeNode<T>* current = root;

    while (current != nullptr)
    {
        parent = current;
        if (node->data < current->data)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    node->parent = parent;
    if (parent == nullptr)
    {
        root = node;
    }
    else if (node->data < parent->data)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }

    fixInsert(node);
}

template <class T>
void rbTree<T>::remove(T key)
{
    rbTreeNode<T> *delNode = nullptr;
    rbTreeNode<T> *replace1 = nullptr; //replacement of delNode for case of both children
    rbTreeNode<T> *replace2 = nullptr; //replacement of replace1

    //find the delNode
    rbTreeNode<T> *node = root;
    while (node != nullptr)
    {
        if (node->data == key)
        {
            delNode = node;
            break;
        }

        if (key < node->data)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    if (delNode == nullptr)
    {
        std::cout << "Key not found in the tree" << std::endl;
        return;
    }

    replace1 = delNode;
    Color replace1OriginalColor = replace1->color; //remember it to tell if fixing needed
    if (delNode->left == nullptr) //leaf or right child only: replace delNode with right child
    {
        replace2 = delNode->right;
        transplantAtCurNode(root, delNode, delNode->right);
    }
    else if (delNode->right == nullptr) //left child only: replace2 delNode with left child
    {
        replace2 = delNode->left;
        transplantAtCurNode(root, delNode, delNode->left);
    }
    else //delNode have both children: replace replace1 with replace2, replace delNode with replace1
    {
        replace1 = maxValueNode(delNode->left); //biggest node in left subtree
        replace1OriginalColor = replace1->color;
        replace2 = replace1->left;           //left child or nullptr

        //replace1 is left child of delNode directly, replacement is automatically done while transplanting replace1 to delNode.
        if (replace1->parent == delNode)
        {
            if (replace2 != nullptr)
            {
                replace2->parent = replace1; //redundant?? replace2 is the left child.
            }
        }
        else
        {
            //replace2 -> replace1
            transplantAtCurNode(root, replace1, replace1->left);

            //left of delNode -> left of replace1: not use transplantAtCurNode because adjustment of replace1 is not finished yet.
            replace1->left = delNode->left;
            replace1->left->parent = replace1;
        }

        //replace1 -> delNode
        transplantAtCurNode(root, delNode, replace1);

        //right of delNode -> right of replace1: not use transplantAtCurNode because replace1 has no right child before.
        replace1->right = delNode->right;
        replace1->right->parent = replace1;

        replace1->color = delNode->color; //keep color
    }

    // create a temporary node if replace2 is null, will be deleted in fixDelete which has argument isNull to remember this.
    bool isNull = false;
    if (replace2 == nullptr &&
        replace1OriginalColor == Color::BLACK)
    {
        replace2 = new rbTreeNode<T>(0);
        rbTreeNode<T> *parent = replace1->parent;
        replace2->color = Color::BLACK;
        replace2->parent = parent;
        if (parent->left == nullptr)
        {
            parent->left = replace2;
        }
        else
        {
            parent->right = replace2;
        }
        isNull = true;
    }
    delete delNode;

    //in case of replace1 is black, fixing is needed.
    if (replace1OriginalColor == Color::BLACK)
    {
        fixDelete(replace2, isNull);
    }
}

template<class T>
void rbTree<T>::fixInsert(rbTreeNode<T> *&node)
{
    //in case red property violation, parent and grandparent must not be null.
    rbTreeNode<T> *parent = node->parent;
    if (parent == nullptr)
    {
        return;
    }
    rbTreeNode<T> *grandparent = parent->parent;
    if (grandparent == nullptr)
    {
        return;
    }

    //loop till balance
    while (node != root                             // reach root
            && node->color == Color::RED            // always true
            && node->parent->color == Color::RED)   // balanced
    {
        //parent is left or right: mirror cases
        if (parent == grandparent->left)
        {
            rbTreeNode<T> *uncle = grandparent->right;

            //uncle is red: swap color of parent level and grandpa, percolate up
            if (uncle != nullptr && uncle->color == Color::RED)
            {
                grandparent->color = Color::RED;
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;
                node = grandparent;
            }
            //uncle is black: rotate red node to uncle's side
            else
            {
                //before rotate at grandpa, make sure node and parent are at the side by rotating at parent.i,e.LL shape.
                if (node == parent->right)
                {
                    rotateLeft(parent);
                    //don't forget to update node&parent because parent becomes left child after rotation.
                    node = parent;
                    parent = node->parent;
                }

                //rotate at grandpa
                rotateRight(grandparent);
                std::swap(parent->color, grandparent->color);

                //after rotation, parent is the top, and it is black now, fixing is done.
                //this is for quiting the loop.
                node = parent;
            }
        }
        else
        //parent is right child
        {
            rbTreeNode<T> *uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == Color::RED)
            {
                grandparent->color = Color::RED;
                parent->color = Color::BLACK;
                uncle->color = Color::BLACK;

                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }

                rotateLeft(grandparent);
                std::swap(parent->color, grandparent->color);

                node = parent;
            }
        }
    }// while loop

    if (node->data)
    // if root reached, alter root to black.
    root->color = Color::BLACK;
}

template <class T>
void rbTree<T>::fixDelete(rbTreeNode<T> *&node, bool isNull)
{
    rbTreeNode<T> *originalNode = node;

    //loop till balance
    while (node != root                 // reach root
        && node->color == Color::BLACK) // node is red so double-black fixed
    {
        //fixing double-black

        //node is left or right: mirror cases
        if (node == node->parent->left)
        {
            rbTreeNode<T>* sibling = node->parent->right;

            //sibling is RED: transfer it to this side by rotating, converting it to BLACK sibling and red parent situation.
            if (sibling->color == Color::RED)
            {
                rotateLeft(node->parent);

                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;

                //update sibling pointer after rotation
                sibling = node->parent->right;
            }

            //sibling has no red child: swap color of node's level and parent, then percolate up
            if ((sibling->left == nullptr || sibling->left->color == Color::BLACK)
                && (sibling->right == nullptr || sibling->right->color == Color::BLACK))
            {
                sibling->color = Color::RED;
                //parent should be set BLACK, but in order to distinguish double-BLACK and BLACK, we do it in the end. i,e.
                    //case parent is RED:   loop will quit, it will become balanced after being set to BLACK at the end of the method.
                    //case parent is BLACK: parent becoming double-BLACK, loop continues.
                node = node->parent;
            } //sibling has no RED child.
            //sibling has any RED child: transfer sibling to this side by rotating, convert it's READ child to BLACK to restore balance.
            else
            {
                //red is at the other side: first rotate to the same side before rotating
                if (sibling->right == nullptr
                    || sibling->right->color == Color::BLACK)
                {
                    rotateRight(sibling);
                    sibling->color = Color::RED;
                    sibling->parent->color = Color::BLACK;

                    sibling = node->parent->right;
                }

                //rotate the BLACK to node's side
                rotateLeft(node->parent);
                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;

                //turn the red to black
                sibling->right->color = Color::BLACK;

                //quit loop
                node  = root;
            }//sibling has any RED child.
        }//node is left child
        else
        //node is right child
        {
            rbTreeNode<T>* sibling = node->parent->left;

            //sibling is RED: transfer it to this side by rotating, converting it to BLACK sibling and red parent situation.
            if (sibling->color == Color::RED)
            {
                rotateRight(node->parent);

                sibling->color = Color::BLACK;
                node->parent->color = Color::RED;

                //update sibling pointer after rotation
                sibling = node->parent->left;
            }

            //sibling has no red child: swap color of node's level and parent, then percolate up
            if ((sibling->left == nullptr || sibling->left->color == Color::BLACK)
                && (sibling->right == nullptr || sibling->right->color == Color::BLACK))
            {
                sibling->color = Color::RED;
                //parent should be set BLACK, but in order to distinguish double-BLACK and BLACK, we do it in the end. i,e.
                //case parent is RED:   loop will quit, it will become balanced after being set to BLACK at the end of the method.
                //case parent is BLACK: parent becoming double-BLACK, loop continues.
                node = node->parent;
            } //sibling has no RED child.
                //sibling has any RED child: transfer sibling to this side by rotating, convert it's READ child to BLACK to restore balance.
            else
            {
                //red is at the other side: first rotate to the same side before rotating
                if (sibling->left == nullptr
                    || sibling->left->color == Color::BLACK)
                {
                    rotateLeft(sibling);
                    sibling->color = Color::RED;
                    sibling->parent->color = Color::BLACK;

                    sibling = node->parent->left;
                }

                //rotate the BLACK to node's side
                rotateRight(node->parent);
                sibling->color = node->parent->color;
                node->parent->color = Color::BLACK;

                //turn the red to black
                sibling->left->color = Color::BLACK;

                //quit loop
                node  = root;
            }//sibling has any RED child.
        }
    }

    //delete the temporary node
    if (isNull)
    {
        if (originalNode == originalNode->parent->left)
        {
            originalNode->parent->left = nullptr;
        }
        else
        {
            originalNode->parent->right = nullptr;
        }
        delete originalNode;
    }

    //set node BLACK at the end
    node->color = Color::BLACK;
}

//get the maximum value node in a subtree.
template <class T>
rbTreeNode<T>* rbTree<T>::maxValueNode(rbTreeNode<T> *&node)
{
    rbTreeNode<T>* current = node;
    while (current->right != nullptr)
    {
        current = current->right;
    }

    return current;
}

//transplant implant subtree onto position of the curSubtree. and curSubtree can be safe delete.
template <class T>
void rbTree<T>::transplantAtCurNode(rbTreeNode<T> *&theRoot, rbTreeNode<T> *&curSubtree, rbTreeNode<T> *&implant)
{
    if (curSubtree->parent == nullptr)
    {
        theRoot = implant;
    }
    else
    {
        if (curSubtree == curSubtree->parent->left)
        {
            curSubtree->parent->left = implant;
        }
        else
        {
            curSubtree->parent->right = implant;
        }
    }

    if (implant != nullptr)
    {
        implant->parent = curSubtree->parent;
    }
}

template <class T>
void rbTree<T>::deleteTree(rbTreeNode<T> *node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <class T>
void rbTree<T>::printHelper(rbTreeNode<T> *subTreeRoot, std::string indent, bool isLeftChild)
{
    if (subTreeRoot != nullptr)
    {
        if (subTreeRoot == root)
        {
            std::cout << "root-";
        }
        else
        {
            std::cout << indent;
            if (isLeftChild)
            {
                std::cout << "L----";
                indent += "    ";
            }
            else
            {
                std::cout << "R----";
                indent += "|   ";
            }
        }

        std::string sColor = (subTreeRoot->color == Color::RED) ? "RED" : "BLACK";
        std::cout << subTreeRoot->data << "(" << sColor << ")" << std::endl;
        printHelper(subTreeRoot->left, indent, true);
        printHelper(subTreeRoot->right, indent, false);
    }
}

template <class T>
void rbTree<T>::printTree()
{
    if (root == nullptr)
    {
        std::cout << "Tree is empty." << std::endl;
    }
    else
    {
        std::cout << "Red-Black Tree:" << std::endl;
        printHelper(root, "", true);
    }
}

//rotate left at node, then node becomes the left child.
template <class T>
void rbTree<T>::rotateLeft(rbTreeNode<T> *&node)
{
    //settle down left child of right child: turn to be right child of node, because node < it < node's right child
    rbTreeNode<T> *child = node->right; //mark middle node as child
    node->right = child->left;
    if (node->right != nullptr)
        node->right->parent = node;

    //bring up middle node
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    //take down left node
    node->parent = child;
    child->left = node;

}

//rotate right at node, then node becomes the right child.
template <class T>
void rbTree<T>::rotateRight(rbTreeNode<T> *&node)
{
    //settle down right child of left child: turn to be left child of node, because node < it < node's left child
    rbTreeNode<T>* child = node->left;     //mark middle node as child
    node->left = child->right;
    if (node->left != nullptr)
        node->left->parent = node;

    //bring up middle node
    child->parent = node->parent;
    if (node->parent == nullptr)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;

    //take down right node
    child->right = node;
    node->parent = child;
}

}

#endif //TESTBINARYSEARCHTREE_RBTREE_H
