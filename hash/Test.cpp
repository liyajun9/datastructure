#include "hashTable.h"
#include "hashChain.h"

int main(int argc, char** argv)
{
    //test hashTable
    lyj::hashTable<int, int> z(11);
    std::pair<int, int> p;

    p.first = 2; p.second = 10;
    z.insert(p);
    p.first = 10; p.second = 50;
    z.insert(p);
    p.first = 24; p.second = 120;
    z.insert(p);
    p.first = 32; p.second = 160;
    z.insert(p);
    p.first = 3; p.second = 15;
    z.insert(p);
    p.first = 12; p.second = 60;
    z.insert(p);

    std::cout << "The dictionary is " << std::endl << z << std::endl;
    std::cout << "Its size is " << z.size() << std::endl;

    std::cout << "Element associated with 2 is " << z.find(2)->second << std::endl;
    std::cout << "Element associated with 10 is " << z.find(10)->second << std::endl;
    std::cout << "Element associated with 12 is " << z.find(12)->second << std::endl;

    //test hashChain
    lyj::hashChains<int, int> c(11);
    std::pair<int, int> q;

    q.first = 2; q.second = 10;
    c.insert(q);
    q.first = 10; q.second = 50;
    c.insert(q);
    q.first = 24; q.second = 120;
    c.insert(q);
    q.first = 32; q.second = 160;
    c.insert(q);
    q.first = 3; q.second = 15;
    c.insert(q);
    q.first = 12; q.second = 60;
    c.insert(q);

    std::cout << "The dictionary is " << std::endl << c << std::endl;
    std::cout << "Its size is " << c.size() << std::endl;

    std::cout << "Element associated with 2 is " << c.find(2)->second << std::endl;
    std::cout << "Element associated with 10 is " << c.find(10)->second << std::endl;
    std::cout << "Element associated with 12 is " << c.find(12)->second << std::endl;
}