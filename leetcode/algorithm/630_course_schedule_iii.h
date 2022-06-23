#pragma once

// https://leetcode.com/problems/course-schedule-iii/
/*
* 630. Course Schedule III
* 
* There are n different online courses numbered from 1 to n. You are given an array courses where
* courses[i] = [durationi, lastDayi] indicate that the ith course should be taken continuously for
* durationi days and must be finished before or on lastDayi.
*
* You will start on the 1st day and you cannot take two or more courses simultaneously.
*
* Return the maximum number of courses that you can take.
*
*
* Example 1:
* Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
* Output: 3
* Explanation: 
*  - There are totally 4 courses, but you can take 3 courses at most:
*    First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready
*    to take the next course on the 101st day.
*  - Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and
*    ready to take the next course on the 1101st day. 
*  - Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
*  - The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds
*    the closed date.
*
* Example 2:
* Input: courses = [[1,2]]
* Output: 1
*
* Example 3:
* Input: courses = [[3,2],[4,3]]
* Output: 0
*
*
* Constraints:
*    1 <= courses.length <= 10^4
*    1 <= durationi, lastDayi <= 10^4
*/

#include <vector>
#include <queue>
#include <algorithm>
#include <gtest/gtest.h>
#include "../util/std_util.h"


namespace CourseScheduleIII {

    class Solution {
    public:
        int scheduleCourse(std::vector<std::vector<int>>& courses) {
            if (courses.size() == 0) {
                return 0;
            }
            // 按截至时间排序，最大的截至时间是最后的终点
            std::sort(courses.begin(), courses.end(), [](std::vector<int>& lhs, std::vector<int>& rhs) {
                return lhs.at(1) < rhs.at(1);
            });

            // 优先级队列，大根堆
            std::priority_queue<int> scheduledCourses;
            int lastDay(0);
            for (auto c : courses) {
                lastDay += c.at(0);
                scheduledCourses.push(c.at(0));
                if (lastDay > c.at(1)) {
                    // 如果添加一个课程导致超过了截至日期，则从已经添加的课程中去掉一个最大的
                    // 因为在添加当前课程之前是不超期的，因此删除一个最大的一定可以保证不超期
                    lastDay -= scheduledCourses.top();
                    scheduledCourses.pop();
                }
            }
            return scheduledCourses.size();
        }
    };

    int testScheduleCourse(std::initializer_list<const char*> input) {
        std::vector<std::vector<int>> courses = StdUtil::generateIntVectorMatrix(input);
        return Solution().scheduleCourse(courses);
    }
}


TEST(_630_CourseScheduleIII, SimpleCases) {
    /*
    * Example 1:
    * Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
    * Output: 3
    */
    EXPECT_EQ(CourseScheduleIII::testScheduleCourse(
        {"[100,200]", "[200,1300]", "[1000,1250]", "[2000,3200]"}),
        3);

    /*
    * Example 2:
    * Input: courses = [[1,2]]
    * Output: 1
    */
    EXPECT_EQ(CourseScheduleIII::testScheduleCourse(
        { "[1,2]" }),
        1);

    /*
    * Example 3:
    * Input: courses = [[3,2],[4,3]]
    * Output: 0
    */
    EXPECT_EQ(CourseScheduleIII::testScheduleCourse(
        { "[3,2]", "[4,3]" }),
        0);
}