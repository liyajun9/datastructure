#include "arrayQueue.h"

int main(int argc, char** argv)
{
    lyj::arrayQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    size_t num = q.size();
    for (auto i = 0; i < num; ++i)
    {
        std::cout << i << ": "<< q.front() << std::endl;
        q.pop();
    }
}
