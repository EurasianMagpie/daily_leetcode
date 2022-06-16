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

            // ������0��ʼ������ÿһ������λ�ã�
            // ��ʣ���������ַ��������̣����Ҵ������г��ȵ�Palindromic�ַ���
            //    ����ÿ������λ�ã�ֻҪ�ҵ�һ������Ǹ�λ�ÿ��ܵ�����
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
        * �ж�һ�������ַ���pStr������ʼλ��startIndex������Ϊsz �����ַ����Ƿ�Ϊ Palindromic
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