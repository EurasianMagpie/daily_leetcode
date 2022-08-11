#pragma once

//  https://leetcode.com/problems/validate-binary-search-tree/
/*
* 98. Validate Binary Search Tree
* 
* Given the root of a binary tree, determine if it is a valid binary search tree (BST).
*
* A valid BST is defined as follows:
*    The left subtree of a node contains only nodes with keys less than the node's key.
*    The right subtree of a node contains only nodes with keys greater than the node's key.
*    Both the left and right subtrees must also be binary search trees.
* 
* Example 1:
* Input: root = [2,1,3]
* Output: true
* 
* Example 2:
* Input: root = [5,1,4,null,null,3,6]
* Output: false
* Explanation: The root node's value is 5 but its right child's value is 4.
* 
* Constraints:
*    The number of nodes in the tree is in the range [1, 104].
*    -2^31 <= Node.val <= 2^31 - 1
*/

#include <vector>
#include "../base/base.h"
#include <gtest/gtest.h>
#include "../util/binary_tree_util.h"

namespace ValidateBinarySearchTree {
    class Solution {
    public:
        bool isValidBST(TreeNode* root) {
            int lastVal(0);
            bool isFirstNode(true);
            return traverse(root, lastVal, isFirstNode);
        }

        bool traverse(TreeNode* node, int& lastVal, bool& isFirstNode) {
            if (node->left) {
                if (!traverse(node->left, lastVal, isFirstNode)) {
                    return false;
                }
            }
            if (isFirstNode) {
                lastVal = node->val;
                isFirstNode = false;
            }
            else {
                if (node->val > lastVal) {
                    lastVal = node->val;
                }
                else {
                    return false;
                }
            }
            if (node->right) {
                if (!traverse(node->right, lastVal, isFirstNode)) {
                    return false;
                }
            }
            return true;
        }
    };

    bool testIsValidBST(const char* input) {
        TreeNode* root = BinaryTreeUtil::generateBinaryTree(input);
        bool r = Solution().isValidBST(root);
        BinaryTreeUtil::releaseBinaryTree(root);
        return r;
    }
}


TEST(_98_ValidateBinarySearchTree, SimpleCases) {
    /*
    * Example 1:
    * Input: root = [2,1,3]
    * Output: true
    */
    EXPECT_EQ(ValidateBinarySearchTree::testIsValidBST("[2,1,3]"), true);

    /*
    * Example 2:
    * Input: root = [5,1,4,null,null,3,6]
    * Output: false
    */
    EXPECT_EQ(ValidateBinarySearchTree::testIsValidBST("[5,1,4,null,null,3,6]"), false);

    /*
    * Input:[5,4,6,null,null,3,7]
    * Output:false
    */
    EXPECT_EQ(ValidateBinarySearchTree::testIsValidBST("[5,4,6,null,null,3,7]"), false);
}
