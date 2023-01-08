#pragma once

//  https://leetcode.com/problems/max-points-on-a-line/description/
/**
* 149. Max Points on a Line
* 
* Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane,
* return the maximum number of points that lie on the same straight line.
* 
* Example 1:
* Input: points = [[1,1],[2,2],[3,3]]
* Output: 3
* 
* Example 2:
* Input: points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
* Output: 4
* 
* Constraints:
*    1 <= points.length <= 300
*    points[i].length == 2
*    -104 <= xi, yi <= 104
*    All the points are unique.
*/

#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace MaxPointsOnALine {
    class Solution {
    public:
        int maxPoints(std::vector<std::vector<int>>& points) {
            int ans(1);
            for (int i = 0; i < points.size() - 1; i++) {
                std::unordered_map<double, int> mp;
                for (int j = i + 1; j < points.size(); j++) {
                    if (points[j][0] == points[i][0]) {
                        mp[100000.0]++;
                    }
                    else {
                        double k = double(points[j][1] - points[i][1]) / double(points[j][0] - points[i][0]);
                        mp[k]++;
                    }
                }
                int x = 1;
                for (auto e : mp) {
                    x = std::max(x, e.second + 1);
                }
                ans = std::max(x, ans);
            }
            return ans;
        }
    };

    int testMaxPoints(std::initializer_list<const char*> input) {
        auto points = StdUtil::generateIntVectorMatrix(input);
        return Solution().maxPoints(points);
    }
}

TEST(_149_MaxPointsOnALine, SimpleCases) {
    EXPECT_EQ(MaxPointsOnALine::testMaxPoints({ "1,1","2,2","3,3" }), 3);

    EXPECT_EQ(MaxPointsOnALine::testMaxPoints({ "1,1","3,2","5,3","4,1","2,3","1,4" }), 4);

    EXPECT_EQ(MaxPointsOnALine::testMaxPoints({ "0,0","4,5","7,8","8,9","5,6","3,4","1,1" }), 5);
}