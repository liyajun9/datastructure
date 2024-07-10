#include "skipList.h"

int main(int argc, char** argv)
{
    lyj::skipList<int, int> z(1000);
    std::pair<int, int> p;

    p.first = 2; p.second = 10;
    z.insert(p);

    p.first = 10; p.second = 50;
    z.insert(p);

    p.first = 6; p.second = 30;
    z.insert(p);

    p.first = 8; p.second = 40;
    z.insert(p);

    p.first = 1; p.second = 5;
    z.insert(p);

    p.first = 12; p.second = 60;
    z.insert(p);

    std::cout << "The dictionary is " << z << std::endl;
    std::cout << "Its size is " << z.size() << std::endl;

    std::cout << "Element associated with 1 is " << z.find(1)->second << std::endl;
    std::cout << "Element associated with 6 is " << z.find(6)->second << std::endl;
    std::cout << "Element associated with 12 is " << z.find(12)->second << std::endl;

    z.erase(1);
    z.erase(2);
    z.erase(6);
    z.erase(12);
    std::cout << "Deleted 1, 2, 6, 12" << std::endl;
    std::cout << "The dictionary is " << z << std::endl;
    std::cout << "Its size is " << z.size() << std::endl;
}
