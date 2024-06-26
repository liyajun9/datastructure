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

        //��������, ��ֹ����:���յ���ҵ�key
        while (currentNode != NULL && currentNode->element.first != theKey)
        {
            currentNode = currentNode->next;
        }

        //����ҵ�key,�����ҵ���Ԫ��
        if (currentNode != NULL && currentNode->element.first == theKey)
        {
            return &currentNode->element;
        }

        //���򷵻�null
        return NULL;
    }

    template<class K, class E>
    void sortedChain<K, E>::insert(const std::pair<const K, E> &thePair)
    {
        pairNode<K, E> *p = firstNode,
                        *tp = NULL;

        //˫ָ�뷨����,���ٵ�ǰԪ�غ�ǰһ��Ԫ��.��ֹ����:�ҵ����봦(��ǰԪ��>=thePair)
        while (p != NULL && p->element.first < thePair.first)
        {
            tp = p;
            p = p->next;
        }

        //׼ȷ�ҵ���key: ����ֵ����
        if (p != NULL && p->element.first == thePair.first)
        {
            p->element.second = thePair.second;
            return;
        }

        //����,������������Ԫ��,���뵽���봦
        pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);
        if (tp == NULL)
            firstNode = newNode;
        else
            tp->next = newNode;

        //������ά���ܳ���
        ++dSize;
    }

    template<class K, class E>
    void sortedChain<K, E>::erase(const K & theKey)
    {
        //˫ָ�뷨����,���ٵ�ǰԪ�غ�ǰһ��Ԫ��.��ֹ����:�ҵ����봦(��ǰԪ��>=thePair)
        pairNode<K, E> *p = firstNode,
                        *tp = NULL;

        while (p != NULL && p->element.first < theKey)
        {
            tp = p;
            p = p->next;
        }

        //ֻ����׼ȷ�ҵ���keyʱ,��ִ��ɾ��
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
