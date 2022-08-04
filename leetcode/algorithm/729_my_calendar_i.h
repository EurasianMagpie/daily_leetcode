#pragma once

//  https://leetcode.com/problems/my-calendar-i/
/*
* 729. My Calendar I
* 
* You are implementing a program to use as your calendar. We can add a new event if adding the event
* will not cause a double booking.
*
* A double booking happens when two events have some non-empty intersection (i.e., some moment is common
* to both events.).
*
* The event can be represented as a pair of integers start and end that represents a booking on the
* half-open interval [start, end), the range of real numbers x such that start <= x < end.
*
* Implement the MyCalendar class:
*  - MyCalendar() Initializes the calendar object.
*  - boolean book(int start, int end) Returns true if the event can be added to the calendar successfully
*    without causing a double booking. Otherwise, return false and do not add the event to the calendar.
*
* Example 1:
* Input:
* ["MyCalendar", "book", "book", "book"]
* [[], [10, 20], [15, 25], [20, 30]]
* Output:
* [null, true, false, true]
*
* Explanation
* MyCalendar myCalendar = new MyCalendar();
* myCalendar.book(10, 20); // return True
* myCalendar.book(15, 25); // return False, It can not be booked because time 15 is already booked by another event.
* myCalendar.book(20, 30); // return True, The event can be booked, as the first event takes every time less than 20, but not including 20.
* 
* Constraints:
*  - 0 <= start < end <= 109
*  - At most 1000 calls will be made to book.
*/

#include <list>
#include <iostream>
#include "../util/std_util.h"
#include <gtest/gtest.h>

namespace MyCalendarI {
    struct CalenderBook {
        int start;
        int end;

        CalenderBook(int s, int e) : start(s), end(e) {}
    };

    class MyCalendar {
        std::list<CalenderBook> mBooks;
    public:
        MyCalendar() {

        }

        bool book(int start, int end) {
            auto pos = mBooks.begin();
            for (auto ite = mBooks.begin(); ite != mBooks.end(); ite++) {
                const CalenderBook book = *ite;
                // 开始时间在当前日程的开始时间之前
                if (start < book.start) {
                    // 结束时间在当前日程开始时间之前
                    // 可以插入，插入位置在当前日程之前
                    if (end <= book.start) {
                        pos = ite;
                        break;
                    }
                    else {
                        // 结束时间有重叠，非法
                        return false;
                    }
                }
                // 开始时间在当前日程开始时间之后
                else {
                    // 开始时间在当前日程结束时间之后，则继续向后查找
                    if (start >= book.end) {
                        pos = ite;
                        pos++;
                    }
                    else {
                        // 开始时间与当前日程有重叠，非法
                        return false;
                    }
                }

            }
            mBooks.insert(pos, CalenderBook(start, end));
            return true;
        }
    };

    /**
     * Your MyCalendar object will be instantiated and called as such:
     * MyCalendar* obj = new MyCalendar();
     * bool param_1 = obj->book(start,end);
     */

    bool testMyCalendar(std::initializer_list<const char*> input, const char* expected) {
        auto bookInput = StdUtil::generateIntVectorMatrix(input);
        std::vector<bool> output;
        MyCalendarI::MyCalendar myCalendar;
        for (auto ite = bookInput.begin(); ite != bookInput.end(); ite++) {
            auto i = *ite;
            output.push_back(myCalendar.book(i.at(0), i.at(1)));
        }
        auto expectedVector = StdUtil::generateBoolVector(expected);
        return StdUtil::compareEqualVector(output, expectedVector);
    }
}

TEST(_729_MyCalendarI, SimpleCases) {
    /*
    * Input:
    * ["MyCalendar","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book","book"]
    * [[],[20,29],[13,22],[44,50],[1,7],[2,10],[14,20],[19,25],[36,42],[45,50],[47,50],[39,45],[44,50],[16,25],[45,50],[45,50],[12,20],[21,29],[11,20],[12,17],[34,40],[10,18],[38,44],[23,32],[38,44],[15,20],[27,33],[34,42],[44,50],[35,40],[24,31]]
    */
    EXPECT_TRUE(MyCalendarI::testMyCalendar(
        {
            "[20,29]",
            "[13,22]",
            "[44,50]",
            "[1,7]",
            "[2,10]",
            "[14,20]",
            "[19,25]",
            "[36,42]",
            "[45,50]",
            "[47,50]",
            "[39,45]",
            "[44,50]",
            "[16,25]",
            "[45,50]",
            "[45,50]",
            "[12,20]",
            "[21,29]",
            "[11,20]",
            "[12,17]",
            "[34,40]",
            "[10,18]",
            "[38,44]",
            "[23,32]",
            "[38,44]",
            "[15,20]",
            "[27,33]",
            "[34,42]",
            "[44,50]",
            "[35,40]",
            "[24,31]"
        },
        "[true,false,true,true,false,true,false,true,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false]")
    );
}