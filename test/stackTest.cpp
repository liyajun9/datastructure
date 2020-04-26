//
// Created by ralph on 4/26/20.
//

#include <gtest/gtest.h>
#include "../stack/stack.h"

TEST(stackTest, basic)
{
    Stack<int> stack;
    int len = rand() % 10 + 1;
    while(len--){
        stack.push(rand() % 100);
    }
    std::cout << "after while(len--), len = " << len << std::endl;
    int size = stack.size();
    for(int i = 0; i < size; ++i){
        std::cout << stack.pop() << " ";
    }
    std::cout << std::endl;
    EXPECT_EQ(stack.size(), 0);
}

TEST(stackTest, radixConvert)
{
    std::string sNum = radixConvert(54234523, 16);
    std::cout << "result is: " << sNum << std::endl;
}

