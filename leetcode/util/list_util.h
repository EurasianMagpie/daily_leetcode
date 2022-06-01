#pragma once

#include "../base/base.h"
#include "input_util.h"

class ListUtil {


public:
	/*
	  根据输入构造一个单链表
	  @input 链表描述数组的字符串描述
	  返回可能为空
	*/
	static ListNode* generateLinkedList(const char* input) {
		auto inputs = InputUtil::parseCommonInputString(input);
		ListNode* pList = nullptr;
		for (auto ite = inputs.rbegin(); ite != inputs.rend(); ite++) {
			pList = createLinkedListNode(std::atoi(ite->c_str()), pList);
		}
		return pList;
	}

	/*
	  销毁由 generateLinkedList 构造的一棵二叉树
	*/
	static void releaseLinkedList(ListNode* root) {
		ListNode* next = root;
		while (next)
		{
			ListNode* node = next;
			next = next->next;
			releaseLinkedListNode(node);
		}
	}

	/*
	* 比较两个链表是否相同
	* 长度相等 && 每个节点的值相等
	*/
	static bool compareEqualLinkedList(ListNode* lhs, ListNode* rhs) {
		while (true)
		{
			if (rhs == nullptr && lhs == nullptr) {
				return true;
			}
			else if (rhs != nullptr && lhs != nullptr) {
				if (rhs->val == lhs->val) {
					rhs = rhs->next;
					lhs = lhs->next;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
	}

private:
	static ListNode* createLinkedListNode(int val, ListNode* next) {
		return new ListNode(val, next);
	}

	static void releaseLinkedListNode(ListNode* node) {
		if (node) {
			delete node;
		}
	}
};