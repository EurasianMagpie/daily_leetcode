#pragma once

// https://leetcode.com/problems/non-decreasing-array/
/*
* 665. Non-decreasing Array
* 
* Given an array nums with n integers, your task is to check if it could become non-decreasing by
modifying at most one element.
*
* We define an array is non-decreasing if nums[i] <= nums[i + 1] holds for every i (0-based) such
* that (0 <= i <= n - 2).
* 
* Example 1:
* Input: nums = [4,2,3]
* Output: true
* Explanation: You could modify the first 4 to 1 to get a non-decreasing array.
*
* Example 2:
* Input: nums = [4,2,1]
* Output: false
* Explanation: You can't get a non-decreasing array by modify at most one element.
*
* Constraints:
*    n == nums.length
*    1 <= n <= 10^4
*    -10^5 <= nums[i] <= 10^5
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace NonDecreasingArray {
    class Solution {
    public:
        bool checkPossibility(std::vector<int>& nums) {
            bool hasSkipped = false;
            // 缓存前两个数字
            int preNum[2] = { -100000, -100000 };

            for (int i = 0; i < nums.size(); i++) {
                if (nums.at(i) >= preNum[(i + 1) % 2]) {
                    preNum[i % 2] = nums.at(i);
                }
                else {
                    if (!hasSkipped) {
                        // 当前的节点比前一个小，但是比前面的前面大，所以前一个数字是凸起，用当前的数字向前抹平
                        if (nums.at(i) >= preNum[i % 2]) {
                            preNum[0] = preNum[1] = nums.at(i);
                        }
                        // 当前的节点比前面两个节点都小，所以当前节点凹陷，用前一个数字抹平当前数字
                        else {
                            preNum[i % 2] = preNum[(i + 1) % 2];
                        }
                        hasSkipped = true;
                    }
                    else {
                        return false;
                    }
                }
            }
            return true;
        }
    };

    bool testCheckPossibility(const char* input) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        return Solution().checkPossibility(nums);
    }
}

TEST(_665_NonDecreasingArray, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [4,2,3]
    * Output: true
    */
    //EXPECT_EQ(NonDecreasingArray::testCheckPossibility("[4,2,3]"), true);

    /*
    * Example 2:
    * Input: nums = [4,2,1]
    * Output: false
    */
    EXPECT_EQ(NonDecreasingArray::testCheckPossibility("[4,2,1]"), false);

    EXPECT_EQ(NonDecreasingArray::testCheckPossibility("[3,4,2,3]"), false);

    EXPECT_EQ(NonDecreasingArray::testCheckPossibility("[3,4,3,3,4,3]"), false);
}
