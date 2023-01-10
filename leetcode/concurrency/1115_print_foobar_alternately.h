#ifndef _____TEST_PRINT_ALTERNATELY_HEADER_____
#define _____TEST_PRINT_ALTERNATELY_HEADER_____

// https://leetcode.com/problems/print-foobar-alternately/
/**
* 1115. Print FooBar Alternately
* 
* The same instance of FooBar will be passed to two different threads:
*    thread A will call foo(), while
*    thread B will call bar().
* Modify the given program to output "foobar" n times.
*/

#include <thread>
#include <mutex>
#include <iostream>
#include <functional>
#include <gtest/gtest.h>

namespace TestPrintFooBarAlternately {

    // todo ÓÐ¸ÅÂÊËÀËø
class FooBar {
private:
    int n;
    std::mutex mMutex;
    std::condition_variable mCond;
    std::atomic_bool mFooFlag;

public:
    FooBar(int n) : mFooFlag(true) {
        this->n = n;
    }

    void foo(std::function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            {
                std::unique_lock<std::mutex> lock(mMutex);
                mCond.wait(lock, [&] { return mFooFlag.load(); });
            }
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            mFooFlag = false;
            mCond.notify_all();
        }
    }

    void bar(std::function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            {
                std::unique_lock<std::mutex> lock(mMutex);
                mCond.wait(lock, [&] { return !mFooFlag.load(); });
            }
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            mFooFlag = true;
            mCond.notify_all();
        }
    }
};
}

TEST(_1115_TestPrintFooBarAlternately, SimpleCases) {
    using namespace TestPrintFooBarAlternately;
    {
        std::ostringstream oss;
        int n = 50;
        FooBar fooBar(50);
        std::thread t1 { &FooBar::foo, &fooBar, [&] { oss << "foo"; } };
        std::thread t2 { &FooBar::bar, &fooBar, [&] { oss << "bar"; } };
        t1.join();
        t2.join();
        std::string sExpected;
        while (n-- > 0) {
            sExpected.append("foobar");
        }
        EXPECT_EQ(oss.str(), sExpected);
    }
}

#endif//_____TEST_PRINT_ALTERNATELY_HEADER_____