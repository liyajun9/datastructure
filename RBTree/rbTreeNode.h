#ifndef TESTBINARYSEARCHTREE_RBNODE_H
#define TESTBINARYSEARCHTREE_RBNODE_H

namespace lyj
{
    enum Color { RED, BLACK };

    template<class T>
    struct rbTreeNode
    {
        Color color;

        T data;
        struct rbTreeNode<T> *left,
                             *right,
                             *parent;
        rbTreeNode(T key): data(key)
                            , color(RED)
                            , parent(nullptr)
                            , left(nullptr)
                            , right(nullptr)
        {}
    };
}
#endif //TESTBINARYSEARCHTREE_RBNODE_H
