#pragma once

//  https://leetcode.com/problems/design-circular-queue/
/*
* 622. Design Circular Queue
* 
* Design your implementation of the circular queue. The circular queue is a linear data
* structure in which the operations are performed based on FIFO (First In First Out)
* principle and the last position is connected back to the first position to make a circle.
* It is also called "Ring Buffer".
*
* One of the benefits of the circular queue is that we can make use of the spaces in front
* of the queue. In a normal queue, once the queue becomes full, we cannot insert the next
* element even if there is a space in front of the queue. But using the circular queue,
* we can use the space to store new values.
*
* Implementation the MyCircularQueue class:
*
* MyCircularQueue(k) Initializes the object with the size of the queue to be k.
   * int Front() Gets the front item from the queue. If the queue is empty, return -1.
   * int Rear() Gets the last item from the queue. If the queue is empty, return -1.
   * boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
   * boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
   * boolean isEmpty() Checks whether the circular queue is empty or not.
   * boolean isFull() Checks whether the circular queue is full or not.
*
* You must solve the problem without using the built-in queue data structure in your
* programming language. 
* 
* 
* Constraints:
*    1 <= k <= 1000
*    0 <= value <= 1000
*    At most 3000 calls will be made to enQueue, deQueue, Front, Rear, isEmpty, and isFull.
*/

#include <gtest/gtest.h>

namespace DesignCircularQueue {

    class MyCircularQueue {
    private:
        int* mBuf;
        int mCapacity;
        int mSize;
        int mHead;
        int mTail;

    public:
        MyCircularQueue(int k) {
            mBuf = new int[k];
            memset(mBuf, 0, sizeof(int) * k);
            mCapacity = k;
            mSize = 0;
            mHead = 0;
            mTail = 0;
        }

        ~MyCircularQueue() {
            if (mBuf) {
                delete[] mBuf;
                mBuf = nullptr;
            }
        }

        bool enQueue(int value) {
            if (isFull()) {
                return false;
            }
            mBuf[mTail] = value;
            mTail = (mTail + 1) % mCapacity;
            mSize++;
            return true;
        }

        bool deQueue() {
            if (isEmpty()) {
                return false;
            }
            mHead = (mHead + 1) % mCapacity;
            mSize--;
            return true;
        }

        int Front() {
            if (isEmpty()) {
                return -1;
            }
            return mBuf[mHead];
        }

        int Rear() {
            if (isEmpty()) {
                return -1;
            }
            return mBuf[(mTail + mCapacity - 1) % mCapacity];
        }

        bool isEmpty() {
            return mSize == 0;
        }

        bool isFull() {
            return mSize == mCapacity;
        }
    };
}


TEST(_622_DesignCircularQueue, SimpleCases) {
    DesignCircularQueue::MyCircularQueue myQueue(3);
    EXPECT_EQ(myQueue.Front(), -1);
    EXPECT_EQ(myQueue.Rear(), -1);
    EXPECT_TRUE(myQueue.enQueue(1));
    EXPECT_TRUE(myQueue.enQueue(2));
    EXPECT_TRUE(myQueue.enQueue(3));
    EXPECT_FALSE(myQueue.enQueue(4));
    EXPECT_EQ(myQueue.Rear(), 3);
    EXPECT_TRUE(myQueue.isFull());
    EXPECT_TRUE(myQueue.deQueue());
    EXPECT_TRUE(myQueue.enQueue(4));
    EXPECT_EQ(myQueue.Rear(), 4);
}