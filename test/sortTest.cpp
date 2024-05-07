//
// Created by ralph on 4/24/20.
//

#include <chrono>
#include "../sort/sort.h"
#include <vector>
#include <iostream>

#define PRINT_OUTPUT
#define TEST_ROUNDS 1
#define INPUT_SIZE 50 * 10
#define RANDOM_RANGE 100000

void testQuickSort()
{
#ifdef PRINT_OUTPUT
    std::cout << "quick sort" << std::endl;
#endif
    long timeCost = 0;
    for(int i = 0 ; i < TEST_ROUNDS; ++i){
        std::vector<int> nums;
        int count = std::rand()%INPUT_SIZE + 1;
#ifdef PRINT_OUTPUT
        std::cout << "input array " << i << ": ";
#endif
        while(count--){
            int tmp = std::rand()%RANDOM_RANGE;
#ifdef PRINT_OUTPUT
            std::cout << tmp << " ";
#endif
            nums.emplace_back(tmp);
        }
#ifdef PRINT_OUTPUT
        std::cout << std::endl;
#endif

        auto beginTime = std::chrono::steady_clock::now();
        quickSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
//        EXPECT_FALSE(foundUnsorted);

#ifdef PRINT_OUTPUT
        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
#endif
    }
    std::cout << "quick sort time cost : " << timeCost << "ms" << std::endl;

}

void testMergeSort()
{
#ifdef PRINT_OUTPUT
    std::cout << "merge sort" << std::endl;
#endif
    long timeCost = 0;
    for(int i = 0 ; i < TEST_ROUNDS; ++i){
        std::vector<int> nums;
        int count = std::rand()%INPUT_SIZE + 1;
#ifdef PRINT_OUTPUT
        std::cout << "input array " << i << ": ";
#endif
        while(count--){
            int tmp = std::rand()%RANDOM_RANGE;
#ifdef PRINT_OUTPUT
            std::cout << tmp << " ";
#endif
            nums.emplace_back(tmp);
        }
#ifdef PRINT_OUTPUT
        std::cout << std::endl;
#endif

        auto beginTime = std::chrono::steady_clock::now();
        mergeSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
//        EXPECT_FALSE(foundUnsorted);

#ifdef PRINT_OUTPUT
        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
#endif
    }
    std::cout << "merge sort time cost : " << timeCost << "ms" << std::endl;

}

void testInsertionSort(){
#ifdef PRINT_OUTPUT
    std::cout << "insertion sort" << std::endl;
#endif
    long timeCost = 0;
    for(int i = 0 ; i < TEST_ROUNDS; ++i){
        std::vector<int> nums;
        int count = std::rand()%INPUT_SIZE + 1;
#ifdef PRINT_OUTPUT
        std::cout << "input array " << i << ": ";
#endif
        while(count--){
            int tmp = std::rand()%RANDOM_RANGE;
#ifdef PRINT_OUTPUT
            std::cout << tmp << " ";
#endif
            nums.emplace_back(tmp);
        }
#ifdef PRINT_OUTPUT
        std::cout << std::endl;
#endif

        auto beginTime = std::chrono::steady_clock::now();
        insertionSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
//        EXPECT_FALSE(foundUnsorted);

#ifdef PRINT_OUTPUT
        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
#endif
    }
    std::cout << "insertion sort time cost : " << timeCost << "ms" << std::endl;

}

void testSelectionSort()
{
#ifdef PRINT_OUTPUT
    std::cout << "selection sort" << std::endl;
#endif
    long timeCost = 0;
    for(int i = 0 ; i < TEST_ROUNDS; ++i){
        std::vector<int> nums;
        int count = std::rand()%INPUT_SIZE + 1;
#ifdef PRINT_OUTPUT
        std::cout << "input array " << i << ": ";
#endif
        while(count--){
            int tmp = std::rand()%RANDOM_RANGE;
#ifdef PRINT_OUTPUT
            std::cout << tmp << " ";
#endif
            nums.emplace_back(tmp);
        }
#ifdef PRINT_OUTPUT
        std::cout << std::endl;
#endif

        auto beginTime = std::chrono::steady_clock::now();
        selectionSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
//        EXPECT_FALSE(foundUnsorted);

#ifdef PRINT_OUTPUT
        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
#endif
    }
    std::cout << "selection sort time cost : " << timeCost << "ms" << std::endl;

}

void testBubbleSort()
{
#ifdef PRINT_OUTPUT
    std::cout << "bubble sort" << std::endl;
#endif
    long timeCost = 0;
    for(int i = 0 ; i < TEST_ROUNDS; ++i){
        std::vector<int> nums;
        int count = std::rand()%INPUT_SIZE + 1;
#ifdef PRINT_OUTPUT
        std::cout << "input array " << i << ": ";
#endif
        while(count--){
            int tmp = std::rand()%RANDOM_RANGE;
#ifdef PRINT_OUTPUT
            std::cout << tmp << " ";
#endif
            nums.emplace_back(tmp);
        }
#ifdef PRINT_OUTPUT
        std::cout << std::endl;
#endif

        auto beginTime = std::chrono::steady_clock::now();
        bubbleSort(&nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();

        bool foundUnsorted = (nums.end() != std::adjacent_find(nums.begin(), nums.end(), std::greater<int>()));
//        EXPECT_FALSE(foundUnsorted);

#ifdef PRINT_OUTPUT
        std::cout << "output array " << i << ": ";
        for(const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
#endif
    }
    std::cout << "bubble sort time cost : " << timeCost << "ms" << std::endl;
}