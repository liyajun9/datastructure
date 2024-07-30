#ifndef TESTBINARYSEARCHTREE_BSTREE_H
#define TESTBINARYSEARCHTREE_BSTREE_H
//abstract data type specification for binary search trees. all methods are pure virtual functions.
#include "../dictionary/dictionary.h"

namespace lyj
{
    template<class K, class E>
    class bsTree : public dictionary<K, E>
    {
    public:
        virtual void ascend() = 0;
    };
}

#endif //TESTBINARYSEARCHTREE_BSTREE_H
