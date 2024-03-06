#ifndef MY_CODE_QUICK_SORT_H
#define MY_CODE_QUICK_SORT_H

#include <iostream>
#include <vector>

namespace my_code {
inline void quick_sort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int mid = arr[(l + r) / 2];
    int i = l - 1, j = r + 1;
    while(i < j) {
        do i++; while(arr[i] < mid);
        do j--; while(arr[j] > mid);
        if (i < j) std::swap(arr[i], arr[j]);
    }
    quick_sort(arr, l, j);
    quick_sort(arr, j + 1, r);
}
}; // namespace my_code
inline void quick_sort_test() {
    std::vector<int> arr { 1, 1, 45, 13, 1234, 12, 3, 123, 12, 312, 31, 2312, 3, 123 };
    my_code::quick_sort(arr, 0, arr.size() - 1);
    for (const auto& item : arr) {
        std::cout << item << ' ';
    }
    std::cout << '\n';
}
#endif