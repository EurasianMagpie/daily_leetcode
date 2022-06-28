#pragma once

// https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/
/*
* 1647. Minimum Deletions to Make Character Frequencies Unique
* 
* A string s is called good if there are no two different characters in s that have the same frequency.
*
* Given a string s, return the minimum number of characters you need to delete to make s good.
*
* The frequency of a character in a string is the number of times it appears in the string. For example,
* in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
* 
* Example 1:
* Input: s = "aab"
* Output: 0
* Explanation: s is already good.
*
* Example 2:
* Input: s = "aaabbbcc"
* Output: 2
* Explanation: You can delete two 'b's resulting in the good string "aaabcc".
* Another way it to delete one 'b' and one 'c' resulting in the good string "aaabbc".
*
* Example 3:
* Input: s = "ceabaacb"
* Output: 2
* Explanation: You can delete both 'c's resulting in the good string "eabaab".
* Note that we only care about characters that are still in the string at the end (i.e. frequency of 0 is ignored).
*
* 
* Constraints:
*    1 <= s.length <= 10^5
*    s contains only lowercase English letters.
*/

#include <string>
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

namespace MinimumDeletionsToMakeCharacterFrequenciesUnique {

    class Solution {
    public:
        // �����ַ�����ͳ��ÿ����ĸ���ֵĴ���
        // �Ը�����ĸ�ĳ��ִ����Ӵ�С������ʱ�Ѿ�����Ҫ����ÿ����ĸ������Ĺ�ϵ
        // ����������ĸ�Ĵ������Ӵ�С������Ĵ��������Լ��Ĵ��������ϱ�ǰһ������С��
        // �����ȥ��Ӧ����ֵ������з�����ȥ��ֵ�����ۼӵ����
        int minDeletions(std::string s) {
            std::vector<int> charCount(26);
            for (auto c : s) {
                charCount[c - 'a'] += 1;
            }
            std::sort(charCount.begin(), charCount.end(), [](int lhs, int rhs) {
                    return lhs > rhs;
                });

            int ans(0);
            int preCount(s.size() + 1);
            for (int n : charCount) {
                if (n == 0) {
                    break;
                }
                if (n >= preCount) {
                    if (preCount > 0) {
                        int delta = n - preCount + 1;
                        preCount = n - delta;
                        ans += delta;
                    }
                    else {
                        ans += n;
                    }
                }
                else {
                    preCount = n;
                }
            }

            return ans;
        }
    };
}

TEST(_1647_MinimumDeletionsToMakeCharacterFrequenciesUnique, SimpleCases) {

    EXPECT_EQ(MinimumDeletionsToMakeCharacterFrequenciesUnique::Solution().minDeletions("abcdefgh"), 7);

    /*
    * Example 1:
    * Input: s = "aab"
    * Output: 0
    */
    EXPECT_EQ(MinimumDeletionsToMakeCharacterFrequenciesUnique::Solution().minDeletions("aab"), 0);

    /*
    * Example 2:
    * Input: s = "aaabbbcc"
    * Output: 2
    */
    EXPECT_EQ(MinimumDeletionsToMakeCharacterFrequenciesUnique::Solution().minDeletions("aaabbbcc"), 2);

    /*
    * Example 3:
    * Input: s = "ceabaacb"
    * Output: 2
    */
    EXPECT_EQ(MinimumDeletionsToMakeCharacterFrequenciesUnique::Solution().minDeletions("ceabaacb"), 2);
}