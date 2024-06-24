#ifndef TEST_WINNERTREE_H
#define TEST_WINNERTREE_H

namespace lyj
{
    template<class T>
    class WinnerTree
    {
    public:
        virtual ~WinnerTree() {}

        //create winner tree with thePlayer[1:numberOfPlayers+1]
        virtual void initialize(T *thePlayer, int theNumberOfPlayers) = 0;

        //return the index of winner
        virtual int winner() const = 0;

        //replay matches following a change in thePlayer
        virtual void rePlay(int thePlayer) = 0;
    };
}

#endif //TEST_WINNERTREE_H
