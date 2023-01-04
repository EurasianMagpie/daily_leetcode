#pragma once

/**
* 938. Range Sum of BST
* https://leetcode.com/problems/range-sum-of-bst/
* 
* Given the root node of a binary search tree and two integers low and high, return the sum
* of values of all nodes with a value in the inclusive range [low, high].
* 
* Example 1:
* Input: root = [10,5,15,3,7,null,18], low = 7, high = 15
* Output: 32
* Explanation: Nodes 7, 10, and 15 are in the range [7, 15]. 7 + 10 + 15 = 32.
* 
* Example 2:
* Input: root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
* Output: 23
* Explanation: Nodes 6, 7, and 10 are in the range [6, 10]. 6 + 7 + 10 = 23.
* 
* Constraints:
* The number of nodes in the tree is in the range [1, 2 * 10^4].
* 1 <= Node.val <= 10^5
* 1 <= low <= high <= 10^5
* All Node.val are unique.
*/

#include "../base/base.h"
#include <functional>
#include "../util/binary_tree_util.h"
#include <gtest/gtest.h>

namespace RangeSumOfBST {
    class Solution {
    public:
        int rangeSumBST(TreeNode* root, int low, int high) {
            int ans(0);
            bool keepWorking(true);
            std::function<void(int)> sumFunc = [=, &ans, &keepWorking](int val) {
                if (val >= low && val <= high) {
                    ans += val;
                }
                else if (val > high) {
                    keepWorking = false;
                }
            };
            if (root) {
                midTraverse(root, sumFunc, keepWorking);
            }
            return ans;
        }

    private:
        void midTraverse(TreeNode* node,
            std::function<void(int)>& sumFunc,
            bool& keepWorking) {
            if (node->left && keepWorking) {
                midTraverse(node->left, sumFunc, keepWorking);
            }
            sumFunc(node->val);
            if (node->right && keepWorking) {
                midTraverse(node->right, sumFunc, keepWorking);
            }
        }
    };

    int testRangeSumBST(const char* input, int low, int high) {
        TreeNode* root = BinaryTreeUtil::generateBinaryTree(input);
        int ret = Solution().rangeSumBST(root, low, high);
        BinaryTreeUtil::releaseBinaryTree(root);
        return ret;
    }
}

TEST(_938_RangeSumOfBST, SimpleCases) {
    {
        EXPECT_EQ(RangeSumOfBST::testRangeSumBST("[10,5,15,3,7,null,18]", 7, 15), 32);
    }

    std::vector<int> a{ 1,2,3,4,5 };
}
