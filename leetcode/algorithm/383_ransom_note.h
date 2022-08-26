#pragma once

//  https://leetcode.com/problems/ransom-note/
/*
* 383. Ransom Note
* 
* Given two strings ransomNote and magazine, return true if ransomNote can be
* constructed by using the letters from magazine and false otherwise.
*
* Each letter in magazine can only be used once in ransomNote.
*
* Example 1:
* Input: ransomNote = "a", magazine = "b"
* Output: false
*
* Example 2:
* Input: ransomNote = "aa", magazine = "ab"
* Output: false
*
* Example 3:
* Input: ransomNote = "aa", magazine = "aab"
* Output: true
*
* Constraints:
*    1 <= ransomNote.length, magazine.length <= 10^5
*    ransomNote and magazine consist of lowercase English letters.
*/

#include <string>
#include <gtest/gtest.h>

namespace RansomNote {
    class Solution {
    public:
        bool canConstruct(std::string ransomNote, std::string magazine) {
            int letters[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
            for (int i = 0; i < magazine.length(); i++) {
                letters[magazine.at(i) - 'a']++;
            }
            for (int i = 0; i < ransomNote.length(); i++) {
                int index = ransomNote.at(i) - 'a';
                if (letters[index] > 0) {
                    letters[index]--;
                }
                else {
                    return false;
                }
            }
            return true;
        }
    };
}


TEST(_383_RansomNote, SimpleCases) {
    /*
    * Example 1:
    * Input: ransomNote = "a", magazine = "b"
    * Output: false
    */
    EXPECT_EQ(RansomNote::Solution().canConstruct("a", "b"), false);

    /*
    * Example 2:
    * Input: ransomNote = "aa", magazine = "ab"
    * Output: false
    */
    EXPECT_EQ(RansomNote::Solution().canConstruct("aa", "ab"), false);

    /*
    * Example 3:
    * Input: ransomNote = "aa", magazine = "aab"
    * Output: true
    */
    EXPECT_EQ(RansomNote::Solution().canConstruct("aa", "aab"), true);
}
