#ifndef _____QUICK_SORT_HEADER_____
#define _____QUICK_SORT_HEADER_____

#include <gtest/gtest.h>
#include "../util/std_util.h"

namespace QuickSort {
    class Solution {
    public:
        void quickSort(std::vector<int>& nums) {
            return quickSort(nums, 0, nums.size() - 1);
        }

    private:
        int partition(std::vector<int>& nums, int begin, int end) {
            int mid = (begin + end) / 2;
            int pivot = nums[mid];
            int count(0);
            for (int i = begin; i <= end; i++) {
                if (nums[i] < pivot) {
                    count++;
                }
            }
            int x = begin + count;
            std::swap(nums[x], nums[mid]);

            int left(begin), right(end);
            while (left < x && right > x) {
                while (nums[left] < pivot) {
                    left++;
                }
                while (nums[right] >= pivot) {
                    right--;
                }
                if (left >= x && right <= x) {
                    break;
                }
                std::swap(nums[left], nums[right]);
            }
            return x;
        }

        void quickSort(std::vector<int>& nums, int begin, int end) {
            if (begin >= end) {
                return;
            }
            int x = partition(nums, begin, end);
            quickSort(nums, begin, x - 1);
            quickSort(nums, x + 1, end);
        }
    };

    bool test(const char* input, const char* expected) {
        std::vector<int> nums = StdUtil::generateIntVector(input);
        Solution().quickSort(nums);
        return StdUtil::compareEqualVector(
            nums,
            StdUtil::generateIntVector(expected)
        );
    }
}


TEST(QuickSort, SimpleCases) {
    using namespace QuickSort;
    {
        EXPECT_TRUE(QuickSort::test("5,4,3,2,1", "1,2,3,4,5"));
    }
}

#endif//_____QUICK_SORT_HEADER_____