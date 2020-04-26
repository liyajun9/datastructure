//
// Created by ralph on 3/26/20.
//

#ifndef DATASTRUCTURE_VECTOR_H
#define DATASTRUCTURE_VECTOR_H

#include <cstdlib>
#include <algorithm>

using Rank = int;

template <typename T>
class Vector{

protected:
    Rank _size;
    int _capacity;
    T* _elem;

    static constexpr int DEFAULT_CAPACITY = 3;

    void copyFrom(const T* A, Rank lo, Rank hi){        //copy from A[lo, hi)
        _capacity = 2 * (hi - lo);  //allocate memory of size = 2 * (hi - lo)
        _elem = new T[_capacity];
        _size = 0;
        while(lo < hi){
            _elem[_size++] = A[lo++];
        }
    }
    void expand(){                                      //expand to twice capacity
        if(_size < _capacity) return;
        if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for(int i = 0; i < _size; ++i){
            _elem[i] = oldElem[i];
        }
        delete [] oldElem;
    }
    void shrink(){
        if(_capacity <= DEFAULT_CAPACITY) return;
        if(_size << 2 > _capacity) return; //must >25% _capacity
        T* oldElem = _elem; _elem = new T[_capacity >>= 1];
        for(int i = 0; i < _size; ++i){
            _elem[i] = oldElem[i];
        }
        delete [] oldElem;
    }

    Rank binSearch(const T& e, Rank lo, Rank hi){
        while(lo < hi){
            Rank mi = (hi + lo) >> 1;
            if(e == _elem[mi])
                return mi;
            else if(e < _elem[mi])
                hi = mi;
            else
                lo = mi + 1;
        }
        return -1;
    }

    bool bubble(Rank lo, Rank hi){
        bool sorted = true;
        while(++lo < hi){
            if(_elem[lo - 1] > _elem[lo]) {
                sorted = false;
                std::swap(_elem[lo - 1], _elem[lo]);
            }
        }
        return sorted;
    }

    void bubbleSort(Rank lo, Rank hi){
        while (!bubble(lo, hi--));
    }

//    Rank max(Rank lo, Rank hi){
//
//    }
//    void selectionSort(Rank lo, Rank hi){
//
//    }

    void merge(Rank lo, Rank mi, Rank hi){
        T* A = _elem + lo;
        int lb = mi - lo;
        T* B = new T[lb];
        for(Rank i = 0; i < lb; ++i){
            B[i] = A[i];
        }
        T* C = _elem + mi;
        int lc = hi - mi;

        for(int i = 0, j = 0, k = 0; j < lb || k < lc; ){
            if((j < lb && ((k >= lc) || B[j] <= C[k]))) A[i++] = B[j++];
            if((k < lc && ((j >= lb) || C[k] < B[j]))) A[i++] = C[k++];
        }
        delete [] B;
    }

    void mergeSort(Rank lo, Rank hi){
        if(lo > hi - 2) return;
        Rank mi = (lo + hi) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi, hi);
        merge(lo, mi, hi);
    }

//    Rank partition(Rank lo, Rank hi){
//        return 0;
//    }
//    void quickSort(Rank lo, Rank hi){
//
//    }
//    void heapSort(Rank lo, Rank hi){
//
//    }

public:
    /* interfaces:
     * constructor:
         * 1. default. empty vector with capacity = 3
         * 2. copy
         * 3. move
     * destructor
     * copy&move control
     * size : size, empty
     * read-only
         * 1.[] (random access)
         * 2.traverse
         * 3.find / search
         * 4.disorder
     * write
         * 1.insert_back
         * 2.remove
         * 3.deduplicate / unique
         * 5.sort
         * 6.shuffle
         * -permute
    */
    explicit Vector(int capacity = DEFAULT_CAPACITY, int size = 0, T v = 0)
    :_size(size)
    ,_capacity(capacity){
        _elem = new T[_capacity];
        for(int i = 0; i < size; _elem[i++] = v);
    }

    Vector(const T* A, Rank n)
    :_capacity(DEFAULT_CAPACITY)
    ,_size(0)
    ,_elem(nullptr){ //ctor from part of other Vector(deep copy)
        copyFrom(A, 0, n);
    }

    Vector(const T* A, Rank lo, Rank hi)
    :_capacity(DEFAULT_CAPACITY)
    ,_size(0)
    ,_elem(nullptr){ //ctor from part of other Vector(deep copy)
        copyFrom(A, lo, hi);
    }

    Vector(const Vector<T>& v)
    :_capacity(DEFAULT_CAPACITY)
    ,_size(0)
    ,_elem(nullptr){ //copy ctor(deep copy)
        copyFrom(v._elem, 0, v._size);
    }

    Vector(const Vector<T>& v, Rank lo, Rank hi)
    :_capacity(DEFAULT_CAPACITY)
    ,_size(0)
    ,_elem(nullptr){ //copy ctor
        copyFrom(v._elem, lo, hi);
    }

    Vector(Vector<T>&& v) noexcept
    :_capacity(v._capacity)
    ,_size(v._size)
    ,_elem(v._elem) { //move ctor
        v._capacity = 0;
        v._size = 0;
        v._elem = nullptr;
    }

    Vector<T>& operator=(const Vector<T>& v){
        if(this == &v) return *this;
        delete [] _elem;
        copyFrom(v._elem, 0, v._size);
        return *this;
    }

    Vector<T>& operator=(Vector<T>&& v) noexcept{
        _capacity = v._capacity;
        _size = v._size;
        _elem = v._elem;
        v._capacity = 0;
        v._size = 0;
        v._elem = nullptr;
    }

    ~Vector() {
        delete [] _elem;
    }

    Rank size() const{
        return _size;
    }

    bool empty() const{
        return _size > 0;
    }

    int disorder() const{
        int count = 0;
        for(int i = 0; i < _size - 1; ++i){
            if(_elem[i] > _elem[i + 1])
                ++count;
        }
        return count;
    }

    Rank find(const T& e) const{
        return find(e, 0, _size);
    }

    Rank find(const T& e, Rank lo, Rank hi) const{
        while(hi-- > lo && (_elem[hi] != e));
        return hi;
    }

    T& operator[](Rank r) const{
        return _elem[r];
    }

    T remove(Rank r){
        T t = _elem[r];
        remove(r, r + 1);
        return t;
    }

    int remove(Rank lo, Rank hi){  //return number of elements be removed
        if(lo == hi) return 0;
        while(hi < _size){
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;
        shrink();
        return hi - lo;
    }

    Rank insert_back(const T& e){    //insert_back back
        insert(_size, e);
    }

    Rank insert(Rank r, const T& e){
        expand();
        for(Rank i = _size; i > r; --i){
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        ++_size;
        return r;
    }

    void shuffle(Rank lo, Rank hi){    //swap v[i-1] and v[rand() % i]
        T* v = _elem[lo];
        for(Rank i = hi - lo; i > 0; --i){
            std::swap(v[i - 1], v[rand() % (i)]);
        }
    }

    void shuffle(){
        shuffle(0, _size);
    }

    int deduplicate(){
        int oldSize = _size;
        for(int i = 0; i < _size; ++i){
            Rank r = find(_elem[i], i + 1, _size);
            if(r)   remove(r);
        }
        shrink();
        return oldSize - _size;
    }

    void traverse(void(*visit)(T&)){  //provide a pointer to function
        for(int i = 0; i < _size; ++i)
            visit(_elem[i]);
    }

    template <typename VST> void traverse(VST& visit){ //provide a functor
        for(int i = 0; i < _size; ++i){
            visit(_elem[i]);
        }
    }

    void sort(Rank lo, Rank hi){
        mergeSort(lo, hi);
    }

    void sort(){
        sort(0, _size);
    }

    Rank search(const T& e) const{ //for ordered vector
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    Rank search(const T& e, Rank lo, Rank hi){
        return binSearch(e, lo, hi);
    }

    int unique(){
        Rank i = 0;
        for(Rank j = 1; j < _size; ++j){
            if(_elem[i] != _elem[j]){
                _elem[++i] = _elem[j];
            }
        }
        Rank n = _size - ++i;
        _size = i;
        return n;
    }
};

//template <typename T> void permute(Vector<T>& v){
//    for(int i = v.size(); i > 0; --i)
//        std::swap(v[i - 1], v[rand() % i]);
//}

#endif //DATASTRUCTURE_VECTOR_H
