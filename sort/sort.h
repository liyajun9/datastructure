//
// Created by ralph on 4/24/20.
//

#ifndef DATASTRUCTURE_SORT_H
#define DATASTRUCTURE_SORT_H

#include <cstdio>
#include <algorithm>

template <typename T>
void bubbleSort(T* ele, size_t n) {
    bool swapped = false;
    while(n > 1){
        for(int i = 0; i < n - 1 ; ++i){
            if(ele[i] > ele[i+1]) {
                std::swap(ele[i], ele[i + 1]);
                swapped = true;
            }
        }
        if(!swapped) break;
        --n;
    }
}

template <typename T>
void insertionSort(T* ele, size_t n) {
    T tmp;
    for(int i = 1; i < n; ++i){
        int pos = -1;
        for(int j = 0; j < i; ++j){
            if(ele[j] > ele[i]) {
                pos = j;
                break;
            }
        }
        if(pos >= 0){
            tmp = ele[i];
            for(int k = i; k >= pos; --k){
                ele[k] = ele[k-1];
            }
            ele[pos] = tmp;
        }
    }
}

#endif //DATASTRUCTURE_SORT_H
