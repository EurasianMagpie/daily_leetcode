#pragma once

// https://leetcode.com/problems/add-binary/
// 67. Add Binary
/*
* Given two binary strings a and b, return their sum as a binary string.
* Example 1:
* Input: a = "11", b = "1"
* Output: "100"
* 
* Example 2:
* Input: a = "1010", b = "1011"
* Output: "10101"
* 
* Constraints:
* 1 <= a.length, b.length <= 104
* a and b consist only of '0' or '1' characters.
* Each string does not contain leading zeros except for the zero itself.
*/

#include <string>
#include <bitset>
#include <gtest/gtest.h>

namespace AddBinary {
    class Solution {
    public:
        // Wrong Answer
        std::string addBinary2(std::string a, std::string b) {
            uint32_t v1(0), v2(0);
            for (auto ia = a.begin(); ia != a.end(); ia++) {
                v1 = (v1 << 1) + (int)(('1' == *ia));
            }
            for (auto ib = b.begin(); ib != b.end(); ib++) {
                v2 = (v2 << 1) + (int)('1' == *ib);
            }
            char szRet[128] = {};
            uint32_t r = v1 + v2;
            uint32_t mask = r;
            int index = 0;
            if (mask > 0) {
                int i = 31;
                while (i >= 0)
                {
                    if (mask & (1 << i)) {
                        index = i;
                        break;
                    }
                    i--;
                }
            }
            int j = index;
            while (j >= 0) {
                szRet[index - j] = r & (1 << j) ? '1' : '0';
                j--;
            }
            
            return std::string(szRet);
        }

        std::string addBinary(std::string a, std::string b) {
            std::size_t sz = a.length() > b.length() ? a.length() : b.length();
            sz++;
            char* buffer = new char[sz + 1];
            memset(buffer, 0, sz + 1);
            bool jinwei = false;
            auto ia = a.rbegin();
            auto ib = b.rbegin();
            int index = 1;
            while (ia != a.rend() && ib != b.rend()) {
                int n = 0;
                if (*ia == '1') {
                    n++;
                }
                if (*ib == '1') {
                    n++;
                }
                if (jinwei) {
                    n++;
                }
                buffer[sz - index] = (n & 1) ? '1' : '0';
                jinwei = n & 2;
                ia++;
                ib++;
                index++;
            }

            while (ia != a.rend()) {
                if (jinwei) {
                    if (*ia == '1') {
                        buffer[sz - index] = '0';
                    }
                    else {
                        buffer[sz - index] = '1';
                        jinwei = false;
                    }
                }
                else {
                    buffer[sz - index] = *ia;
                }
                ia++;
                index++;
            }
            while (ib != b.rend()) {
                if (jinwei) {
                    if (*ib == '1') {
                        buffer[sz - index] = '0';
                    }
                    else {
                        buffer[sz - index] = '1';
                        jinwei = false;
                    }
                }
                else {
                    buffer[sz - index] = *ib;
                }
                ib++;
                index++;
            }

            if (jinwei) {
                buffer[sz - index] = '1';
                index++;
                jinwei = false;
            }

            std::string ret(&buffer[sz - index + 1]);
            delete[] buffer;
            return ret;
        }
    };
}

TEST(_67_AddBinary, SimpleCases) {

    /*
    * Example 1:
    * Input: a = "11", b = "1"
    * Output: "100"
    */
    EXPECT_EQ("100", AddBinary::Solution().addBinary("11", "1"));

    /*
    * Example 2:
    * Input: a = "1010", b = "1011"
    * Output: "10101"
    */
    EXPECT_EQ("10101", AddBinary::Solution().addBinary("1010", "1011"));


    /*
    * Wrong Answer:
    * Input:
    * a = "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101"
    * b = "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011"
    * Expected: "110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000"
    */
    EXPECT_EQ("110111101100010011000101110110100000011101000101011001000011011000001100011110011010010011000000000",
        AddBinary::Solution().addBinary(
            "10100000100100110110010000010101111011011001101110111111111101000000101111001110001111100001101",
            "110101001011101110001111100110001010100001101011101010000011011011001011101111001100000011011110011"));
}