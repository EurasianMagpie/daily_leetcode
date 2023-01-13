#pragma once

// https://leetcode.com/problems/longest-path-with-different-adjacent-characters/
/*
* 2246. Longest Path With Different Adjacent Characters
* You are given a tree (i.e. a connected, undirected graph that has no cycles) rooted
* at node 0 consisting of n nodes numbered from 0 to n - 1. The tree is represented
* by a 0-indexed array parent of size n, where parent[i] is the parent of node i.
* Since node 0 is the root, parent[0] == -1.
*
* You are also given a string s of length n, where s[i] is the character assigned to node i.
*
* Return the length of the longest path in the tree such that no pair of adjacent
* nodes on the path have the same character assigned to them.
*
* Constraints:
*    n == parent.length == s.length
*    1 <= n <= 105
*    0 <= parent[i] <= n - 1 for all i >= 1
*    parent[0] == -1
*    parent represents a valid tree.
*    s consists of only lowercase English letters.
*/

#include <vector>
#include <list>
#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace LongestPathWithDifferentAdjacentCharacters {

    class Solution {
    public:
        // 求解的是无向无环图内的最长路径
        // 问题可以转化为：
        //    以每个节点为顶点的每个子树中寻找最长的两条到叶子的最长路径
        //    再把最长的两个子树路径长度拼起来，得到以当前节点为顶点的最长路径
        //    对每个节点计算能得到的最长路径长度，其中最大值就是解
        int longestPath(std::vector<int>& parent, std::string s) {
            // 把节点的父节点关系转换成节点的字节列表的关系
            std::vector<std::vector<int>> child(parent.size());
            for (int i = 1; i < parent.size(); i++) {
                child[parent[i]].push_back(i);
            }

            int ans(0);
            dfs(0, child, s, ans);
            return ans;
        }

    private:
        // 深度遍历: 
        //   对于每个节点，计算出最长的两个子树路径长度，并得到以当前节点为顶点的最长路径
        //   更新整体解
        //   返回以当前节点为根的子树中单条最长路径长度
        int dfs(int n, std::vector<std::vector<int>>& child, std::string& s, int& ans) {
            // 没有子节点
            if (child[n].empty()) {
                ans = std::max(ans, 1);
                return 1;
            }

            // 有子节点，计算子路径中最大的两个
            int len1(0), len2(0);
            for (int e : child[n]) {
                int r = dfs(e, child, s, ans);
                if (s[e] == s[n]) {
                    continue;
                }
                if (r > len1) {
                    len2 = len1;
                    len1 = r;
                }
                else {
                    len2 = std::max(r, len2);
                }
            }
            ans = std::max(ans, len1 + len2 + 1);
            return len1 + 1;
        }
    };

    int testLongestPath(const char* parent, const char* s) {
        return Solution().longestPath(StdUtil::generateIntVector(parent), s);
    }
}

TEST(_2246_LongestPathWithDifferentAdjacentCharacters, SimpleCases) {
    using namespace LongestPathWithDifferentAdjacentCharacters;

    EXPECT_EQ(testLongestPath("[-1,0,0,1,1,2]", "abacbe"), 3);
    EXPECT_EQ(testLongestPath("[-1,0,0,0]", "aabc"), 3);

    EXPECT_EQ(testLongestPath("[-1,0]", "mm"), 1);
    EXPECT_EQ(testLongestPath("[-1,0]", "mx"), 2);

    EXPECT_EQ(testLongestPath("[-1,0,1]", "aab"), 2);
    EXPECT_EQ(testLongestPath("-1,0,0,2,2,3,4,5,6", "abcdefghi"), 7);

    EXPECT_EQ(testLongestPath("[-1,0,0,2,3,2,4]", "aaaxaax"), 4);

    EXPECT_EQ(testLongestPath(
        "[-1,137,65,60,73,138,81,17,45,163,145,99,29,162,19,20,132,132,13,60,21,18,155,65,13,163,125,102,96,60,50,101,100,86,162,42,162,94,21,56,45,56,13,23,101,76,57,89,4,161,16,139,29,60,44,127,19,68,71,55,13,36,148,129,75,41,107,91,52,42,93,85,125,89,132,13,141,21,152,21,79,160,130,103,46,65,71,33,129,0,19,148,65,125,41,38,104,115,130,164,138,108,65,31,13,60,29,116,26,58,118,10,138,14,28,91,60,47,2,149,99,28,154,71,96,60,106,79,129,83,42,102,34,41,55,31,154,26,34,127,42,133,113,125,113,13,54,132,13,56,13,42,102,135,130,75,25,80,159,39,29,41,89,85,19]",
        "ajunvefrdrpgxltugqqrwisyfwwtldxjgaxsbbkhvuqeoigqssefoyngykgtthpzvsxgxrqedntvsjcpdnupvqtroxmbpsdwoswxfarnixkvcimzgvrevxnxtkkovwxcjmtgqrrsqyshxbfxptuvqrytctujnzzydhpal"),
        17);
}
