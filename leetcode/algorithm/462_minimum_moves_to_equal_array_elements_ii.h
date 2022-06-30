#pragma once

//  https://leetcode.com/problems/minimum-moves-to-equal-array-elements-ii/
/*
* 462. Minimum Moves to Equal Array Elements II
* 
* Given an integer array nums of size n, return the minimum number of moves required to make
* all array elements equal.
*
* In one move, you can increment or decrement an element of the array by 1.
*
* Test cases are designed so that the answer will fit in a 32-bit integer.
* 
* Example 1:
* Input: nums = [1,2,3]
* Output: 2
* Explanation:
* Only two moves are needed (remember each move increments or decrements one element):
* [1,2,3]  =>  [2,2,3]  =>  [2,2,2]
*
* Example 2:
* Input: nums = [1,10,2,9]
* Output: 16
*
*
* Constraints:
*    n == nums.length
*    1 <= nums.length <= 10^5
*    -10^9 <= nums[i] <= 10^9
*/

#include <vector>
#include <algorithm>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace MinimumMovesToEqualArrayElementsII {

    class Solution {
    public:
        int minMoves2(std::vector<int>& nums) {
            std::sort(nums.begin(), nums.end());
            int x = nums.at(nums.size() / 2);
            int64_t ans(0);
            for (auto n : nums) {
                ans += std::abs(n - x);
            }
            return ans;
        }
    };

    int testMinMoves2(const char* input) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        return Solution().minMoves2(nums);
    }
}

TEST(_462_MinimumMovesToEqualArrayElementsII, SimpleCases) {
    EXPECT_EQ(MinimumMovesToEqualArrayElementsII::testMinMoves2("[1,0,0,8,6]"), 14);

    /*
    * Example 1:
    * Input: nums = [1,2,3]
    * Output: 2
    */
    EXPECT_EQ(MinimumMovesToEqualArrayElementsII::testMinMoves2("[1,2,3]"), 2);

    /*
    * Example 2:
    * Input: nums = [1,10,2,9]
    * Output: 16
    */
    EXPECT_EQ(MinimumMovesToEqualArrayElementsII::testMinMoves2("[1,10,2,9]"), 16);
}