#pragma once

//  https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
/*
* 1423. Maximum Points You Can Obtain from Cards
* 
* There are several cards arranged in a row, and each card has an associated number of points. The points
* are given in the integer array cardPoints.
*
* In one step, you can take one card from the beginning or from the end of the row. You have to take
* exactly k cards.
*
* Your score is the sum of the points of the cards you have taken.
*
* Given the integer array cardPoints and the integer k, return the maximum score you can obtain.
* 
* Example 1:
* Input: cardPoints = [1,2,3,4,5,6,1], k = 3
* Output: 12
* Explanation: After the first step, your score will always be 1. However, choosing the rightmost card
* first will maximize your total score. The optimal strategy is to take the three cards on the right,
* giving a final score of 1 + 6 + 5 = 12.
* 
* Example 2:
* Input: cardPoints = [2,2,2], k = 2
* Output: 4
* Explanation: Regardless of which two cards you take, your score will always be 4.
*
* Example 3:
* Input: cardPoints = [9,7,7,9,7,7,9], k = 7
* Output: 55
* Explanation: You have to take all the cards. Your score is the sum of points of all cards.
*
* Constraints:
*    1 <= cardPoints.length <= 10^5
*    1 <= cardPoints[i] <= 10^4
*    1 <= k <= cardPoints.length
*/

#include <vector>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace MaximumPointsYouCanObtainFromCards {

    /*
    * 思路：
    * 1. 首先想到的是动态规划求解，但复杂度肯定过高
    * 2. 这个问题可以转化为，找到数组 cardPoints 中，连续 cardPoints.length - 7 个元素求和最小的位置，
    *    用总数减去这个最小和的子数组就是这个问题的解
    *    先计算出第一个子数组的和，然后采用滑动窗口方式依次计算比较后续子数组，时间复杂度O(N)
    */
    class Solution {
    public:
        int maxScore(std::vector<int>& cardPoints, int k) {
            int sumAll(0);
            int subVectorLength = cardPoints.size() - k;
            // 如果cardPoints的长度就是k，直接返回数组求和
            if (subVectorLength <= 0) {
                for (auto n : cardPoints) {
                    sumAll += n;
                }
                return sumAll;
            }

            int minSumOfSubVector(0);
            int sumOfEachSubVector(0);
            // 计算从索引0开始的第一个子数组的和
            for (int i = 0; i < subVectorLength; i++) {
                sumOfEachSubVector += cardPoints.at(i);
            }
            sumAll = minSumOfSubVector = sumOfEachSubVector;
            
            // 向后移动子数组，比较出更小的子数组的和，并累加全数组的和
            for (int j = 0; j < cardPoints.size() - subVectorLength; j++) {
                sumOfEachSubVector = sumOfEachSubVector + cardPoints.at(j + subVectorLength) - cardPoints.at(j);
                if (sumOfEachSubVector < minSumOfSubVector) {
                    minSumOfSubVector = sumOfEachSubVector;
                }
                sumAll += cardPoints.at(j + subVectorLength);
            }
            
            // 结果是 全数组的和 减去 最小的子数组的和
            return sumAll - minSumOfSubVector;
        }
    };

    int testMaxScore(const char* input, int k) {
        std::vector<int> cardPoints = StdUtil::generateIntVector(input);
        return Solution().maxScore(cardPoints, k);
    }
}

TEST(_1423_MaximumPointsYouCanObtainFromCards, SimpleCases) {
    /*
    * Example 1:
    * Input: cardPoints = [1,2,3,4,5,6,1], k = 3
    * Output: 12
    */
    EXPECT_EQ(MaximumPointsYouCanObtainFromCards::testMaxScore("[1,2,3,4,5,6,1]", 3), 12);

    /*
    * Example 2:
    * Input: cardPoints = [2,2,2], k = 2
    * Output: 4
    */
    EXPECT_EQ(MaximumPointsYouCanObtainFromCards::testMaxScore("[2,2,2]", 2), 4);

    /*
    * Example 3:
    * Input: cardPoints = [9,7,7,9,7,7,9], k = 7
    * Output: 55
    */
    EXPECT_EQ(MaximumPointsYouCanObtainFromCards::testMaxScore("[9,7,7,9,7,7,9]", 7), 55);
}