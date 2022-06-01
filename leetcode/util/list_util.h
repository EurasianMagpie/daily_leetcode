#pragma once

#include "../base/base.h"
#include "input_util.h"

class ListUtil {


public:
	/*
	  �������빹��һ��������
	  @input ��������������ַ�������
	  ���ؿ���Ϊ��
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
	  ������ generateLinkedList �����һ�ö�����
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
	* �Ƚ����������Ƿ���ͬ
	* ������� && ÿ���ڵ��ֵ���
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