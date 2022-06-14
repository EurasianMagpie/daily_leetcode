#pragma once

// https://leetcode.com/problems/delete-operation-for-two-strings/
/*
* 583. Delete Operation for Two Strings
* 
* Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2
* the same.
*
* In one step, you can delete exactly one character in either string.
* 
* Example 1:
* Input: word1 = "sea", word2 = "eat"
* Output: 2
* Explanation: You need one step to make "sea" to "ea" and another step to make "eat" to "ea".
*
* Example 2:
* Input: word1 = "leetcode", word2 = "etco"
* Output: 4
*
*
* Constraints:
*    1 <= word1.length, word2.length <= 500
*    word1 and word2 consist of only lowercase English letters.
*/

#include <string>
#include <map>
#include <gtest/gtest.h>

namespace DeleteOperationForTwoStrings {
    class Solution {
    public:
        int minDistance(std::string word1, std::string word2) {
            // 1 <= word1.length, word2.length <= 500, 高16位是i1, 低16位是i2
            std::map<uint32_t, std::size_t> cacheMap;
            std::size_t lcs = longestCommonSubseq(word1, word1.length() - 1, word2, word2.length() - 1, cacheMap);
            cacheMap.clear();
            return (int)(word1.length() + word2.length() - (lcs << 1));
        }

    private:
        /*
        * 是一个 最大共同子序列 的问题， Longest Common SubSequence (LCS)， 使用动态规划求解
        * f(i1, i2) 表示对于两个字符串在位置 i1 和 i2 的最大公共子序列长度, 则
        * f(i1, i2) = | isSame(i1, i2)   当 i2 == 0 && i2 == 0 时
        *             | max{ f(i1 - 1, i2 - 1) + isSame(i1, i2), f(i1 - 1, j), f(i1, i2 - 1) }
        * 其中计算过程中得出的 f(m, n) 的值可以被缓存复用
        */
        std::size_t longestCommonSubseq(std::string& s1, std::size_t i1, std::string& s2, std::size_t i2, std::map<uint32_t, std::size_t>& cacheMap) {
            uint32_t key = uint16_t(i1) << 16 | uint16_t(i2);
            auto cache = cacheMap.find(key);
            if (cache != cacheMap.end()) {
                //std::cout << ">>>>>> " << i1 << "," << i2 << " \t- " << cache->second << std::endl; // debug log
                return cache->second;
            }
            std::size_t isSame = s1.at(i1) == s2.at(i2) ? 1 : 0;
            std::size_t r1(0), r2(0), r12(isSame);
            if (i1 > 0) {
                r1 = longestCommonSubseq(s1, i1 - 1, s2, i2, cacheMap);
            }
            if (i2 > 0) {
                r2 = longestCommonSubseq(s1, i1, s2, i2 - 1, cacheMap);
            }
            if (i1 > 0 && i2 > 0) {
                r12 += longestCommonSubseq(s1, i1 - 1, s2, i2 - 1, cacheMap);
            }
            std::size_t ret = std::max(std::max(r1, r2), r12);
            cacheMap[key] = ret;
            //std::cout << "calced " << i1 << "," << i2 << " \t- " << ret << std::endl; // debug log
            return ret;
        }
    };
}

TEST(_583_DeleteOperationForTwoStrings, SimpleCases) {
    /*
    * Example 1:
    * Input: word1 = "sea", word2 = "eat"
    * Output: 2
    */
    EXPECT_EQ(DeleteOperationForTwoStrings::Solution().minDistance("sea", "eat"), 2);

    /*
    * Example 2:
    * Input: word1 = "leetcode", word2 = "etco"
    * Output: 4
    */
   EXPECT_EQ(DeleteOperationForTwoStrings::Solution().minDistance("leetcode", "etco"), 4);

   EXPECT_EQ(DeleteOperationForTwoStrings::Solution()
       .minDistance(
           "abcdefghijklmnopqrstuvwxyz",
           "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz"),
       26);
}