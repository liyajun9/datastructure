//
// Created by ralph on 4/24/20.
//

#include <gtest/gtest.h>
#include <chrono>
#include "../sort/sort.h"

TEST(sort, bubbleSort) {
    std::cout << "bubble sort" << std::endl;
    long timeCost = 0;
    for(int i = 0 ; i < 100; ++i){
        std::vector<int> nums;
        int count = std::rand()%10 + 1;
        std::cout << "input array " << i << ": ";
        while(count--){
            int tmp = std::rand()%1000;
            std::cout << tmp << " ";
            nums.emplace_back(tmp);
        }
        std::cout << std::endl;

        auto beginTime = std::chrono::steady_clock::now();
        bubbleSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
        EXPECT_FALSE(foundUnsorted);

        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
    }
    std::cout << "time cost : " << timeCost << "ns" << std::endl;
}

TEST(sort, insertionSort) {
    std::cout << "insertion sort" << std::endl;
    long timeCost = 0;
    for(int i = 0 ; i < 100; ++i){
        std::vector<int> nums;
        int count = std::rand()%10 + 1;
        std::cout << "input array " << i << ": ";
        while(count--){
            int tmp = std::rand()%1000;
            std::cout << tmp << " ";
            nums.emplace_back(tmp);
        }
        std::cout << std::endl;

        auto beginTime = std::chrono::steady_clock::now();
        insertionSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
        EXPECT_FALSE(foundUnsorted);

        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
    }
    std::cout << "time cost : " << timeCost << "ns" << std::endl;

}