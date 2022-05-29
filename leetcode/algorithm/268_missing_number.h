#pragma once

// https://leetcode.com/problems/missing-number/

/*
* 268. Missing Number
* 
* Given an array nums containing n distinct numbers in the range [0, n], 
* return the only number in the range that is missing from the array.
* 
* Example 1:
* Input: nums = [3,0,1]
* Output: 2
* Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 
* 2 is the missing number in the range since it does not appear in nums.
* 
* Example 2:
* Input: nums = [0,1]
* Output: 2
* Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 
* 2 is the missing number in the range since it does not appear in nums.
* 
* Example 3:
* Input: nums = [9,6,4,2,3,5,7,0,1]
* Output: 8
* Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 
* 8 is the missing number in the range since it does not appear in nums.
* 
* Constraints:
*  n == nums.length
*  1 <= n <= 104
*  0 <= nums[i] <= n
*  All the numbers of nums are unique.
* 
* Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>

#include "../util/std_util.h"

namespace MissingNumber {
    class Solution {
    public:
        int missingNumber(std::vector<int>& nums) {
            std::priority_queue<int, std::vector<int>, std::greater<int>> values;
            for (auto ite = nums.begin(); ite != nums.end(); ite++) {
                values.push(*ite);
            }
            int n = 0;
            while (!values.empty())
            {
                if (n != values.top()) {
                    return n;
                }
                n++;
                values.pop();
            }
            return n;
        }
    };

    int testMissingNumber(const char* input) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        return Solution().missingNumber(nums);
    }
}

TEST(_268_MissingNumber, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [3,0,1]
    * Output: 2
    * Explanation: n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 
    * 2 is the missing number in the range since it does not appear in nums.
    */
    EXPECT_EQ(2, MissingNumber::testMissingNumber("[3,0,1]"));

    /* 
    * Example 2:
    * Input: nums = [0,1]
    * Output: 2
    * Explanation: n = 2 since there are 2 numbers, so all numbers are in the range [0,2]. 
    * 2 is the missing number in the range since it does not appear in nums.
    */
    EXPECT_EQ(2, MissingNumber::testMissingNumber("[0,1]"));

    /* 
    * Example 3:
    * Input: nums = [9,6,4,2,3,5,7,0,1]
    * Output: 8
    * Explanation: n = 9 since there are 9 numbers, so all numbers are in the range [0,9]. 
    * 8 is the missing number in the range since it does not appear in nums.
    */
    EXPECT_EQ(8, MissingNumber::testMissingNumber("[9,6,4,2,3,5,7,0,1]"));
}