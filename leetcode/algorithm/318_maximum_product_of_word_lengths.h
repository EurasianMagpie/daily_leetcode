#pragma once

// https://leetcode.com/problems/maximum-product-of-word-lengths/

/*
* 318. Maximum Product of Word Lengths
* 
* Given a string array words, return the maximum value of length(word[i]) * length(word[j]) 
* where the two words do not share common letters. If no such two words exist, return 0.
* 
* Example 1:
* Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
* Output: 16
* Explanation: The two words can be "abcw", "xtfn".
* 
* Example 2:
* Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
* Output: 4
* Explanation: The two words can be "ab", "cd".
* 
* Example 3:
* Input: words = ["a","aa","aaa","aaaa"]
* Output: 0
* Explanation: No such pair of words.
* 
* Constraints:
*  2 <= words.length <= 1000
*  1 <= words[i].length <= 1000
*  words[i] consists only of lowercase English letters.
*/

#include <vector>
#include <string>
#include <gtest/gtest.h>

#include "../util/std_util.h"

namespace MaximumProductOfWordLengths {
    class Solution {
        struct wordsInfo {
            int length;
            uint32_t mask; // words[i] consists only of lowercase English letters. 32bit is enough!

            wordsInfo(std::size_t n, uint32_t m) : length(n), mask(m) {}
        };
    public:
        int maxProduct(std::vector<std::string>& words) {
            std::size_t sz = words.size();
            if (sz < 2) {
                return 0;
            }

            int ret = 0;
            std::vector<wordsInfo> info;
            for (auto ite = words.begin(); ite != words.end(); ite++) {
                std::string word = *ite;
                info.push_back(wordsInfo(word.length(), calcWordMask(word)));
            }
            for (auto ite1 = info.begin(); ite1 != info.end(); ite1++) {
                auto ite2 = ite1 + 1;
                while (ite2 != info.end())
                {
                    int r = calcProductResult(*ite1, *ite2);
                    if (r > ret) {
                        ret = r;
                    }
                    ite2++;
                }
            }
            return ret;
        }

        uint32_t calcWordMask(std::string& word) {
            uint32_t mask = 0;
            for (auto ite = word.begin(); ite != word.end(); ite++) {
                char c = *ite;
                mask |= 1 << (c - 'a');
            }
            return mask;
        }

        int calcProductResult(wordsInfo& left, wordsInfo& right) {
            return left.mask & right.mask ? 0 : left.length * right.length;
        }
    };

    int testMaxProduct(const char* input) {
        std::vector<std::string> words = StdUtil::generateStringVector(input);
        return Solution().maxProduct(words);
    }
}

TEST(_318_MaximumProductOfWordLengths, SimpleCases) {
    /*
    * Example 1:
    * Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
    * Output: 16
    * Explanation: The two words can be "abcw", "xtfn".
    */
    EXPECT_EQ(16, MaximumProductOfWordLengths::testMaxProduct("[abcw,baz,foo,bar,xtfn,abcdef]"));

    /*
    * Example 2:
    * Input: words = ["a","ab","abc","d","cd","bcd","abcd"]
    * Output: 4
    * Explanation: The two words can be "ab", "cd".
    */
    //EXPECT_EQ(4, MaximumProductOfWordLengths::testMaxProduct("[a,ab,abc,d,cd,bcd,abcd]"));

    /*
    * Example 3:
    * Input: words = ["a","aa","aaa","aaaa"]
    * Output: 0
    * Explanation: No such pair of words.
    */
    //EXPECT_EQ(0, MaximumProductOfWordLengths::testMaxProduct("[a,aa,aaa,aaaa]"));
}