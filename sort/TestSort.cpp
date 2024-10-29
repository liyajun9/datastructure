#include "sortMethod.h"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    // test mergeSort
    int arr[] = {43,6546,91,321,98,3,9823,7565,67454,982,765,544,8765,986,123};
    size_t n = sizeof(arr)/sizeof(int);

    lyj::mergeSort(arr, n);
    for (auto i=0; i<n; ++i)
        std::cout << i << ": " << arr[i] << std::endl;

    // test quickSort
    int arr1[] = {43,6546,91,321,98,3,9823,7565,67454,982,765,544,8765,986,123};
    size_t n1 = sizeof(arr1)/sizeof(int);
    lyj::quickSort(arr1, 0, n1);
    for (auto i=0; i<n1; ++i)
        std::cout << i << ": " << arr1[i] << std::endl;

    return 0;
}