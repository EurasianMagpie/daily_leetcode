#pragma once

// https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
/*
* 1658. Minimum Operations to Reduce X to Zero
* 
* You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost
* or the rightmost element from the array nums and subtract its value from x. Note that this modifies the
* array for future operations.
*
* Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.
* 
* Example 1:
* Input: nums = [1,1,4,2,3], x = 5
* Output: 2
* Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
*
* Example 2:
* Input: nums = [5,6,7,8,9], x = 4
* Output: -1
*
* Example 3:
* Input: nums = [3,2,20,1,1,3], x = 10
* Output: 5
* Explanation: The optimal solution is to remove the last three elements and the first two elements (5 operations in total) to reduce x to zero.
*
*
* Constraints:
*    1 <= nums.length <= 10^5
*    1 <= nums[i] <= 10^4
*    1 <= x <= 10^9
*/

#include <vector>
#include <map>
#include <gtest/gtest.h>
#include "../util/std_util.h"


namespace MinimumOperationsToReduceXToZero {

    class Solution {
    public:
        int minOperations(std::vector<int>& nums, int x) {
            int r = -1;

            // 左右两侧，累加后小于等于x的选项
            //   key -累加后的值 value - 在nums中的索引值
            std::map<int, int> lhsChoice;
            std::map<int, int> rhsChoice;

            // 分别计算左右两侧的选项累计值
            std::size_t sz = nums.size();
            bool needCalcLeft(true), needCalcRight(true);
            int suml(0), sumr(0);
            for (std::size_t i = 0; i < sz; i++) {
                if (needCalcLeft) {
                    suml += nums.at(i);
                    if (suml < x) {
                        lhsChoice[suml] = i;
                    }
                    else if (suml == x) {
                        lhsChoice[suml] = i;
                        needCalcLeft = false;
                        if (r > 0) {
                            if (i + 1 < r) {
                                r = i + 1;
                            }
                        }
                        else {
                            r = i + 1;
                        }
                    }
                    else {
                        needCalcLeft = false;
                    }
                }

                if (needCalcRight) {
                    std::size_t rIdx = sz - 1 - i;
                    sumr += nums.at(rIdx);
                    if (sumr < x) {
                        rhsChoice[sumr] = rIdx;
                    }
                    else if (sumr == x) {
                        rhsChoice[sumr] = rIdx;
                        needCalcRight = false;
                        if (r > 0) {
                            if (i + 1 < r) {
                                r = i + 1;
                            }
                        }
                        else {
                            r = i + 1;
                        }
                    }
                    else {
                        needCalcRight = false;
                    }
                }

                if (!needCalcLeft && !needCalcRight) {
                    break;
                }
            }

            // 是否有两侧组合的更优解
            for (auto ite = lhsChoice.begin(); ite != lhsChoice.end(); ite++) {
                int v = x - ite->first;
                auto findInRight = rhsChoice.find(v);
                // 如果右侧有对应值，且两侧索引没有重叠，则可用
                if (findInRight != rhsChoice.end()
                    && ite->second < findInRight->second) {
                    int thisResult = ite->second + 1 + sz - findInRight->second;
                    if (r > 0) {
                        if (thisResult < r) {
                            r = thisResult;
                        }
                    }
                    else {
                        r = thisResult;
                    }
                }
            }

            return r;
        }
    };


    /*
    * 这种解法复杂度过高
    * Time Limit Exceeded
    */
    class Solution2 {
    public:
        int minOperations(std::vector<int>& nums, int x) {
            if (nums.size() == 0) {
                return -1;
            }
            return tryOpertate(nums, x, 0, nums.size() - 1);
        }

    private:
        /*
        * 对于int数组，在给定区间[leftIndex, rightIndex]内，计算如何以更少的步骤减少x到0
        * 返回当前区间内所需最小步数
        */
        int tryOpertate(std::vector<int>& nums, int x, int leftIndex, int rightIndex) {
            // 左右指针相遇
            if (leftIndex == rightIndex) {
                return nums.at(leftIndex) == x ? 1 : -1;
            }

            // 试试移动左指针的结果
            int leftResult;
            int leftValue = nums.at(leftIndex);
            if (leftValue == x) {
                return 1;
            }
            else if (leftValue < x) {
                leftResult = tryOpertate(nums, x - leftValue, leftIndex + 1, rightIndex) + 1;
            }
            else {
                leftResult = -1;
            }

            // 试试移动右指针的结果
            int rightResult;
            int rightValue = nums.at(rightIndex);
            if (nums.at(rightIndex) == x) {
                return 1;
            }
            else if (rightValue < x) {
                rightResult = tryOpertate(nums, x - rightValue, leftIndex, rightIndex - 1) + 1;
            }
            else {
                rightResult = -1;
            }

            if (leftResult > 0 && rightResult > 0) {
                return std::min(leftResult, rightResult);
            }
            else if (leftResult > 0) {
                return leftResult;
            }
            else if (rightResult > 0) {
                return rightResult;
            }
            return -1;
        }
    };

    int testMinOperations(const char* nums, int x) {
        std::vector<int> numsVector = StdUtil::generateIntVector(nums);
        return Solution().minOperations(numsVector, x);
    }
}

TEST(_1658_MinimumOperationsToReduceXToZero, SimpleCases) {
    /*
    * Example 1:
    * Input: nums = [1,1,4,2,3], x = 5
    * Output: 2
    */
    EXPECT_EQ(MinimumOperationsToReduceXToZero::testMinOperations("[1,1,4,2,3]", 5), 2);

    /*
    * Example 2:
    * Input: nums = [5,6,7,8,9], x = 4
    * Output: -1
    */
    EXPECT_EQ(MinimumOperationsToReduceXToZero::testMinOperations("[5,6,7,8,9]", 4), -1);

    /*
    * Example 3:
    * Input: nums = [3,2,20,1,1,3], x = 10
    * Output: 5
    */
    EXPECT_EQ(MinimumOperationsToReduceXToZero::testMinOperations("[3,2,20,1,1,3]", 10), 5);

    /*
    * Time Limit Exceeded
    * Input: [1241,8769,9151,3211,2314,8007,3713,5835,2176,8227,5251,9229,904,1899,5513,7878,8663,3804,2685,3501,1204,9742,2578,8849,1120,4687,5902,9929,6769,8171,5150,1343,9619,3973,3273,6427,47,8701,2741,7402,1412,2223,8152,805,6726,9128,2794,7137,6725,4279,7200,5582,9583,7443,6573,7221,1423,4859,2608,3772,7437,2581,975,3893,9172,3,3113,2978,9300,6029,4958,229,4630,653,1421,5512,5392,7287,8643,4495,2640,8047,7268,3878,6010,8070,7560,8931,76,6502,5952,4871,5986,4935,3015,8263,7497,8153,384,1136]
             894887480
    */
    EXPECT_EQ(MinimumOperationsToReduceXToZero::testMinOperations(
        "[1241,8769,9151,3211,2314,8007,3713,5835,2176,8227,5251,9229,904,1899,5513,7878,8663,3804,2685,3501,1204,9742,2578,8849,1120,4687,5902,9929,6769,8171,5150,1343,9619,3973,3273,6427,47,8701,2741,7402,1412,2223,8152,805,6726,9128,2794,7137,6725,4279,7200,5582,9583,7443,6573,7221,1423,4859,2608,3772,7437,2581,975,3893,9172,3,3113,2978,9300,6029,4958,229,4630,653,1421,5512,5392,7287,8643,4495,2640,8047,7268,3878,6010,8070,7560,8931,76,6502,5952,4871,5986,4935,3015,8263,7497,8153,384,1136]",
        894887480),
        -1);
}
