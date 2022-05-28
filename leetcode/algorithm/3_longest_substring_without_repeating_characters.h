#pragma once

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

/*
3. Longest Substring Without Repeating Characters

Given a string s, find the length of the longest substring without repeating characters.


Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.


Constraints:
. 0 <= s.length <= 5 * 104
. s consists of English letters, digits, symbols and spaces.
*/

#include <string>
#include <map>
#include <gtest/gtest.h>


namespace LongestSubstringWithoutRepeatingCharacters {

    class Solution {
    public:
        int lengthOfLongestSubstring(std::string s) {
            std::size_t sz = s.size();
            if (sz == 0) {
                return 0;
            }
            std::map<char, int> mapContainingChar;
            const char* p1 = s.c_str();
            const char* p2 = s.c_str();
            const char* pEnd = p1 + sz;
            int r = 0;
            while (p1 < pEnd && p2 < pEnd)
            {
                while (p2 < pEnd)
                {
                    char c = *p2;
                    auto search = mapContainingChar.find(c);
                    if (search != mapContainingChar.end()) {
                        int offset = search->second;
                        p1 += offset + 1;
                        p2 = p1;
                        mapContainingChar.clear();
                        break;
                    }
                    else {
                        mapContainingChar[c] = p2 - p1;
                        if (r < mapContainingChar.size()) {
                            r = mapContainingChar.size();
                        }
                        p2++;
                    }
                }
            }
            return r;
        }
    };

    int lengthOfLongestSubstring(std::string s) {
        return Solution().lengthOfLongestSubstring(s);
    }
}

TEST(_3_LongestSubstringWithoutRepeatingCharacters, SimpleCases) {
    /*
        Example 1:
        Input: s = "abcabcbb"
        Output: 3
        Explanation: The answer is "abc", with the length of 3. */
    EXPECT_EQ(3, LongestSubstringWithoutRepeatingCharacters::lengthOfLongestSubstring("abcabcbb"));

    /*
        Example 2:
        Input: s = "bbbbb"
        Output: 1
        Explanation: The answer is "b", with the length of 1. */
    EXPECT_EQ(1, LongestSubstringWithoutRepeatingCharacters::lengthOfLongestSubstring("bbbbb"));

    /*
        Example 3:
        Input: s = "pwwkew"
        Output: 3
        Explanation: The answer is "wke", with the length of 3.
        Notice that the answer must be a substring, "pwke" is a subsequence and not a substring. */
    EXPECT_EQ(3, LongestSubstringWithoutRepeatingCharacters::lengthOfLongestSubstring("pwwkew"));
}

