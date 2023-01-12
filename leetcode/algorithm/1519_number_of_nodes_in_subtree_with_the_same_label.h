#pragma once

// https://leetcode.com/problems/number-of-nodes-in-the-sub-tree-with-the-same-label/description/
/*
* 1519. Number of Nodes in the Sub-Tree With the Same Label
* 
* You are given a tree (i.e. a connected, undirected graph that has no cycles) consisting of n nodes
* numbered from 0 to n - 1 and exactly n - 1 edges. The root of the tree is the node 0, and each node
* of the tree has a label which is a lower-case character given in the string labels (i.e. The node
* with the number i has the label labels[i]).
*
* The edges array is given on the form edges[i] = [ai, bi], which means there is an edge between
* nodes ai and bi in the tree.
*
* Return an array of size n where ans[i] is the number of nodes in the subtree of the ith node which
* have the same label as node i.
*
* A subtree of a tree T is the tree consisting of a node in T and all of its descendant nodes.
*/

#include <vector>
#include <set>
#include <unordered_map>
#include <gtest/gtest.h>


namespace NumberOfNodesInTheSubTreeWithTheSameLabel {
    class Solution {
    public:
        std::vector<int> countSubTrees(int n, std::vector<std::vector<int>>& edges, std::string labels) {
            // 讲所有边存储为 节点-相邻节点 的映射
            std::vector<std::vector<int>> adj(n);
            for (const std::vector<int>& e : edges) {
                adj[e[0]].push_back(e[1]);
                adj[e[1]].push_back(e[0]);
            }
            std::vector<int> ans(n, 0);
            // 从节点 0 开始，深度遍历
            dfs(0, ans, labels, adj);
            return ans;
        }

        // 返回当前子树中所有字符出现的次数
        std::vector<int> dfs(int v, std::vector<int>& ans, std::string& labels, std::vector<std::vector<int>>& adj) {
            ans[v] = 1;
            std::vector<int> cCount(26, 0);
            cCount[labels[v] - 'a'] = 1;

            // 深度遍历相邻节点
            auto adjNodes = adj[v];
            for (auto e : adjNodes) {
                if (ans[e] == 0) {
                    std::vector<int> r = dfs(e, ans, labels, adj);
                    for (int i = 0; i < cCount.size(); i++) {
                        cCount[i] += r[i];
                    }
                }
            }
            ans[v] = cCount[labels[v] - 'a'];
            return cCount;
        }
    };

    bool testCountSubTrees(
        int n,
        std::initializer_list<const char*> edgesInput,
        const char* labelsInput,
        const char* expectedDesc) {
        std::vector<int> output = Solution().countSubTrees(
            n, StdUtil::generateIntVectorMatrix(edgesInput), std::string(labelsInput));
        std::vector<int> expected = StdUtil::generateIntVector(expectedDesc);
        return StdUtil::compareEqualVector(output, expected);
    }
}

TEST(_1519_NumberOfNodesInTheSubTreeWithTheSameLabel, SimpleCases) {
    using namespace NumberOfNodesInTheSubTreeWithTheSameLabel;
    EXPECT_TRUE(testCountSubTrees(7, { "0,1","0,2","1,4","1,5","2,3","2,6" }, "abaedcd", "[2,1,1,1,1,1,1]"));
    EXPECT_TRUE(testCountSubTrees(4, { "0,1","1,2","0,3" }, "bbbb", "[4,2,1,1]"));
    EXPECT_TRUE(testCountSubTrees(5, { "0,1","0,2","1,3","0,4" }, "aabab", "[3,2,1,1,1]"));
}