#pragma once

// https://leetcode.com/problems/longest-string-chain/
/*
* 1048. Longest String Chain
* 
* You are given an array of words where each word consists of lowercase English letters.
*
* wordA is a predecessor of wordB if and only if we can insert exactly one letter anywhere in wordA without
* changing the order of the other characters to make it equal to wordB.
*
* For example, "abc" is a predecessor of "abac", while "cba" is not a predecessor of "bcad".
* 
* A word chain is a sequence of words [word1, word2, ..., wordk] with k >= 1, where word1 is a predecessor of
* word2, word2 is a predecessor of word3, and so on. A single word is trivially a word chain with k == 1.
*
* Return the length of the longest possible word chain with words chosen from the given list of words.
* 
* Example 1:
* Input: words = ["a","b","ba","bca","bda","bdca"]
* Output: 4
* Explanation: One of the longest word chains is ["a","ba","bda","bdca"].
*
* Example 2:
* Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
* Output: 5
* Explanation: All the words can be put in a word chain ["xb", "xbc", "cxbc", "pcxbc", "pcxbcf"].
*
* Example 3:
* Input: words = ["abcd","dbqca"]
* Output: 1
* Explanation: The trivial word chain ["abcd"] is one of the longest word chains.
* ["abcd","dbqca"] is not a valid word chain because the ordering of the letters is changed.
*
*
* Constraints:
*    1 <= words.length <= 1000
*    1 <= words[i].length <= 16
*    words[i] only consists of lowercase English letters.
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include "../util/std_util.h"
#include <gtest/gtest.h>

namespace LongestStringChain {
    class Solution {
    public:
        int longestStrChain(std::vector<std::string>& words) {
            // 首先按字符串长度排序，使字符串长度依次增大
            std::sort(words.begin(), words.end(),
                [] (std::string& lhs, std::string& rhs) {
                    return lhs.size() < rhs.size();
                }
            );
            int lscResult = 1;

            // 在每个索引位置的问题状态：
            //     key   - 位置索引
            //     value - 当前索引位置的 Longest String Chain | LSC
            std::map<int, int> stateMap;
            // 每个字符串长度对应的起始索引位置
            //     key   - 字符串的长度
            //     value - 长度为key的字符串最早出现的位置索引
            std::map<std::size_t, int> startIndexOfStringLength;
            // 上一个字符串的长度
            std::size_t lastStringLength = 0;

            // 依次计算到每个节点，如果比已有结果大则更新为已有结果
            for (int i = 0; i < words.size(); i++) {
                // 如果当前字符串长度变大，则记录这个字符串长度对应的起始位置
                std::size_t sz = words.at(i).length();
                if (sz > lastStringLength) {
                    startIndexOfStringLength[sz] = i;
                    lastStringLength = sz;
                }

                // 是否存在比当前字符串长度少1的字符串
                //     如果存在，则分别比较长度少1的字符串是否为前序，
                //          如果有是，则当前的 LSC 在前序的基础上加1, 并取与所有长度少1的字符串计算结果中最大的值作为当前 LSC
                //          如果没有一个是，则 LSC 为 1
                //     如果不存在，则 LSC 为 1
                int lsc(1);
                auto iteBegin = startIndexOfStringLength.find(sz - 1);
                auto iteEnd = startIndexOfStringLength.find(sz);
                if (iteBegin != startIndexOfStringLength.end() && iteEnd != startIndexOfStringLength.end()) {
                    for (int j = iteBegin->second; j < iteEnd->second; j++) {
                        if (isPredecessor(words.at(j), words.at(i))) {
                            int tmpLsc = stateMap[j] + 1;
                            if (tmpLsc > lsc) {
                                lsc = tmpLsc;
                            }
                        }
                    }
                    /* lsc = 1; */
                }
                /*
                else {
                    lsc = 1;
                }*/


                // 保存当前节点状态到缓存
                stateMap[i] = lsc;

                if (lsc > lscResult) {
                    lscResult = lsc;
                }
            }
            return lscResult;
        }

    private:
        // 判断两个字符串 word1 是否为 word2 的前序
        bool isPredecessor(std::string word1, std::string word2) {
            if (word1.size() > 0 && word2.size() != word1.size() + 1) {
                return false;
            }
            auto ite1 = word1.begin();
            auto ite2 = word2.begin();
            bool isSkipped = false;
            while (ite1 != word1.end()) {
                if (*ite1 == *ite2) {
                    ite1++;
                    ite2++;
                }
                else {
                    if (isSkipped) {
                        return false;
                    }
                    else {
                        ite2++;
                        isSkipped = true;
                    }
                }
            }
            return true;
        }
    };

    int testLongestStrChain(const char* input) {
        std::vector<std::string> words = StdUtil::generateStringVector(input);
        int r = Solution().longestStrChain(words);
        //std::cout << "case ---------------------------" << std::endl;
        //std::cout << "Input:\t" << input << std::endl;
        //std::cout << "Output:\t" << r << std::endl;
        return r;
    }
}


TEST(_1048_LongestStringChain, SimpleCases) {
    /*
    * Example 1:
    * Input: words = ["a","b","ba","bca","bda","bdca"]
    * Output: 4
    */
    //EXPECT_EQ(LongestStringChain::testLongestStrChain("[a,b,ba,bca,bda,bdca]"), 4);

    /*
    * Example 2:
    * Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
    * Output: 5
    */
    //EXPECT_EQ(LongestStringChain::testLongestStrChain("[xbc,pcxbcf,xb,cxbc,pcxbc]"), 5);

    /*
    * Example 3:
    * Input: words = ["abcd","dbqca"]
    * Output: 1
    */
    //EXPECT_EQ(LongestStringChain::testLongestStrChain("[abcd,dbqca]"), 1);


    EXPECT_EQ(LongestStringChain::testLongestStrChain("[bdca,bda,ca,dca,a]"), 4);
    //EXPECT_EQ(LongestStringChain::testLongestStrChain("[xbc,pcxbcf,xb,cxbc,pcxbc]"), 5);

    //EXPECT_EQ(LongestStringChain::testLongestStrChain("[xbc]"), 1);
}