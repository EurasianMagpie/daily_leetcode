#pragma once

// https://leetcode.com/problems/kth-largest-element-in-an-array/
/*
* 215. Kth Largest Element in an Array
* 
* Given an integer array nums and an integer k, return the kth largest element in the array.
*
* Note that it is the kth largest element in the sorted order, not the kth distinct element.
* 
* Example 1:
* Input: nums = [3,2,1,5,6,4], k = 2
* Output: 5
*
* Example 2:
* Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
* Output: 4
*
*
* Constraints:
*   1 <= k <= nums.length <= 10^4
*   -10^4 <= nums[i] <= 10^4
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace KthLargestElementInAnArray {
    class Solution0 {
    public:
        int findKthLargest(std::vector<int>& nums, int k) {
            std::priority_queue<int> numsPq;
            for (auto n : nums) {
                numsPq.push(n);
            }
            // 1 <= k <= nums.length
            int r(0);
            for (int i = 0; i < k; i++) {
                r = numsPq.top();
                numsPq.pop();
            }
            return r;
        }
    };

    class Solution {
    public:
        int findKthLargest(std::vector<int>& nums, int k) {
            if (nums.size() > 1) {
                findKthLargestInRange(nums, 0, nums.size() - 1, k - 1);
            }
            return nums[k - 1];
        }

        void findKthLargestInRange(std::vector<int>& nums, int begin, int end, int k) {
            int x = partition(nums, begin, end);
            if (k < x && x - 1 > begin) {
                findKthLargestInRange(nums, begin, x - 1, k);
            }
            else if (k > x && x + 1 < end) {
                findKthLargestInRange(nums, x + 1, end, k);
            }
        }

        int partition(std::vector<int>& nums, int begin, int end) {
            int x = (begin + end) / 2;
            int pivot = nums[x];
            std::swap(nums[x], nums[end]);
            int left(begin), right(end - 1);
            while (true) {
                while (nums[left] >= pivot && left <= right) {
                    left++;
                }
                while (nums[right] < pivot && left <= right && right > 0) {
                    right--;
                }
                if (left < right) {
                    std::swap(nums[left], nums[right]);
                }
                else {
                    break;
                }
            }
            std::swap(nums[left], nums[end]);
            return left;
        }
    };


    int testFindKthLargest(const char* strNums, int k) {
        std::vector<int> nums = StdUtil::generateIntVector(strNums);
        return Solution().findKthLargest(nums, k);
    }
}

TEST(_215_KthLargestElementInAnArray, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [3,2,1,5,6,4], k = 2
    * Output: 5
    */
    EXPECT_EQ(KthLargestElementInAnArray::testFindKthLargest("[3,2,1,5,6,4]", 2), 5);

    /*
    * Example 2:
    * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
    * Output: 4
    */
    EXPECT_EQ(KthLargestElementInAnArray::testFindKthLargest("[3,2,3,1,2,4,5,5,6]", 4), 4);

    EXPECT_EQ(KthLargestElementInAnArray::testFindKthLargest("[3,1,4,2]", 2), 3);

    EXPECT_EQ(KthLargestElementInAnArray::testFindKthLargest("[1]", 1), 1);

    EXPECT_EQ(KthLargestElementInAnArray::testFindKthLargest("[2,1]", 1), 2);
}