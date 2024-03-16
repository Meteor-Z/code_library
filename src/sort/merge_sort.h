#ifndef CODE_MERGE_SORT_H
#define CODE_MERGE_SORT_H

#include <vector>
#include <thread>
#include <iostream>

namespace code {
inline void merge_sort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int mid = (l + r) / 2;

    merge_sort(arr, l, mid);
    merge_sort(arr, mid + 1, r);

    int i = l, j = mid + 1;
    
    std::vector<int> tmp;

    while(i <= mid && j <= r) {
        if (arr[i] <= arr[j]) tmp.push_back(arr[i++]);
        else tmp.push_back(arr[j++]);
    }
    
    while(i <= mid) tmp.push_back(arr[i++]);
    while(j <= r) tmp.push_back(arr[j++]);

    for (i = l, j = 0; i <= r;i++,j++) arr[i] = tmp[j];
    
}

inline void muti_merge_sort(std::vector<int>& arr, int l, int r) {
    if (l >= r) return;

    int mid = (l + r) / 2;

    // 只有l r 之间大于一定的距离的时候，才开多线程进行排序，否则进行常规的排序
    if (r - l + 1 >= 1000) {
        std::thread t1(muti_merge_sort, std::ref(arr), l, mid);
        std::thread t2(muti_merge_sort, std::ref(arr), mid + 1, r);

        t1.join();
        t2.join();
    } else {
        merge_sort(arr, l, mid);
        merge_sort(arr, mid + 1, r);
    }

    std::vector<int> temp;

    mid = (l + r) / 2;
    int i = l, j = mid + 1;

    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) temp.push_back(arr[i++]);
        else temp.push_back(arr[j++]);
    }

    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (i = l, j = 0; i <= r; i++, j++) arr[i] = temp[j];
}
};
inline void merge_sort_test() {
    std::vector<int> arr { 1, 1, 45, 13, 1234, 12, 3, 123, 12, 312, 31, 2312, 3, 123 };
    code::merge_sort(arr, 0, arr.size() - 1);
    for (const auto& item : arr) {
        std::cout << item << ' ';
    }
    std::cout << '\n';

    std::vector<int> arr_2;
    for (int i =  10000; i >= 0;i--) {
        arr_2.push_back(i);
    }

    code::muti_merge_sort(arr_2, 0, arr_2.size() - 1);
    for (const auto& item: arr_2) {
        std::cout << item << ' ';
    }
    std::cout << '\n';
};
#endif