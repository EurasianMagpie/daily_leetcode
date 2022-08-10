#pragma once

//  https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/
/*
* 108. Convert Sorted Array to Binary Search Tree
* 
* Given an integer array nums where the elements are sorted in ascending order,
* convert it to a height-balanced binary search tree.
*
* A height-balanced binary tree is a binary tree in which the depth of the two subtrees
* of every node never differs by more than one.
* 
* Example 1:
* Input: nums = [-10,-3,0,5,9]
* Output: [0,-3,9,-10,null,5]
* Explanation: [0,-10,5,null,-3,null,9] is also accepted:
*
* Example 2:
* Input: nums = [1,3]
* Output: [3,1]
* Explanation: [1,null,3] and [3,1] are both height-balanced BSTs.
*
* Constraints:
*    1 <= nums.length <= 104
*    -104 <= nums[i] <= 104
*    nums is sorted in a strictly increasing order.
*/

#include <vector>
#include "../base/base.h"
#include <gtest/gtest.h>
#include "../util/std_util.h"
#include "../util/binary_tree_util.h"

namespace ConvertSortedArrayToBinarySearchTree {

    class Solution {
    public:
        TreeNode* sortedArrayToBST(std::vector<int>& nums) {
            return createBST(nums, 0, nums.size() - 1);
        }

        TreeNode* createBST(std::vector<int>& nums, int begin, int end) {
            TreeNode* node(nullptr);
            int pos = (begin + end) >> 1;
            node = new TreeNode(nums.at(pos));
            if (begin < pos) {
                node->left = createBST(nums, begin, pos - 1);
            }
            if (end > pos) {
                node->right = createBST(nums, pos + 1, end);
            }
            return node;
        }
    };

    bool testSortedArrayToBST(const char* input, const char* expected) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        TreeNode* output = Solution().sortedArrayToBST(nums);
        TreeNode* expectedTree = BinaryTreeUtil::generateBinaryTree(expected);
        bool r = BinaryTreeUtil::compareEqualBinaryTree(output, expectedTree);
        BinaryTreeUtil::releaseBinaryTree(expectedTree);
        BinaryTreeUtil::releaseBinaryTree(output);  // !!!
        return r;
    }
}

TEST(_108_ConvertSortedArrayToBinarySearchTree, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [-10,-3,0,5,9]
    * Output: [0,-3,9,-10,null,5]
    */
    EXPECT_TRUE(ConvertSortedArrayToBinarySearchTree::testSortedArrayToBST(
        "[-10,-3,0,5,9]", "[0,-10,5,null,-3,null,9]"));
}