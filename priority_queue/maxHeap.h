#ifndef DATASTRUCTURE_MAXHEAP_H
#define DATASTRUCTURE_MAXHEAP_H

#include <vector>

namespace lyj
{

    template <class T>
    class maxHeap
    {
    public:
        explicit maxHeap(int initial_capacity=16);

        virtual ~maxHeap() {}

        virtual bool empty()
        {
            return _heapSize == 0;
        };

        virtual int size() const
        {
            return _heapSize;
        }

        virtual void push(const T& theElement);
        virtual void pop();
        virtual T& top();
        void initialize(std::vector<T> theHeap);


    private:
        size_t _heapSize;     //number of elements in queue. and _heapSize = index of the last element
//        size_t _arrayLength;  //queue capacity+1. 数组长度, 主要用于判读是否需增长.由于采用从索引为1的位置开始使用,总共浪费一个位置.
        std::vector<T> _heap;
    };

    template<class T>
    maxHeap<T>::maxHeap(int initial_capacity)
    {
//       _arrayLength = initial_capacity;
       _heap.reserve(initial_capacity + 1);
    }

    template<class T>
    void maxHeap<T>::push(const T &theElement)
    {
//        // 是否需要增长数组.
//        if (_heapSize == _arrayLength - 1)
//        {
//            _arrayLength *= 2;
//            _heap.resize(_arrayLength);
//        }

        //初始条件: 将新结点插入到队列末尾
        int currentNode = ++_heapSize;
        int parentNode = currentNode / 2;

        //上溯终止条件: 当前已为根结点,或者无需再上溯
        while (currentNode != 1 && theElement > _heap[parentNode])
        {
            // 将父结点的值交换到当前结点
            _heap[currentNode] = _heap[parentNode];

            // 下一循环值: 父结点作为当前结点
            currentNode = parentNode;
            parentNode = currentNode / 2;
        }

        _heap[currentNode] = theElement;
    }

    template<class T>
    void maxHeap<T>::pop()
    {
        //特殊情况:空树,直接返回
        if (_heapSize == 0)
            return;

        //删除最大元素
        _heap[1].~T();

        //取出最后一个元素,准备下溯并为其找到一个合适的位置
        T lastElement = _heap[_heapSize--];

        //初始条件
        int currentNode = 1;
        int child = 2;

        //终止条件
        while (child <= _heapSize)
        {
            //判断最后一个元素是否能放在该位置: 是否>=左右孩子.为此先找到左右孩子中的大者.
            if (child < _heapSize && _heap[child + 1] > _heap[child])
            {
                ++child;
            }

            //可以放
            if (lastElement >= _heap[child])
                break;

            //不能放,将大孩子往上放
            _heap[currentNode] = _heap[child];
            currentNode = child;
            child *= 2;
        }

        _heap[currentNode] = lastElement;
    }

    template<class T>
    T& maxHeap<T>::top()
    {
        return _heap[1];
    }

    template<class T>
    void maxHeap<T>::initialize(std::vector<T> theHeap)
    {
        //heap index begin from 1
        std::copy(theHeap.begin(), theHeap.end(), _heap.begin() + 1);
        _heapSize = theHeap.size();

        //自下而上,挨个为所有父结点寻找合适的位置(下溯法)
        for (int parent = _heapSize / 2; parent >= 1; parent--)
        {
            T parentElement = _heap[parent];

            //执行下溯
            int child = 2 * parent;
            while (child <= _heapSize)
            {
                //获得较大的孩子
                if (child < _heapSize && _heap[child + 1] > _heap[child])
                {
                    ++child;
                }

                //是否满足最大堆
                if (parentElement >= _heap[child])
                {
                    break; //满足时就不需要再将子结点上移了
                }

                //不满足,子结点上移
                _heap[child / 2] = _heap[child];

                //跳到下一层
                child = child * 2;
            }

            //最后找到合适位置
            _heap[child / 2] = parentElement;
        }
    }
}

#endif //DATASTRUCTURE_MAXHEAP_H
