#pragma once

//  https://leetcode.com/problems/reordered-power-of-2/
/*
* 869. Reordered Power of 2
* 
* You are given an integer n. We reorder the digits in any order (including the original order)
* such that the leading digit is not zero.
*
* Return true if and only if we can do this so that the resulting number is a power of two.
* 
* Example 1:
* Input: n = 1
* Output: true
*
* Example 2:
* Input: n = 10
* Output: false
*
* Constraints:
*   1 <= n <= 10^9
*/
/*
* ������͵Ĳ���������ﲹ��һ��
* ��Ŀ����˼�ǣ�
* ��һ��ʮ�������ĸ��������������������ϣ��Ƿ������г�2���ݡ�
* ���磺����61�����������6��1��������Ϊ 16������2����
*/

#include <string>
#include <set>
#include <algorithm>
#include <gtest/gtest.h>

namespace ReorderedPowerOf2 {
    class Solution {
    public:
        bool reorderedPowerOf2(int n) {
            std::set<std::string> powOf2;
            for (int i = 0; i < 30; i++) {
                std::string s = std::to_string(1 << i);
                std::sort(s.begin(), s.end());
                powOf2.insert(s);
            }
            std::string input = std::to_string(n);
            std::sort(input.begin(), input.end());
            return powOf2.find(input) != powOf2.end();
        }
    };
}

TEST(_869_ReorderedPowerOf2, SimpleCases) {
    // 16
    EXPECT_EQ(ReorderedPowerOf2::Solution().reorderedPowerOf2(61), true);

    // 256
    EXPECT_EQ(ReorderedPowerOf2::Solution().reorderedPowerOf2(652), true);

    // 1024
    EXPECT_EQ(ReorderedPowerOf2::Solution().reorderedPowerOf2(1042), true);
}