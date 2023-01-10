//  test_building_h2o.h
#ifndef _____TEST_BUILDING_H2O_HEADER_____
#define _____TEST_BUILDING_H2O_HEADER_____

#include <thread>
#include <mutex>
#include <functional>
#include <atomic>
#include <iostream>
#include <gtest/gtest.h>


namespace BuildingH2O {

class H2O {
public:
    H2O() : h1(0), h2(0), o(0) {

    }

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::call_once(sH1Flag, [&] { tIsH1 = true; });

        if (tIsH1) {
            std::cout << "hydrogen:h1 - wait" << std::endl;
        }
        else {
            std::cout << "hydrogen:h2 - wait" << std::endl;
        }

        std::unique_lock<std::mutex> lock(mMutex);
        mCond.wait(lock, [&]() -> bool {
            return tIsH1 ? h1.load() == 0 : h2.load() == 0;
            });

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();

        if (tIsH1) {
            std::cout << "hydrogen:h1++" << std::endl;
            h1++;
        }
        else {
            std::cout << "hydrogen:h2++" << std::endl;
            h2++;
        }
        fireNext();
        mCond.notify_all();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::cout << "hydrogen:o - wait" << std::endl;
        std::unique_lock<std::mutex> lock(mMutex);
        mCond.wait(lock, [&] { return o.load() == 0; });
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        std::cout << "hydrogen:o++" << std::endl;
        o++;
        fireNext();
        mCond.notify_all();
    }

private:
    bool fireNext() {
        if (h1.load() == 1 && h2.load() == 1 && o.load() == 1) {
            std::cout << "fireNext reset" << std::endl;
            h1.store(0);
            h2.store(0);
            o.store(0);
            return true;
        }
        return false;
    }

private:
    static std::once_flag sH1Flag;
    static thread_local bool tIsH1;

private:
    std::atomic_int h1;
    std::atomic_int h2;
    std::atomic_int o;
    std::mutex mMutex;
    std::condition_variable mCond;
};

std::once_flag H2O::sH1Flag;
thread_local bool H2O::tIsH1 = false;


void elementProc(std::function<void()> elementFun, int n) {
    while (n-- > 0) {
        elementFun();
    }
}
}

TEST(_1117_BuildingH2O, SimpleCases) {
    using namespace BuildingH2O;
    {
        int n = 20;
        std::ostringstream os;
        std::vector<std::thread> thrds;
        H2O h2o;
        thrds.emplace_back(&elementProc, std::bind(&H2O::hydrogen, &h2o, [&] {os << "H"; }), n);
        thrds.emplace_back(&elementProc, std::bind(&H2O::hydrogen, &h2o, [&] {os << "H"; }), n);
        thrds.emplace_back(&elementProc, std::bind(&H2O::oxygen, &h2o, [&] {os << "O"; }), n);
        for (auto& t : thrds) {
            t.join();
        }
        std::cout << "TestBuildingH2O - output:" << std::endl;
        std::cout << os.str() << std::endl;
    }
}

#endif//_____TEST_BUILDING_H2O_HEADER_____