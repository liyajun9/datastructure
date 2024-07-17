#ifndef TESTSKIPLIST_HASHTABLE_H
#define TESTSKIPLIST_HASHTABLE_H
#include <iostream>
#include "hash.h"

namespace lyj
{
    template<class K, class E>
    class hashTable
    {
    public:
        hashTable(int theDivisor = 11); //default <20 divisor
        ~hashTable()
        {
            delete [] table;
        }

        bool empty() const
        {
            return dSize == 0;
        }

        int size() const
        {
            return dSize;
        }

        std::pair<const K, E>* find(const K&) const;

        void insert(const std::pair<const K, E>&);

        void output(std::ostream& out) const;

    protected:
        int search(const K&) const;

    protected:
        hash<K> hashFn;                //maps type K to non-negative integer
        std::pair<const K, E>** table; //hashTable. an array of pair<const K, E>*

        int dSize;
        int divisor;
    };

    template<class K, class E>
    hashTable<K, E>::hashTable(int theDivisor)
    {
        divisor = theDivisor;
        dSize = 0;

        table = new std::pair<const K, E>*[divisor]();
        for (int i=0; i<divisor; ++i)
            table[i] = NULL;
    }

    // Search an open addressed hash table for a pair with key theKey.
    // Return location of matching pair if found, otherwise return
    // location where a pair with key theKey may be inserted
    // provided the hash table is not full.
    template<class K, class E>
    int hashTable<K, E>::search(const K &theKey) const
    {
        int homeBucket = (int)hashFn(theKey) % divisor;
        int pos = homeBucket;
        do{
           if (table[pos] == NULL
           || table[pos]->first == theKey)
               return pos;

           pos = ++pos % divisor;
        } while (pos != homeBucket);

        return homeBucket; //full, return homeBucket
    }

    template<class K, class E>
    std::pair<const K, E>* hashTable<K, E>::find(const K &theKey) const
    {
        int pos = search(theKey);
        if (table[pos]->first == theKey)
            return table[pos];

        return NULL;
    }

    template<class K, class E>
    void hashTable<K, E>::insert(const std::pair<const K, E> &thePair)
    {
        const K &theKey = thePair.first;
        int pos = search(theKey);

        if (table[pos] == NULL)
        {
            table[pos] = new std::pair<const K, E>(thePair);
            ++dSize;
        }
        else
        {
            if (table[pos]->first == theKey)
            {
                table[pos]->second = thePair.second; //update
            }
            else
                throw std::exception();
        }
    }

    template<class K, class E>
    void hashTable<K, E>::output(std::ostream &out) const
    {
        for (int i=0; i<divisor; ++i)
        {
            if (table[i] == NULL)
                out << "NULL" << std::endl;
            else
                out << table[i]->first << " " << table[i]->second << std::endl;
        }
    }

    //overload <<
    template<class K, class E>
    std::ostream& operator<<(std::ostream& out, hashTable<K, E>& x)
    {
        x.output(out);
        return out;
    }
}

#endif //TESTSKIPLIST_HASHTABLE_H
