#pragma once

// https://leetcode.com/problems/maximum-erasure-value/
/*
* 1695. Maximum Erasure Value
* 
* You are given an array of positive integers nums and want to erase a subarray containing unique elements.
* The score you get by erasing the subarray is equal to the sum of its elements.
*
* Return the maximum score you can get by erasing exactly one subarray.
*
* An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is
* equal to a[l],a[l+1],...,a[r] for some (l,r).
* 
* Example 1:
* Input: nums = [4,2,4,5,6]
* Output: 17
* Explanation: The optimal subarray here is [2,4,5,6].
*
* Example 2:
* Input: nums = [5,2,1,2,5,2,1,2,5]
* Output: 8
* Explanation: The optimal subarray here is [5,2,1] or [1,2,5].
*
*
* Constraints:
*    1 <= nums.length <= 10^5
*    1 <= nums[i] <= 10^4
* 
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace MaximumErasureValue {
    class Solution {
    private:
        /*
        * 在区间[begin, end]中查找是否包含数字num，
        * 如果存在，返回num的索引值，否则返回-1
        */
        int findNumInRange(std::vector<int>& nums, int num, int begin, int end) {
            for (int i = begin; i <= end; i++) {
                if (nums.at(i) == num) {
                    return i;
                }
            }
            return -1;
        }
    public:

        /*
        * 先计算一个累加值数组
        * 再遍历数组，如果存在重复数字，则按相应区间计算累加值的差作为score
        */
        int maximumUniqueSubarray(std::vector<int>& nums) {
            int ret(0);
            std::size_t sz = nums.size();
            std::vector<int> sums(sz);
            int sum(0);
            for (int i = 0; i < sz; i++) {
                sum += nums.at(i);
                sums.at(i) = sum;
            }


            int begin(0);
            int beginSum(0);
            for (int i = 1; i < sz; i++) {
                int num = nums.at(i);
                int findIndex = findNumInRange(nums, num, begin, i - 1);
                if (findIndex >= 0) {
                    int r = sums.at(i - 1) - beginSum;
                    if (r > ret) {
                        ret = r;
                    }
                    begin = findIndex + 1;
                    beginSum = sums.at(findIndex);
                }
            }
            int r = sums.at(sz - 1) - beginSum;
            if (r > ret) {
                ret = r;
            }

            return ret;
        }
    };

    int testMaximumUniqueSubarray(const char* nums) {
        std::vector<int> numsVector = StdUtil::generateIntVector(nums);
        return Solution().maximumUniqueSubarray(numsVector);
    }
}

TEST(_1695_MaximumErasureValue, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [4,2,4,5,6]
    * Output: 17
    */
    EXPECT_EQ(MaximumErasureValue::testMaximumUniqueSubarray("[4,2,4,5,6]"), 17);

    /*
    * Example 2:
    * Input: nums = [5,2,1,2,5,2,1,2,5]
    * Output: 8
    */
    EXPECT_EQ(MaximumErasureValue::testMaximumUniqueSubarray("[5,2,1,2,5,2,1,2,5]"), 8);


    EXPECT_EQ(MaximumErasureValue::testMaximumUniqueSubarray("[1]"), 1);
}