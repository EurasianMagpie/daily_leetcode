#pragma once

// https://leetcode.com/problems/sudoku-solver/
/*
* 37. Sudoku Solver / 数独
*
* Write a program to solve a Sudoku puzzle by filling the empty cells.
*
* A sudoku solution must satisfy all of the following rules:
*  1. Each of the digits 1-9 must occur exactly once in each row.
*  2. Each of the digits 1-9 must occur exactly once in each column.
*  3. Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
* The '.' character indicates empty cells.
*/

#include <vector>
#include <iostream>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace SudokuSolver {
    class Solution {
        struct Pos
        {
            unsigned char row;
            unsigned char col;

            Pos(unsigned char r, unsigned char c) : row(r), col(c) {}
        };
    public:
        void solveSudoku(std::vector<std::vector<char>>& board) {
            // 每行，每列，每个box，剩余可用数字，按位
            unsigned short unUsedNumsRow[9] =
            { 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff };
            unsigned short unUsedNumsCol[9] =
            { 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff };
            unsigned short unUsedNumsBox[9] =
            { 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff, 0x01ff };

            std::vector<Solution::Pos> unknownPos;
            for (std::size_t i = 0; i < board.size(); i++) {
                std::vector<char>& row = board.at(i);
                for (std::size_t j = 0; j < row.size(); j++) {
                    char c = row.at(j);
                    if (c == '.') {
                        unknownPos.push_back(Solution::Pos(i, j));
                    }
                    else {
                        int n = c - '1';
                        applyNumInPosition(n, i, j, unUsedNumsRow, unUsedNumsCol, unUsedNumsBox);
                    }
                }
            }

            while (!unknownPos.empty()) {
                std::size_t sz = unknownPos.size();

                auto ite = unknownPos.begin();
                while (ite != unknownPos.end())
                {
                    std::size_t row = (*ite).row;
                    std::size_t col = (*ite).col;
                    int n = trySolvePosition(
                        unUsedNumsRow[row],
                        unUsedNumsCol[col],
                        unUsedNumsBox[getBoxIndex(row, col)]
                    );
                    if (n > 0) {
                        board.at(row).at(col) = n;
                        std::cout << "(" << row << "," << col << ") - " << n << std::endl;
                        applyNumInPosition(n, row, col, unUsedNumsRow, unUsedNumsCol, unUsedNumsBox);
                        ite = unknownPos.erase(ite);
                    }
                    else {
                        ite++;
                    }
                    
                }

                if (sz == unknownPos.size()) {
                    std::cout << "can not solve" << std::endl;
                    break;
                }
            }
        }

        inline int getBoxIndex(std::size_t row, std::size_t col) {
            std::size_t boxRow = row / 3;
            std::size_t boxCol = col / 3;
            return (boxRow * 3) + boxCol;
        }

        inline void applyNumInPosition(
            int num,
            std::size_t row,
            std::size_t col,
            unsigned short* unUsedNumsRow,
            unsigned short* unUsedNumsCol,
            unsigned short* unUsedNumsBox) {
            if (num >= 0 && num < 9) {
                unsigned short mask = ~(1 << num);
                unUsedNumsRow[row] &= mask;
                unUsedNumsCol[col] &= mask;
                unUsedNumsBox[getBoxIndex(row, col)] &= mask;
            }
        }

        /*
        * 试图计算单个坐标的解
        * unUsedInRow 当前行剩余可用数字
        * unUsedInCol 当前列剩余可用数字
        * unUsedInBox 当前Box剩余可用数字
        * 
        * 返回值：如果有唯一解，返回值当前坐标解，否则返回-1
        */
        int trySolvePosition(
            unsigned short unUsedInRow,
            unsigned short unUsedInCol,
            unsigned short unUsedInBox) {

            // 剩余可用数字的交集，如果是确定的一个数，则是一个确定的解
            unsigned short x = unUsedInRow & unUsedInCol & unUsedInBox;
            switch (x)
            {
            case 0x0001:
                return 1;
            case 0x0002:
                return 2;
            case 0x0004:
                return 3;
            case 0x0008:
                return 4;
            case 0x0010:
                return 5;
            case 0x0020:
                return 6;
            case 0x0040:
                return 7;
            case 0x0080:
                return 8;
            case 0x0100:
                return 9;
            default:
                return -1;
            }

            // 如果不是确定的解
            // 则遍历box中的空格，按剩余可用数字寻找，是否存在某个数字只能放在特定的位置
        }
    };

    bool testSolveSudoku(
        std::initializer_list<const char*> input,
        std::initializer_list<const char*> expected) {
        
        std::size_t sz = input.size();
        std::size_t szExpected = expected.size();
        if (sz == 0 || szExpected == 0 || sz != szExpected) {
            return false;
        }
        std::vector<std::vector<char>> board = StdUtil::generateCharVectorMatrix(input);
        Solution().solveSudoku(board);
        std::vector<std::vector<char>> expectedVector = StdUtil::generateCharVectorMatrix(expected);
        return StdUtil::compareEqualVectorMatrix<char>(board, expectedVector);
    }
}

TEST(_37_SudokuSolver, SimpleCases) {
    /*
    Example 1:
    Input: board = [
    ["5","3",".",".","7",".",".",".","."],
    ["6",".",".","1","9","5",".",".","."],
    [".","9","8",".",".",".",".","6","."],
    ["8",".",".",".","6",".",".",".","3"],
    ["4",".",".","8",".","3",".",".","1"],
    ["7",".",".",".","2",".",".",".","6"],
    [".","6",".",".",".",".","2","8","."],
    [".",".",".","4","1","9",".",".","5"],
    [".",".",".",".","8",".",".","7","9"]
    ]
    Output: [
    ["5","3","4","6","7","8","9","1","2"],
    ["6","7","2","1","9","5","3","4","8"],
    ["1","9","8","3","4","2","5","6","7"],
    ["8","5","9","7","6","1","4","2","3"],
    ["4","2","6","8","5","3","7","9","1"],
    ["7","1","3","9","2","4","8","5","6"],
    ["9","6","1","5","3","7","2","8","4"],
    ["2","8","7","4","1","9","6","3","5"],
    ["3","4","5","2","8","6","1","7","9"]
    ]
    */
    EXPECT_TRUE(SudokuSolver::testSolveSudoku(
        {
            "[5,3,.,.,7,.,.,.,.]",
            "[6,.,.,1,9,5,.,.,.]",
            "[.,9,8,.,.,.,.,6,.]",
            "[8,.,.,.,6,.,.,.,3]",
            "[4,.,.,8,.,3,.,.,1]",
            "[7,.,.,.,2,.,.,.,6]",
            "[.,6,.,.,.,.,2,8,.]",
            "[.,.,.,4,1,9,.,.,5]",
            "[.,.,.,.,8,.,.,7,9]"
        },
        {
            "[5,3,4,6,7,8,9,1,2]",
            "[6,7,2,1,9,5,3,4,8]",
            "[1,9,8,3,4,2,5,6,7]",
            "[8,5,9,7,6,1,4,2,3]",
            "[4,2,6,8,5,3,7,9,1]",
            "[7,1,3,9,2,4,8,5,6]",
            "[9,6,1,5,3,7,2,8,4]",
            "[2,8,7,4,1,9,6,3,5]",
            "[3,4,5,2,8,6,1,7,9]"
        }
    ));
}