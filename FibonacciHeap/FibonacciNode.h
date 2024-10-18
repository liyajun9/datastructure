#ifndef TESTFIBONACCI_FIBONACCINODE_H
#define TESTFIBONACCI_FIBONACCINODE_H

namespace lyj
{
    template<class T>
    struct FibonacciNode
    {
        FibonacciNode* parent;
        FibonacciNode* child;  //��С����ָ��. left or right? the child with minimum key!

        FibonacciNode* left;
        FibonacciNode* right;

        int degree;    //��ǰ���Ķ�

        char mark;     //black or white
        char visited;        //flag for assisting in the Find node function

        T data;

        FibonacciNode(T data_) : data(data_)
        {
            degree = 0;
            mark = 'W';
            visited = 'N';
            parent = NULL;
            child = NULL;

            left = this;   //��ʼ��ʱ,left��right��ָ������
            right = this;
        }
    };
}
#endif //TESTFIBONACCI_FIBONACCINODE_H
