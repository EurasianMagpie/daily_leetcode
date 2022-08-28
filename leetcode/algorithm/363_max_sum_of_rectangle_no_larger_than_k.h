#pragma once

//  https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/
/*
* 363. Max Sum of Rectangle No Larger Than K
* 
* Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in
* the matrix such that its sum is no larger than k.
*
* It is guaranteed that there will be a rectangle with a sum no larger than k.
* 
* Example 1:
* Input: matrix = [[1,0,1],[0,-2,3]], k = 2
* Output: 2
* Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
*
* Example 2:
* Input: matrix = [[2,2,-1]], k = 3
* Output: 3
*
* Constraints:
*    m == matrix.length
*    n == matrix[i].length
*    1 <= m, n <= 100
*    -100 <= matrix[i][j] <= 100
*    -10^5 <= k <= 10^5
*
* Follow up: What if the number of rows is much larger than the number of columns?
*/

#include <vector>
#include <gtest/gtest.h>
#include "../util/std_util.h"
#include <iostream>

namespace MaxSumOfRectangleNoLargerThanK {
    class Solution {
    public:
        int maxSumSubmatrix(std::vector<std::vector<int>>& matrix, int k) {
            int rows = matrix.size();
            int cols = matrix.at(0).size();
            // 遍历一边，计算出每个格子从原点的累计和
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    int v = matrix.at(i).at(j);
                    if (i > 0) {
                        v += matrix.at(i - 1).at(j);
                    }
                    if (j > 0) {
                        v += matrix.at(i).at(j - 1);
                    }
                    if (i > 0 && j > 0) {
                        v -= matrix.at(i - 1).at(j - 1);
                    }
                    matrix.at(i).at(j) = v;
                }
            }

            int ans(-1000000);
            // 从[c, r] 开始，依次计算扩张到 [cols, rows]各个矩阵的 累计和
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    for (int i = r; i < rows; i++) {
                        for (int j = c; j < cols; j++) {
                            //int sum = matrix.at(i).at(j) - matrix.at(r).at(j) - matrix.at(i).at(c) + matrix.at(r).at(c);
                            int sum = matrix.at(i).at(j);
                            if (r > 0) {
                                sum -= matrix.at(r - 1).at(j);
                            }
                            if (c > 0) {
                                sum -= matrix.at(i).at(c - 1);
                            }
                            if (r > 0 && c > 0) {
                                sum += matrix.at(r - 1).at(c - 1);
                            }

                            std::cout << "[" << r << "," << c << "] -- [" << i << "," << j << "] -- sum:" << sum << std::endl;

                            if (k == sum) {
                                return k;
                            }
                            else if (sum <= k && sum > ans) {
                                ans = sum;
                            }
                        }
                    }
                }
            }
            return ans;
        }
    };

    int testMaxSumSubmatrix(std::initializer_list<const char*> inputMatrix, int k) {
        std::vector<std::vector<int>> matrix = StdUtil::generateIntVectorMatrix(inputMatrix);
        return Solution().maxSumSubmatrix(matrix, k);
    }
}

TEST(_363_MaxSumOfRectangleNoLargerThanK, SimpleCases) {
    /*
    * Example 1:
    * Input: matrix = [[1,0,1],[0,-2,3]], k = 2
    * Output: 2
    */
    EXPECT_EQ(MaxSumOfRectangleNoLargerThanK::testMaxSumSubmatrix({"[1,0,1]", "[0,-2,3]"}, 2), 2);

    /*
    * Example 2:
    * Input: matrix = [[2,2,-1]], k = 3
    * Output: 3
    */
    EXPECT_EQ(MaxSumOfRectangleNoLargerThanK::testMaxSumSubmatrix({ "[2,2,-1]" }, 3), 3);

    EXPECT_EQ(MaxSumOfRectangleNoLargerThanK::testMaxSumSubmatrix({ "[1,0,1]", "[0,-2,3]" }, -2), -2);

    EXPECT_EQ(MaxSumOfRectangleNoLargerThanK::testMaxSumSubmatrix({ "[2,2,-1]" }, 0), -1);

    EXPECT_EQ(MaxSumOfRectangleNoLargerThanK::testMaxSumSubmatrix({ "[1,1,8]" }, 9), 9);
}