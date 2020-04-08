//
// Created by ralph on 3/31/20.
//

#ifndef DATASTRUCTURE_DOUBLYLINKEDLIST_H
#define DATASTRUCTURE_DOUBLYLINKEDLIST_H

#include <cstddef>

#define ListNodePosi(T) ListNode<T>*

using Rank = int;

template<typename T>
class ListNode {
    /* interfaces:
     * constructor:
         * 1.default. Note: this is only used to construct List::head and List::tail. all data members are with random value.
         * 2.with data provided. m_prev and m_next are set to nullptr.
         * 3.with data, m_prev, m_next provided.
     * insertAsPrev
     * insertAsNext
     */
public:
    ListNode() {} //used only to construct List::head and List::tail
    explicit ListNode(T data): m_data(data), m_prev(nullptr), m_next(nullptr){}
    ListNode(T data, ListNodePosi(T) prev, ListNodePosi(T) next){}

    ListNodePosi(T) insertAsPrev(const T& e){
        ListNodePosi(T) newElem = new ListNode(e);
        newElem->m_prev = m_prev; if(m_prev) m_prev->m_next = newElem;
        newElem->m_next = this; m_prev = newElem;
        return newElem;
    }

    ListNodePosi(T) insertAsNext(const T& e){
        ListNodePosi(T) newElem = new ListNode(e);
        newElem->m_next = m_next; if(m_next) m_next->m_prev = newElem;
        newElem->m_prev = this; m_next = newElem;
        return newElem;
    }

public:
    T m_data;
    ListNodePosi(T) m_prev;
    ListNodePosi(T) m_next;
};

template<typename T>
class List{
protected:
    void init(){
        m_head = new ListNode<T>;
        m_tail = new ListNode<T>;
        m_head->m_prev = nullptr; m_head->m_next = m_tail;
        m_tail->m_next = nullptr; m_tail->m_prev = m_head;
        m_size = 0;
    }

    int clear(){
        int oldSize = m_size;
        for(int i = 0; i < oldSize; ++i)
            remove(first());
        return oldSize;
    }

    void copyNodes(ListNodePosi(T) elem, int n){ //copy from list (n nodes from elem)
        init();
        while(n--) {
            insertAsLast(elem->m_data);
            elem = elem->m_next;
        }
    }

    ListNodePosi(T) selectMax(ListNodePosi(T) p, int n){
        ListNodePosi(T) maxNode = p;
        while(n-- > 1 && (p = p->m_next) != m_tail){
            if(p->m_data > maxNode->m_data){
                maxNode = p;
            }
        }
        return maxNode;
    }

    ListNodePosi(T) selectMax(){
        return selectMax(first(), m_size);
    }

    void selectionSort(ListNodePosi(T)& p, int n){
        ListNodePosi(T) tailPos = p;
        for(int i = 0; i < n; ++i)
            tailPos = tailPos->m_next;
        ListNodePosi(T) headPos = p->m_prev;
        while(n-- > 1){
            ListNodePosi(T) max = selectMax(headPos->m_next, n);
            insertBefore(tailPos, max->m_data);
            remove(max);
            tailPos = tailPos->m_prev;
        }
    }

    void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T)& q, int m){
        ListNodePosi(T) head = p->m_prev;
        while(m > 0){
            if(n > 0 && p->m_data <= q->m_data){
                p = p->m_next;
                if(p == q) break;
                n--;
            }else{
                insertBefore(p, q->m_data);
                q = q->m_next;
                L.remove(q->m_prev);
                m--;
            }
        }
        p = head->m_next;
    }

    void mergeSort(ListNodePosi(T)& p, int n){
        if(n < 2) return;
        int m = (n >> 1);
        ListNodePosi(T) q = p;
        for(int i = 0; i < m; ++i)
            q = q->m_next;

        mergeSort(p, m);
        mergeSort(q, n-m);
        merge(p, m, *this, q, n-m);
    }

    void insertionSort(ListNodePosi(T)& p, int n){ //sort n elements start from p
        size_t num = 1;
        p = p->m_next;
        ListNodePosi(T) q;
        while(n-- > 1){
            q = p->m_next;
            insertBefore(search(p->m_data, first(), num++), p->m_data);
            remove(p); p = q;
        }
    }

public:
    /* interfaces:
     * constructor:
         * 1.default. empty list with only head and tail.
         * 2.copied from specified list.
     * destructor: release all nodes and head and tail.
     * size: size, empty.
     * read-only:
         * 1.[](random access), first, last
         * 2.traverse
         * 3.find / search
     * write:
         * 1.insertAsFirst, insertAsLast, insertBefore, insertAfter
         * 2.remove
         * 3.deduplicate, unique
         * 4.sort
     */
    List(){
        init();
    }

    List(const List<T>& list):m_size(list.m_size){
        copyNodes(list.first(), m_size);
    }

    List(const List<T>& list, Rank r, int n){
        copyNodes(list[r], n);
    }

    List(ListNodePosi(T) elem, int n){
        copyNodes(elem, n);
    }

    ~List(){
        clear();
        delete m_head;
        delete m_tail;
    }

    Rank size() const { return m_size; }
    bool empty() const { return m_size <= 0;}
    T& operator[](Rank r) const{
        ListNodePosi(T) p = m_head;
        while(r-- >= 0){  p = p->m_next;  }
        return p->m_data;
    }
    ListNodePosi(T) first() const { return m_head->m_next; }
    ListNodePosi(T) last() const { return m_tail->m_prev; }
    bool valid(ListNodePosi(T) p){
        return p && (m_head != p) && (m_tail != p);
    }

    int disorder() const{

    }

    ListNodePosi(T) find(const T& e, ListNodePosi(T) p, int n) const { //find the first element which has value of e
        while(n--){
            if(p->m_data == e) return p;
            p = p->m_next;
        }
        return nullptr;
    }

    ListNodePosi(T) find(const T& e) const{
        return find(e, first(), m_size);
    }

    ListNodePosi(T) search(const T& e, ListNodePosi(T) p, int n) const{
        while(n--){
            if(p->m_data >= e) break;
            p = p->m_next;
        }
        return p; //may be left boundary if search failed. invoker must verify the return value.
    }

    ListNodePosi(T) search(const T& e) const{
        return search(e, first(), m_size);
    }

    ListNodePosi(T) insertAsFirst(const T& e){
        ++m_size;
        return m_head->insertAsNext(e);
    }

    ListNodePosi(T) insertAsLast(const T& e){
        ++m_size;
        return m_tail->insertAsPrev(e);
    }

    ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e){
        ++m_size;
        return p->insertAsNext(e);
    }

    ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e){
        ++m_size;
        p->insertAsPrev(e);
    }

    T remove(ListNodePosi(T) p){
        --m_size;
        p->m_prev->m_next = p->m_next;
        p->m_next->m_prev = p->m_prev;
        T e = p->m_data;
        delete p;
        return e;
    }

    void merge(List<T>& L);

    void sort(ListNodePosi(T) p, int n){
//        insertionSort(p, n);
//        selectionSort(p, n);
        mergeSort(p, n);
    }

    void sort(){
        sort(first(), m_size);
    }

    int deduplicate(){  //unsorted list.  return removed number
        if(m_size < 2) return 0;
        int oldSize = m_size;
        ListNodePosi(T) p = m_head; int num = 1;
        while((p = p->m_next) != m_tail){
            ListNodePosi(T) q = find(p->m_data, first(), num);
            q ? remove(p) : ++num;
        }
        return oldSize - m_size;
    }

    int unique(){ //sorted list. return removed number
        if(m_size < 2) return 0;
        size_t oldSize = m_size;
        ListNodePosi(T) p = first(); ListNodePosi(T) q;
        while((q = p->m_next) != m_tail){
            q->m_data == p->m_data ? remove(q) : p = q;
        }
        return oldSize - m_size;
    }

//    void reverse();

    void traverse(void (*visit)(T& )){
        ListNodePosi(T) p = m_head;
        while((p = p->m_next) != m_tail){
            visit(p->m_data);
        }
    }

    template <typename VST> void traverse(VST& vst){
        ListNodePosi(T) p = m_head;
        while((p = p->m_next) != m_tail){
            vst(p->m_data);
        }
    }

private:
    size_t m_size;
    //with sentinel nodes, every element in the List has both prev and next, avoid boundary degeneration
    ListNodePosi(T) m_head; //head sentinel node
    ListNodePosi(T) m_tail; //tail sentinel node
};


#endif //DATASTRUCTURE_DOUBLYLINKEDLIST_H
