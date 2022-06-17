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
        // �Ѿ����������Ľڵ�ķ���״̬
        enum NodeState
        {
            EMPTY       = 0,
            CAMERA      = 1,    // �ýڵ������
            MONITORED   = 2,    // �ýڵ㱻�������
        };
    public:
        int minCameraCover(TreeNode* root) {
            int cameraCount(0);
            setupCamera(root, cameraCount, 0);
            return cameraCount;
        }

    private:
        /*
        * ����Ϊָ���ڵ㰲װ���
        * ����ֵ����װ����Ľ��
        */
        NodeState setupCamera(TreeNode* node, int& camerCount, int depth) {
            // �Ե�ǰ�����ӽڵ���ж�  �Ƿ���Ҷ�ӣ��Ƿ���Լ�����ȱ���
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

            // ������ӽڵ㣬�Ҷ���Ҷ�ӣ������Ϊ���
            if ((leftIsLeaf && rightIsLeaf) || (leftIsLeaf && !node->right) || (!node->left && rightIsLeaf)) {
                camerCount++;
                return CAMERA;
            }

            
            if (leftGoDeep && rightGoDeep) {
                // ����ͬʱ�ݹ�
                NodeState leftState = setupCamera(node->left, camerCount, depth + 1);
                NodeState rightState = setupCamera(node->right, camerCount, depth + 1);
                NodeState currentState = calcNodeState(leftState, rightState, depth);
                if (currentState == CAMERA) {
                    camerCount++;
                }
                return currentState;
            }
            else if (leftGoDeep) {
                // ֻ���������ݹ�
                NodeState leftState = setupCamera(node->left, camerCount, depth + 1);
                NodeState rightState = rightIsLeaf ? EMPTY : MONITORED;
                NodeState currentState = calcNodeState(leftState, rightState, depth);
                if (currentState == CAMERA) {
                    camerCount++;
                }
                return currentState;
            }
            else if (rightGoDeep) {
                // ֻ���Ҳ�����ݹ�
                NodeState leftState = leftIsLeaf ? EMPTY : MONITORED;
                NodeState rightState = setupCamera(node->right, camerCount, depth + 1);
                NodeState currentState = calcNodeState(leftState, rightState, depth);
                if (currentState == CAMERA) {
                    camerCount++;
                }
                return currentState;
            }
            else {
                // ��һ���ڵ�
                camerCount++;
                return CAMERA;
            }
        }

        /*
        * ���������ӽڵ�ķ���״̬���Լ���ǰ��ȣ�������ǰ�ڵ�Ӧ�ò��õ�״̬
        */
        NodeState calcNodeState(NodeState leftState, NodeState rightState, int depth) {
            // �����һ���ڵ��ǿ�״̬������������
            if (leftState == EMPTY || rightState == EMPTY) {
                return CAMERA;
            }
            // ���������һ���ڵ���������򷵻ر����
            else if (leftState == CAMERA || rightState == CAMERA) {
                return MONITORED;
            }
            // ����һ������ MONITORED
            else {
                // ������Ǹ��ڵ㣬����Է��ؿ�״̬������������
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