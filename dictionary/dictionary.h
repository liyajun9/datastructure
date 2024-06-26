#ifndef TESTWINNERTREE_DICTIONARY_H
#define TESTWINNERTREE_DICTIONARY_H
#include "pairNode.h"
#include <utility>

namespace lyj
{
    template<class K, class E>
    class dictionary
    {
    public:
        virtual ~dictionary() {}
        virtual bool empty() const = 0;                         //����true, ���ҽ����ֵ�Ϊ��
        virtual int size() const = 0;                           //�����ֵ������Ե���Ŀ
        virtual std::pair<const K,E>* find(const K&) const = 0; //����ƥ�����Ե�ָ��
        virtual void erase(const K&) = 0;                       //ɾ��ƥ�������
        virtual void insert(const std::pair<const K, E>&) = 0;  //���ֵ��в���һ������
    };
}
#endif //TESTWINNERTREE_DICTIONARY_H
