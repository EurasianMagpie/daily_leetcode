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
            // ���Ȱ��ַ�����������ʹ�ַ���������������
            std::sort(words.begin(), words.end(),
                [] (std::string& lhs, std::string& rhs) {
                    return lhs.size() < rhs.size();
                }
            );
            int lscResult = 1;

            // ��ÿ������λ�õ�����״̬��
            //     key   - λ������
            //     value - ��ǰ����λ�õ� Longest String Chain | LSC
            std::map<int, int> stateMap;
            // ÿ���ַ������ȶ�Ӧ����ʼ����λ��
            //     key   - �ַ����ĳ���
            //     value - ����Ϊkey���ַ���������ֵ�λ������
            std::map<std::size_t, int> startIndexOfStringLength;
            // ��һ���ַ����ĳ���
            std::size_t lastStringLength = 0;

            // ���μ��㵽ÿ���ڵ㣬��������н���������Ϊ���н��
            for (int i = 0; i < words.size(); i++) {
                // �����ǰ�ַ������ȱ�����¼����ַ������ȶ�Ӧ����ʼλ��
                std::size_t sz = words.at(i).length();
                if (sz > lastStringLength) {
                    startIndexOfStringLength[sz] = i;
                    lastStringLength = sz;
                }

                // �Ƿ���ڱȵ�ǰ�ַ���������1���ַ���
                //     ������ڣ���ֱ�Ƚϳ�����1���ַ����Ƿ�Ϊǰ��
                //          ������ǣ���ǰ�� LSC ��ǰ��Ļ����ϼ�1, ��ȡ�����г�����1���ַ���������������ֵ��Ϊ��ǰ LSC
                //          ���û��һ���ǣ��� LSC Ϊ 1
                //     ��������ڣ��� LSC Ϊ 1
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


                // ���浱ǰ�ڵ�״̬������
                stateMap[i] = lsc;

                if (lsc > lscResult) {
                    lscResult = lsc;
                }
            }
            return lscResult;
        }

    private:
        // �ж������ַ��� word1 �Ƿ�Ϊ word2 ��ǰ��
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