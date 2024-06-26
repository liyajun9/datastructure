#ifndef TESTWINNERTREE_PAIRNODE_H
#define TESTWINNERTREE_PAIRNODE_H
#include <utility>

namespace lyj
{
    template <class K, class E>
    struct pairNode
    {
        typedef std::pair<const K, E> pairType;
        pairType element;
        pairNode<K, E> *next;

        pairNode(const pairType& thePair):element(thePair), next(nullptr)
        {
        }
        pairNode(const pairType& thePair, pairNode<K, E>* theNext) : element(thePair)
        {
            next = theNext;
        }
    };
}
#endif //TESTWINNERTREE_PAIRNODE_H
