#pragma once

// https://leetcode.com/problems/merge-sorted-array/
/*
* 88. Merge Sorted Array
* 
* You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, and two integers m and n,
* representing the number of elements in nums1 and nums2 respectively.
*
* Merge nums1 and nums2 into a single array sorted in non-decreasing order.
*
* The final sorted array should not be returned by the function, but instead be stored inside the array nums1.
* To accommodate this, nums1 has a length of m + n, where the first m elements denote the elements that should
* be merged, and the last n elements are set to 0 and should be ignored. nums2 has a length of n.
* 
* Example 1:
* Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
* Output: [1,2,2,3,5,6]
* Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
* The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.
*
* Example 2:
* Input: nums1 = [1], m = 1, nums2 = [], n = 0
* Output: [1]
* Explanation: The arrays we are merging are [1] and [].
* The result of the merge is [1].
*
* Example 3:
* Input: nums1 = [0], m = 0, nums2 = [1], n = 1
* Output: [1]
* Explanation: The arrays we are merging are [] and [1].
* The result of the merge is [1].
* Note that because m = 0, there are no elements in nums1. The 0 is only there to ensure the merge result can
* fit in nums1.
* 
* Constraints:
*    nums1.length == m + n
*    nums2.length == n
*    0 <= m, n <= 200
*    1 <= m + n <= 200
*    -10^9 <= nums1[i], nums2[j] <= 10^9
* 
* Follow up: Can you come up with an algorithm that runs in O(m + n) time?
*/

#include <vector>
#include "../util/std_util.h"
#include <gtest/gtest.h>

namespace MergeSortedArray {
    class Solution {
    public:
        void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
            if (n == 0) {
                return;
            }
            std::vector<int> nums(m + n);
            int index1(0), index2(0);
            for (int i = 0; i < m + n; i++) {
                if (index1 < m) {
                    if (index2 < n) {
                        if (nums1[index1] <= nums2[index2]) {
                            nums[i] = nums1[index1];
                            index1++;
                        }
                        else {
                            nums[i] = nums2[index2];
                            index2++;
                        }
                    }
                    else {
                        nums[i] = nums1[index1];
                        index1++;
                    }
                }
                else if (index2 < n) {
                    nums[i] = nums2[index2];
                    index2++;
                }
                else {
                    break;
                }
            }
            memcpy(nums1.data(), nums.data(), sizeof(int) * (m + n));
        }
    };

    bool testMerge(const char* nums1, int m, const char* nums2, int n, const char* expected) {
        std::vector<int> numsVector1 = StdUtil::generateIntVector(nums1);
        std::vector<int> numsVector2 = StdUtil::generateIntVector(nums2);
        Solution().merge(numsVector1, m, numsVector2, n);
        std::vector<int> numsExpected = StdUtil::generateIntVector(expected);
        return StdUtil::compareEqualVector<int>(numsVector1, numsExpected);
    }
}

TEST(_88_MergeSortedArray, SimpleCases) {
    /*
    * Example 1:
    * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    * Output: [1,2,2,3,5,6]
    */
    EXPECT_TRUE(MergeSortedArray::testMerge("[1,2,3,0,0,0]", 3, "[2,5,6]", 3, "[1,2,2,3,5,6]"));

    /*
    * Example 2:
    * Input: nums1 = [1], m = 1, nums2 = [], n = 0
    * Output: [1]
    */
    EXPECT_TRUE(MergeSortedArray::testMerge("[1]", 1, "[]", 0, "[1]"));

    /*
    *Example 3:
    * Input: nums1 = [0], m = 0, nums2 = [1], n = 1
    * Output: [1]
    */
    EXPECT_TRUE(MergeSortedArray::testMerge("[0]", 0, "[1]", 1, "[1]"));
}