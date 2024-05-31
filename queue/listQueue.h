//
// Created by ralph on 4/26/20.
//

#ifndef DATASTRUCTURE_QUEUE_H
#define DATASTRUCTURE_QUEUE_H

#include <functional>
#include "../list/doublyLinkedList.h"

template <typename T>
class listQueue : public List<T>{
public:
    void enqueue(const T& e) {
        this->insertAsLast(e);
    }

    T dequeue() {
        return this->remove(this->first());
    }

    T& front() {
        return this->first()->m_data;
    }
};

template <typename T>
void RoundRobin(const listQueue<T>& queue, const std::function<void(T)>& func) {
    while(true){
        T ele = queue.dequeue();
        func(ele);
        queue.enqueue(ele);
    }
};


#endif //DATASTRUCTURE_QUEUE_H
