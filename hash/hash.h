#ifndef TESTSKIPLIST_HASH_H
#define TESTSKIPLIST_HASH_H
#include <iostream>
#include <string>

namespace lyj
{
    //functions to convert from type K to non-negative integer derived from similar classes in SGI STL
    template <class K> class hash;

    template<> class hash<std::string>
    {
    public:
        size_t operator()(const std::string &theKey) const
        {
            unsigned long hashValue = 0;
            int length = (int)theKey.length();

            for (int i=0; i<length; ++i)
            {
                hashValue = hashValue*5 + theKey.at(i);
            }

            return size_t(hashValue);
        }
    };

    template<> class hash<int>
    {
    public:
        size_t operator()(const int theKey) const
        {
            return size_t(theKey);
        }
    };

    template<> class hash<long>
    {
    public:
        size_t operator()(const long theKey) const
        {
            return size_t(theKey);
        }
    };

    template<> class hash<uint16_t>
    {
    public:
        size_t operator()(const uint16_t theKey) const
        {
            return size_t(theKey);
        }
    };

    template<> class hash<uint32_t>
    {
    public:
        size_t operator()(const uint32_t theKey) const
        {
            return size_t(theKey);
        }
    };

    template<> class hash<uint64_t>
    {
    public:
        size_t operator()(const uint64_t theKey) const
        {
            return size_t(theKey);
        }
    };

}

#endif //TESTSKIPLIST_HASH_H
