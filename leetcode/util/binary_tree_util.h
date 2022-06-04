#pragma once

#include <regex>
#include <iostream>
#include <list>
#include "../base/base.h"
#include "input_util.h"


class BinaryTreeUtil {

private:
    enum BinaryTreeNodeValueType
    {
        TYPE_INT = 0,
        TYPE_NULL = 1,
    };

    struct BinaryTreeNodeValue
    {
        BinaryTreeNodeValueType type;
        int value;

        BinaryTreeNodeValue(BinaryTreeNodeValueType t, int v) : type(t), value(v) {}
    };

public:
    /*
      根据输入构造一棵二叉树
      @input 二叉树数组的字符串描述
      返回可能为空
    */
    static TreeNode* generateBinaryTree(const char* input) {
        std::vector<BinaryTreeNodeValue> nodes = parseBinaryTreeString(input);
        if (nodes.size() == 0) {
            return nullptr;
        }
        std::size_t sz = nodes.size();
        std::vector<TreeNode*> treeNodes(sz);
        for (int i = sz - 1; i >= 0; i--)
        {
            TreeNode* treeNode = createBinaryTreeNode(nodes.at(i));
            treeNodes[i] = treeNode;
            if (!treeNode) {
                continue;
            }

            int leftIndex = 2 * (i + 1) - 1;
            if (leftIndex < sz) {
                treeNode->left = treeNodes.at(leftIndex);
            }
            else {
                continue;
            }

            int rightIndex = 2 * (i + 1);
            if (rightIndex < sz) {
                treeNode->right = treeNodes.at(rightIndex);
            }
        }
        return treeNodes.at(0);
    }

    /*
      销毁由 generateBinaryTree 构造的一棵二叉树
    */
    static void releaseBinaryTree(TreeNode* root) {
        if (!root) {
            return;
        }
        std::list<TreeNode*> nodes;
        nodes.push_back(root);
        while (!nodes.empty()) {
            TreeNode* curNode = nodes.front();
            nodes.pop_front();
            if (curNode->left) {
                nodes.push_back(curNode->left);
            }
            if (curNode->right) {
                nodes.push_back(curNode->right);
            }
            releaseBinaryTreeNode(curNode);
        }
    }

private:
    /*
      根据字符串输入，解析节点值数组
      输入格式如 [1,2,3,4,5,6,null,8]
    */
    static std::vector<BinaryTreeNodeValue> parseBinaryTreeString(const char* input) {
        std::vector<BinaryTreeNodeValue> values;
        auto inputs = InputUtil::parseCommonInputString(input);
        for (auto ite = inputs.begin(); ite != inputs.end(); ite++) {
            values.push_back(createNodeValue(*ite));
        }
        return values;
    }

    static BinaryTreeNodeValue createNodeValue(std::string& value) {
        if (value.length() == 0 || value.compare("null") == 0) {
            return BinaryTreeNodeValue(TYPE_NULL, 0);
        }
        else {
            int v = std::atoi(value.c_str());
            return BinaryTreeNodeValue(TYPE_INT, v);
        }
    }

    static TreeNode* createBinaryTreeNode(const BinaryTreeNodeValue& nodeValue) {
        if (nodeValue.type == TYPE_INT) {
            return new TreeNode(nodeValue.value);
        }
        else {
            return nullptr;
        }
    }

    static void releaseBinaryTreeNode(TreeNode* node) {
        if (node) {
            delete node;
        }
    }
};