#include "binarySearchTree.h"
#include "binarySearchTreeWithVisit.h"
#include <iostream>

void visit(char& u)
{
    std::cout << "element value is " << u << std::endl;
}

int main(int argc, char **argv)
{
    //Test binarySearchTree
    lyj::binarySearchTree<int, char> y;
    y.insert(std::pair<int, char>(1, 'a'));
    y.insert(std::pair<int, char>(6, 'c'));
    y.insert(std::pair<int, char>(4, 'b'));
    y.insert(std::pair<int, char>(8, 'd'));
    std::cout << "Tree size is " << y.size() << std::endl;
    std::cout << "Elements in ascending order are" << std::endl;
    y.ascend();

    std::pair<const int, char> *s = y.find(4);
    std::cout << "Search for 4 succeeds" << std::endl;
    std::cout << s->first << ' ' << s->second << std::endl;
    y.erase(4);
    std::cout << "4 deleted " << std::endl;
    std::cout << "Tree size is " << y.size() << std::endl;
    std::cout << "Elements in ascending order are" << std::endl;
    y.ascend();

    s = y.find(8);
    std::cout << "Search for 8 succeeds" << std::endl;
    std::cout << s->first << ' ' << s->second << std::endl;
    y.erase(8);
    std::cout << "8 deleted " << std::endl;
    std::cout << "Tree size is " << y.size() << std::endl;
    std::cout << "Elements in ascending order are" << std::endl;
    y.ascend();

    s = y.find(6);
    std::cout << "Search for 6 succeeds" << std::endl;
    std::cout << s->first << ' ' << s->second << std::endl;
    y.erase(6);
    std::cout << "6 deleted " << std::endl;
    std::cout << "Tree size is " << y.size() << std::endl;
    std::cout << "Elements in ascending order are" << std::endl;
    y.ascend();

    s = y.find(1);
    std::cout << "Search for 1 succeeds" << std::endl;
    std::cout << s->first << ' ' << s->second << std::endl;
    y.erase(1);
    std::cout << "1 deleted " << std::endl;
    std::cout << "Tree size is " << y.size() << std::endl;
    std::cout << "Elements in ascending order are" << std::endl;
    y.ascend();


    //Test binarySearchTreeWithVisit
    lyj::binarySearchTreeWithVisit<int, char> z;
    z.insert(std::pair<int, char>(1, 'a'), visit);
    z.insert(std::pair<int, char>(6, 'c'), visit);
    z.insert(std::pair<int, char>(4, 'b'), visit);
    z.insert(std::pair<int, char>(8, 'd'), visit);
    std::cout << "Tree size is " << z.size() << std::endl;
    std::cout << "Elements in ascending order are" << std::endl;
    z.ascend();
}
