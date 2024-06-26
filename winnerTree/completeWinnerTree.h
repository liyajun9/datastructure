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
        for (s = 1; 2 * s <= n - 1; s += s); //2s就是下一层的第一个编号, s+=s就是2s

        lowExt = 2 * (n - s);
        offset = 2 * s - 1;

        //比赛时,将内部结点与外部结点结合成一棵整树,方便运算
        //play matches for lowest-level external nodes
        for (i = 2; i <= lowExt; i += 2)
        {
            play((offset + i) / 2, i - 1, i);
        }

        //选手成单数时, 需要将成单数的外部结点与最后一个内部结点比赛
        if (n % 2 == 1)
        {
            //special case for odd n, play internal and external node
            //last node: tree[n-1], first external node(is the next node of lowExt): lowExt + 1
            play(n/2, tree[n-1], lowExt+1);
            i = lowExt + 3; //跳到下一对选手的右选手处
        }
        else
        {
            i = lowExt + 2; //跳到下一对选手的右选手处
        }

        //如果还有与内部结点在同一层的外部结点(成双数的), 为他们进行比赛
        //play matches for the 2nd lowest-level external nodes
        //i is left-most remaining external node
        for(; i <= n; i += 2)
        {
            play((i-lowExt + n-1)/2, i-1, i);
        }
    }

    //在父结点parent处开始比赛. 约定:若父结点为右孩子时会自动触发比赛,直至根结点或父结点不再是右孩子(因为只有左孩子时,是无需进行比赛的),该函数用于初始化
    /*
     * parent:    parent在树中的索引
     * leftChild: 左孩子的key值(ie.选手编号)
     * rightChild:右孩子的key值
     */
    template<class T>
    void CompleteWinnerTree<T>::play(int parent, int leftChild, int rightChild)
    {
        //play matches beginning at tree[parent]
        tree[parent] = player[leftChild] <= player[rightChild] ? leftChild : rightChild;

        while (parent % 2 == 1 && parent > 1) //右孩子且不为根结点
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
        if (thePlayer <= lowExt) //在最底层
        {
            matchNode = (offset + thePlayer) / 2; //父结点根据offset和选手编号计算出
            leftChild = 2*matchNode - offset;     //左选手编号根据父结点和offset计算出
            rightChild = leftChild + 1;           //右选手编号根据左选手编号推导出
        }
        else //在倒数第2层
        {
            matchNode = (thePlayer-lowExt + n-1) / 2;  //父结点根据lowExt和选手编号计算出
            if (2*matchNode == n-1) //内部结点成单数的情况
            {
                leftChild = tree[2*matchNode];  //左选手编号在内部结点
                rightChild = thePlayer;         //右选手就是当前选手
            }
            else //内部结点是双数,此时左右孩子都不在树中,无法在树中查询出左右孩子的值,需要去计算它们在选手中的编号
            {
                leftChild = 2*matchNode -n + 1 + lowExt; //左孩子 = 整树中左孩子索引 - (内部结点数) + 最底层外部结点数(最底层外部结点在左边,因此编号都在其前面)
                rightChild = leftChild + 1;
            }
        }

        tree[matchNode] = player[leftChild] <= player[rightChild] ? leftChild : rightChild;

        //往上重赛,但要先处理一种特殊情况: 父结点为最后一个内部结点,且为左孩子,此时其右孩子为选手(其编号无法在树中查询).其它情况下,左右孩子均在树中.
        //special case for second match
        if (matchNode == n - 1 && n%2 == 1)
        {
            matchNode /= 2; //move to parent
            tree[matchNode] = (player[tree[n - 1]] <= player[lowExt + 1]) ? tree[n-1] : lowExt + 1;
        }

        //play remaining matches.沿着父结点一直往上,直到根结点
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
