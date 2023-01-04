#ifndef _____1195_FIZZ_BUZZ_MULTITHREADED_HEADER_____
#define _____1195_FIZZ_BUZZ_MULTITHREADED_HEADER_____

#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <gtest/gtest.h>

namespace FizzBuzzMultithreaded {
    class FizzBuzz {
    private:
        enum Type {
            UNKNOWN = -1,
            NUMBER = 0,
            FIZZ = 1,
            BUZZ = 2,
            FIZZBUZZ = 3
        };

    private:
        int mMax;
        std::atomic_int mNumber;
        Type mNumberType;
        std::mutex mMutex;
        std::condition_variable mCond;
        std::atomic_bool mStopped;

    public:
        FizzBuzz(int n) : mMax(n), mNumber(0), mNumberType(UNKNOWN), mStopped(false) {
            fireNext();
        }

        // printFizz() outputs "fizz".
        void fizz(std::function<void()> printFizz) {
            while (!mStopped) {
                {
                    //std::cout << "fizz wait" << std::endl;
                    std::unique_lock<std::mutex> lk(mMutex);
                    mCond.wait(lk, [this] {
                        return mNumberType == FIZZ || mStopped;
                        });
                    if (!mStopped) {
                        printFizz();
                    }
                }
                fireNext();
            }
        }

        // printBuzz() outputs "buzz".
        void buzz(std::function<void()> printBuzz) {
            while (!mStopped) {
                {
                    //std::cout << "buzz wait" << std::endl;
                    std::unique_lock<std::mutex> lk(mMutex);
                    mCond.wait(lk, [this] {
                        return mNumberType == BUZZ || mStopped;
                        });
                    if (!mStopped) {
                        printBuzz();
                    }
                }
                fireNext();
            }
        }

        // printFizzBuzz() outputs "fizzbuzz".
        void fizzbuzz(std::function<void()> printFizzBuzz) {
            while (!mStopped) {
                {
                    //std::cout << "fizzbuzz wait" << std::endl;
                    std::unique_lock<std::mutex> lk(mMutex);
                    mCond.wait(lk, [this] {
                        return mNumberType == FIZZBUZZ || mStopped;
                        });
                    if (!mStopped) {
                        printFizzBuzz();
                    }
                }
                fireNext();
            }
        }

        // printNumber(x) outputs "x", where x is an integer.
        void number(std::function<void(int)> printNumber) {
            while (!mStopped) {
                {
                    //std::cout << "number wait" << std::endl;
                    std::unique_lock<std::mutex> lk(mMutex);
                    mCond.wait(lk, [this] {
                        return mNumberType == NUMBER || mStopped;
                        });
                    if (!mStopped) {
                        printNumber(mNumber);
                    }
                }
                fireNext();
            }
        }

    private:
        void fireNext() {
            if (mStopped) {
                return;
            }
            if (++mNumber <= mMax) {
                mNumberType = typeOfNumber(mNumber);
                //std::cout << "fireNext : " << mNumber << " - type:" << descType(mNumberType) << std::endl;
            }
            else {
                //std::cout << "fireNext : stop" << std::endl;
                mStopped = true;
            }
            mCond.notify_all();
        }

        inline Type typeOfNumber(int n) {
            bool d3 = n % 3 == 0;
            bool d5 = n % 5 == 0;
            if (d3 && d5) {
                return FIZZBUZZ;
            }
            else if (d3) {
                return FIZZ;
            }
            else if (d5) {
                return BUZZ;
            }
            else {
                return NUMBER;
            }
        }

        inline const char* descType(Type t) {
            switch (t) {
            default:
            case UNKNOWN:
                return "unknown";
            case NUMBER:
                return "number";
            case FIZZ:
                return "fizz";
            case BUZZ:
                return "buzz";
            case FIZZBUZZ:
                return "fizzbuzz";
            }
        }
    };

    template<typename T>
    void fnPrint(std::ostringstream& os, T t) {
        os << t;
    }

    bool runText(int n, const char* expected) {
        FizzBuzz fb(n);
        std::ostringstream os;
        std::thread t1(&FizzBuzz::fizz, &fb, std::bind(fnPrint<const char*>, std::ref(os), "fizz"));
        std::thread t2(&FizzBuzz::buzz, &fb, std::bind(fnPrint<const char*>, std::ref(os), "buzz"));
        std::thread t3(&FizzBuzz::fizzbuzz, &fb, std::bind(fnPrint<const char*>, std::ref(os), "fizzbuzz"));
        std::thread t4(&FizzBuzz::number, &fb, std::bind(fnPrint<int>, std::ref(os), std::placeholders::_1));
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        //std::cout << "FizzBuzz[" << n << "]-output: " << os.str() << std::endl;
        std::string output(os.str());
        std::string expect(expected);
        return output == expect;
    }
}

TEST(_1195_FizzBuzzMultithreaded, SimpleCases) {
    EXPECT_TRUE(FizzBuzzMultithreaded::runText(15, "12fizz4buzzfizz78fizzbuzz11fizz1314fizzbuzz"));
}

#endif//_____1195_FIZZ_BUZZ_MULTITHREADED_HEADER_____