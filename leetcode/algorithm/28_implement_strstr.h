#pragma once

//  https://leetcode.com/problems/implement-strstr/
/*
* 28. Implement strStr()
* 
* Implement strStr().
*
* Given two strings needle and haystack, return the index of the first occurrence of
* needle in haystack, or -1 if needle is not part of haystack.
*
* Clarification:
* What should we return when needle is an empty string? This is a great question to ask
* during an interview.
*
* For the purpose of this problem, we will return 0 when needle is an empty string. This
* is consistent to C's strstr() and Java's indexOf().
*
* Example 1:
* Input: haystack = "hello", needle = "ll"
* Output: 2
*
* Example 2:
* Input: haystack = "aaaaa", needle = "bba"
* Output: -1
*
* Constraints:
*    1 <= haystack.length, needle.length <= 10^4
*    haystack and needle consist of only lowercase English characters.
*/

#include <string>
#include <gtest/gtest.h>

namespace ImplementStrStr {
    class Solution {
    public:
        int strStr(std::string haystack, std::string needle) {
            if (needle.size() > haystack.size()) {
                return -1;
            }
            for (int i = 0; i < haystack.size() - needle.size() + 1; i++) {
                int sz = needle.size();
                for (int j = 0; j < needle.size(); j++) {
                    if (needle.at(j) != haystack.at(i + j)) {
                        break;
                    }
                    else {
                        sz--;
                    }
                }
                if (sz == 0) {
                    return i;
                }
            }
            return -1;
        }
    };
}

TEST(_28_ImplementStrStr, SimpleCases) {
    /*
    * Example 1:
    * Input: haystack = "hello", needle = "ll"
    * Output: 2
    */
    EXPECT_EQ(ImplementStrStr::Solution().strStr("hello", "ll"), 2);

    /*
    * Example 2:
    * Input: haystack = "aaaaa", needle = "bba"
    * Output: -1
    */
    EXPECT_EQ(ImplementStrStr::Solution().strStr("aaaaa", "bba"), -1);

    EXPECT_EQ(ImplementStrStr::Solution().strStr("a", "a"), 0);
    EXPECT_EQ(ImplementStrStr::Solution().strStr("cccaa", "aa"), 3);
}