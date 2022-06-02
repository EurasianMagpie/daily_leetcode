#pragma once

// https://leetcode.com/problems/transpose-matrix/
/*
* 867. Transpose Matrix
* 
* Given a 2D integer array matrix, return the transpose of matrix.
*
* The transpose of a matrix is the matrix flipped over its main diagonal, 
* switching the matrix's row and column indices.
* 
*		2	4	-1		2	-10	18
*		-10	5	11	=>	4	5	-7
*		18	-7	6		-1	11	6
* 
* Example 1:
* Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
* Output: [[1,4,7],[2,5,8],[3,6,9]]
*
* Example 2:
* Input: matrix = [[1,2,3],[4,5,6]]
* Output: [[1,4],[2,5],[3,6]]
* 
* Constraints:
*  m == matrix.length
*  n == matrix[i].length
*  1 <= m, n <= 1000
*  1 <= m * n <= 10^5
*  -10^9 <= matrix[i][j] <= 10^9
*/

#include <vector>
#include <gtest/gtest.h>

#include "../util/std_util.h"

namespace TransposeMatrix {
    class Solution {
    public:
        std::vector<std::vector<int>> transpose(std::vector<std::vector<int>>& matrix) {
            std::size_t sz1 = matrix.size();
            std::size_t sz2 = matrix.at(0).size();
            std::vector<std::vector<int>> ret = std::vector<std::vector<int>>(sz2);
            for (std::size_t i = 0; i < sz2; i++) {
                ret.at(i) = std::vector<int>(sz1);
            }
            for (std::size_t i = 0; i < sz1; i++) {
                for (std::size_t j = 0; j < sz2; j++) {
                    ret[j][i] = matrix[i][j];
                }
            }
            return ret;
        }
    };

    bool testTranspose(
        std::initializer_list<const char*> input,
        std::initializer_list<const char*> expected) {
        std::vector<std::vector<int>> matirx = StdUtil::generateIntVectorMatrix(input);
        std::vector<std::vector<int>> outputMtx = Solution().transpose(matirx);
        std::vector<std::vector<int>> expectedMtx = StdUtil::generateIntVectorMatrix(expected);
        return StdUtil::compareEqualVectorMatrix<int>(outputMtx, expectedMtx);
    }
}

TEST(_867_TransposeMatrix, SimpleCases) {
    /*
    * Example 1:
    * Input : matrix = [[1,2,3],[4,5,6],[7,8,9]]
    * Output : [[1,4,7],[2,5,8],[3,6,9]]
    */
    EXPECT_TRUE(TransposeMatrix::testTranspose(
        {
            "[1,2,3]",
            "[4,5,6]",
            "[7,8,9]",
        },
        {
            "[1,4,7]",
            "[2,5,8]",
            "[3,6,9]", 
        }
    ));

    /*
    * Example 2 :
    * Input : matrix = [[1,2,3],[4,5,6]]
    * Output : [[1,4],[2,5],[3,6]]
    */
    EXPECT_TRUE(TransposeMatrix::testTranspose(
        {
            "[1,2,3]",
            "[4,5,6]",
        },
        {
            "[1,4]",
            "[2,5]",
            "[3,6]",
        }
    ));
}