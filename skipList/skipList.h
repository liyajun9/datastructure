//
// Created by ralph on 4/16/20.
//

#ifndef DATASTRUCTURE_SKIPLIST_H
#define DATASTRUCTURE_SKIPLIST_H
#include <cmath>
#include <utility>
#include "../dictionary/dictionary.h"
#include "skipNode.h"
#include <iostream>
#include <sstream>
#include <cmath>

namespace lyj
{
    template<class K, class E>
    class skipList : public dictionary<K, E>
    {
    public:
        skipList(K, int maxPairs = 10000, float prob=0.5);
        ~skipList();

        bool empty() const
        {
            return dSize == 0;
        }

        int size() const
        {
            return dSize;
        }

        std::pair<const K, E>* find(const K&) const;

        void erase(const K&);

        void insert(const std::pair<const K, E>&);

        void output(std::ostream& out) const;

    protected:
        int level() const;                      //generate a random level number. this level number is the maximum level that the current new node should go.
        skipNode<K,E>* search(const K&) const;  //search and saving last nodes seen

    protected:
        float cutoff;       //used to decide level number. its value is prob * MAX_RANDOM
        int levels;         //max current nonempty chain
        int dSize;          //number of pairs in dictionary
        int maxLevel;       //max permissible chain level
        K tailKey;          //a large key. all keys in dictionary must less than it.

        skipNode<K,E>* headerNode;  //header node of the whole skipList
        skipNode<K,E>* tailNode;    //tail node of the whole skipList
        skipNode<K,E>** last;       //last[i] = last node seen on level i. ie., the insertion point. updated after searching, and used when inserting and deleting.
    };


    template <class K, class E>
    skipList<K, E>::skipList(K largeKey, int maxPairs, float prob)
    {
        cutoff = prob * (float)RAND_MAX;
        levels = 0;
        tailKey = largeKey;
        maxLevel = (int)std::ceil(logf((float)maxPairs) / logf(1/prob)) - 1;

        std::pair<K, E> thePair;
        thePair.first = tailKey;
        headerNode = new skipNode<K, E>(thePair, maxLevel + 1);
        tailNode = new skipNode<K, E>(thePair, 0); //size is 0 because tailNode doesn't need have next.

        last = new skipNode<K,E>*[maxLevel + 1];

        //header pointers to tail at all levels as lists are empty
        for (int i=0; i<maxLevel+1; ++i)
        {
            headerNode->next[i] = tailNode;
        }
    }

    template <class K, class E>
    skipList<K, E>::~skipList()
    {
        skipNode<K,E>* nextNode;
        while (headerNode != tailNode)
        {
            nextNode = headerNode->next[0];
            delete headerNode;
            headerNode = nextNode;
        }

        delete tailNode;
        delete []last;
    }

    template <class K, class E>
    std::pair<const K, E>* skipList<K, E>::find(const K& theKey) const
    {
        if (theKey >= tailKey)
        {
            return NULL;
        }

        skipNode<K, E>* beforeNode = headerNode;
        for (int i=levels; i >= 0; --i)
        {
            while (beforeNode->next[i]->element.first < theKey)
            {
                beforeNode = beforeNode->next[i];
            }
        }

        if (beforeNode->next[0]->element.first == theKey)
        {
            return &beforeNode->next[0]->element;
        }

        return NULL;
    }

    template <class K, class E>
    int skipList<K, E>::level() const
    {
        int level = 0;
        while (rand() < cutoff)
        {
            ++level;
        }

        return level <= maxLevel? level : levels;
    }

    template <class K, class E>
    skipNode<K, E>* skipList<K, E>::search(const K& theKey) const
    {
        skipNode<K, E> *beforeNode = headerNode;
        for (int i=levels; i>=0; --i)
        {
            while(beforeNode->next[i]->element.first < theKey)
            {
                beforeNode = beforeNode->next[i];
            }
            last[i] = beforeNode;
        }

        return beforeNode->next[0];
    }

    template <class K, class E>
    void skipList<K, E>::insert(const std::pair<const K, E>& thePair)
    {
        if (thePair.first >= tailKey)
        {
            std::ostringstream oss;
            oss << "Key = " << thePair.first << " Must be < " << tailKey;
            std::cout << oss.str() << std::endl;
            return;
        }

        skipNode<K, E>* theNode = search(thePair.first);
        if (theNode->element.first == thePair.first)
        {
            theNode->element.second = thePair.second;
            return;
        }

        int theLevel = level();
        if (theLevel > levels)
        {
            theLevel = ++levels;
            last[theLevel] = headerNode;
        }

        skipNode<K, E>* newNode = new skipNode<K, E>(thePair, theLevel + 1);
        for (int i = 0; i <= theLevel; ++i)
        {
            newNode->next[i] = last[i]->next[i];
            last[i]->next[i] = newNode;
        }

        dSize++;
    }

    template <class K, class E>
    void skipList<K, E>::erase(const K& theKey)
    {
        if (theKey >= tailKey)
        {
            return;
        }

        skipNode<K, E>* theNode = search(theKey);
        if (theNode->element.first != theKey)
        {
            return;
        }

        for (int i=0; i<= levels && last[i]->next[i] == theNode; ++i)
        {
            last[i]->next[i] = theNode->next[i];
        }

        while (levels > 0 && headerNode->next[levels] == tailNode)
        {
            --levels;
        }

        delete theNode;
        --dSize;
    }

    template <class K, class E>
    void skipList<K, E>::output(std::ostream &out) const
    {
        //output from headerNode->next to the node before tailNode. at level 0(i.e, the original chain).
        for (skipNode<K, E>* currentNode = headerNode->next[0]; currentNode != tailNode; currentNode = currentNode->next[0])
        {
            out << currentNode->element.first << " " << currentNode->element.second << "  ";
        }
    }

    template <class K, class E>
    std::ostream& operator<<(std::ostream& out, const skipList<K,E>& x)
    {
        x.output(out);
        return out;
    }

}


#endif //DATASTRUCTURE_SKIPLIST_H
