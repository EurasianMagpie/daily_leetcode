#pragma once

// https://leetcode.com/problems/partitioning-into-minimum-number-of-deci-binary-numbers/
/*
* 1689. Partitioning Into Minimum Number Of Deci-Binary Numbers
* 
* A decimal number is called deci-binary if each of its digits is either 0 or 1 without any leading zeros.
* For example, 101 and 1100 are deci-binary, while 112 and 3001 are not.
*
* Given a string n that represents a positive decimal integer, return the minimum number of positive
* deci-binary numbers needed so that they sum up to n.
* 
* Example 1:
* Input: n = "32"
* Output: 3
* Explanation: 10 + 11 + 11 = 32
*
* Example 2:
* Input: n = "82734"
* Output: 8
*
* Example 3:
* Input: n = "27346209830709182346"
* Output: 9
*
* Constraints:
*    1 <= n.length <= 105
*    n consists of only digits.
*    n does not contain any leading zeros and represents a positive integer.
*/

#include <string>
#include <gtest/gtest.h>

namespace PartitioningIntoMinimumNumberOfDeciBinaryNumbers {

    /*
    * 这个题没水准
    * 字符串中包含的最大数字就是返回值
    */
    class Solution {
    public:
        int minPartitions(std::string n) {
            int ans(0);
            for (auto c : n) {
                int x = c - '0';
                if (x > ans) {
                    ans = x;
                }
                if (ans == 9) {
                    break;
                }
            }
            return ans;
        }
    };
}

TEST(_1689_PartitioningIntoMinimumNumberOfDeciBinaryNumbers, SimpleCases) {
    /*
    * Example 3:
    * Input: n = "27346209830709182346"
    * Output: 9
    */
    EXPECT_EQ(PartitioningIntoMinimumNumberOfDeciBinaryNumbers::Solution()
        .minPartitions("27346209830709182346"), 9);
}