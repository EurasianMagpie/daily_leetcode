#pragma once

//  https://leetcode.com/problems/lexicographically-smallest-equivalent-string/
/*
* 1061. Lexicographically Smallest Equivalent String
* 
* You are given two strings of the same length s1 and s2 and a string baseStr.
* 
* We say s1[i] and s2[i] are equivalent characters.
* 
* For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
* Equivalent characters follow the usual rules of any equivalence relation:
*    Reflexivity: 'a' == 'a'.
*    Symmetry: 'a' == 'b' implies 'b' == 'a'.
*    Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
*
* For example, given the equivalency information from s1 = "abc" and s2 = "cde", "acd" and "aab"
* are equivalent strings of baseStr = "eed", and "aab" is the lexicographically smallest equivalent
* string of baseStr.
*
* Return the lexicographically smallest equivalent string of baseStr by using the equivalency
* information from s1 and s2.
* 
* Example 1:
* Input: s1 = "parker", s2 = "morris", baseStr = "parser"
* Output: "makkek"
* Explanation: Based on the equivalency information in s1 and s2, we can group their characters
* as [m,p], [a,o], [k,r,s], [e,i].
* The characters in each group are equivalent and sorted in lexicographical order.
* So the answer is "makkek".
* 
* Input: s1 = "hello", s2 = "world", baseStr = "hold"
* Output: "hdld"
* Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [h,w], [d,e,o], [l,r].
* So only the second letter 'o' in baseStr is changed to 'd', the answer is "hdld".
* 
* 
* Constraints:
*    1 <= s1.length, s2.length, baseStr <= 1000
*    s1.length == s2.length
*    s1, s2, and baseStr consist of lowercase English letters.
*/

#include <string>
#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>


namespace LexicographicallySmallestEquivalentString {
    class Solution {
    public:
        std::string smallestEquivalentString(std::string s1, std::string s2, std::string baseStr) {
            std::unordered_map<char, std::shared_ptr<char>> mp;
            for (int i = 0; i < s1.size(); i++) {
                makeEqual(s1[i], s2[i], mp);
            }
            std::string s;
            for (const char c : baseStr) {
                if (mp.find(c) != mp.end()) {
                    const char cc = *(mp[c]);
                    s.push_back(cc);
                }
                else {
                    s.push_back(c);
                }
            }
            return s;
        }

        inline void makeEqual(char c1, char c2, std::unordered_map<char, std::shared_ptr<char>>& mp) {
            if (c1 == c2) {
                return;
            }
            if (c1 > c2) {
                std::swap(c1, c2);
            }

            auto f1 = mp.find(c1) != mp.end();
            auto f2 = mp.find(c2) != mp.end();
            if (f1) {
                if (f2) {
                    auto p1 = mp[c1];
                    auto p2 = mp[c2];
                    *p1 = std::min(std::min(*p1, *p2), c1);
                    for (auto& ite : mp) {
                        if (ite.second == p2) {
                            ite.second = p1;
                        }
                    }
                }
                else {
                    auto p = mp[c2] = mp[c1];
                    if (c1 < *p) {
                        *p = c1;
                    }
                }
            }
            else {
                if (f2) {
                    auto p = mp[c1] = mp[c2];
                    if (c1 < *p) {
                        *p = c1;
                    }
                }
                else {
                    mp[c1] = mp[c2] = std::make_shared<char>(c1);
                }
            }
        }
    };

    std::string testSmallestEquivalentString(
        const char* s1Input,
        const char* s2Input,
        const char* baseStrInput) {
        return Solution().smallestEquivalentString(s1Input, s2Input, baseStrInput);
    }
}


TEST(_1061_LexicographicallySmallestEquivalentString, SimpleCases) {
    using namespace LexicographicallySmallestEquivalentString;
    EXPECT_EQ(testSmallestEquivalentString("parker", "morris", "parser"), "makkek");
    EXPECT_EQ(testSmallestEquivalentString("hello", "world", "hold"), "hdld");
    EXPECT_EQ(testSmallestEquivalentString("leetcode", "programs", "sourcecode"), "aauaaaaada");

    EXPECT_EQ(testSmallestEquivalentString(
        "ceihfgechfcbjhadaibhghcbdhfaecdaijigaaafcadebciabb",
        "gafbfceidigjceeigcddichdhhbgibjbaagbfciiecjaiajahh",
        "eoiloytuagirigmbarebhzgveiavyruxlrxzbommyfjjngfktd"),
        "aoaloytuaaaraamaaraaazavaaavyruxlrxzaommyaaanaakta");
}