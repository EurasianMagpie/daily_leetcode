#pragma once

//  https://leetcode.com/problems/sort-the-matrix-diagonally/
/*
* 1329. Sort the Matrix Diagonally
* 
* A matrix diagonal is a diagonal line of cells starting from some cell in either the
* topmost row or leftmost column and going in the bottom-right direction until reaching
* the matrix's end. For example, the matrix diagonal starting from mat[2][0], where
* mat is a 6 x 3 matrix, includes cells mat[2][0], mat[3][1], and mat[4][2].
*
* Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order
* and return the resulting matrix.
* 
* Example 1:
* Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
* Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
*
* Example 2:
* Input: mat = [[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]
* Output: [[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,50,66],[84,28,75,33,55,68]]
*
* Constraints:
*    m == mat.length
*    n == mat[i].length
*    1 <= m, n <= 100
*    1 <= mat[i][j] <= 100
*/
/*
* �ھ����ÿһ��45��Խ���������
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace SortTheMatrixDiagonally {
    class Solution {
    public:
        std::vector<std::vector<int>> diagonalSort(std::vector<std::vector<int>>& mat) {
            int rows = mat.size();
            int cols = mat.at(0).size();

            // �����ǣ������Խ���
            for (int r = 1; r < rows; r++) {
                std::priority_queue<int> pq;
                int i(r), j(0);
                while (i < rows && j < cols) {
                    pq.push(mat[i++][j++]);
                }
                while (!pq.empty()) {
                    mat[--i][--j] = pq.top();
                    pq.pop();
                }
            }

            // �����ǣ����Խ���
            for (int c = 0; c < cols; c++) {
                std::priority_queue<int> pq;
                int i(0), j(c);
                while (i < rows && j < cols) {
                    pq.push(mat[i++][j++]);
                }
                while (!pq.empty()) {
                    mat[--i][--j] = pq.top();
                    pq.pop();
                }
            }

            return mat;
        }
    };

    bool testDiagonalSort(std::initializer_list<const char*> input, std::initializer_list<const char*> expected) {
        std::vector<std::vector<int>> inputMat = StdUtil::generateIntVectorMatrix(input);
        std::vector<std::vector<int>> expectedMat = StdUtil::generateIntVectorMatrix(expected);
        std::vector<std::vector<int>> outputMat = Solution().diagonalSort(inputMat);
        return StdUtil::compareEqualVectorMatrix(outputMat, expectedMat);
    }
}

TEST(_1329_SortTheMatrixDiagonally, SimpleCases) {
    /*
    * Example 1:
    * Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
    * Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
    */
    EXPECT_TRUE(SortTheMatrixDiagonally::testDiagonalSort(
        {
            "[3,3,1,1]",
            "[2,2,1,2]",
            "[1,1,1,2]"
        },
        {
            "[1,1,1,1]",
            "[1,2,2,2]",
            "[1,2,3,3]"
        })
    );

    /*
    * Example 2:
    * Input: mat = [[11,25,66,1,69,7],[23,55,17,45,15,52],[75,31,36,44,58,8],[22,27,33,25,68,4],[84,28,14,11,5,50]]
    * Output: [[5,17,4,1,52,7],[11,11,25,45,8,69],[14,23,25,44,58,15],[22,27,31,36,50,66],[84,28,75,33,55,68]]
    */
    EXPECT_TRUE(SortTheMatrixDiagonally::testDiagonalSort(
        {
            "[11,25,66,1,69,7]",
            "[23,55,17,45,15,52]",
            "[75,31,36,44,58,8]",
            "[22,27,33,25,68,4]",
            "[84,28,14,11,5,50]"
        },
        {
            "[5,17,4,1,52,7]",
            "[11,11,25,45,8,69]",
            "[14,23,25,44,58,15]",
            "[22,27,31,36,50,66]",
            "[84,28,75,33,55,68]"
        })
    );
}