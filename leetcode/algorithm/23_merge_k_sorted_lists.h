#pragma once

// https://leetcode.com/problems/merge-k-sorted-lists/

/*
23. Merge k Sorted Lists

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
Merge all the linked-lists into one sorted linked-list and return it.

Example 1:
Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6


Example 2:
Input: lists = []
Output: []


Example 3:
Input: lists = [[]]
Output: []


Constraints:
    k == lists.length
    0 <= k <= 104
    0 <= lists[i].length <= 500
    -104 <= lists[i][j] <= 104
    lists[i] is sorted in ascending order.
    The sum of lists[i].length will not exceed 104.
*/

#include <vector>
#include <queue>
#include <initializer_list>
#include "../base/base.h"
#include "../util/list_util.h"

#include <gtest/gtest.h>

namespace MergeKSortedLists {
    class Solution {
        struct ListNodePred : public std::greater<ListNode*>
        {
            _NODISCARD constexpr bool operator()(const ListNode* _Left, const ListNode* _Right) const {
                return _Left->val > _Right->val;
            }
        };
    public:
        ListNode* mergeKLists(std::vector<ListNode*>& lists) {
            std::priority_queue<ListNode*, std::vector<ListNode*>, ListNodePred> allValue;
            for (auto ite = lists.begin(); ite != lists.end(); ite++) {
                ListNode* p = *ite;
                while (p)
                {
                    allValue.push(p);
                    p = p->next;
                }
            }
            ListNode* ret(nullptr), *p(nullptr);
            if (!allValue.empty()) {
                ret = p = allValue.top();
                ret->next = nullptr;
                allValue.pop();
            }
            while (!allValue.empty())
            {
                p->next = allValue.top();
                p = p->next;
                p->next = nullptr;
                allValue.pop();
            }
            return ret;
        }
    };

    /*
    * expected
    * ... K¸öÁ´±íµÄÃèÊö
    */
    bool testMergeKLists(std::initializer_list<const char*> inputs, const char* expected) {
        std::vector<ListNode*> lists;
        for (const auto& input : inputs) {
            lists.push_back(ListUtil::generateLinkedList(input));
        }
        ListNode* mergedList = Solution().mergeKLists(lists);
        ListNode* expectedList = ListUtil::generateLinkedList(expected);
        bool r = ListUtil::compareEqualLinkedList(mergedList, expectedList);
        ListUtil::releaseLinkedList(expectedList);
        ListUtil::releaseLinkedList(mergedList);
        return r;
    }
}

TEST(_23_MergeKSortedLists, SimpleCases) {
    /*
    Example 1:
    Input: lists = [[1,4,5],[1,3,4],[2,6]]
    Output: [1,1,2,3,4,4,5,6]
    Explanation: The linked-lists are:
    [
      1->4->5,
      1->3->4,
      2->6
    ]
    merging them into one sorted list:
    1->1->2->3->4->4->5->6
    */
    EXPECT_TRUE(MergeKSortedLists::testMergeKLists({"[1,4,5]", "[1,3,4]", "[2,6]"}, "[1,1,2,3,4,4,5,6]"));

    /*
    Example 2:
    Input: lists = []
    Output: []
    */
    EXPECT_TRUE(MergeKSortedLists::testMergeKLists({}, "[]"));

    /*
    Example 3:
    Input: lists = [[]]
    Output: []
    */
    EXPECT_TRUE(MergeKSortedLists::testMergeKLists({""}, "[]"));
}