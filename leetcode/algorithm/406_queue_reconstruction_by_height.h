#pragma once

// https://leetcode.com/problems/queue-reconstruction-by-height/
/*
* 406. Queue Reconstruction by Height
* 
* You are given an array of people, people, which are the attributes of some people in a queue
* (not necessarily in order). Each people[i] = [hi, ki] represents the ith person of height hi
* with exactly ki other people in front who have a height greater than or equal to hi.
*
* Reconstruct and return the queue that is represented by the input array people. The returned
* queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of
* the jth person in the queue (queue[0] is the person at the front of the queue).
* 
* Example 1:
* Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
* Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
* Explanation:
*  Person 0 has height 5 with no other people taller or the same height in front.
*  Person 1 has height 7 with no other people taller or the same height in front.
*  Person 2 has height 5 with two persons taller or the same height in front, which is person 0 and 1.
*  Person 3 has height 6 with one person taller or the same height in front, which is person 1.
*  Person 4 has height 4 with four people taller or the same height in front, which are people 0, 1, 2, and 3.
*  Person 5 has height 7 with one person taller or the same height in front, which is person 1.
*  Hence [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] is the reconstructed queue.
* 
* Example 2:
* Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
* Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
* 
* Constraints:
*    1 <= people.length <= 2000
*    0 <= hi <= 10^6
*    0 <= ki < people.length
*    It is guaranteed that the queue can be reconstructed.
*/

#include <vector>
#include <list>
#include <algorithm>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace QueueReconstructionByHeight {
    // 参考这个解
    // https://leetcode.com/problems/queue-reconstruction-by-height/discuss/2211641/Visual-Explanation-or-JAVA-Greedy
    // 基本逻辑：
    // 1. 对于h相同的两个人，按k排序，k越小越靠前；
    // 2. 对于h不同的两个人，按h排序，h越大越靠前；
    // 3. 做总体排序时，按h从高到底进行插入，这么做的原因是：插入h更低的人到前面，不会影响高h的k值逻辑
    class Solution {
    public:
        std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>>& people) {
            std::sort(people.begin(), people.end(), [](std::vector<int>& lhs, std::vector<int>& rhs) {
                if (lhs[0] == rhs[0]) {
                    return lhs[1] < rhs[1];
                }
                else {
                    return lhs[0] > rhs[0];
                }
                });
            std::list<std::vector<int>> list;
            for (auto p : people) {
                auto pos = list.begin();
                int n = 0;
                while (n < p[1]) {
                    pos++;
                    n++;
                }
                list.insert(pos, p);
            }
            return std::vector<std::vector<int>>(list.begin(), list.end());
        }
    };

    bool testReconstructQueue(
        std::initializer_list<const char*> input, std::initializer_list<const char*> expected) {
        std::vector<std::vector<int>> people = StdUtil::generateIntVectorMatrix(input);
        std::vector<std::vector<int>> output = Solution().reconstructQueue(people);
        std::vector<std::vector<int>> expectedMatrix = StdUtil::generateIntVectorMatrix(expected);
        return StdUtil::compareEqualVectorMatrix(output, expectedMatrix);
    }
}

TEST(_406_QueueReconstructionByHeight, SimpleCases) {
    /*
    * Example 1:
    * Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
    * Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
    */
    EXPECT_TRUE(QueueReconstructionByHeight::testReconstructQueue(
        { "[7,0]","[4,4]","[7,1]","[5,0]","[6,1]","[5,2]" },
        { "[5,0]","[7,0]","[5,2]","[6,1]","[4,4]","[7,1]" }
    ));

    /*
    * Example 2:
    * Input: people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
    * Output: [[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
    */
    EXPECT_TRUE(QueueReconstructionByHeight::testReconstructQueue(
        { "[6,0]","[5,0]","[4,0]","[3,2]","[2,2]","[1,4]" },
        { "[4,0]","[5,0]","[2,2]","[3,2]","[1,4]","[6,0]" }
    ));
}