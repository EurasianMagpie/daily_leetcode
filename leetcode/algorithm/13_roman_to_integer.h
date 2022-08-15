#pragma once

//  https://leetcode.com/problems/roman-to-integer/
/*
* 13. Roman to Integer
* 
* Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
*    Symbol       Value
*    I             1
*    V             5
*    X             10
*    L             50
*    C             100
*    D             500
*    M             1000
*
* For example, 2 is written as II in Roman numeral, just two ones added together. 12 is written as XII,
* which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.
*
* Roman numerals are usually written largest to smallest from left to right. However, the numeral for
* four is not IIII. Instead, the number four is written as IV. Because the one is before the five we
* subtract it making four. The same principle applies to the number nine, which is written as IX. There
* are six instances where subtraction is used:
*    I can be placed before V (5) and X (10) to make 4 and 9. 
*    X can be placed before L (50) and C (100) to make 40 and 90. 
*    C can be placed before D (500) and M (1000) to make 400 and 900.
*    Given a roman numeral, convert it to an integer.
*
* Example 1:
* Input: s = "III"
* Output: 3
* Explanation: III = 3.
*
* Example 2:
* Input: s = "LVIII"
* Output: 58
* Explanation: L = 50, V= 5, III = 3.
*
* Example 3:
* Input: s = "MCMXCIV"
* Output: 1994
* Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*
* Constraints:
*    1 <= s.length <= 15
*    s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
*    It is guaranteed that s is a valid roman numeral in the range [1, 3999].
*/

#include <string>
#include <gtest/gtest.h>

namespace RomanToInteger {
    class Solution {
    public:
        int romanToInt(std::string s) {
            int r(0);
            int l(s.length());
            for (int i = 0; i < l; i++) {
                switch (s.at(i)) {
                case 'I':
                    if (i < l - 1) {
                        if (s.at(i + 1) == 'V') {
                            r += 4;
                            i++;
                        }
                        else if (s.at(i + 1) == 'X') {
                            r += 9;
                            i++;
                        }
                        else {
                            r += 1;
                        }
                    }
                    else {
                        r += 1;
                    }
                    break;
                case 'V':
                    r += 5;
                    break;
                case 'X':
                    if (i < l - 1) {
                        if (s.at(i + 1) == 'L') {
                            r += 40;
                            i++;
                        }
                        else if (s.at(i + 1) == 'C') {
                            r += 90;
                            i++;
                        }
                        else {
                            r += 10;
                        }
                    }
                    else {
                        r += 10;
                    }
                    break;
                case 'L':
                    r += 50;
                    break;
                case 'C':
                    if (i < l - 1) {
                        if (s.at(i + 1) == 'D') {
                            r += 400;
                            i++;
                        }
                        else if (s.at(i + 1) == 'M') {
                            r += 900;
                            i++;
                        } else {
                            r += 100;
                        }
                    }
                    else {
                        r += 100;
                    }
                    break;
                case 'D':
                    r += 500;
                    break;
                case 'M':
                    r += 1000;
                    break;
                default:
                    break;
                }
            }
            return r;
        }
    };
}

TEST(_13_RomanToInteger, SimpleCases) {
    EXPECT_EQ(RomanToInteger::Solution().romanToInt("III"), 3);

    EXPECT_EQ(RomanToInteger::Solution().romanToInt("LVIII"), 58);

    EXPECT_EQ(RomanToInteger::Solution().romanToInt("MCMXCIV"), 1994);
}