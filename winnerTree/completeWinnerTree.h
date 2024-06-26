#ifndef TEST_COMPLETEWINNERTREE_H
#define TEST_COMPLETEWINNERTREE_H
#include "winnerTree.h"
#include <exception>
#include <iostream>

namespace lyj
{
    template<class T>
    class CompleteWinnerTree : public WinnerTree<T>
    {
    public :
        CompleteWinnerTree(T *thePlayer, int theNumberOfPlayers)
        : lowExt(0), offset(0), tree(NULL), numberOfPlayers(0), player(NULL)
        {
            tree = NULL;
            initialize(thePlayer, theNumberOfPlayers);
        }
        ~CompleteWinnerTree()
        {
            delete [] tree;
        }
        void initialize(T*, int);
        int winner() const
        {
            return tree[1];
        }
        int winner(int i) const
        {
            return (i < numberOfPlayers) ? tree[i] : 0;
        }
        void rePlay(int);
        void output() const;

    private:
        int lowExt;     //lowest-level external nodes
        int offset;     //2^log(n-1) - 1
        int *tree;      //array for winner tree: tree[1] ~ tree[n-1]. value of element is the index of players in player array.
        int numberOfPlayers;
        T *player;      //array of players: player[1] ~ player[n]

        void play(int parent, int leftPlayer, int rightPlayer);
    };

    template<class T>
    void CompleteWinnerTree<T>::initialize(T *thePlayer, int theNumberOfPlayers)
    {
        //create winner tree for thePlayer[1:numberOfPlayers]
        int n = theNumberOfPlayers;
        if (n < 2)
            throw std::exception();

        player = thePlayer;
        numberOfPlayers = n;
        delete [] tree;
        tree = new int[n];

        //compute s = 2^log(n-1).   ie.the lowest left
        int i(0), s(0);
        for (s = 1; 2 * s <= n - 1; s += s); //2s������һ��ĵ�һ�����, s+=s����2s

        lowExt = 2 * (n - s);
        offset = 2 * s - 1;

        //����ʱ,���ڲ�������ⲿ����ϳ�һ������,��������
        //play matches for lowest-level external nodes
        for (i = 2; i <= lowExt; i += 2)
        {
            play((offset + i) / 2, i - 1, i);
        }

        //ѡ�ֳɵ���ʱ, ��Ҫ���ɵ������ⲿ��������һ���ڲ�������
        if (n % 2 == 1)
        {
            //special case for odd n, play internal and external node
            //last node: tree[n-1], first external node(is the next node of lowExt): lowExt + 1
            play(n/2, tree[n-1], lowExt+1);
            i = lowExt + 3; //������һ��ѡ�ֵ���ѡ�ִ�
        }
        else
        {
            i = lowExt + 2; //������һ��ѡ�ֵ���ѡ�ִ�
        }

        //����������ڲ������ͬһ����ⲿ���(��˫����), Ϊ���ǽ��б���
        //play matches for the 2nd lowest-level external nodes
        //i is left-most remaining external node
        for(; i <= n; i += 2)
        {
            play((i-lowExt + n-1)/2, i-1, i);
        }
    }

    //�ڸ����parent����ʼ����. Լ��:�������Ϊ�Һ���ʱ���Զ���������,ֱ�������򸸽�㲻�����Һ���(��Ϊֻ������ʱ,��������б�����),�ú������ڳ�ʼ��
    /*
     * parent:    parent�����е�����
     * leftChild: ���ӵ�keyֵ(ie.ѡ�ֱ��)
     * rightChild:�Һ��ӵ�keyֵ
     */
    template<class T>
    void CompleteWinnerTree<T>::play(int parent, int leftChild, int rightChild)
    {
        //play matches beginning at tree[parent]
        tree[parent] = player[leftChild] <= player[rightChild] ? leftChild : rightChild;

        while (parent % 2 == 1 && parent > 1) //�Һ����Ҳ�Ϊ�����
        {
            tree[parent/2] = (player[tree[parent-1]] <= player[tree[parent]]) ? tree[parent-1] : tree[parent];
            parent /= 2;
        }
    }

    template<class T>
    void CompleteWinnerTree<T>::rePlay(int thePlayer)
    {
        //replay matches for player thePlayer
        int n = numberOfPlayers;
        if (thePlayer <= 0 || thePlayer > n)
            throw std::exception();

        int matchNode,  // node where next match is to be played
            leftChild,  // left child of matchNode
            rightChild; // right child of matchNode

        //find first match node and its children
        if (thePlayer <= lowExt) //����ײ�
        {
            matchNode = (offset + thePlayer) / 2; //��������offset��ѡ�ֱ�ż����
            leftChild = 2*matchNode - offset;     //��ѡ�ֱ�Ÿ��ݸ�����offset�����
            rightChild = leftChild + 1;           //��ѡ�ֱ�Ÿ�����ѡ�ֱ���Ƶ���
        }
        else //�ڵ�����2��
        {
            matchNode = (thePlayer-lowExt + n-1) / 2;  //��������lowExt��ѡ�ֱ�ż����
            if (2*matchNode == n-1) //�ڲ����ɵ��������
            {
                leftChild = tree[2*matchNode];  //��ѡ�ֱ�����ڲ����
                rightChild = thePlayer;         //��ѡ�־��ǵ�ǰѡ��
            }
            else //�ڲ������˫��,��ʱ���Һ��Ӷ���������,�޷������в�ѯ�����Һ��ӵ�ֵ,��Ҫȥ����������ѡ���еı��
            {
                leftChild = 2*matchNode -n + 1 + lowExt; //���� = �������������� - (�ڲ������) + ��ײ��ⲿ�����(��ײ��ⲿ��������,��˱�Ŷ�����ǰ��)
                rightChild = leftChild + 1;
            }
        }

        tree[matchNode] = player[leftChild] <= player[rightChild] ? leftChild : rightChild;

        //��������,��Ҫ�ȴ���һ���������: �����Ϊ���һ���ڲ����,��Ϊ����,��ʱ���Һ���Ϊѡ��(�����޷������в�ѯ).���������,���Һ��Ӿ�������.
        //special case for second match
        if (matchNode == n - 1 && n%2 == 1)
        {
            matchNode /= 2; //move to parent
            tree[matchNode] = (player[tree[n - 1]] <= player[lowExt + 1]) ? tree[n-1] : lowExt + 1;
        }

        //play remaining matches.���Ÿ����һֱ����,ֱ�������
        matchNode /= 2;
        for (; matchNode >= 1; matchNode /= 2)
        {
            tree[matchNode] = (player[tree[2*matchNode]] <= player[tree[2*matchNode + 1]]) ? tree[2*matchNode] : tree[2*matchNode + 1];
        }
    }

    template<class T>
    void CompleteWinnerTree<T>::output() const
    {
        std::cout << "number of players = " << numberOfPlayers << " lowExt = " << lowExt << " offset = " << offset << std::endl;
        std::cout << "complete winner tree pointers are " << std::endl;

        for (int i = 1; i < numberOfPlayers; ++i)
            std::cout << tree[i] << " ";
        std::cout << std::endl;
    }
}


#endif //TEST_COMPLETEWINNERTREE_H
