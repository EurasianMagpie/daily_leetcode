#pragma once

//  https://leetcode.com/problems/split-array-into-consecutive-subsequences/
/*
* 659. Split Array into Consecutive Subsequences
* 
* You are given an integer array nums that is sorted in non-decreasing order.
*
* Determine if it is possible to split nums into one or more subsequences such that
* both of the following conditions are true:
*  - Each subsequence is a consecutive increasing sequence (i.e. each integer is
*    exactly one more than the previous integer).
*  - All subsequences have a length of 3 or more.
*
* Return true if you can split nums according to the above conditions, or false otherwise.
*
* A subsequence of an array is a new array that is formed from the original array by
* deleting some (can be none) of the elements without disturbing the relative positions
* of the remaining elements. (i.e., [1,3,5] is a subsequence of [1,2,3,4,5] while
* [1,3,2] is not).
* 
* Example 1:
* Input: nums = [1,2,3,3,4,5]
* Output: true
* Explanation: nums can be split into the following subsequences:
* [1,2,3,3,4,5] --> 1, 2, 3
* [1,2,3,3,4,5] --> 3, 4, 5
*
* Example 2:
* Input: nums = [1,2,3,3,4,4,5,5]
* Output: true
* Explanation: nums can be split into the following subsequences:
* [1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
* [1,2,3,3,4,4,5,5] --> 3, 4, 5
*
* Example 3:
* Input: nums = [1,2,3,4,4,5]
* Output: false
* Explanation: It is impossible to split nums into consecutive increasing
* subsequences of length 3 or more.
*
* Constraints:
*    1 <= nums.length <= 10^4
*    -1000 <= nums[i] <= 1000
*    nums is sorted in non-decreasing order.
*/

#include <vector>
#include <gtest/gtest.h>
#include "../util/std_util.h"


namespace SplitArrayIntoConsecutiveSubsequences {
    class Solution {
        struct Seq {
            int begin;
            int end;

            Seq(int b, int e) : begin(b), end(e) {}
        };

    public:
        bool isPossible(std::vector<int>& nums) {
            std::vector<Seq*> seqs;
            for (int n : nums) {
                // 倒序查找第一个以 n - 1 结尾的序列
                Seq* seq = findSeqEndBy(seqs, n - 1);
                // 找到了，则将 n 附加到该序列
                if (seq) {
                    seq->end = n;
                }
                // 没找到，创建一个以n开始&结尾的新序列
                else {
                    seqs.push_back(new Seq(n, n));
                }
            }

            // 如果序列数大于1，且每个序列长度大于2则返回true
            // 否则返回false
            bool r(true);
            if (seqs.size() > 0) {
                for (Seq* q : seqs) {
                    if (q->end - q->begin < 2) {
                        r = false;
                        break;
                    }
                }
            }
            else {
                r = false;
            }
            for (Seq* q : seqs) {
                delete q;
            }
            return r;
        }

        Seq* findSeqEndBy(std::vector<Seq*>& seqs, int end) {
            Seq* r(nullptr);
            for (int i = seqs.size() - 1; i >= 0; i--) {
                if (seqs.at(i)->end == end) {
                    r = seqs.at(i);
                    break;
                }
                else if (seqs.at(i)->end < end) {
                    break;
                }
            }
            return r;
        }
    };

    bool testIsPossible(const char* input) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        return Solution().isPossible(nums);
    }
}

TEST(_659_SplitArrayIntoConsecutiveSubsequences, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [1,2,3,3,4,5]
    * Output: true
    */
    EXPECT_EQ(SplitArrayIntoConsecutiveSubsequences::testIsPossible("[1,2,3,3,4,5]"), true);

    /*
    * Example 2:
    * Input: nums = [1,2,3,3,4,4,5,5]
    * Output: true
    */
    EXPECT_EQ(SplitArrayIntoConsecutiveSubsequences::testIsPossible("[1,2,3,3,4,4,5,5]"), true);

    /*
    * Example 3:
    * Input: nums = [1,2,3,4,4,5]
    * Output: false
    */
    EXPECT_EQ(SplitArrayIntoConsecutiveSubsequences::testIsPossible("[1,2,3,4,4,5]"), false);
}