#pragma once

// https://leetcode.com/problems/the-dining-philosophers/
/**
* 1226. The Dining Philosophers
* Five silent philosophers sit at a round table with bowls of spaghetti. 
* Forks are placed between each pair of adjacent philosophers.
*
* Each philosopher must alternately think and eat. However, a philosopher
* can only eat spaghetti when they have both left and right forks. Each
* fork can be held by only one philosopher and so a philosopher can use
* the fork only if it is not being used by another philosopher. After an
* individual philosopher finishes eating, they need to put down both forks
* so that the forks become available to others. A philosopher can take the
* fork on their right or the one on their left as they become available,
* but cannot start eating before getting both forks.
*
* Eating is not limited by the remaining amounts of spaghetti or stomach
* space; an infinite supply and an infinite demand are assumed.
*
* Design a discipline of behaviour (a concurrent algorithm) such that no
* philosopher will starve; i.e., each can forever continue to alternate
* between eating and thinking, assuming that no philosopher can know when
* others may want to eat or think.
* 
* 
* The philosophers' ids are numbered from 0 to 4 in a clockwise order.
* Implement the function
* void wantsToEat(philosopher, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork)
* where:
*    philosopher is the id of the philosopher who wants to eat.
*    pickLeftFork and pickRightFork are functions you can call to pick the corresponding forks of that philosopher.
*    eat is a function you can call to let the philosopher eat once he has picked both forks.
*    putLeftFork and putRightFork are functions you can call to put down the corresponding forks of that philosopher.
*    The philosophers are assumed to be thinking as long as they are not asking to eat (the function is not being called with their number).
*
* Five threads, each representing a philosopher, will simultaneously use
* one object of your class to simulate the process. The function may be
* called for the same philosopher more than once, even before the last call ends.
*/

#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <gtest/gtest.h>


namespace TheDiningPhilosophers {

    const int PhilosopherCount = 5;

    class DiningPhilosophers {
    public:
        DiningPhilosophers() {
            //std::fill_n(mForkInUse, false, PhilosopherCount);
        }

        void wantsToEat(int philosopher,
            std::function<void()> pickLeftFork,
            std::function<void()> pickRightFork,
            std::function<void()> eat,
            std::function<void()> putLeftFork,
            std::function<void()> putRightFork) {
            const int left = philosopher;
            const int right = (philosopher + PhilosopherCount - 1) % PhilosopherCount;
            if (left % 2 == 0) {
                //std::cout << "id:" << philosopher << " left:" << left << " right:" << right << " [left]first:" << left << std::endl;
                wantsToEat(left, right, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork);
            }
            else {
                //std::cout << "id:" << philosopher << " left:" << left << " right:" << right << " [right]first:" << right << std::endl;
                wantsToEat(right, left, pickRightFork, pickLeftFork, eat, putRightFork, putLeftFork);
            }
        }

        void wantsToEat(
            int fork1,
            int fork2,
            std::function<void()> pickFork1,
            std::function<void()> pickFork2,
            std::function<void()> eat,
            std::function<void()> putFork1,
            std::function<void()> putFork2) {
                {
                    //std::cout << "wait[1] fork:" << fork1 << std::endl;
                    std::unique_lock<std::mutex> lock1(mMutex[fork1]);
                    mCond[fork1].wait(lock1, [=]() { return !mForkInUse[fork1]; });
                    mForkInUse[fork1] = true;
                    pickFork1();

                    //std::cout << "wait[2] fork:" << fork2 << std::endl;
                    std::unique_lock<std::mutex> lock2(mMutex[fork2]);
                    mCond[fork2].wait(lock2, [=]() { return !mForkInUse[fork2]; });
                    mForkInUse[fork2] = true;
                    pickFork2();

                    eat();

                    putFork2();
                    mForkInUse[fork2] = false;
                    putFork1();
                    mForkInUse[fork1] = false;
                }
                mCond[fork2].notify_one();
                mCond[fork1].notify_one();
        }

    private:
        // 每个哲学家左边有一个叉子，这个叉子的id与哲学家id相同
        std::mutex mMutex[PhilosopherCount];
        std::condition_variable mCond[PhilosopherCount];
        std::atomic_bool mForkInUse[PhilosopherCount];
    };

    class Philosopher {
    public:
        static void reset(int n) {
            sExpectEatTimes = n;
            std::fill_n(sEatRecord, 0, PhilosopherCount);
        }

        static void pickLeft(int id) {
            //std::cout << "id:" << id << "pickLeft" << std::endl;
        }

        static void pickRight(int id) {
            //std::cout << "id:" << id << "pickRight" << std::endl;
        }

        static void eat(int id) {
            //std::cout << "id:" << id << "eat" << std::endl;
            sEatRecord[id]++;
        }

        static void putLeft(int id) {
            //std::cout << "id:" << id << "putLeft" << std::endl;
        }

        static void putRight(int id) {
            //std::cout << "id:" << id << "putRight" << std::endl;
        }

    public:
        Philosopher(int id, DiningPhilosophers& dining)
            : mId(id), mDining(dining) {
            mFnPickLeft = std::bind(Philosopher::pickLeft, mId);
            mFnPickRight = std::bind(Philosopher::pickRight, mId);
            mFnEat = std::bind(Philosopher::eat, mId);
            mFnPutLeft = std::bind(Philosopher::putLeft, mId);
            mFnPutRight = std::bind(Philosopher::putRight, mId);
        }

        void PhilosopherProc() {
            while (sEatRecord[mId] < sExpectEatTimes) {
                mDining.wantsToEat(mId, mFnPickLeft, mFnPickRight, mFnEat, mFnPutLeft, mFnPutRight);
            }
        }

    public:
        static int sExpectEatTimes;
        static int sEatRecord[PhilosopherCount];

    private:
        int mId;
        DiningPhilosophers& mDining;
        std::function<void()> mFnPickLeft;
        std::function<void()> mFnPickRight;
        std::function<void()> mFnEat;
        std::function<void()> mFnPutLeft;
        std::function<void()> mFnPutRight;
    };
    int Philosopher::sExpectEatTimes = 1;
    int Philosopher::sEatRecord[PhilosopherCount] = {};


    bool runTest(int n) {
        Philosopher::reset(n);
        DiningPhilosophers dining;
        std::vector<Philosopher> philosophers;
        for (int i = 0; i < PhilosopherCount; i++) {
            philosophers.emplace_back(i, dining);
        }
        std::vector<std::thread> threads;
        for (int i = 0; i < PhilosopherCount; i++) {
            threads.emplace_back(&Philosopher::PhilosopherProc, &philosophers[i]);
        }
        for (int i = 0; i < PhilosopherCount; i++) {
            threads[i].join();
        }
        for (int i = 0; i < PhilosopherCount; i++) {
            if (Philosopher::sEatRecord[i] != n) {
                return false;
            }
        }
        return true;
    }
}

TEST(_1226_TheDiningPhilosophers, SimpleCases) {
    EXPECT_TRUE(TheDiningPhilosophers::runTest(1));
}