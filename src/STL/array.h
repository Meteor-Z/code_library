#ifndef MY_CODE_STL_ARRAY_H
#define MY_CODE_STL_ARRAY_H

#include <cstddef>
namespace my_code {
template <typename T, size_t Number>
struct Array {
    T& operator[](size_t pos) { return arr[pos]; }
    const T& operator[](size_t pos) const { return arr[pos]; }

    T& front() { return arr[0]; }

    const T& front() const { return arr[0]; }

    T& back() { return arr[Number - 1]; }
    const T& back() const { return arr[Number - 1]; }

    constexpr size_t size() const noexcept { return Number; }

    T arr[Number];
};
} // namespace my_code
#endif