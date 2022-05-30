#pragma once

// https://leetcode.com/problems/divide-two-integers/
/*
* 29. Divide Two Integers
*
* Given two integers dividend and divisor, divide two integers without using multiplication,
* division, and mod operator.
*
* The integer division should truncate toward zero, which means losing its fractional part.
* For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
*
* Return the quotient after dividing dividend by divisor.
*
* Note: Assume we are dealing with an environment that could only store integers within
* the 32-bit signed integer range: [−2^31, 2^31 − 1]. For this problem, if the quotient is
* strictly greater than 2^31 - 1, then return 2^31 - 1, and if the quotient is strictly less
* than -2^31, then return -2^31.
*
* Example 1:
* Input: dividend = 10, divisor = 3
* Output: 3
* Explanation: 10/3 = 3.33333.. which is truncated to 3.
*
* Example 2:
* Input: dividend = 7, divisor = -3
* Output: -2
* Explanation: 7/-3 = -2.33333.. which is truncated to -2.
*
* Constraints:
*  -2^31 <= dividend, divisor <= 2^31 - 1
*  divisor != 0
*/
#include <math.h>
#include <gtest/gtest.h>


namespace DivideTwoIntegers {
    const int MAX_RANGE = 0x7fffffff;
    const int MIN_RANGE = 0x80000000;

    class Solution {
    public:
        // 在计算阶段使用无符号数，计算完结果之后根据结果的符号判断边界值
        int divide(int dividend, int divisor) {
            uint64_t a = (uint64_t)std::abs((int64_t)dividend);
            uint64_t b = (uint64_t)std::abs((int64_t)divisor);
            uint64_t quotient = 0;   // 商

            for (int i = 63; i >= 0; i--) {
                if ((a >> i) >= b) {
                    quotient += (1 << i);
                    a -= (b << i);
                }
            }

            if ((dividend ^ divisor) < 0) {
                if (quotient >= int64_t(0x80000000)) {
                    return 0x80000000;
                }
                else {
                    quotient = ~quotient + 1;
                }
            }
            else {
                if (quotient > 0x7fffffff) {
                    return 0x7fffffff;
                }
            }

            return (int32_t) quotient;
        }

        // 这是一个错误的解,在计算阶段使用了有符号数，符号位会起到干扰作用
        // 上面的解，在计算阶段使用无符号数，计算完结果之后根据符号判断边界值
        int divide2(int dividend, int divisor) {
            if (divisor == 1) {
                return dividend;
            }
            if (dividend == 0x80000000) {
                dividend = 0x80000001;
            }
            int64_t a = std::abs((int64_t)dividend);
            int64_t b = std::abs((int64_t)divisor);
            int64_t quotient = 0;   // 商

            for (int i = 31; i >= 0; i--) {
                if ((a >> i) >= b) {
                    quotient += (1 << i);
                    a -= (b << i);
                }
            }

            if ((dividend ^ divisor) < 0) {
                quotient = ~quotient + 1;
            }
            
            return (int32_t)quotient;
        }
    };

    int testDivide(int dividend, int divisor) {
        return Solution().divide(dividend, divisor);
    }
}

TEST(_29_DivideTwoIntegers, SimpleCases) {
    /*
    * Example 1:
    * Input: dividend = 10, divisor = 3
    * Output: 3
    * Explanation: 10/3 = 3.33333.. which is truncated to 3.
    */
    EXPECT_EQ(3, DivideTwoIntegers::testDivide(10, 3));

    /*
    * Example 2:
    * Input: dividend = 7, divisor = -3
    * Output: -2
    * Explanation: 7/-3 = -2.33333.. which is truncated to -2.
    */
    EXPECT_EQ(-2, DivideTwoIntegers::testDivide(7, -3));

    EXPECT_EQ(0x7fffffff, DivideTwoIntegers::testDivide(0x7fffffff, 1));
    EXPECT_EQ(0xffffffff, DivideTwoIntegers::testDivide(0xffffffff, 1));
    EXPECT_EQ(0x80000000, DivideTwoIntegers::testDivide(0x80000000, 1));
    
    /*
    * Wrong Answer
    * Input:    -2147483648 / -1
    * Expected: 2147483647
    */
    EXPECT_EQ(2147483647, DivideTwoIntegers::testDivide(-2147483648, -1));

    /*
    * Wrong Answer
    * Input:    -2147483648 / 1
    * Expected: -2147483648
    */
    EXPECT_EQ(-2147483648, DivideTwoIntegers::testDivide(-2147483648, 1));
    
    /*
    * Wrong Answer
    * Input:    -2147483648 / 2
    * Expected: -1073741824
    */
    EXPECT_EQ(-1073741824, DivideTwoIntegers::testDivide(-2147483648, 2));
}