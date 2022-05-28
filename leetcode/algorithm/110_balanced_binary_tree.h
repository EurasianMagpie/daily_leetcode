#pragma once

// https://leetcode.com/problems/balanced-binary-tree/

/**
	Given a binary tree, determine if it is height - balanced.

	For this problem, a height - balanced binary tree is defined as :

	a binary tree in which the left and right subtrees of every node differ in height by no more than 1.
*/

#include <list>
#include <math.h>
#include <gtest/gtest.h>
#include "../base/base.h"
#include "../util/binary_tree_util.h"


namespace BalancedBinaryTree {

    struct TreeNodeWithHeight {
        TreeNode* node;
        int height;

        TreeNodeWithHeight(TreeNode* n, int h) : node(n), height(h) {}
    };

    class Solution {
    public:
        bool isBalanced(TreeNode* root) {
            return checkBalanced(root) >= 0;
        }

        /*
          检查子树是否平衡，并返回子树高度
          return : >= 0 子树平衡，返回值是子树高度
                   <0   子树不平衡
        */
        int checkBalanced(TreeNode* root) {
            if (!root) {
                return 0;
            }
            int leftResult = checkBalanced(root->left);
            if (leftResult < 0) {
                return leftResult;
            }
            int rightResult = checkBalanced(root->right);
            if (rightResult < 0) {
                return rightResult;
            }

            int delta = abs(leftResult - rightResult);
            if (delta > 1) {
                return 0 - delta;
            }
            int r = leftResult > rightResult ? leftResult : rightResult;
            return r + 1;
        }
    };

    bool isBalanced(const char* input) {
        TreeNode* pRoot = BinaryTreeUtil::generateBinaryTree(input);
        bool r = Solution().isBalanced(pRoot);
        BinaryTreeUtil::releaseBinaryTree(pRoot);
        return r;
    }
}

TEST(_110_BalancedBinaryTree, SimpleCases) {
    //  Input: root = [3,9,20,null,null,15,7]
    //  Expected: true
    EXPECT_EQ(true, BalancedBinaryTree::isBalanced("[3,9,20,null,null,15,7]"));

    //  Input: root = [1,2,2,3,3,null,null,4,4]
    //  Expected: false
    EXPECT_EQ(false, BalancedBinaryTree::isBalanced("[1,2,2,3,3,null,null,4,4]"));

    //  Input: root = []
    //  Expected: true
    EXPECT_EQ(true, BalancedBinaryTree::isBalanced("[]"));

    //		                1
    //              2		        3
    //          4	    5	    6	    null
    //      8
    //  Input: [1,2,3,4,5,6,null,8]
    //  Expected: true
    EXPECT_EQ(true, BalancedBinaryTree::isBalanced("[1,2,3,4,5,6,null,8]"));
}