#pragma once

// https://leetcode.com/problems/search-suggestions-system/
/*
* 1268. Search Suggestions System
* 
* You are given an array of strings products and a string searchWord.
*
* Design a system that suggests at most three product names from products after each character of
* searchWord is typed. Suggested products should have common prefix with searchWord. If there are
* more than three products with a common prefix return the three lexicographically minimums products.
*
* Return a list of lists of the suggested products after each character of searchWord is typed.
* 
* 
* Example 1:
* Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
* Output: [
*    ["mobile","moneypot","monitor"],
*    ["mobile","moneypot","monitor"],
*    ["mouse","mousepad"],
*    ["mouse","mousepad"],
*    ["mouse","mousepad"]
*    ]
* Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
* After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
* After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
* 
* 
* Example 2:
* Input: products = ["havana"], searchWord = "havana"
* Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
*
* 
* Example 3:
* Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
* Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
* 
* 
* Constraints:
*    1 <= products.length <= 1000
*    1 <= products[i].length <= 3000
*    1 <= sum(products[i].length) <= 2 * 104
*    All the strings of products are unique.
*    products[i] consists of lowercase English letters.
*    1 <= searchWord.length <= 1000
*    searchWord consists of lowercase English letters.
*/

#include <string>
#include <vector>
#include <algorithm>
#include "../util/std_util.h"
#include <gtest/gtest.h>

namespace SearchSuggestionsSystem {
    class Solution {
    public:
        std::vector<std::vector<std::string>> suggestedProducts(
            std::vector<std::string>& products, std::string searchWord) {
            // 对products按字典顺序排序
            std::sort(products.begin(), products.end());

            int searchIndex(0);
            bool emptyResult(false);
            std::vector<std::vector<std::string>> ret;
            std::size_t productSize = products.size();
            const char* pSearch = searchWord.c_str();
            for (int i = 0; i < searchWord.size(); i++) {
                std::vector<std::string> eachResult;
                int RemainingResult = 3;
                int nextSearchIndex(searchIndex);
                if (!emptyResult) {
                    for (int j = searchIndex; j < productSize; j++) {
                        int cmpResult = comparePrefix(products.at(j), pSearch, i + 1);
                        if (cmpResult < 0) {
                            nextSearchIndex++;
                        }
                        else if (cmpResult > 0) {
                            if (RemainingResult == 3) {
                                emptyResult = true;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            // == 0
                            eachResult.push_back(products.at(j));
                            RemainingResult--;
                            if (RemainingResult == 0) {
                                break;
                            }
                        }
                    }
                }
                ret.push_back(eachResult);
                searchIndex = nextSearchIndex;
            }
            return ret;
        }

    private:
        /*
        * 按字典顺序 比较 word 与 prefix 前缀
        * 返回值
        *   -1  word前缀更小
        *   0   word前缀与prefix吻合
        *   1   word前缀比prefix大
        */
        int comparePrefix(std::string& word, const char* prefix, int prefixSize) {
            bool wordIsShorter(false);
            int sz(prefixSize);
            if (word.size() < prefixSize) {
                sz = word.size();
                wordIsShorter = true;
            }
            int result(0);
            for (int i = 0; i < sz; i++) {
                char c1 = word.at(i);
                char c2 = *(prefix + i);
                if (c1 < c2) {
                    result = -1;
                    break;
                }
                else if (c1 > c2) {
                    result = 1;
                    break;
                }
                else {
                    result = 0;
                }
            }
            if (wordIsShorter && result == 0) {
                result = -1;
            }
            return result;
        }
    };

    bool testSuggestedProducts(
        const char* input,
        const char* searchWord,
        std::initializer_list<const char*> expected) {
        std::vector<std::string> products = StdUtil::generateStringVector(input);
        std::vector<std::vector<std::string>> output = Solution().suggestedProducts(products, searchWord);
        std::vector<std::vector<std::string>> expectedVector = StdUtil::generateStringVectorMatrix(expected);
        return StdUtil::compareEqualVectorMatrix<std::string>(output, expectedVector);
    }
}

TEST(_1268_SearchSuggestionsSystem, SimpleCases) {
    /*
    * Example 1:
    * Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
    * Output: [
    *    ["mobile","moneypot","monitor"],
    *    ["mobile","moneypot","monitor"],
    *    ["mouse","mousepad"],
    *    ["mouse","mousepad"],
    *    ["mouse","mousepad"]
    *    ]
    */
    EXPECT_TRUE(SearchSuggestionsSystem::testSuggestedProducts(
        "[mobile,mouse,moneypot,monitor,mousepad]",
        "mouse",
        {
            "[mobile,moneypot,monitor]",
            "[mobile,moneypot,monitor]",
            "[mouse,mousepad]",
            "[mouse,mousepad]",
            "[mouse,mousepad]"
        }));

    /*
    * Example 2:
    * Input: products = ["havana"], searchWord = "havana"
    * Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
    */
    EXPECT_TRUE(SearchSuggestionsSystem::testSuggestedProducts(
        "[havana]",
        "havana",
        {
            "[havana]",
            "[havana]",
            "[havana]",
            "[havana]",
            "[havana]",
            "[havana]"
        }));

    /*
    * Example 3:
    * Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
    * Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
    */
    EXPECT_TRUE(SearchSuggestionsSystem::testSuggestedProducts(
        "[bags,baggage,banner,box,cloths]",
        "bags",
        {
            "[baggage,bags,banner]",
            "[baggage,bags,banner]",
            "[baggage,bags]",
            "[bags]"
        }));
}

