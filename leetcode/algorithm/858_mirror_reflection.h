#pragma once

//  https://leetcode.com/problems/mirror-reflection/
/*
* 858. Mirror Reflection
* 
* There is a special square room with mirrors on each of the four walls. Except for the southwest corner,
* there are receptors on each of the remaining corners, numbered 0, 1, and 2.
*
* The square room has walls of length p and a laser ray from the southwest corner first meets the east
* wall at a distance q from the 0th receptor.
*
* Given the two integers p and q, return the number of the receptor that the ray meets first.
*
* The test cases are guaranteed so that the ray will meet a receptor eventually.
* 
* Example 1:
* Input: p = 2, q = 1
* Output: 2
* Explanation: The ray meets receptor 2 the first time it gets reflected back to the left wall.
* 
* Example 2:
* Input: p = 3, q = 1
* Output: 1
*
* Constraints:
*  1 <= q <= p <= 1000
*/

#include <gtest/gtest.h>

namespace MirrorReflection {
    class Solution {
        // ����˼·
        // https://leetcode.com/problems/mirror-reflection/discuss/2376191/C%2B%2B-Java-Python-or-Faster-then-100-or-Full-explanations-or
    public:
        int mirrorReflection(int p, int q) {
            while (p > 0 && !(p & 1) && q > 0 && !(q & 1)) {
                p = p >> 1;
                q = q >> 1;
            }
            // ���ڵ� q �� m, ���ڵ� p �� n
            if (q & 1) {
                return p & 1 ? 1 : 2;
            }
            else {
                return 0;
            }
        }
    };
}