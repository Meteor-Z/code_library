#ifndef MY_CODE_HEAP_H
#define MY_CODE_HEAP_H

#include <vector>
#include <iostream>

namespace my_code {
void down(std::vector<int>& arr, int u) {
    size_t t = u;
    if (u * 2 <= arr.size() - 1 && arr[u * 2] < arr[t])
        t = u * 2;
    if (u * 2 + 1 <= arr.size() - 1 && arr[u * 2 + 1] < arr[t])
        t = 2 * u + 1;
    if (u != t) {
        std::swap(arr[u], arr[t]);
        down(arr, t);
    }
}
inline void heap_sort(std::vector<int>& arr) {
    for (size_t i = arr.size() - 1; i; i--) {
        down(arr, i);
    }
}

}; // namespace my_code

inline void heap_sort_test() {
    
    std::vector<int> arr { 0, 45, 14, 23, 1, 2, 53, 213, 1, 3 };
    int n = arr.size();
    my_code::heap_sort(arr);
    int cnt = arr.size();
    while(cnt--) {
        std::cout << arr[1] << ' ';
        arr[1] = arr[cnt--];
        my_code::down(arr,1);
    }
    
}
#endif