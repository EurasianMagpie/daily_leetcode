#pragma once

// https://leetcode.com/problems/furthest-building-you-can-reach/
/*
* 1642. Furthest Building You Can Reach
* 
* You are given an integer array heights representing the heights of buildings, some bricks, and some ladders.
*
* You start your journey from building 0 and move to the next building by possibly using bricks or ladders.
*
* While moving from building i to building i+1 (0-indexed),
*  - If the current building's height is greater than or equal to the next building's height,
*    you do not need a ladder or bricks.
*  - If the current building's height is less than the next building's height, you can either
*    use one ladder or (h[i+1] - h[i]) bricks.
*
* Return the furthest building index (0-indexed) you can reach if you use the given ladders and bricksoptimally.
* 
* Example 1:
* Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
* Output: 4
* Explanation: Starting at building 0, you can follow these steps:
*   - Go to building 1 without using ladders nor bricks since 4 >= 2.
*   - Go to building 2 using 5 bricks. You must use either bricks or ladders because 2 < 7.
*   - Go to building 3 without using ladders nor bricks since 7 >= 6.
*   - Go to building 4 using your only ladder. You must use either bricks or ladders because 6 < 9.
*   It is impossible to go beyond building 4 because you do not have any more bricks or ladders.
* 
* Example 2:
* Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
* Output: 7
*
* Example 3:
* Input: heights = [14,3,19,3], bricks = 17, ladders = 0
* Output: 3
*
*
* Constraints:
*   1 <= heights.length <= 105
*   1 <= heights[i] <= 106
*   0 <= bricks <= 109
*   0 <= ladders <= heights.length
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace FurthestBuildingYouCanReach {

    /*
    * 先消耗bricks，并用优先级队列记录抵消过的gap，
    * 当砖块不足，再用ladders抵消已经越过的最大gap，并恢复相应的bricks直到能越过当前gap
    */
    class Solution {
    public:
        int furthestBuilding(std::vector<int>& heights, int bricks, int ladders) {
            int i = 1;
            std::priority_queue<int, std::vector<int>, std::less<int>> gaps;
            for (; i < heights.size(); i++) {
                int gap = heights.at(i) - heights.at(i - 1);
                if (gap <= 0) {
                    continue;
                }

                bricks -= gap;
                gaps.push(gap);

                while (ladders > 0 && gaps.size() > 0 && bricks < 0) {
                    bricks += gaps.top();
                    gaps.pop();
                    ladders--;
                }

                if (bricks < 0) {
                    break;
                }
            }
            return i - 1;
        }
    };


    /*
    * 时间复杂度过高O(2^n)，超时了
    */
    class Solution1 {
    public:
        int furthestBuilding(std::vector<int>& heights, int bricks, int ladders) {
            return calcFurthestBuilding(heights, 0, bricks, ladders);
        }

    private:
        int calcFurthestBuilding(std::vector<int>& heights, int index, int bricks, int ladders) {
            if (index == heights.size() - 1) {
                return index;
            }
            int delta = heights.at(index + 1) - heights.at(index);
            if (delta <= 0) {
                return calcFurthestBuilding(heights, index + 1, bricks, ladders);
            }
            int r1(index), r2(index);
            if (bricks >= delta) {
                r1 = calcFurthestBuilding(heights, index + 1, bricks - delta, ladders);
            }
            if (ladders > 0) {
                r2 = calcFurthestBuilding(heights, index + 1, bricks, ladders - 1);
            }
            return r2 > r1 ? r2 : r1;
        }
    };

    int testFurthestBuilding(const char* input, int bricks, int ladders) {
        std::vector<int> heights = StdUtil::generateIntVector(input);
        return Solution().furthestBuilding(heights, bricks, ladders);
    }
}

TEST(_1642_FurthestBuildingYouCanReach, SimpleCases) {
    /*
    * Example 1:
    * Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
    * Output: 4
    */
    EXPECT_EQ(FurthestBuildingYouCanReach::testFurthestBuilding("[4,2,7,6,9,14,12]", 5, 1), 4);

    /*
    * Example 2:
    * Input: heights = [4,12,2,7,3,18,20,3,19], bricks = 10, ladders = 2
    * Output: 7
    */
    EXPECT_EQ(FurthestBuildingYouCanReach::testFurthestBuilding("[4,12,2,7,3,18,20,3,19]", 10, 2), 7);

    /*
    * Example 3:
    * Input: heights = [14,3,19,3], bricks = 17, ladders = 0
    * Output: 3
    */
    EXPECT_EQ(FurthestBuildingYouCanReach::testFurthestBuilding("[14,3,19,3]", 17, 0), 3);
}