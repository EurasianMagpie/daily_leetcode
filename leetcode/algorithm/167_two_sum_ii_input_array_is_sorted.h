#pragma once

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
/*
* 167. Two Sum II - Input Array Is Sorted
* 
* Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order,
* find two numbers such that they add up to a specific target number. Let these two numbers
* be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
*
* Return the indices of the two numbers, index1 and index2, added by one as an integer
* array [index1, index2] of length 2.
*
* The tests are generated such that there is exactly one solution. You may not use the same element twice.
*
* Your solution must use only constant extra space.
* 
* Example 1:
* Input: numbers = [2,7,11,15], target = 9
* Output: [1,2]
* Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
* 
* Example 2:
* Input: numbers = [2,3,4], target = 6
* Output: [1,3]
* Explanation: The sum of 2 and 4 is 6. Therefore index1 = 1, index2 = 3. We return [1, 3].
* 
* Example 3:
* Input: numbers = [-1,0], target = -1
* Output: [1,2]
* Explanation: The sum of -1 and 0 is -1. Therefore index1 = 1, index2 = 2. We return [1, 2].
* 
* Constraints:
*    2 <= numbers.length <= 3 * 104
*    -1000 <= numbers[i] <= 1000
*    numbers is sorted in non-decreasing order.
*    -1000 <= target <= 1000
*    The tests are generated such that there is exactly one solution.
*/

#include <vector>
#include <map>
#include "../util/std_util.h"
#include <gtest/gtest.h>


namespace TwoSumIIInputArrayIsSorted {
    class Solution {
    public:
        std::vector<int> twoSum(std::vector<int>& numbers, int target) {
            std::vector<int> ret;
            // 已经被遍历过的数字，key：期望遇到的值，value：该数字的索引
            std::map<int, int> preNumberInfo;
            for (std::size_t i = 0; i < numbers.size(); i++) {
                int num = numbers.at(i);
                auto ite = preNumberInfo.find(num);
                if (ite != preNumberInfo.end()) {
                    ret.push_back(ite->second + 1);
                    ret.push_back(i + 1);
                }
                else {
                    preNumberInfo[target - num] = i;
                }
            }
            return ret;
        }
    };

    bool testTwoSum(const char* nums, int target, const char* expected) {
        std::vector<int> numbers = StdUtil::generateIntVector(nums);
        std::vector<int> output = Solution().twoSum(numbers, target);
        std::vector<int> expectedVector = StdUtil::generateIntVector(expected);
        return StdUtil::compareEqualVector(output, expectedVector);
    }
}

TEST(_167_TwoSumIIInputArrayIsSorted, SimpleCases) {
    /*
    * * Example 1:
    * Input: numbers = [2,7,11,15], target = 9
    * Output: [1,2]
    */
    EXPECT_TRUE(TwoSumIIInputArrayIsSorted::testTwoSum("[2,7,11,15]", 9, "[1,2]"));
}
