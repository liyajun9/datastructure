#ifndef DATASTRUCTURE_MAXPRIORITYQUEUE_H
#define DATASTRUCTURE_MAXPRIORITYQUEUE_H
namespace lyj
{

template<class T>
class maxPriorityQueue
{
public:
    virtual ~maxPriorityQueue(){}

    virtual bool empty() const = 0;
    virtual int size() const = 0;

    virtual const T& top() = 0;  //return reference to the max element
    virtual void pop() = 0;//remove the top element
    virtual void push(const T& theElement) = 0; //add theElement to the queue
};

}
#endif //DATASTRUCTURE_MAXPRIORITYQUEUE_H
