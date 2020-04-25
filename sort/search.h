//
// Created by ralph on 4/25/20.
//

#ifndef DATASTRUCTURE_SEARCH_H
#define DATASTRUCTURE_SEARCH_H

#include <cstdio>

template <typename T>
int binarySearch(T target, T* ele, size_t n){
    int lo = 0;
    int hi = n;
    int mi = n >> 1;
    while(hi > lo){
        if(target == ele[mi])
            return mi;
        else if(target < ele[mi])
            hi = mi;
        else
            lo = mi + 1;
        mi = lo + ((hi - lo) >> 1);
    }
    return -1;
}

#endif //DATASTRUCTURE_SEARCH_H
