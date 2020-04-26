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
   for(int i = 1 ; i < n; ++i){ //for [1,n), insert_back into left sorted array
       //insertion
       int key = ele[i];
       for(int j = i - 1; j >= 0; --j){
           if(ele[j] > key)
               ele[j+1] = ele[j];    //move all greater elements right toward
           else {
               ele[j+1] = key;      //insert_back the key and break
               break;
           }
       }
   }
}

template <typename T>
void selectionSort(T* ele, size_t n) {
    for(int i = 0; i < n; ++i){     //for[0, n), select the smallest, place in the left
        int index = i;
        for(int j = i + 1; j < n; ++j){ //for[i+1, n), find the smallest
            if(ele[j] < ele[index]){
                index = j;
            }
        }
        std::swap(ele[i], ele[index]);  //swap smallest and left position
    }
}

template <typename T>
void merge(T* ele, size_t n, size_t mi){
    T* arrA = new T[mi]; std::copy(ele, ele + mi, arrA);
    int lenA = mi;
    T* arrB = ele + mi;
    int lenB = n - mi;

    T* arrC = ele;
    int k = 0;
    for(int i = 0, j = 0; i < lenA || j < lenB;){
        if(i < lenA && (j >= lenB || arrA[i] <= arrB[j])) arrC[k++] = arrA[i++];
        if(j < lenB && (i >= lenA || arrB[j] < arrA[i])) arrC[k++] = arrB[j++];
    }
    delete []arrA;
}

template <typename T>
void mergeSort(T* ele, size_t n) {
    if(n < 2) return;
    int mi = n >> 1;
    mergeSort(ele, mi);
    mergeSort(ele + mi, n - mi);
    merge(ele, n, mi);
}

template <typename T>
size_t partition(T* ele, size_t n){
    std::swap(ele[0], ele[std::rand() % n]);
    T pivot = ele[0];
    int lo = 0;
    int hi = n - 1;
    while(lo < hi){
        while(lo < hi){
            if(ele[hi] > pivot)
                --hi;
            else{
                ele[lo++] = ele[hi]; //will not check this ele again
                break;
            }
        }

        while(lo < hi){
            if(ele[lo] < pivot)
                ++lo;
            else{
                ele[hi--] = ele[lo];  //will not check this ele again
                break;
            }
        }
    }
    ele[lo] = pivot;
    return lo;
}

template <typename T>
void quickSort(T* ele, size_t n) {
    if(n < 2) return;
    size_t mi = partition(ele, n);
    quickSort(ele, mi);
    quickSort(ele + mi + 1, n - mi - 1);
}

template <typename T>
void heapSort(T* ele, size_t n) {

}

#endif //DATASTRUCTURE_SORT_H
