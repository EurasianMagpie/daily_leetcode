#pragma once

//  https://leetcode.com/problems/minimum-number-of-refueling-stops/
/*
* 871. Minimum Number of Refueling Stops
* 
* A car travels from a starting position to a destination which is target miles east of the
* starting position.
*
* There are gas stations along the way. The gas stations are represented as an array
* stations where stations[i] = [positioni, fueli] indicates that the ith gas station
* is positioni miles east of the starting position and has fueli liters of gas.
*
* The car starts with an infinite tank of gas, which initially has startFuel liters of
* fuel in it. It uses one liter of gas per one mile that it drives. When the car
* reaches a gas station, it may stop and refuel, transferring all the gas from the
* station into the car.
*
* Return the minimum number of refueling stops the car must make in order to reach its
* destination. If it cannot reach the destination, return -1.
*
* Note that if the car reaches a gas station with 0 fuel left, the car can still refuel
* there. If the car reaches the destination with 0 fuel left, it is still considered to
* have arrived.
* 
* Example 1:
* Input: target = 1, startFuel = 1, stations = []
* Output: 0
* Explanation: We can reach the target without refueling.
*
* Example 2:
* Input: target = 100, startFuel = 1, stations = [[10,100]]
* Output: -1
* Explanation: We can not reach the target (or even the first gas station).
*
* Example 3:
* Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
* Output: 2
* Explanation: We start with 10 liters of fuel.
* We drive to position 10, expending 10 liters of fuel.  We refuel from 0 liters to 60 liters of gas.
* Then, we drive from position 10 to position 60 (expending 50 liters of fuel),
* and refuel from 10 liters to 50 liters of gas.  We then drive to and reach the target.
* We made 2 refueling stops along the way, so we return 2.
* 
* Constraints:
*    1 <= target, startFuel <= 10^9
*    0 <= stations.length <= 500
*    0 <= positioni <= positioni+1 < target
*    1 <= fueli < 10^9
*/

#include <vector>
#include <queue>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace MinimumNumberOfRefuelingStops {
    /*
    * 解法一
    * 动态规划， 复杂度 2^n，超时
    */
    class Solution1 {
    public:
        int minRefuelStops(int target, int startFuel, std::vector<std::vector<int>>& stations) {
            return solve(target, startFuel, stations, 0, 0);
        }

    private:
        int solve(int target, int startFuel, std::vector<std::vector<int>>& stations, int index, int mileStone) {
            // 是否直接能到终点
            if (startFuel >= target) {
                return 0;
            }
            // 是否还有下一个加油站
            if (index >= stations.size()) {
                // 没有加油站，又不够到终点
                return -1;
            }

            // 是否能到下一个加油站
            int toNextStation = stations[index][0] - mileStone;
            if (startFuel < toNextStation) {
                return -1;
            }

            // 进下一个加油站
            int r1 = solve(target - toNextStation, startFuel - toNextStation + stations[index][1], stations, index + 1, stations[index][0]);

            // 不进下一个加油站
            int r2 = solve(target - toNextStation, startFuel - toNextStation, stations, index + 1, stations[index][0]);

            if (r1 == -1 && r2 == -1) {
                return -1;
            }
            else if (r1 >= 0 && r2 >= 0) {
                return std::min(r1 + 1, r2);
            }
            else {
                return r1 == -1 ? r2 : r1 + 1;
            }
        }
    };

    /*
    * 解法二：
    * 从当前可获得的资源中，取最有的资源应用之后，继续迭代，使用优先级队列
    * 复杂度 n*Log(n)
    */
    class Solution {
    public:
        int minRefuelStops(int target, int startFuel, std::vector<std::vector<int>>& stations) {
            int result(0);
            std::priority_queue<int> pq;

            int currentFuel = startFuel;
            int i(0), sz(stations.size());
            while (currentFuel < target)
            {
                while (i < sz && stations[i][0] <= currentFuel)
                {
                    pq.push(stations[i][1]);
                    i++;
                }

                if (pq.empty()) {
                    return -1;
                }

                currentFuel += pq.top();
                pq.pop();
                result++;
            }
            return result;
        }
    };

    int testMinRefuelStops(int target, int startFuel, std::initializer_list<const char*> input) {
        std::vector<std::vector<int>> stations = StdUtil::generateIntVectorMatrix(input);
        return Solution().minRefuelStops(target, startFuel,stations);
    }
}

TEST(_871_MinimumNumberOfRefuelingStops, SimpleCases) {
    /*
    * Example 1:
    * Input: target = 1, startFuel = 1, stations = []
    * Output: 0
    */
    EXPECT_EQ(MinimumNumberOfRefuelingStops::testMinRefuelStops(1, 1, {}), 0);

    /*
    * Example 2:
    * Input: target = 100, startFuel = 1, stations = [[10,100]]
    * Output: -1
    */
    EXPECT_EQ(MinimumNumberOfRefuelingStops::testMinRefuelStops(100, 1, {"[10,100]"}), -1);

    /*
    * Example 3:
    * Input: target = 100, startFuel = 10, stations = [[10,60],[20,30],[30,30],[60,40]]
    * Output: 2
    */
    EXPECT_EQ(MinimumNumberOfRefuelingStops::testMinRefuelStops(
        100, 10, { "[10,60]","[20,30]","[30,30]","[60,40]"}), 2);

    /*
    * Input:  100,  25,  [[25,25],[50,25],[75,25]]
    * Output: 3
    */
    EXPECT_EQ(MinimumNumberOfRefuelingStops::testMinRefuelStops(
        100, 25, { "[25,25]","[50,25]","[75,25]" }), 3);

    /*
    * Input:  100,  50,  [[25,50],[50,25]]
    * Output: 1
    */
    EXPECT_EQ(MinimumNumberOfRefuelingStops::testMinRefuelStops(
        100, 50, { "[25,50]","[50,25]" }), 1);

    /*
    * 1000
    10
    [[7,217],[10,211],[17,146],[21,232],[25,310],[48,175],[53,23],[63,158],[71,292],[96,85],[100,302],[102,295],[116,110],[122,46],[131,20],[132,19],[141,13],[163,85],[169,263],[179,233],[191,169],[215,163],[224,231],[228,282],[256,115],[259,3],[266,245],[283,331],[299,21],[310,224],[315,188],[328,147],[345,74],[350,49],[379,79],[387,276],[391,92],[405,174],[428,307],[446,205],[448,226],[452,275],[475,325],[492,310],[496,94],[499,313],[500,315],[511,137],[515,180],[519,6],[533,206],[536,262],[553,326],[561,103],[564,115],[582,161],[593,236],[599,216],[611,141],[625,137],[626,231],[628,66],[646,197],[665,103],[668,8],[691,329],[699,246],[703,94],[724,277],[729,75],[735,23],[740,228],[761,73],[770,120],[773,82],[774,297],[780,184],[791,239],[801,85],[805,156],[837,157],[844,259],[849,2],[860,115],[874,311],[877,172],[881,109],[888,321],[894,302],[899,321],[908,76],[916,241],[924,301],[933,56],[960,29],[979,319],[983,325],[988,190],[995,299],[996,97]]
    */
}