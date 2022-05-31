#pragma once

// https://leetcode.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
/*
* 1461. Check If a String Contains All Binary Codes of Size K
* 
* Given a binary string s and an integer k, return true if every binary code of length k is a substring of s. Otherwise, return false.
* 
* Example 1:
* Input: s = "00110110", k = 2
* Output: true
* Explanation: The binary codes of length 2 are "00", "01", "10" and "11". They can be all found as substrings at indices 0, 1, 3 and 2 respectively.
* 
* Example 2:
* Input: s = "0110", k = 1
* Output: true
* Explanation: The binary codes of length 1 are "0" and "1", it is clear that both exist as a substring. 
* 
* Example 3:
* Input: s = "0110", k = 2
* Output: false
* Explanation: The binary code "00" is of length 2 and does not exist in the array.
*
* Constraints:
*  1 <= s.length <= 5 * 105
*  s[i] is either '0' or '1'.
*  1 <= k <= 20
*/

#include <string>
#include <map>
#include <gtest/gtest.h>
#include <iostream>

namespace CheckIfAStringContainsAllBinaryCodesOfSizeK {
    /*
    * 超时了，复杂度过高， O(n * m)
    */
    class Solution1 {
        typedef std::map<int, bool> CodeMap;

    public:
        bool hasAllCodes(std::string s, int k) {
            if (k <= 0) {
                return false;
            }
            // 字符串最少长度： code长度k + 可能的编码数量(1 << k) - 1
            if (s.length() < k + (1 << k) - 1) {
                return false;
            }

            // 数据结构，分层的结果缓存
            CodeMap* codeMaps = new CodeMap[k];
            
            bool r = false;
            for (std::size_t i = 0; i < s.length() - (k - 1); i++) {
                if (!checkCodes(s, k, i, 1, codeMaps)) {
                    continue;
                }
                else {
                    CodeMap& codeMap = codeMaps[0];
                    if (codeMap.find(0) != codeMap.end() && codeMap.find(1) != codeMap.end()) {
                        r = true;
                        break;
                    }
                }
            }
            delete[] codeMaps;
            return r;
        }

        bool checkCodes(
            std::string s,
            int k,
            std::size_t offset,
            std::size_t count,
            std::map<int, bool>* codeMaps) {

            // 先查缓存，如果当前级别以下的所有细分case都包含了，则直接返回
            std::string subs = s.substr(offset, count);
            int code = binaryAtoi(subs);
            CodeMap& codeMap = codeMaps[count - 1];
            if (codeMap.find(code) != codeMap.end()) {
                std::cout << "in cache - level:" << count << "\tcode:" << code << std::endl;
                return true;
            }

            if (count < k) {
                // 如果还需要继续细分，则增加字串长度继续查找
                bool r = checkCodes(s, k, offset, count + 1, codeMaps);
                if (r) {
                    // 如果下一级返回true，则判断本级的两种case是否都为true，
                    // 如果是，则更新本级缓存为true，并返回true
                    int code1 = code << 1;
                    int code2 = code1 + 1;
                    CodeMap& codeMapNextLevel = codeMaps[count];
                    if (codeMapNextLevel.find(code1) != codeMapNextLevel.end()
                        && codeMapNextLevel.find(code2) != codeMapNextLevel.end()) {
                        std::cout << "mark - node - level:" << count << "\tcode:" << code << std::endl;
                        codeMap[code] = true;
                        return true;
                    }
                }
                return false;
            }
            else {
                // 如果已经达到字串最大长度k，则直接记录当前code为true
                std::cout << "mark - leaf - level:" << count << "\tcode:" << code << std::endl;
                codeMap[code] = true;
                return true;
            }
        }

        int binaryAtoi(std::string& binaryString) {
            int r = 0;
            for (auto ite = binaryString.begin(); ite != binaryString.end(); ite++) {
                r = (r << 1) | ((*ite == '1') ? 1 : 0);
            }
            return r;
        }
    };

    class Solution2 {
        //遍历一次s，取出所有符合条件的字串，并加入到集合，最后判断集合中的数量是否符合理论数量
    public:
        bool hasAllCodes(std::string s, int k) {
            if (k <= 0) {
                return false;
            }
            // 字符串最少长度： code长度k + 可能的编码数量(1 << k) - 1
            int codeCount = 1 << k;
            if (s.length() < k + codeCount - 1) {
                return false;
            }

            std::set<std::size_t> codes;
            for (std::size_t i = 0; i < s.length() - (k - 1); i++) {
                std::string subs = s.substr(i, k);
                codes.insert(std::hash<std::string>{}(subs));
                if (codes.size() == codeCount) {
                    return true;
                }
            }
            return false;
        }
    };

    bool testHasAllCodes(const char* input, int k) {
        return Solution2().hasAllCodes(input, k);
    }
}

TEST(_1461_CheckIfAStringContainsAllBinaryCodesOfSizeK, SimpleCases) {
    /*
    * Example 1:
    * Input: s = "00110110", k = 2
    * Output: true
    */
    EXPECT_EQ(true, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("00110110", 2));

    /*
    * Example 2:
    * Input: s = "0110", k = 1
    * Output: true
    */
    EXPECT_EQ(true, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("0110", 1));

    /*
    * Example 3:
    * Input: s = "0110", k = 2
    * Output: false
    */
    EXPECT_EQ(false, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("0110", 2));


    EXPECT_EQ(false, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("0110", 0));
    EXPECT_EQ(false, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("0110", 7));

    /*
    * Wrong Answer
    * Input:    "00110", 2
    * Expected: true
    */
    EXPECT_EQ(true, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("00110", 2));

    /*
    * Wrong Answer
    * Input:    "00000000001011100", 3
    * Expected: true
    */
    EXPECT_EQ(true, CheckIfAStringContainsAllBinaryCodesOfSizeK::testHasAllCodes("00000000001011100", 3));
}