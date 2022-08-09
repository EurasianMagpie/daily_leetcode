#pragma once

// https://leetcode.com/problems/longest-increasing-subsequence/
/*
* 300. Longest Increasing Subsequence
* 
* Given an integer array nums, return the length of the longest strictly increasing subsequence.
*
* A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
*
* Example 1:
* Input: nums = [10,9,2,5,3,7,101,18]
* Output: 4
* Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
*
* Example 2:
* Input: nums = [0,1,0,3,2,3]
* Output: 4
*
* Example 3:
* Input: nums = [7,7,7,7,7,7,7]
* Output: 1
*
* Constraints:
*   1 <= nums.length <= 2500
*   -104 <= nums[i] <= 104
*
* Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
*/

#include <vector>
#include "../util/std_util.h"
#include <gtest/gtest.h>


namespace LongestIncreasingSubsequence {

    class Solution {
    public:
        // 
        // https://leetcode.com/problems/longest-increasing-subsequence/discuss/2395570/Python3-oror-7-lines-binSearch-cheating-wexplanation-oror-TM%3A-9482
        int lengthOfLIS(std::vector<int>& nums) {
            std::vector<int> seq;
            seq.push_back(nums.at(0));
            for (int i = 1; i < nums.size(); i++) {
                if (nums.at(i) > seq.at(seq.size() - 1)) {
                    seq.push_back(nums.at(i));
                }
                else {
                    int j = seq.size() - 1;
                    do {
                        if (j == 0) {
                            break;
                        }
                        else {
                            if (seq.at(j - 1) >= nums.at(i)) {
                                j--;
                            }
                            else {
                                break;
                            }
                        }
                    } while (true);
                    seq.at(j) = nums.at(i);
                }
            }
            return seq.size();
        }
    };

    int testLengthOfLIS(const char* input) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        return Solution().lengthOfLIS(nums);
    }
}

TEST(_300_LongestIncreasingSubsequence, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [10,9,2,5,3,7,101,18]
    * Output: 4
    */
    EXPECT_EQ(LongestIncreasingSubsequence::testLengthOfLIS("[10,9,2,5,3,7,101,18]"), 4);

    /*
    * Example 2:
    * Input: nums = [0,1,0,3,2,3]
    * Output: 4
    */
    EXPECT_EQ(LongestIncreasingSubsequence::testLengthOfLIS("[0,1,0,3,2,3]"), 4);

    /*
    * Example 3:
    * Input: nums = [7,7,7,7,7,7,7]
    * Output: 1
    */
    EXPECT_EQ(LongestIncreasingSubsequence::testLengthOfLIS("[7,7,7,7,7,7,7]"), 1);
}