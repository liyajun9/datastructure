#ifndef TESTFIBONACCI_FIBONACCINODE_H
#define TESTFIBONACCI_FIBONACCINODE_H

namespace lyj
{
    template<class T>
    struct FibonacciNode
    {
        FibonacciNode* parent;
        FibonacciNode* child;  //最小孩子指针. left or right? the child with minimum key!

        FibonacciNode* left;
        FibonacciNode* right;

        int degree;    //当前结点的度

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

            left = this;   //初始化时,left和right都指向自身
            right = this;
        }
    };
}
#endif //TESTFIBONACCI_FIBONACCINODE_H
