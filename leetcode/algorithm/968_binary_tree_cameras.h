#pragma once

// https://leetcode.com/problems/binary-tree-cameras/
/*
* 968. Binary Tree Cameras
* 
* You are given the root of a binary tree. We install cameras on the tree nodes where each camera at a node
* can monitor its parent, itself, and its immediate children.
*
* Return the minimum number of cameras needed to monitor all nodes of the tree.
* 
* Example 1:
* Input: root = [0,0,null,0,0]
* Output: 1
* Explanation: One camera is enough to monitor all nodes if placed as shown.
* 
* Example 2:
* Input: root = [0,0,null,0,null,0,null,null,0]
* Output: 2
* Explanation: At least two cameras are needed to monitor all nodes of the tree. The above image shows one of
* the valid configurations of camera placement.
* 
* 
* Constraints:
*    The number of nodes in the tree is in the range [1, 1000].
*    Node.val == 0
* 
*/

#include "../base/base.h"
#include "../util/binary_tree_util.h"
#include <gtest/gtest.h>

namespace BinaryTreeCameras {
    /**
     * Definition for a binary tree node.
     * struct TreeNode {
     *     int val;
     *     TreeNode *left;
     *     TreeNode *right;
     *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
     * };
     */
    class Solution {
        // 已经被遍历过的节点的返回状态
        enum NodeState
        {
            EMPTY       = 0,
            CAMERA      = 1,    // 该节点是相机
            MONITORED   = 2,    // 该节点被相机监视
        };
    public:
        int minCameraCover(TreeNode* root) {
            int cameraCount(0);
            setupCamera(root, cameraCount, 0);
            return cameraCount;
        }

    private:
        /*
        * 尝试为指定节点安装相机
        * 返回值，安装相机的结果
        */
        NodeState setupCamera(TreeNode* node, int& camerCount, int depth) {
            // 对当前左右子节点的判断  是否是叶子，是否可以继续深度遍历
            bool leftIsLeaf = false;
            bool leftGoDeep = false;
            if (node->left) {
                if (!node->left->left && !node->left->right) {
                    leftIsLeaf = true;
                }
                else {
                    leftGoDeep = true;
                }
            }
            bool rightIsLeaf = false;
            bool rightGoDeep = false;
            if (node->right) {
                if (!node->right->left && !node->right->right) {
                    rightIsLeaf = true;
                }
                else {
                    rightGoDeep = true;
                }
            }

            // 如果有子节点，且都是叶子，则可作为相机
            if ((leftIsLeaf && rightIsLeaf) || (leftIsLeaf && !node->right) || (!node->left && rightIsLeaf)) {
                camerCount++;
                return CAMERA;
            }

            
            if (leftGoDeep && rightGoDeep) {
                // 两侧同时递归
                NodeState leftState = setupCamera(node->left, camerCount, depth + 1);
                NodeState rightState = setupCamera(node->right, camerCount, depth + 1);
                NodeState currentState = calcNodeState(leftState, rightState, depth);
                if (currentState == CAMERA) {
                    camerCount++;
                }
                return currentState;
            }
            else if (leftGoDeep) {
                // 只在左侧继续递归
                NodeState leftState = setupCamera(node->left, camerCount, depth + 1);
                NodeState rightState = rightIsLeaf ? EMPTY : MONITORED;
                NodeState currentState = calcNodeState(leftState, rightState, depth);
                if (currentState == CAMERA) {
                    camerCount++;
                }
                return currentState;
            }
            else if (rightGoDeep) {
                // 只在右侧继续递归
                NodeState leftState = leftIsLeaf ? EMPTY : MONITORED;
                NodeState rightState = setupCamera(node->right, camerCount, depth + 1);
                NodeState currentState = calcNodeState(leftState, rightState, depth);
                if (currentState == CAMERA) {
                    camerCount++;
                }
                return currentState;
            }
            else {
                // 单一根节点
                camerCount++;
                return CAMERA;
            }
        }

        /*
        * 根据左右子节点的返回状态，以及当前深度，决定当前节点应该采用的状态
        */
        NodeState calcNodeState(NodeState leftState, NodeState rightState, int depth) {
            // 如果有一个节点是空状态，则必须是相机
            if (leftState == EMPTY || rightState == EMPTY) {
                return CAMERA;
            }
            // 否则，如果有一个节点是相机，则返回被监控
            else if (leftState == CAMERA || rightState == CAMERA) {
                return MONITORED;
            }
            // 否则，一定都是 MONITORED
            else {
                // 如果不是根节点，则可以返回空状态，否则就是相机
                return depth > 0 ? EMPTY : CAMERA;
            }
        }
    };

    int testMinCameraCover(const char* inputTree) {
        TreeNode* root = BinaryTreeUtil::generateBinaryTree(inputTree);
        int r = Solution().minCameraCover(root);
        BinaryTreeUtil::releaseBinaryTree(root);
        return r;
    }
}

TEST(_968_BinaryTreeCameras, SimpleCases) {

    EXPECT_EQ(BinaryTreeCameras::testMinCameraCover("[0,0,0,null,null,null,0]"), 2);
    EXPECT_EQ(BinaryTreeCameras::testMinCameraCover("[0]"), 1);

    /*
    * Input: root = [0,0,null,0,0]
    * Output: 1
    */
    EXPECT_EQ(BinaryTreeCameras::testMinCameraCover("[0,0,null,0,0]"), 1);

    /*
    * Input: root = [0,0,null,0,null,0,null,null,0]
    * Output: 2
    */
    EXPECT_EQ(BinaryTreeCameras::testMinCameraCover("[0,0,null,0,null,0,null,null,0]"), 2);

    EXPECT_EQ(BinaryTreeCameras::testMinCameraCover(
        "[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]"),
        5);
}