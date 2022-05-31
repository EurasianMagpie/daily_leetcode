#pragma once

// https://leetcode.com/problems/number-of-steps-to-reduce-a-number-to-zero/
/*
* 1342. Number of Steps to Reduce a Number to Zero
* 
* Given an integer num, return the number of steps to reduce it to zero.
*
* In one step, if the current number is even, you have to divide it by 2, 
* otherwise, you have to subtract 1 from it.
* 
* Example 1:
* Input: num = 14
* Output: 6
* Explanation: 
* Step 1) 14 is even; divide by 2 and obtain 7. 
* Step 2) 7 is odd; subtract 1 and obtain 6.
* Step 3) 6 is even; divide by 2 and obtain 3. 
* Step 4) 3 is odd; subtract 1 and obtain 2. 
* Step 5) 2 is even; divide by 2 and obtain 1. 
* Step 6) 1 is odd; subtract 1 and obtain 0.
*
* Example 2:
* Input: num = 8
* Output: 4
* Explanation: 
* Step 1) 8 is even; divide by 2 and obtain 4. 
* Step 2) 4 is even; divide by 2 and obtain 2. 
* Step 3) 2 is even; divide by 2 and obtain 1. 
* Step 4) 1 is odd; subtract 1 and obtain 0.
*
* Example 3:
* Input: num = 123
* Output: 12
*
*
* Constraints:
*  0 <= num <= 10^6
*/

namespace NumberOfStepsToReduceANumberToZero {
    class Solution {
    public:
        int numberOfSteps(int num) {
            int64_t n = num;
            bool valueBegin = false;
            int ret(0);
            for (int i = 31; i >= 0; i--) {
                if ((1 << i) & n) {
                    ret += 2;
                    valueBegin = true;
                }
                else {
                    if (valueBegin) {
                        ret++;
                    }
                }
            }
            if (valueBegin) {
                ret--;
            }
            return ret;
        }
    };

    int testNumberOfSteps(int num) {
        return Solution().numberOfSteps(num);
    }
}

TEST(_1342_NumberOfStepsToReduceANumberToZero, SimpleCases) {
    /*
    * Example 1:
    * Input: num = 14
    * Output: 6
    */
    EXPECT_EQ(6, NumberOfStepsToReduceANumberToZero::testNumberOfSteps(14));

    /*
    * Example 2:
    * Input: num = 8
    * Output: 4
    */
    EXPECT_EQ(4, NumberOfStepsToReduceANumberToZero::testNumberOfSteps(8));

    /*
    * Example 3:
    * Input: num = 123
    * Output: 12
    */
    EXPECT_EQ(12, NumberOfStepsToReduceANumberToZero::testNumberOfSteps(123));

    EXPECT_EQ(0, NumberOfStepsToReduceANumberToZero::testNumberOfSteps(0));
}