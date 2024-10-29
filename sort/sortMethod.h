#ifndef TESTFIBONACCI_SORTMETHOD_H
#define TESTFIBONACCI_SORTMETHOD_H
#include <string>
#include <cstring>

namespace lyj
{

//merge sort
template<class T>
void merge2AdjacentSegments(T *arr, size_t n, size_t mid)
{
    T *auxArr = new T[n];
    memcpy(reinterpret_cast<void *>(auxArr), reinterpret_cast<const void *>(arr), n*sizeof(T));

    size_t idxOfFirst(0);
    size_t idxOfSecond(mid);
    size_t i(0);
    while (i < n && idxOfFirst < mid && idxOfSecond < n)
    {
        if (auxArr[idxOfFirst] < auxArr[idxOfSecond])
            arr[i++] = auxArr[idxOfFirst++];
        else
            arr[i++] = auxArr[idxOfSecond++];
    }

    if (i < n)
    {
        if (idxOfFirst < mid)
            memcpy(reinterpret_cast<void *>(&arr[i]), static_cast<const void *>(&auxArr[idxOfFirst]), (mid - idxOfFirst) * sizeof(T));
        else
            memcpy(reinterpret_cast<void *>(&arr[i]), static_cast<const void *>(&auxArr[idxOfSecond]), (n-idxOfSecond)*sizeof(T));
    }

    delete []auxArr;
}

template<class T>
void mergeSort(T *origArr, size_t n)
{
    if (n < 2) return;
    int mid = n >> 1;
    mergeSort(origArr, mid);
    mergeSort(origArr+mid, n-mid);
    merge2AdjacentSegments(origArr, n, mid);
}


//quick sort
template<class T>
int partition(T *arr, int begin, int end)
{
    //random select pivot
    std::swap(arr[end-1], arr[begin + std::rand() % (end-begin)]);
    int pivot = arr[end-1];

    int idxSmall = begin;
    int idx = begin; //skip the pivot
    for (; idx < end-1; ++idx)
    {
        if (arr[idx] < pivot)
        {
            std::swap(arr[idxSmall++], arr[idx]);
        }
    }

    if (idxSmall != end - 1)
        std::swap(arr[idxSmall], arr[end-1]);
    return idxSmall;
}

template<class T>
void quickSort(T *arr, int begin, int end)
{
    if (end - begin > 1)
    {
        int idxPivot = partition(arr, begin, end);

        quickSort(arr, begin, idxPivot);
        quickSort(arr, idxPivot+1, end);
    }
}

}
#endif //TESTFIBONACCI_SORTMETHOD_H
