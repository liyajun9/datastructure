#ifndef TESTDICTIONARY_SKIPNODE_H
#define TESTDICTIONARY_SKIPNODE_H
#include <utility>

namespace lyj{

    template<class K, class E>
    struct skipNode
    {
        typedef std::pair<const K, E> pairType;

        pairType element;
        skipNode<K,E> **next;  //pointer to next node on each level. there are n+1 pointers in n-level skipList.

        skipNode(const pairType& thePair, int size) : element(thePair)
        {
            next = new skipNode<K, E> * [size];
        }

        ~skipNode()
        {
            delete []next;
        }
    };

}
#endif //TESTDICTIONARY_SKIPNODE_H
