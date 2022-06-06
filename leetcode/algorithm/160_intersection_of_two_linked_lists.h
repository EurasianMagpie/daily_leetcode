#pragma once

// https://leetcode.com/problems/intersection-of-two-linked-lists/
/*
* 160. Intersection of Two Linked Lists
* 
* Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect.
* If the two linked lists have no intersection at all, return null.
* 
* The test cases are generated such that there are no cycles anywhere in the entire linked structure.
* 
* Note that the linked lists must retain their original structure after the function returns.
* 
* Custom Judge:
* The inputs to the judge are given as follows (your program is not given these inputs):
*    intersectVal - The value of the node where the intersection occurs. This is 0 if there is no intersected node.
*    listA - The first linked list.
*    listB - The second linked list.
*    skipA - The number of nodes to skip ahead in listA (starting from the head) to get to the intersected node.
*    skipB - The number of nodes to skip ahead in listB (starting from the head) to get to the intersected node.

* The judge will then create the linked structure based on these inputs and pass the two heads, headA and headB
* to your program. If you correctly return the intersected node, then your solution will be accepted.
* 
* Example 1:
* A:         4 -> 1 ->
*                       8 -> 4 -> 5
* B:    5 -> 6 -> 1 ->
* Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
* Output: Intersected at '8'
* Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect).
* From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,6,1,8,4,5]. 
* There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
* 
* 
* Constraints:
*    The number of nodes of listA is in the m.
*    The number of nodes of listB is in the n.
*    1 <= m, n <= 3 * 104
*    1 <= Node.val <= 105
*    0 <= skipA < m
*    0 <= skipB < n
*    intersectVal is 0 if listA and listB do not intersect.
*    intersectVal == listA[skipA] == listB[skipB] if listA and listB intersect.
*
* Follow up: Could you write a solution that runs in O(m + n) time and use only O(1) memory?
*/

#include "../base/base.h"
#include "../util/list_util.h"
#include <gtest/gtest.h>


namespace IntersectionOfTwoLinkedLists {

    class Solution {
    public:
        ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
            std::set<ListNode*> nodesOfA;
            std::set<ListNode*> nodesOfB;
            ListNode* r(nullptr);
            ListNode* pA(headA);
            ListNode* pB(headB);
            while (pA || pB) {
                if (pA) {
                    if (nodesOfB.find(pA) != nodesOfB.end()) {
                        return pA;
                    }
                    nodesOfA.insert(pA);
                    pA = pA->next;
                }
                if (pB) {
                    if (nodesOfA.find(pB) != nodesOfA.end()) {
                        return pB;
                    }
                    nodesOfB.insert(pB);
                    pB = pB->next;
                }
            }
            return nullptr;
        }
    };

    bool testGetIntersectionNode(const char* listA, const char* listB, const char* intersectList) {
        ListNode* headA = ListUtil::generateLinkedList(listA);
        ListNode* headB = ListUtil::generateLinkedList(listB);
        ListNode* headIntersect = ListUtil::generateLinkedList(intersectList);
        ListNode* tailA(headA);
        ListNode* tailB(headB);
        while (tailA && tailA->next) {
            tailA = tailA->next;
        }
        while (tailB && tailB->next) {
            tailB = tailB->next;
        }
        if (tailA) {
            tailA->next = headIntersect;
        }
        if (tailB) {
            tailB->next = headIntersect;
        }
        ListNode* pIntersectionNode = Solution().getIntersectionNode(headA, headB);
        bool ret = pIntersectionNode == headIntersect;
        if (tailA) {
            tailA->next = nullptr;
        }
        if (tailB) {
            tailB->next = nullptr;
        }
        ListUtil::releaseLinkedList(headIntersect);
        ListUtil::releaseLinkedList(headB);
        ListUtil::releaseLinkedList(headA);
        return ret;
    }
}

TEST(_160_IntersectionOfTwoLinkedLists, SimpleCases) {
    /*
    * Example 1:
    * A:         4 -> 1 ->
    *                       8 -> 4 -> 5
    * B:    5 -> 6 -> 1 ->
    * Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
    * Output: Intersected at '8'
    */
    EXPECT_TRUE(IntersectionOfTwoLinkedLists::testGetIntersectionNode(
        "[4,1]", "[5,6,1]", "[8,4,5]"
    ));
}