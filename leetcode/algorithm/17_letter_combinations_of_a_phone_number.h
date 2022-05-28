#pragma once

// https://leetcode.com/problems/letter-combinations-of-a-phone-number/
/*
* 17. Letter Combinations of a Phone Number
* Given a string containing digits from 2-9 inclusive, 
* return all possible letter combinations that the 
* number could represent. Return the answer in any order.
* 
* A mapping of digit to letters (just like on the telephone buttons) 
* is given below. Note that 1 does not map to any letters.
* 
* [1 ]		[2 abc]		[3 def]
* [4 ghi]	[5 jkl]		[8 mno]
* [7 pqrs]	[8 tuv]		[9 wxyz]
* [*]		[0  ]		[#]
* 
* 

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]
 

Constraints:
  * 0 <= digits.length <= 4
  * digits[i] is a digit in the range ['2', '9'].
*/

#include <string>
#include <vector>
#include <map>
#include <gtest/gtest.h>

namespace LetterCombinationsOfAPhoneNumber {

    /*
    Success
    Details 
    Runtime: 0 ms, faster than 100.00% of C++ online submissions for Letter Combinations of a Phone Number.
    Memory Usage: 6.4 MB, less than 85.86% of C++ online submissions for Letter Combinations of a Phone Number.
    */

    class Solution {

    public:
        std::vector<std::string> letterCombinations(std::string digits) {
            std::vector<std::string> ret;
            std::size_t sz = digits.size();
            if (sz == 0) {
                return ret;
            }

            static std::map<char, std::string> sNumToLetters;
            char* buffer = (char*)malloc(sz + 1);
            if (!buffer) {
                return ret;
            }
            memset(buffer, 0, sz + 1);

            calcOutput(ret, digits, buffer, 0);

            free(buffer);
            return ret;
        }

        void calcOutput(std::vector<std::string>& ret, std::string& digits, char* buffer, int index) {
            char c = digits.at(index);
            bool isLast = (index == digits.size() - 1);
            if (c >= '0' && c <= '9') {
                std::size_t letterCount = getLetter(c, 0);
                for (std::size_t i = 1; i <= letterCount; i++) {
                    buffer[index] = getLetter(c, i);
                    if (isLast) {
                        ret.push_back(std::string(buffer));
                    }
                    else {
                        calcOutput(ret, digits, buffer, index + 1);
                    }
                }
            }
            else {
                buffer[index] = c;
                if (isLast) {
                    ret.push_back(std::string(buffer));
                }
                else {
                    calcOutput(ret, digits, buffer, index + 1);
                }
            }

            buffer[index] = 0;
        }

        static char getLetter(char c, int index) {
            static char lettersTab[10][5] = {
                {1, ' ', 0,   0,   0},
                {1, '1', 0,   0,   0},
                {3, 'a', 'b', 'c', 0},
                {3, 'd', 'e', 'f', 0},
                {3, 'g', 'h', 'i', 0},
                {3, 'j', 'k', 'l', 0},
                {3, 'm', 'n', 'o', 0},
                {4, 'p', 'q', 'r', 's'},
                {3, 't', 'u', 'v', 0},
                {4, 'w', 'x', 'y', 'z'},
            };
            return lettersTab[c - '0'][index];
        }
    };

    void testLetterCombinations(const char* input) {
        std::vector<std::string> ret = Solution().letterCombinations(input);
    }

    void test() {
        testLetterCombinations("23");
        testLetterCombinations("");
        testLetterCombinations("2");
    }
}