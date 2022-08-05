#pragma once

// https://leetcode.com/problems/combination-sum-iv/
/*
* 377. Combination Sum IV
* 
* Given an array of distinct integers nums and a target integer target, return the number of possible
* combinations that add up to target.
*
* The test cases are generated so that the answer can fit in a 32-bit integer.
* 
* Example 1:
* Input: nums = [1,2,3], target = 4
* Output: 7
* Explanation:
*  The possible combination ways are:
*  (1, 1, 1, 1)
*  (1, 1, 2)
*  (1, 2, 1)
*  (1, 3)
*  (2, 1, 1)
*  (2, 2)
*  (3, 1)
*  Note that different sequences are counted as different combinations.
* 
* Example 2:
* Input: nums = [9], target = 3
* Output: 0
*
* Constraints:
*    1 <= nums.length <= 200
*    1 <= nums[i] <= 1000
*    All the elements of nums are unique.
*    1 <= target <= 1000
* 
* Follow up:
* What if negative numbers are allowed in the given array?
* How does it change the problem?
* What limitation we need to add to the question to allow negative numbers?
*/

#include <vector>
#include <algorithm>
#include "../util/std_util.h"
#include <gtest/gtest.h>

namespace CombinationSumIV {

    class Solution {
    public:
        int combinationSum4(std::vector<int>& nums, int target) {
            std::sort(nums.begin(), nums.end());
            std::map<int, int> cache;
            return sum4(nums, target, cache);
        }

    private:
        int sum4(std::vector<int>& nums, int target, std::map<int, int>& cache) {
            auto fd = cache.find(target);
            if (fd != cache.end()) {
                return fd->second;
            }
            int ans = 0;
            for (int n : nums) {
                int nextTarget = target - n;
                if (nextTarget > 0) {
                    ans += sum4(nums, nextTarget, cache);
                }
                else if (nextTarget == 0) {
                    ans++;
                    break;
                }
                else {
                    break;
                }
            }
            cache[target] = ans;
            return ans;
        }
    };

    int testCombinationSum4(const char* input, int target) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        return Solution().combinationSum4(nums, target);
    }
}


TEST(_377_CombinationSumIV, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [1,2,3], target = 4
    * Output: 7
    */
    EXPECT_EQ(CombinationSumIV::testCombinationSum4("[1,2,3]", 4), 7);

    /*
    * Example 2:
    * Input: nums = [9], target = 3
    * Output: 0
    */
    EXPECT_EQ(CombinationSumIV::testCombinationSum4("[9]", 3), 0);
}