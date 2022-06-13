#pragma once

// https://leetcode.com/problems/triangle/

/*
* 120. Triangle
* 
* Given a triangle array, return the minimum path sum from top to bottom.
* 
* For each step, you may move to an adjacent number of the row below. More formally, if you are on index i
* on the current row, you may move to either index i or index i + 1 on the next row.
* 
* Example 1:
* Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
* Output: 11
* Explanation: The triangle looks like:
*       2
*      3 4
*     6 5 7
*    4 1 8 3
* The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
* 
* Example 2:
* Input: triangle = [[-10]]
* Output: -10
* 
* 
* Constraints:
*    1 <= triangle.length <= 200
*    triangle[0].length == 1
*    triangle[i].length == triangle[i - 1].length + 1
*    -10^4 <= triangle[i][j] <= 10^4
*/

#include <vector>
#include <gtest/gtest.h>
#include "../util/std_util.h"


namespace Triangle {
    class Solution {
    public:
        /*
        * 从最后一行开始，为每一个上一行节点选择更小的值 向上累加，最后的顶点值就是最短路径
        */
        int minimumTotal(std::vector<std::vector<int>>& triangle) {
            std::size_t sz = triangle.size();
            for (int i = sz - 2; i >= 0; i--) {
                for (int j = 0; j < i + 1; j++) {
                    triangle[i][j] += triangle[i + 1][j] < triangle[i + 1][j + 1] ? triangle[i + 1][j] : triangle[i + 1][j + 1];
                }
            }
            return triangle[0][0];
        }
    };

    int testMinimumTotal(std::initializer_list<const char*> input) {
        std::vector<std::vector<int>> triangle = StdUtil::generateIntVectorMatrix(input);
        return Solution().minimumTotal(triangle);
    }
}

TEST(_120_Triangle, SimpleCases) {
    /*
    * Example 1:
    * Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
    * Output: 11
    */
    EXPECT_EQ(Triangle::testMinimumTotal({"[2]", "[3,4]", "[6,5,7]", "[4,1,8,3]"}), 11);

    /*
    * Example 2:
    * Input: triangle = [[-10]]
    * Output: -10
    */
    EXPECT_EQ(Triangle::testMinimumTotal({"[-10]"}), -10);
}