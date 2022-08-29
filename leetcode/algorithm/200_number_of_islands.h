#pragma once

//  https://leetcode.com/problems/number-of-islands/
/*
* 200. Number of Islands
* 
* Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's
* (water), return the number of islands.
*
* An island is surrounded by water and is formed by connecting adjacent lands
* horizontally or vertically. You may assume all four edges of the grid are all surrounded
* by water.
* 
* Example 1:
* Input: grid = [
*      ["1","1","1","1","0"],
*      ["1","1","0","1","0"],
*      ["1","1","0","0","0"],
*      ["0","0","0","0","0"]
*    ]
* Output: 1
* 
* Example 2:
* Input: grid = [
*      ["1","1","0","0","0"],
*      ["1","1","0","0","0"],
*      ["0","0","1","0","0"],
*      ["0","0","0","1","1"]
*    ]
* Output: 3
*
* Constraints:
*    m == grid.length
*    n == grid[i].length
*    1 <= m, n <= 300
*    grid[i][j] is '0' or '1'.
*/

#include <vector>
#include <gtest/gtest.h>
#include "../util/std_util.h"


namespace NumberOfIslands {
    // 遍历每一个元素，一旦发现元素为1， 则从这个元素开始，遍历对应的整个岛，并对该岛所有元素染色为大于1的值，并计数
    class Solution {
    public:
        int numIslands(std::vector<std::vector<char>>& grid) {
            int ans(0);
            int rows = grid.size();
            int cols = grid.at(0).size();
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (grid[i][j] == '1') {
                        ans++;
                        markThisIsland(grid, i, j, rows, cols);
                    }
                }
            }
            return ans;
        }

        void markThisIsland(std::vector<std::vector<char>>& grid, int i, int j, int rows, int cols) {
            grid[i][j] = 'x';
            // test right
            if (j + 1 < cols && grid[i][j + 1] == '1') {
                markThisIsland(grid, i, j + 1, rows, cols);
            }
            // test down
            if (i + 1 < rows && grid[i + 1][j] == '1') {
                markThisIsland(grid, i + 1, j, rows, cols);
            }
            // test left
            if (j - 1 >= 0 && grid[i][j - 1] == '1') {
                markThisIsland(grid, i, j - 1, rows, cols);
            }
            // test up
            if (i - 1 >= 0 && grid[i - 1][j] == '1') {
                markThisIsland(grid, i - 1, j, rows, cols);
            }
        }
    };

    int testNumIslands(std::initializer_list<const char*> input) {
        std::vector<std::vector<char>> grid = StdUtil::generateCharVectorMatrix(input);
        return Solution().numIslands(grid);
    }
}

TEST(_200_NumberOfIslands, SimpleCases) {
    /*
    * Example 1:
    * Input: grid = [
    *      ["1","1","1","1","0"],
    *      ["1","1","0","1","0"],
    *      ["1","1","0","0","0"],
    *      ["0","0","0","0","0"]
    *    ]
    * Output: 1
    */
    EXPECT_EQ(NumberOfIslands::testNumIslands({
            "[1,1,1,1,0]",
            "[1,1,0,1,0]",
            "[1,1,0,0,0]",
            "[0,0,0,0,0]",
        }), 1);

    /*
    * Example 2:
    * Input: grid = [
    *      ["1","1","0","0","0"],
    *      ["1","1","0","0","0"],
    *      ["0","0","1","0","0"],
    *      ["0","0","0","1","1"]
    *    ]
    * Output: 3
    */
    EXPECT_EQ(NumberOfIslands::testNumIslands({
            "[1,1,0,0,0]",
            "[1,1,0,0,0]",
            "[0,0,1,0,0]",
            "[0,0,0,1,1]",
        }), 3);//*/
}