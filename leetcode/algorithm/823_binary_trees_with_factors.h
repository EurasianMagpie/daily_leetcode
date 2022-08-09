#pragma once

//  https://leetcode.com/problems/binary-trees-with-factors/
/*
* 823. Binary Trees With Factors
* 
* Given an array of unique integers, arr, where each integer arr[i] is strictly greater than 1.
*
* We make a binary tree using these integers, and each number may be used for any number of times.
* Each non-leaf node's value should be equal to the product of the values of its children.
*
* Return the number of binary trees we can make. The answer may be too large so return the answer
* modulo 109 + 7.
*
* Example 1:
* Input: arr = [2,4]
* Output: 3
* Explanation: We can make these trees: [2], [4], [4, 2, 2]
*
* Example 2:
* Input: arr = [2,4,5,10]
* Output: 7
* Explanation: We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10, 5, 2].
*
* Constraints:
*    1 <= arr.length <= 1000
*    2 <= arr[i] <= 109
*    All the values of arr are unique.
*/

#include <vector>
#include <algorithm>
#include <map>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace BinaryTreesWithFactors {

    const int mod = 1000000007;

    class Solution {
    public:
        int numFactoredBinaryTrees(std::vector<int>& arr) {
            std::sort(arr.begin(), arr.end());
            std::map<int, int64_t> cache;

            int64_t ans(0);
            for (int i = 0; i < arr.size(); i++) {
                calcEachNum(arr, i, cache, ans);
            }

            return ans % mod;
        }

        void calcEachNum(std::vector<int>& arr, int index, std::map<int, int64_t>& cache, int64_t& ans) {
            int64_t r(1);
            for (auto ite = cache.begin(); ite != cache.end(); ite++) {
                if (arr[index] % ite->first == 0) {
                    auto fd = cache.find(arr[index] / ite->first);
                    if (fd != cache.end()) {
                        r += ite->second * fd->second;
                    }
                }
            }
            ans += r;
            cache[arr[index]] = r;
        }
    };

    int testNumFactoredBinaryTrees(const char* input) {
        std::vector<int> arr = StdUtil::generateIntVector(input);
        return Solution().numFactoredBinaryTrees(arr);
    }
}

TEST(_823_BinaryTreesWithFactors, SimpleCases) {
    /*
    * Example 1:
    * Input: arr = [2,4]
    * Output: 3
    */
    EXPECT_EQ(BinaryTreesWithFactors::testNumFactoredBinaryTrees("[2,4]"), 3);

    /*
    * Example 2:
    * Input: arr = [2,4,5,10]
    * Output: 7
    */
    EXPECT_EQ(BinaryTreesWithFactors::testNumFactoredBinaryTrees("[2,4,5,10]"), 7);

    EXPECT_EQ(BinaryTreesWithFactors::testNumFactoredBinaryTrees("[2, 4, 8, 16]"), 23);

    EXPECT_EQ(BinaryTreesWithFactors::testNumFactoredBinaryTrees("[2,4,8,16,32,128,64,512,256,1024,2048,4096,8192,16384,32768,65536,131072]"), 278704924);
}