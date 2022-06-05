#pragma once

// https://leetcode.com/problems/n-queens-ii/
/*
* 52. N-Queens II
* 
* The n-queens puzzle is the problem of placing n queens on an n x n chessboard
* such that no two queens attack each other.
* 
* Given an integer n, return the number of distinct solutions to the n-queens puzzle.
* 
* Example 1:
* Input: n = 4
* Output: 2
* Explanation: There are two distinct solutions to the 4-queens puzzle as shown.
* 
* Example 2:
* Input: n = 1
* Output: 1
*/

#include <vector>
#include <gtest/gtest.h>

namespace NQueensII {
    class Solution {
        struct Position {
            unsigned char row;
            unsigned char col;
            Position(int r, int c) : row(r), col(c) {}
        };
    public:
        int totalNQueens(int n) {
            if (n == 1) {
                return 1;
            }
            else if (n == 2 || n == 3) {
                // 无解
                return 0;
            }
            int totalSolution(0);
            std::vector<Position> tmpResult;
            doSolve(n, 0, tmpResult, totalSolution);
            return totalSolution;
        }

        void doSolve(
            int n,
            int row,
            std::vector<Position>& tmpResult,
            int& totalSolution) {
            // 对于每一行，逐个尝试计算解
            for (int col = 0; col < n; col++) {
                if (checkPosition(row, col, tmpResult)) {
                    tmpResult.push_back(Position(row, col));
                    if (row == n - 1) {
                        // 如果在最后一行找到一个解，这是一个有效解
                        totalSolution++;
                    }
                    else {
                        // 不是最后一行，递归下一行
                        doSolve(n, row + 1, tmpResult, totalSolution);
                    }
                    tmpResult.pop_back();
                }
            }
        }

        /*
        * 根据临时解已经存在的坐标，判断坐标(row, col) 是否可用
        */
        bool checkPosition(int row, int col, std::vector<Position>& tmpResult) {
            for (auto ite = tmpResult.begin(); ite != tmpResult.end(); ite++) {
                Position pos = *ite;
                if (pos.col == col) {
                    // 不可在同一列
                    return false;
                }
                else if (std::abs(pos.row - row) == std::abs(pos.col - col)) {
                    // 不可在斜线上
                    return false;
                }
                // 由于是逐行递归，因此不会出现同一行的情况
            }
            return true;
        }
    };
}

TEST(_52_NQueensII, SimpleCases) {
    /*
    * Example 1:
    * Input: n = 4
    * Output: 2
    */
    EXPECT_EQ(2, NQueensII::Solution().totalNQueens(4));
}