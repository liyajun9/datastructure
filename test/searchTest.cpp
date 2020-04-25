//
// Created by ralph on 4/25/20.
//

#include <gtest/gtest.h>
#include <chrono>
#include "../sort/sort.h"
#include "../sort/search.h"

#define TEST_ROUNDS 10
#define PRINT_OUTPUT
#define INPUT_SIZE 1000
#define RANDOM_RANGE 100000

TEST(searchTest, binarySearch){
    for( int k = 0; k < TEST_ROUNDS; ++k) {
        int res = -1;
        int target = 0;

        long timeCost = 0;

        std::vector<int> nums;
        int count = INPUT_SIZE;
        while (count--) {
            int tmp = std::rand() % RANDOM_RANGE;
            nums.emplace_back(tmp);
        }
        quickSort(&nums[0], nums.size());
        target = rand() % 2 ? nums[rand() % nums.size()] : 12345;

        std::cout << "binary search " << target << std::endl;

#ifdef PRINT_OUTPUT
        std::cout << "input array " << ": ";
        for (const auto n : nums)
            std::cout << n << " ";
        std::cout << std::endl;
#endif

        auto beginTime = std::chrono::steady_clock::now();
        res = binarySearch(target, &nums[0], nums.size());
        auto endTime = std::chrono::steady_clock::now();
        timeCost = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - beginTime).count();

        auto it = std::lower_bound(nums.begin(), nums.end(), target);
        int result = (it == nums.end() || *it != target) ? -1 : it - nums.begin();
        EXPECT_EQ(res, result);

        if (res >= 0)
            std::cout << "search result: ele[" << res << "] = " << nums[res] << std::endl;
        else
            std::cout << "can't find it in the array" << std::endl;

        std::cout << "binarySearch time cost : " << timeCost << "ms" << std::endl;
    }
}