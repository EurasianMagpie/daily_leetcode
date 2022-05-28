#pragma once

// https://leetcode.com/problems/swap-nodes-in-pairs/
/*
24. Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head. 
You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

Example 1:
Input: head = [1,2,3,4]
Output: [2,1,4,3]

Example 2:
Input: head = []
Output: []

Example 3:
Input: head = [1]
Output: [1]

Constraints:

The number of nodes in the list is in the range [0, 100].
0 <= Node.val <= 100
*/


#include "../base/base.h"
#include "../util/list_util.h"

#include <gtest/gtest.h>

namespace SwapNodesInPairs {
    class Solution {
    public:

        /*
        * pre_p2(null?) -> p1 -> p2 -> next_p1
        */
        ListNode* swapPairs(ListNode* head) {
            ListNode* p1(head), * pre_p2(nullptr), * ret(nullptr);
            while (p1)
            {
                ListNode* p2 = p1->next;
                if (p2) {
                    ListNode* next_p1 = p2->next;
                    if (pre_p2) {
                        pre_p2->next = p2;
                    }
                    pre_p2 = p1;
                    p1->next = p2->next;
                    p2->next = p1;

                    if (!ret) {
                        ret = p2;
                    }
                    p1 = next_p1;
                }
                else {
                    break;
                }
            }
            return ret ? ret : head;
        }

    };

    bool testSwapPairs(const char* input, const char* expected) {
        ListNode* pIn = ListUtil::generateLinkedList(input);
        ListNode* pExpected = ListUtil::generateLinkedList(expected);
        ListNode* pOut = Solution().swapPairs(pIn);
        bool r = ListUtil::compareEqualLinkedList(pOut, pExpected);
        ListUtil::releaseLinkedList(pExpected);
        ListUtil::releaseLinkedList(pIn);
        return r;
    }
}

TEST(_24_SwapNodesInPairs, SimpleCases) {
    /*
    Example 1:
    Input: head = [1,2,3,4]
    Output: [2,1,4,3]
    */
    EXPECT_TRUE(SwapNodesInPairs::testSwapPairs("[1,2,3,4]", "[2,1,4,3]"));

    /*
    Example 2:
    Input: head = []
    Output: []
    */
    EXPECT_TRUE(SwapNodesInPairs::testSwapPairs("[]", "[]"));

    /*
    Example 3:
    Input: head = [1]
    Output: [1]
    */
    EXPECT_TRUE(SwapNodesInPairs::testSwapPairs("[1]", "[1]"));
}

