#pragma once

//  https://leetcode.com/problems/count-vowels-permutation/
/*
* 1220. Count Vowels Permutation
* 
* Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
*    Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
*    Each vowel 'a' may only be followed by an 'e'.
*    Each vowel 'e' may only be followed by an 'a' or an 'i'.
*    Each vowel 'i' may not be followed by another 'i'.
*    Each vowel 'o' may only be followed by an 'i' or a 'u'.
*    Each vowel 'u' may only be followed by an 'a'.
*    Since the answer may be too large, return it modulo 10^9 + 7.
* 
* Example 1:
* Input: n = 1
* Output: 5
* Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
*
* Example 2:
* Input: n = 2
* Output: 10
* Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".
*
* Example 3: 
* Input: n = 5
* Output: 68
*
* Constraints:
*    1 <= n <= 2 * 10^4
*/

#include <gtest/gtest.h>


namespace CountVowelsPermutation {

    class Solution {
        // index of 
        const int a = 0;
        const int e = 1;
        const int i = 2;
        const int o = 3;
        const int u = 4;

    public:
        int countVowelPermutation(int n) {
            // count of strings end with :
            //              a, e, i, o, u
            int64_t count[5] = {1, 1, 1, 1, 1};
            int64_t temp[5] = {};
            int64_t m = pow(10, 9) + 7;

            while (n-- > 1) {
                // a = e + i + u
                temp[a] = (count[e] + count[i] + count[u]) % m;
                // e = a + i
                temp[e] = (count[a] + count[i]) % m;
                // i = e + o
                temp[i] = (count[e] + count[o]) % m;
                // o = i;
                temp[o] = count[i];
                // u = i + o
                temp[u] = (count[i] + count[o]) % m;

                memcpy(count, temp, sizeof(count));
            }

            return (count[a] + count[e] + count[i] + count[o] + count[u]) % m;
        }
    };
}


TEST(_1220_CountVowelsPermutation, SimpleCases) {

    /*
    * Example 1:
    * Input: n = 1
    * Output: 5
    */
    //EXPECT_EQ(CountVowelsPermutation::Solution().countVowelPermutation(1), 5);

    /*
    * Example 2:
    * Input: n = 2
    * Output: 10
    */
    EXPECT_EQ(CountVowelsPermutation::Solution().countVowelPermutation(2), 10);

    /*
    * Example 3: 
    * Input: n = 5
    * Output: 68
    */
    EXPECT_EQ(CountVowelsPermutation::Solution().countVowelPermutation(5), 68);
}