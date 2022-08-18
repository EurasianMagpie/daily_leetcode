#pragma once

//  https://leetcode.com/problems/reduce-array-size-to-the-half/
/*
* 1338. Reduce Array Size to The Half
* 
* You are given an integer array arr. You can choose a set of integers and remove all the
* occurrences of these integers in the array.
*
* Return the minimum size of the set so that at least half of the integers of the array are
* removed.
* 
* Example 1:
* Input: arr = [3,3,3,3,5,5,5,2,2,7]
* Output: 2
* Explanation: Choosing {3,7} will make the new array [5,5,5,2,2] which
* has size 5 (i.e equal to half of the size of the old array).
* Possible sets of size 2 are {3,5},{3,2},{5,2}.
* Choosing set {2,7} is not possible as it will make the new array
* [3,3,3,3,5,5,5] which has a size greater than half of the size of the
* old array.
*
* Example 2:
* Input: arr = [7,7,7,7,7,7]
* Output: 1
* Explanation: The only possible set you can choose is {7}. This will make
* the new array empty.
*
* Constraints:
*    2 <= arr.length <= 105
*    arr.length is even.
*    1 <= arr[i] <= 105
*/

#include <vector>
#include <queue>
#include <map>
#include <gtest/gtest.h>
#include "../util/std_util.h"


namespace ReduceArraySizeToTheHalf {
    class Solution {
    public:
        int minSetSize(std::vector<int>& arr) {
            std::map<int, int> numCount;
            for (int n : arr) {
                auto fd = numCount.find(n);
                if (fd != numCount.end()) {
                    numCount[n] = numCount[n] + 1;
                }
                else {
                    numCount[n] = 1;
                }
            }
            std::priority_queue<int, std::vector<int>, std::less<int>> pq;
            for (auto ite = numCount.begin(); ite != numCount.end(); ite++) {
                pq.push(ite->second);
            }
            int target = arr.size() >> 1;
            int ans(0);
            do {
                target -= pq.top();
                pq.pop();
                ans++;
            } while (target > 0);
            return ans;
        }
    };

    int testMinSetSize(const char* input) {
        std::vector<int> arr = StdUtil::generateIntVector(input);
        return Solution().minSetSize(arr);
    }
}


TEST(_1338_ReduceArraySizeToTheHalf, SimpleCases) {
    /*
    * Example 1:
    * Input: arr = [3,3,3,3,5,5,5,2,2,7]
    * Output: 2
    */
    EXPECT_EQ(ReduceArraySizeToTheHalf::testMinSetSize("[3,3,3,3,5,5,5,2,2,7]"), 2);

    /*
    * Example 2:
    * Input: arr = [7,7,7,7,7,7]
    * Output: 1
    */
}