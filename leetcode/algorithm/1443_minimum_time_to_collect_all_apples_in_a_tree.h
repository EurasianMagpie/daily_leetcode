#pragma once
//  https://leetcode.com/problems/minimum-time-to-collect-all-apples-in-a-tree/
/**
* 1443. Minimum Time to Collect All Apples in a Tree
* 
* Given an undirected tree consisting of n vertices numbered from 0 to n-1, which
* has some apples in their vertices. You spend 1 second to walk over one edge of 
* the tree. Return the minimum time in seconds you have to spend to collect all
* apples in the tree, starting at vertex 0 and coming back to this vertex.
*
* The edges of the undirected tree are given in the array edges, where edges[i] = [ai, bi]
* means that exists an edge connecting the vertices ai and bi. Additionally, there
* is a boolean array hasApple, where hasApple[i] = true means that vertex i has an apple;
* otherwise, it does not have any apple.
* 
* Constraints:
*    1 <= n <= 105
*    edges.length == n - 1
*    edges[i].length == 2
*    0 <= ai < bi <= n - 1
*    fromi < toi
*    hasApple.length == n
*/

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace MinimumTimeToCollectAllApplesInATree {
    class Solution {
    public:
        int minTime(int n, std::vector<std::vector<int>>& edges, std::vector<bool>& hasApple) {
            // 与当前节点相邻的节点
            std::unordered_map<int, std::set<int>> nodeTo;
            for (const auto& e : edges) {
                nodeTo[e[0]].insert(e[1]);
                nodeTo[e[1]].insert(e[0]);
            }

            std::set<int> appleNodeSet{ 0 };
            std::set<int> usedNodeSet;
            // 从节点 0 开始深度遍历，找到通往苹果路径上所有节点
            dfs(0, nodeTo, hasApple, usedNodeSet, appleNodeSet);
            return (appleNodeSet.size() - 1) * 2;
        }

        bool dfs(
            int v,
            std::unordered_map<int, std::set<int>>& nodeTo,
            std::vector<bool>& hasApple,
            std::set<int>& usedNodeSet,
            std::set<int>& appleNodeSet) {
            usedNodeSet.insert(v);
            bool r = hasApple[v];
            std::set<int>& adjNodes = nodeTo[v];
            for (int e : adjNodes) {
                if (usedNodeSet.find(e) == usedNodeSet.end()) {
                    r |= dfs(e, nodeTo, hasApple, usedNodeSet, appleNodeSet);
                }
            }
            if (r) {
                appleNodeSet.insert(v);
            }
            return r;
        }
    };

    int testMinTime(int n, std::initializer_list<const char*> edgesInput, const char* hasAppleInput) {
        return Solution().minTime(
            n,
            StdUtil::generateIntVectorMatrix(edgesInput),
            StdUtil::generateBoolVector(hasAppleInput));
    }
}

TEST(_1443_MinimumTimeToCollectAllApplesInATree, SimpleCases) {
    using namespace MinimumTimeToCollectAllApplesInATree;

    EXPECT_EQ(testMinTime(7, { "0,1","0,2","1,4","1,5","2,3","2,6" }, "[false,false,true,false,true,true,false]"), 8);
    EXPECT_EQ(testMinTime(7, { "0,1","0,2","1,4","1,5","2,3","2,6" }, "[false,false,true,false,false,true,false]"), 6);
    EXPECT_EQ(testMinTime(7, { "0,1","0,2","1,4","1,5","2,3","2,6" }, "[false,false,false,false,false,false,false]"), 0);

    EXPECT_EQ(testMinTime(4, { "0,2","0,3","1,2" }, "[false,true,false,false]"), 4);
}