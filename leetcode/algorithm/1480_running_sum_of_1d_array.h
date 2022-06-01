#pragma once

// https://leetcode.com/problems/running-sum-of-1d-array/

/*
* 1480. Running Sum of 1d Array
* 
* Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]¡­nums[i]).
* Return the running sum of nums.
* 
* Example 1:
* Input: nums = [1,2,3,4]
* Output: [1,3,6,10]
* Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
*
* Example 2:
* Input: nums = [1,1,1,1,1]
* Output: [1,2,3,4,5]
* Explanation: Running sum is obtained as follows: [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1].
*
* Example 3:
* Input: nums = [3,1,2,10,1]
* Output: [3,4,6,16,17]
* 
* 
* Constraints:
*  1 <= nums.length <= 1000
*  -10^6 <= nums[i] <= 10^6
*/

#include <vector>
#include <gtest/gtest.h>

#include "../util/std_util.h"

namespace RunningSumOf1dArray {
    class Solution {
    public:
        std::vector<int> runningSum(std::vector<int>& nums) {
            std::vector<int> ret;
            int sum = 0;
            for (auto ite = nums.begin(); ite != nums.end(); ite++) {
                sum += *ite;
                ret.push_back(sum);
            }
            return ret;
        }
    };

    bool testRunningSum(const char* input, const char* expected) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        std::vector<int> output = Solution().runningSum(nums);
        std::vector<int> expectedVector = StdUtil::generateIntVector(expected);
        return StdUtil::compareEqualVector<int>(output, expectedVector);
    }
}

TEST(_1480_RunningSumOf1dArray, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [1,2,3,4]
    * Output: [1,3,6,10]
    */
    EXPECT_TRUE(RunningSumOf1dArray::testRunningSum("[1,2,3,4]", "[1,3,6,10]"));

    /*
    * Example 2:
    * Input: nums = [1,1,1,1,1]
    * Output: [1,2,3,4,5]
    */
    EXPECT_TRUE(RunningSumOf1dArray::testRunningSum("[1,1,1,1,1]", "[1,2,3,4,5]"));

    /*
    * Example 3:
    * Input: nums = [3,1,2,10,1]
    * Output: [3,4,6,16,17]
    */
    EXPECT_TRUE(RunningSumOf1dArray::testRunningSum("[3,1,2,10,1]", "[3,4,6,16,17]"));
}