#pragma once

// https://leetcode.com/problems/print-zero-even-odd/

/**
* 1116. Print Zero Even Odd
* 
* You have a function printNumber that can be called with an integer parameter and prints it to the console.
*
* For example, calling printNumber(7) prints 7 to the console.
* You are given an instance of the class ZeroEvenOdd that has three functions: zero, even, and odd. The same instance of ZeroEvenOdd will be passed to three different threads:
*
* Thread A: calls zero() that should only output 0's.
* Thread B: calls even() that should only output even numbers.
* Thread C: calls odd() that should only output odd numbers.
* Modify the given class to output the series "010203040506..." where the length of the series must be 2n.
*
* Implement the ZeroEvenOdd class:
* ZeroEvenOdd(int n) Initializes the object with the number n that represents the numbers that should be printed.
* void zero(printNumber) Calls printNumber to output one zero.
* void even(printNumber) Calls printNumber to output one even number.
* void odd(printNumber) Calls printNumber to output one odd number.
*/

#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

namespace PrintZeroEvenOdd {
    class ZeroEvenOdd {
    private:
        int n;
        int mNext;
        bool mNextZero;
        bool mStop;
        std::mutex mMutex;
        std::condition_variable mCond;

    public:
        ZeroEvenOdd(int n) {
            this->n = n;
            this->mNext = 0;
            this->mNextZero = true;
            this->mStop = false;
        }

        // printNumber(x) outputs "x", where x is an integer.
        void zero(std::function<void(int)> printNumber) {
            bool r = false;
            do {
                //std::cout << "zero - loop begin" << std::endl;
                r = loopNext([&]() -> bool {
                    return mStop || mNextZero;
                    },
                    [&]() {
                        //std::cout << "zero - print 0" << std::endl;
                        printNumber(0);
                    },
                        [&]() {
                        mNextZero = false;
                        ++mNext;
                        mCond.notify_all();
                    },
                    "zero");
            } while (r);
           // std::cout << "zero - loop quit" << std::endl;
        }

        void even(std::function<void(int)> printNumber) {
            bool r = false;
            do {
                //std::cout << "even - loop begin" << std::endl;
                r = loopNext([&]() -> bool {
                    return mStop || (!mNextZero && !(mNext & 1));
                    },
                    [&]() {
                        //std::cout << "even - print " << mNext << std::endl;
                        printNumber(mNext);
                    },
                        [&]() {
                        if (mNext == n) {
                            //std::cout << "even - stop" << std::endl;
                            mStop = true;
                        }
                        mNextZero = true;
                        mCond.notify_all();
                    }, 
                    "even");
            } while (r);
            //std::cout << "even - loop quit" << std::endl;
        }

        void odd(std::function<void(int)> printNumber) {
            bool r = false;
            do {
                //std::cout << "odd - loop begin" << std::endl;
                r = loopNext([&]() -> bool {
                    return mStop || (!mNextZero && mNext & 1);
                    },
                    [&]() {
                        //std::cout << "odd - print " << mNext << std::endl;
                        printNumber(mNext);
                    },
                        [&]() {
                        if (mNext == n) {
                            //std::cout << "odd - stop" << std::endl;
                            mStop = true;
                        }
                        mNextZero = true;
                        mCond.notify_all();
                    },
                    "odd");
            } while (r);
            //std::cout << "odd - loop quit" << std::endl;
        }

        bool loopNext(
            std::function<bool(void)> canPrint,
            std::function<void(void)> print,
            std::function<void(void)> fireNext,
            std::string who) {
            std::unique_lock<std::mutex> lk(mMutex);
            mCond.wait(lk, canPrint);
            if (mStop) {
                //std::cout << who <<  " - loopNext r:false" << std::endl;
                return false;
            }
            else {
                print();
                fireNext();
                //std::cout << who << " - loopNext r:true" << std::endl;
                return true;
            }
        }
    };
}

TEST(_1116_PrintZeroEvenOdd, SimpleCases) {
    using namespace PrintZeroEvenOdd;
    {
        std::ostringstream oss;
        int n = 5;
        ZeroEvenOdd obj(n);
        auto fnPrint = [&](int n) { oss << n; };
        std::thread t1{ &ZeroEvenOdd::zero, &obj, fnPrint };
        std::thread t2{ &ZeroEvenOdd::even, &obj, fnPrint };
        std::thread t3{ &ZeroEvenOdd::odd, &obj, fnPrint };
        t1.join();
        t2.join();
        t3.join();
        std::string sExpected;
        for (int i = 1; i <= n; i++) {
            char sz[8] = {};
            sprintf(sz, "%d", i);
            sExpected.append("0").append(sz);
        }
        EXPECT_EQ(oss.str(), sExpected);
    }
}