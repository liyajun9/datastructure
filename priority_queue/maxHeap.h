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
//        size_t _arrayLength;  //queue capacity+1. ���鳤��, ��Ҫ�����ж��Ƿ�������.���ڲ��ô�����Ϊ1��λ�ÿ�ʼʹ��,�ܹ��˷�һ��λ��.
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
//        // �Ƿ���Ҫ��������.
//        if (_heapSize == _arrayLength - 1)
//        {
//            _arrayLength *= 2;
//            _heap.resize(_arrayLength);
//        }

        //��ʼ����: ���½����뵽����ĩβ
        int currentNode = ++_heapSize;
        int parentNode = currentNode / 2;

        //������ֹ����: ��ǰ��Ϊ�����,��������������
        while (currentNode != 1 && theElement > _heap[parentNode])
        {
            // ��������ֵ��������ǰ���
            _heap[currentNode] = _heap[parentNode];

            // ��һѭ��ֵ: �������Ϊ��ǰ���
            currentNode = parentNode;
            parentNode = currentNode / 2;
        }

        _heap[currentNode] = theElement;
    }

    template<class T>
    void maxHeap<T>::pop()
    {
        //�������:����,ֱ�ӷ���
        if (_heapSize == 0)
            return;

        //ɾ�����Ԫ��
        _heap[1].~T();

        //ȡ�����һ��Ԫ��,׼�����ݲ�Ϊ���ҵ�һ�����ʵ�λ��
        T lastElement = _heap[_heapSize--];

        //��ʼ����
        int currentNode = 1;
        int child = 2;

        //��ֹ����
        while (child <= _heapSize)
        {
            //�ж����һ��Ԫ���Ƿ��ܷ��ڸ�λ��: �Ƿ�>=���Һ���.Ϊ�����ҵ����Һ����еĴ���.
            if (child < _heapSize && _heap[child + 1] > _heap[child])
            {
                ++child;
            }

            //���Է�
            if (lastElement >= _heap[child])
                break;

            //���ܷ�,���������Ϸ�
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

        //���¶���,����Ϊ���и����Ѱ�Һ��ʵ�λ��(���ݷ�)
        for (int parent = _heapSize / 2; parent >= 1; parent--)
        {
            T parentElement = _heap[parent];

            //ִ������
            int child = 2 * parent;
            while (child <= _heapSize)
            {
                //��ýϴ�ĺ���
                if (child < _heapSize && _heap[child + 1] > _heap[child])
                {
                    ++child;
                }

                //�Ƿ���������
                if (parentElement >= _heap[child])
                {
                    break; //����ʱ�Ͳ���Ҫ�ٽ��ӽ��������
                }

                //������,�ӽ������
                _heap[child / 2] = _heap[child];

                //������һ��
                child = child * 2;
            }

            //����ҵ�����λ��
            _heap[child / 2] = parentElement;
        }
    }
}

#endif //DATASTRUCTURE_MAXHEAP_H
