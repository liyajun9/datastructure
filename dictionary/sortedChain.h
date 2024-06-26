#ifndef TESTWINNERTREE_SORTEDCHAIN_H
#define TESTWINNERTREE_SORTEDCHAIN_H
#include "dictionary.h"
#include "pairNode.h"
#include <iostream>

namespace lyj
{
    template<class K, class E>
    class sortedChain : public dictionary<K, E>
    {
    public:
        sortedChain()
        {
            firstNode = NULL;
            dSize = 0;
        }
        ~sortedChain();

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
        pairNode<K, E>* firstNode;  //pointer to the first node in chain
        int dSize;                  //number of elements in dictionary
    };

    template<class K, class E>
    sortedChain<K, E>::~sortedChain()
    {
        while (firstNode != NULL)
        {
            pairNode<K, E>* nextNode = firstNode->next;
            delete firstNode;
            firstNode = nextNode;
        }
    }

    template<class K, class E>
    std::pair<const K, E>* sortedChain<K, E>::find(const K & theKey) const
    {
        pairNode<K, E>* currentNode = firstNode;

        //遍历链表, 终止条件:到终点或找到key
        while (currentNode != NULL && currentNode->element.first != theKey)
        {
            currentNode = currentNode->next;
        }

        //如果找到key,返回找到的元素
        if (currentNode != NULL && currentNode->element.first == theKey)
        {
            return &currentNode->element;
        }

        //否则返回null
        return NULL;
    }

    template<class K, class E>
    void sortedChain<K, E>::insert(const std::pair<const K, E> &thePair)
    {
        pairNode<K, E> *p = firstNode,
                        *tp = NULL;

        //双指针法遍历,跟踪当前元素和前一个元素.终止条件:找到插入处(当前元素>=thePair)
        while (p != NULL && p->element.first < thePair.first)
        {
            tp = p;
            p = p->next;
        }

        //准确找到了key: 更新值即可
        if (p != NULL && p->element.first == thePair.first)
        {
            p->element.second = thePair.second;
            return;
        }

        //否则,依参数创建新元素,插入到插入处
        pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);
        if (tp == NULL)
            firstNode = newNode;
        else
            tp->next = newNode;

        //别忘记维护总长度
        ++dSize;
    }

    template<class K, class E>
    void sortedChain<K, E>::erase(const K & theKey)
    {
        //双指针法便利,跟踪当前元素和前一个元素.终止条件:找到插入处(当前元素>=thePair)
        pairNode<K, E> *p = firstNode,
                        *tp = NULL;

        while (p != NULL && p->element.first < theKey)
        {
            tp = p;
            p = p->next;
        }

        //只有在准确找到了key时,才执行删除
        if (p != NULL && p->element.first == theKey)
        {
            if (tp == NULL)
                firstNode = p->next;
            else
                tp->next = p->next;
            delete p;
            --dSize;
        }
    }

    template<class K, class E>
    void sortedChain<K, E>::output(std::ostream &out) const
    {
        for (pairNode<K, E>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
        {
            out << currentNode->element.first << " " << currentNode->element.second << "   ";
        }
    }

    template<class K, class E>
    std::ostream& operator<<(std::ostream& out, const sortedChain<K, E>& x)
    {
        x.output(out);
        return out;
    }

}
#endif //TESTWINNERTREE_SORTEDCHAIN_H
