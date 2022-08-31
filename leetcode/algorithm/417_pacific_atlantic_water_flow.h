#pragma once

//  https://leetcode.com/problems/pacific-atlantic-water-flow/
/*
* 417. Pacific Atlantic Water Flow
* 
* There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic
* Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic
* Ocean touches the island's right and bottom edges.
*
* The island is partitioned into a grid of square cells. You are given an m x n integer
* matrix heights where heights[r][c] represents the height above sea level of the cell
* at coordinate (r, c).
*
* The island receives a lot of rain, and the rain water can flow to neighboring cells
* directly north, south, east, and west if the neighboring cell's height is less than
* or equal to the current cell's height. Water can flow from any cell adjacent to an
* ocean into the ocean.
*
* Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that
* rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
* 
* Example 1:
* Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
* Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
* Explanation: The following cells can flow to the Pacific and Atlantic oceans,
* as shown below:
*    [0,4]: [0,4] -> Pacific Ocean 
*           [0,4] -> Atlantic Ocean
*    [1,3]: [1,3] -> [0,3] -> Pacific Ocean 
*           [1,3] -> [1,4] -> Atlantic Ocean
*    [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
*           [1,4] -> Atlantic Ocean
*    [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
*           [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
*    [3,0]: [3,0] -> Pacific Ocean 
*           [3,0] -> [4,0] -> Atlantic Ocean
*    [3,1]: [3,1] -> [3,0] -> Pacific Ocean 
*           [3,1] -> [4,1] -> Atlantic Ocean
*    [4,0]: [4,0] -> Pacific Ocean 
*           [4,0] -> Atlantic Ocean
* Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
* 
* Example 2:
* Input: heights = [[1]]
* Output: [[0,0]]
* Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.
* 
* Constraints:
*    m == heights.length
*    n == heights[r].length
*    1 <= m, n <= 200
*    0 <= heights[r][c] <= 10^5
*/

#include <vector>
#include <queue>
#include <map>
#include <gtest/gtest.h>
#include <algorithm>
#include "../util/std_util.h"


namespace PacificAtlanticWaterFlow {

    // 从沿岸逆推流域
    class Solution {
    public:
        std::vector<std::vector<int>> pacificAtlantic(std::vector<std::vector<int>>& heights) {
            std::vector<std::vector<int>> ans;
            int rows = heights.size();
            int cols = heights[0].size();
            // 为两大洋分别初始化一个矩阵，存储每个位置到某一个大洋的可达性
            std::vector<std::vector<int>> pacific(rows, std::vector<int>(cols, 0));
            std::vector<std::vector<int>> atlantic(rows, std::vector<int>(cols, 0));

            // 初始化太平洋流域可达位置队列
            std::queue<std::pair<int, int>> q1;
            for (int i = 0; i < rows; i++) {
                q1.push({ i, 0 });
            }
            for (int j = 0; j < cols; j++) {
                q1.push({ 0, j });
            }
            // 从初始位置开始，遍历所有相邻可达位置
            bfs(heights, q1, pacific);

            // 初始化大西洋流域可达位置队列
            std::queue<std::pair<int, int>> q2;
            for (int i = 0; i < rows; i++) {
                q2.push({ i, cols - 1 });
            }
            for (int j = 0; j < cols; j++) {
                q2.push({ rows - 1, j });
            }
            // 从初始位置开始，遍历所有相邻可达位置
            bfs(heights, q2, atlantic);

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (pacific[i][j] == 1 && atlantic[i][j] == 1) {
                        ans.push_back({ i, j });
                    }
                }
            }
            return ans;
        }

    private:
        // 广度优先遍历
        // 相邻位置高度只要不低于当前位置高度，认为可以到达
        void bfs(
            std::vector<std::vector<int>>& heights,
            std::queue<std::pair<int, int>>& q,
            std::vector<std::vector<int>>& riverBasin) {
            int rows = heights.size();
            int cols = heights[0].size();
            while (!q.empty()) {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();
                riverBasin[r][c] = 1;

                int v = heights[r][c];
                if (r - 1 >= 0 && heights[r - 1][c] >= v && riverBasin[r - 1][c] == 0) {
                    q.push({ r - 1, c });
                }
                if (r + 1 < rows && heights[r + 1][c] >= v && riverBasin[r + 1][c] == 0) {
                    q.push({ r + 1, c });
                }
                if (c - 1 >= 0 && heights[r][c - 1] >= v && riverBasin[r][c - 1] == 0) {
                    q.push({ r, c - 1 });
                }
                if (c + 1 < cols && heights[r][c + 1] >= v && riverBasin[r][c + 1] == 0) {
                    q.push({ r, c + 1 });
                }
            }
        }
    };

    bool testPacificAtlantic(std::initializer_list<const char*> input, std::initializer_list<const char*> expected) {
        std::vector<std::vector<int>> heights = StdUtil::generateIntVectorMatrix(input);
        std::vector<std::vector<int>> output = Solution().pacificAtlantic(heights);
        std::vector<std::vector<int>> expectedResult = StdUtil::generateIntVectorMatrix(expected);
        std::sort(output.begin(), output.end());
        std::sort(expectedResult.begin(), expectedResult.end());
        return StdUtil::compareEqualVectorMatrix(output, expectedResult);
    }
}

TEST(_417_PacificAtlanticWaterFlow, SimpleCases) {
    /*
    * Example 1:
    * Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
    * Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
    */
    EXPECT_TRUE(PacificAtlanticWaterFlow::testPacificAtlantic(
        {
            "[1,2,2,3,5]",
            "[3,2,3,4,4]",
            "[2,4,5,3,1]",
            "[6,7,1,4,5]",
            "[5,1,1,2,4]"
        }, 
        {
            "[0,4]",
            "[1,3]",
            "[1,4]",
            "[2,2]",
            "[3,0]",
            "[3,1]",
            "[4,0]"
        }));
}