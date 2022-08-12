#pragma once

//  https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
/*
* 235. Lowest Common Ancestor of a Binary Search Tree
* 
* Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two
* given nodes in the BST.
*
* According to the definition of LCA on Wikipedia: “The lowest common ancestor is
* defined between two nodes p and q as the lowest node in T that has both p and q as
* descendants (where we allow a node to be a descendant of itself).”
*
* Example 1:
* Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
* Output: 6
* Explanation: The LCA of nodes 2 and 8 is 6.
*
* Example 2:
* Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
* Output: 2
* Explanation: The LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according to the LCA definition.
*
* Example 3:
* Input: root = [2,1], p = 2, q = 1
* Output: 2
*
* Constraints:
* The number of nodes in the tree is in the range [2, 105].
*    -10^9 <= Node.val <= 10^9
*    All Node.val are unique.
*    p != q
*    p and q will exist in the BST.
*/

#include "../base/base.h"
#include <vector>
#include <gtest/gtest.h>
#include "../util/binary_tree_util.h"

namespace LowestCommonAncestorOfABinarySearchTree {
    class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            std::vector<TreeNode*> seq1;
            std::vector<TreeNode*> seq2;
            searchNodeSeq(root, p, seq1);
            searchNodeSeq(root, q, seq2);

            TreeNode* ans(root);
            int pos = std::min(seq1.size(), seq2.size());
            for (int i = pos - 1; i >= 0; i--) {
                if (seq1[i] == seq2[i]) {
                    ans = seq1[i];
                    break;
                }
            }
            return ans;
        }

        bool searchNodeSeq(TreeNode* root, TreeNode* node, std::vector<TreeNode*>& seq) {
            seq.push_back(root);
            // 这里判断 root == node 即可，为了本地构造测试用例方便改用val相等判断，这样符合题目约束条件的 val 唯一
            if (root->val == node->val) {
                return true;
            }
            if (root->left) {
                if (searchNodeSeq(root->left, node, seq)) {
                    return true;
                }
            }
            if (root->right) {
                if (searchNodeSeq(root->right, node, seq)) {
                    return true;
                }
            }
            seq.pop_back();
            return false;
        }
    };

    int testLowestCommonAncestor(const char* tree, const char* p, const char* q) {
        TreeNode* root = BinaryTreeUtil::generateBinaryTree(tree);
        // 严格意义上，p和q都应该是root所指向的已经存在node，这里是为了构造用例方便
        TreeNode* _p = BinaryTreeUtil::generateBinaryTree(p);
        TreeNode* _q = BinaryTreeUtil::generateBinaryTree(q);
        TreeNode* ans = Solution().lowestCommonAncestor(root, _p, _q);
        int r = ans->val;
        BinaryTreeUtil::releaseBinaryTree(_q);
        BinaryTreeUtil::releaseBinaryTree(_p);
        BinaryTreeUtil::releaseBinaryTree(root);
        return r;
    }
}

TEST(_235_LowestCommonAncestorOfABinarySearchTree, SimpleCases) {
    /*
    * Example 1:
    * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
    * Output: 6
    */
    EXPECT_EQ(LowestCommonAncestorOfABinarySearchTree::testLowestCommonAncestor(
        "[6,2,8,0,4,7,9,null,null,3,5]", "2", "8"), 6);

    /*
    * Example 2:
    * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
    * Output: 2
    */
    EXPECT_EQ(LowestCommonAncestorOfABinarySearchTree::testLowestCommonAncestor(
        "[6,2,8,0,4,7,9,null,null,3,5]", "2", "4"), 2);

    /*
    * Example 3:
    * Input: root = [2,1], p = 2, q = 1
    * Output: 2
    */
    EXPECT_EQ(LowestCommonAncestorOfABinarySearchTree::testLowestCommonAncestor(
        "[2,1]", "2", "1"), 2);

    /*
    * Example 3:
    * Input: root = [6,2,8,0,4,7,9,null,null,3,5], p = 3, q = 5
    * Output: 4
    */
    EXPECT_EQ(LowestCommonAncestorOfABinarySearchTree::testLowestCommonAncestor(
        "[6,2,8,0,4,7,9,null,null,3,5]", "3", "5"), 4);
}

