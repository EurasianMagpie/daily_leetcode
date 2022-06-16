#pragma once

// https://leetcode.com/problems/longest-palindromic-substring/
/*
* 5. Longest Palindromic Substring
* 
* Given a string s, return the longest palindromic substring in s.
* 
* Example 1:
* Input: s = "babad"
* Output: "bab"
* Explanation: "aba" is also a valid answer.
*
* Example 2:
* Input: s = "cbbd"
* Output: "bb"
*
*
* Constraints:
*    1 <= s.length <= 1000
*    s consist of only digits and English letters.
*/

#include <string>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace LongestPalindromicSubstring {
    class Solution {
    public:
        std::string longestPalindrome(std::string s) {
            int sz = s.size();
            const char* pStr = s.c_str();
            int longestStartIndex = 0;
            int longestLength = 1;

            // 从索引0开始，对于每一个索引位置，
            // 从剩余的最大子字符串逐渐缩短，查找大于已有长度的Palindromic字符串
            //    对于每个索引位置，只要找到一个解就是该位置可能的最大解
            for (int i = 0; i + longestLength <= sz; i++) {
                for (int j = sz - i; j > longestLength; j--) {
                    if (isPalindromicString(pStr, i, j)) {
                        longestStartIndex = i;
                        longestLength = j;
                        break;
                    }
                }
            }

            return std::string(pStr + longestStartIndex, longestLength);
        }

    private:
        /*
        * 判断一个对于字符串pStr，从起始位置startIndex，长度为sz 的子字符串是否为 Palindromic
        */
        inline bool isPalindromicString(const char* pStr, int startIndex, int sz) {
            const char* pStart = pStr + startIndex;
            for (int i = 0; i < (sz >> 1); i++) {
                if (*(pStart + i) != *(pStart + sz - 1 - i)) {
                    return false;
                }
            }
            return true;
        }
    };
}

TEST(_5_LongestPalindromicSubstring, SimpleCases) {
    /*
    * Example 1:
    * Input: s = "babad"
    * Output: "bab"
    */
    EXPECT_EQ(LongestPalindromicSubstring::Solution().longestPalindrome("babad"), "bab");

    /*
    * Example 2:
    * Input: s = "cbbd"
    * Output: "bb"
    */
    EXPECT_EQ(LongestPalindromicSubstring::Solution().longestPalindrome("cbbd"), "bb");
}