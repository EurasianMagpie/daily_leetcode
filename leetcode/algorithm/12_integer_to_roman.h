#pragma once

//  https://leetcode.com/problems/integer-to-roman/
/*
* 12. Integer to Roman
* 
* Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.
* 
*    Symbol       Value
*    I             1
*    V             5
*    X             10
*    L             50
*    C             100
*    D             500
*    M             1000
*
* For example, 2 is written as II in Roman numeral, just two one's added together. 12
* is written as XII, which is simply X + II. The number 27 is written as XXVII, which
* is XX + V + II.
*
* Roman numerals are usually written largest to smallest from left to right. However, the
* numeral for four is not IIII. Instead, the number four is written as IV. Because the
* one is before the five we subtract it making four. The same principle applies to the
* number nine, which is written as IX. There are six instances where subtraction is used:
*
*    I can be placed before V (5) and X (10) to make 4 and 9. 
*    X can be placed before L (50) and C (100) to make 40 and 90. 
*    C can be placed before D (500) and M (1000) to make 400 and 900.
*
* Given an integer, convert it to a roman numeral.
*
* Example 1:
* Input: num = 3
* Output: "III"
* Explanation: 3 is represented as 3 ones.
*
* Example 2:
* Input: num = 58
* Output: "LVIII"
* Explanation: L = 50, V = 5, III = 3.
*
* Example 3:
* Input: num = 1994
* Output: "MCMXCIV"
* Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
*
* Constraints:
*   1 <= num <= 3999
*/

#include <string>
#include <gtest/gtest.h>

namespace IntegerToRoman {
    class Solution {
    public:
        std::string intToRoman(int num) {
            static const char* rmCode[][10] = {
                "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX",
                "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC",
                "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM",
                "", "M", "MM", "MMM", "",   "",  "",   "",    "",     "",
            };
            std::string r;
            r.append(rmCode[3][num / 1000]);
            r.append(rmCode[2][(num % 1000) / 100]);
            r.append(rmCode[1][(num % 100) / 10]);
            r.append(rmCode[0][num % 10]);
            return r;
        }
    };
}

TEST(_12_IntegerToRoman, SimpleCases) {
    /*
    * Example 1:
    * Input: num = 3
    * Output: "III"
    */
    EXPECT_EQ(IntegerToRoman::Solution().intToRoman(3), "III");

    /*
    * Example 2:
    * Input: num = 58
    * Output: "LVIII"
    */
    EXPECT_EQ(IntegerToRoman::Solution().intToRoman(58), "LVIII");

    /*
    * Example 3:
    * Input: num = 1994
    * Output: "MCMXCIV"
    */
    EXPECT_EQ(IntegerToRoman::Solution().intToRoman(1994), "MCMXCIV");
}