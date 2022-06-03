#pragma once


// https://leetcode.com/problems/range-sum-query-2d-immutable/
/*
* 304. Range Sum Query 2D - Immutable
* 
* Given a 2D matrix matrix, handle multiple queries of the following type:
* 
* Calculate the sum of the elements of matrix inside the rectangle defined by
* its upper left corner (row1, col1) and lower right corner (row2, col2).
* 
* Implement the NumMatrix class:
* - NumMatrix(int[][] matrix) Initializes the object with the integer matrix matrix.
* - int sumRegion(int row1, int col1, int row2, int col2) Returns the sum of
*   the elements of matrix inside the rectangle defined by its upper left corner (row1, col1)
*   and lower right corner (row2, col2).
* 
* 
*/

#include <vector>
#include <gtest/gtest.h>

#include "../util/std_util.h"

namespace RangeSumQuery2DImmutable {

    class NumMatrix {
    private:
        std::vector<std::vector<int>> mSumedMatrix;
    public:
        NumMatrix(std::vector<std::vector<int>>& matrix) {
            init(matrix);
        }

        int sumRegion(int row1, int col1, int row2, int col2) {
            row1--;
            col1--;
            int ret = mSumedMatrix.at(row2).at(col2);
            if (row1 >= 0) {
                ret -= mSumedMatrix.at(row1).at(col2);
            }
            if (col1 >= 0) {
                ret -= mSumedMatrix.at(row2).at(col1);
            }
            if (row1 >= 0 && col1 >= 0) {
                ret += mSumedMatrix.at(row1).at(col1);
            }
            return ret;
        }

        void init(std::vector<std::vector<int>>& matrix) {
            std::vector<std::vector<int>> rowSumedMatrix;
            int rowSz = matrix.size();
            int colSz = matrix.at(0).size();
            {
                for (int i = 0; i < rowSz; i++) {
                    std::vector<int> row;
                    int sum = 0;
                    for (int j = 0; j < colSz; j++) {
                        sum += matrix.at(i).at(j);
                        row.push_back(sum);
                    }
                    rowSumedMatrix.push_back(row);
                }
            }
            {
                std::vector<int> emptyRow(colSz, 0);
                std::vector<int>& lastRow = emptyRow;
                for (int i = 0; i < rowSz; i++) {
                    std::vector<int> row;
                    for (int j = 0; j < colSz; j++) {
                        row.push_back(rowSumedMatrix.at(i).at(j) + lastRow.at(j));
                    }
                    mSumedMatrix.push_back(row);
                    lastRow = row;
                }
            }
        }
    };

    /*
    * Time Limit Exceeded !!!
    */
    class NumMatrix0 {
    private:
        std::vector<std::vector<int>> mMatrix;
    public:
        NumMatrix0(std::vector<std::vector<int>>& matrix) {
            mMatrix = matrix;
        }

        int sumRegion(int row1, int col1, int row2, int col2) {
            int ret = 0;
            for (int i = row1; i <= row2; i++) {
                for (int j = col1; j <= col2; j++) {
                    ret += mMatrix.at(i).at(j);
                }
            }
            return ret;
        }
    };

    /**
     * Your NumMatrix object will be instantiated and called as such:
     * NumMatrix* obj = new NumMatrix(matrix);
     * int param_1 = obj->sumRegion(row1,col1,row2,col2);
     */

}

TEST(_304_RangeSumQuery2DImmutable, SimpleCases) {
    /*
    * Example 1:
    * Input
    * ["NumMatrix",
    * "sumRegion", "sumRegion", "sumRegion"]
    * [[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]],
    * [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
    * Output
    * [null, 8, 11, 12]
    */

    std::initializer_list<const char*> input = {
        "[3,0,1,4,2]", "[5,6,3,2,1]", "[1,2,0,1,5]", "[4,1,0,1,7]", "[1,0,3,0,5]"
    };
    std::vector<std::vector<int>> matrix = StdUtil::generateIntVectorMatrix(input);
    RangeSumQuery2DImmutable::NumMatrix* pNumMatrix = new RangeSumQuery2DImmutable::NumMatrix(matrix);

    EXPECT_EQ(8, pNumMatrix->sumRegion(2, 1, 4, 3));

    EXPECT_EQ(11, pNumMatrix->sumRegion(1, 1, 2, 2));

    EXPECT_EQ(12, pNumMatrix->sumRegion(1, 2, 2, 4));

    delete pNumMatrix;
}