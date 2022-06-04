#pragma once

// https://leetcode.com/problems/n-queens/
/*
* 51. N-Queens
* 
* The n-queens puzzle is the problem of placing n queens on an n x n chessboard
* such that no two queens attack each other.
*
* Given an integer n, return all distinct solutions to the n-queens puzzle. 
* You may return the answer in any order.
*
* Each solution contains a distinct board configuration of the n-queens' placement,
* where 'Q' and '.' both indicate a queen and an empty space, respectively.
* 
* Example 1:
* Input: n = 4
* Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
* 
* Example 2:
* Input: n = 1
* Output: [["Q"]]
*
* Constraints:
*  1 <= n <= 9
*/

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <gtest/gtest.h>

#include "../util/std_util.h"

namespace NQueens {

    class Solution {
        struct Position {
            unsigned char row;
            unsigned char col;
            Position(int r, int c) : row(r), col(c) {}
        };
    public:
        std::vector<std::vector<std::string>> solveNQueens(int n) {
            std::vector<std::vector<std::string>> solutions;
            if (n == 1) {
                // 固定解
                std::vector<std::string> r;
                r.push_back("Q");
                solutions.push_back(r);
                return solutions;
            }
            else if (n == 2 || n == 3) {
                // 无解
                return solutions;
            }
            
            std::vector<Position> tmpResult;
            doSolve(n, 0, tmpResult, solutions);
            return solutions;
        }

        void doSolve(
            int n,
            int row,
            std::vector<Position>& tmpResult,
            std::vector<std::vector<std::string>>& solutions) {
            // 对于每一行，逐个尝试计算解
            for (int col = 0; col < n; col++) {
                if (checkPosition(row, col, tmpResult)) {
                    tmpResult.push_back(Position(row, col));
                    if (row == n - 1) {
                        // 如果在最后一行找到一个解，则保存这个有效解
                        addSolution(n, tmpResult, solutions);
                    }
                    else {
                        // 不是最后一行，递归下一行
                        doSolve(n, row + 1, tmpResult, solutions);
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

        void addSolution(
            int n,
            std::vector<Position>& tmpResult,
            std::vector<std::vector<std::string>>& solutions) {
            char* buf = new char[n + 1];
            memset(buf, '.', n);
            buf[n] = 0;
            std::vector<std::string> solution;
            for (auto ite = tmpResult.begin(); ite != tmpResult.end(); ite++) {
                std::string row(buf);
                row.at((*ite).col) = 'Q';
                solution.push_back(row);
            }
            delete[] buf;
            solutions.push_back(solution);
        }
    };

    bool testSolveNQueens(int input, std::initializer_list<const char*> exptected) {
        std::vector<std::vector<std::string>> output = Solution().solveNQueens(input);
        std::vector<std::vector<std::string>> exptectedResult = StdUtil::generateStringVectorMatrix(exptected);
        std::sort(output.begin(), output.end());
        std::sort(exptectedResult.begin(), exptectedResult.end());
        return StdUtil::compareEqualVectorMatrix(exptectedResult, output);
    }
}

TEST(_51_NQueens, SimpleCases) {
    /*
    * Example 1:
    * Input: n = 4
    * Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
    */
    EXPECT_TRUE(NQueens::testSolveNQueens(4,
        {
            "[.Q..,...Q,Q...,..Q.]",
            "[..Q.,Q...,...Q,.Q..]"
        }
    ));

    /* 
    * Example 2:
    * Input: n = 1
    * Output: [["Q"]]
    */
    EXPECT_TRUE(NQueens::testSolveNQueens(1, { "[Q]" }));
}