#ifndef TESTSKIPLIST_HASHCHAIN_H
#define TESTSKIPLIST_HASHCHAIN_H
#include "hash.h"
#include "../dictionary/dictionary.h"
#include "../dictionary/sortedChain.h"

namespace lyj
{
    template<class K, class E>
    class hashChains : public dictionary<K, E>
    {
    public:
        hashChains(int theDivisor = 11)
        {
            divisor = theDivisor;
            dSize = 0;

            table = new sortedChain<K, E>[divisor];
        }

        ~hashChains()
        {
            delete []table;
        }

        bool empty() const
        {
            return dSize == 0;
        }

        int size() const
        {
            return dSize;
        }

        std::pair<const K, E>* find(const K& theKey) const
        {
            int homeBucket = hashFn(theKey) % divisor;
            return table[homeBucket].find(theKey);
        }

        void insert(const std::pair<const K, E>& thePair)
        {
            int homeBucket = hashFn(thePair.first) % divisor;
            int homeSize = table[homeBucket].size();
            table[homeBucket].insert(thePair);
            if (table[homeBucket].size() > homeSize) //insert successful
                ++dSize;
        }

        void erase(const K& theKey)
        {
            int bucket = hashFn(theKey) % divisor;
            table[bucket].erase(theKey);
        }

        void output(std::ostream& out) const
        {
            for (int i=0; i<divisor; ++i)
            {
                if (table[i].size() == 0)
                    out << "NULL" << std::endl;
                else
                {
                    table[i].output(out);
                }
            }
        }

    protected:
        sortedChain<K, E>* table;       //hash table
        hash<K> hashFn;
        int dSize;
        int divisor;
    };

    template<class K, class E>
    std::ostream& operator<<(std::ostream &out, const hashChains<K, E>& x)
    {
        x.output(out);
        return out;
    }
}


#endif //TESTSKIPLIST_HASHCHAIN_H
