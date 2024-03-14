#ifndef MY_CODE_VECTOR_H
#define MY_CODE_VECTOR_H

#include <cassert>
#include <cstdio>
#include <utility>
#include <iostream>

namespace my_code {
template <typename T>
class Vector {
public:
    explicit Vector() noexcept = default;
    Vector(size_t n) : m_cap(n), m_ptr(alloc(n)) {
        for (; m_len < m_cap; m_len++) {
            construct(m_ptr + m_len);
        }
    }

    Vector(size_t n, const T& val) : m_cap(n), m_ptr(alloc(n)) {
        for (; m_len < m_cap; m_len++) {
            construct(m_ptr + m_len, val);
        }
    }

    // 有可能出现错误
    Vector(const Vector& rhs) : m_cap(rhs.m_cap), m_ptr(alloc(rhs.m_cap)) {
        std::cout << "ffff" << std::endl;
        for (; m_len < rhs.m_len; m_len++) {
            construct(m_ptr+m_len, rhs.m_ptr[m_len]);
        }
    }

    Vector(Vector&& rhs) {
        m_len = std::exchange(rhs.m_len, 0);
        m_cap = std::exchange(rhs.m_cap, 0);
        m_ptr = std::exchange(rhs.m_ptr, nullptr);
    }

    Vector(std::initializer_list<T> list) : m_cap(list.size()), m_ptr(alloc(m_cap)) {
        for (const auto& item : list) {
            construct(m_ptr + m_len, item);
            m_len++;
        }
    }

    void swap(Vector& other) noexcept {
        using std::swap;
        swap(m_len, other.m_len);
        swap(m_cap, other.m_cap);
        swap(m_ptr, other.m_ptr);
    }

    void clear() {
        for (; m_len > 0; m_len--) {
            destroy(m_ptr + m_len - 1);
        }
    }
    ~Vector() noexcept {
        clear();
        dealloc(m_ptr);
    }

    Vector& operator=(const Vector& rhs) {
        if (*this != rhs) {
            Vector { rhs }.swap(*this);
        }
        return *this;
    }

    Vector& operator=(Vector&& rhs) {
        if (*this != rhs) {
            Vector { std::move(rhs) }.swap(*this);
        }
        return *this;
    }

    Vector& operator=(std::initializer_list<T> list) {
        Vector { list }.swap(*this);
        return *this;
    }

    void push_back(const T& val) { emplace_back(val); }

    void push_back(T&& val) { emplace_back(std::move(val)); }

    template <typename... Args>
    void emplace_back(Args... args) {
        if (m_len == m_cap) {
            size_t new_cap = m_cap ? m_cap * 2 : 1;
            T* new_ptr = alloc(new_cap);

            for (size_t new_len = 0; new_len < m_cap; new_len++) {
                construct(new_ptr + new_len, std::move_if_noexcept(m_ptr[new_len]));
            }
            m_cap = new_cap;
            std::swap(m_ptr, new_ptr);
            dealloc(new_ptr);
        }
        construct(m_ptr + m_len, std::forward<Args>(args)...);
        m_len++;
    }

    void pop_back() {
        destroy(m_ptr + m_len - 1);
        m_len--;
    }

    T& back() { return *(m_ptr + m_len - 1); }

    size_t size() const noexcept { return m_len; }
    size_t capacity() const noexcept { return m_cap; }
    bool empty() const noexcept { return m_len == 0; }

    T& operator[](size_t index) { return m_ptr[index]; }
    const T& operator[](size_t index) const { return m_ptr[index]; }

    T* begin() noexcept { return m_ptr; }
    T* end() noexcept { return m_ptr + m_len; };

    const T* begin() const noexcept { return m_ptr; }
    const T* end() const noexcept { return m_ptr + m_len; }

private:
    T* alloc(size_t n) { return static_cast<T*>(::operator new(sizeof(T) * n)); }

    void dealloc(T* ptr) { ::operator delete(ptr); }

    template <typename... Args>
    void construct(T* ptr, Args&&... args) {
        ::new (ptr) T(std::forward<Args>(args)...);
    }

    void destroy(T* ptr) { ptr->~T(); };

private:
    size_t m_cap { 0 };
    size_t m_len { 0 };
    T* m_ptr { nullptr };
};

inline void vector_test() {
    Vector<int> arr_1 { 1, 2, 3, 4, 5, 5 };
    for (auto& item : arr_1) {
        std::cout << item << std::endl;
    }

    // ------------------------------------------------------

    Vector<std::string> arr_2 { "hello", "yes", "no", "ji" };
    Vector<std::string> arr_3 = std::move(arr_2);
    std::cout << arr_3[2] << std::endl;

    // -----------------------------------------------------------

    Vector<int> arr_4;
    for (int i = 0; i < 100; i++) {
        arr_4.push_back(i);
        printf("val = %d, size = %zu, cap = %zu \n", arr_4[i], arr_4.size(),
               arr_4.capacity());
        assert(arr_4.capacity() >= arr_4.size());
    }
    while (!arr_4.empty()) {
        std::cout << arr_4.back() << " ";
        arr_4.pop_back();
    }
    std::cout << '\n';

    // ---------------------------------------------------------------

    Vector<std::string> arr_5(3, "哈哈");
    for (const auto& item : arr_5) {
        std::cout << item << std::endl;
    }

    arr_5.push_back("jijiji");
    arr_5.push_back("caocaocao");

    printf("arr_5: size = %zu, cap = %zu\n", arr_5.size(), arr_5.capacity());
    
    Vector<std::string> arr_6 = arr_5;
     for (const auto& item : arr_6) {
        std::cout << item << std::endl;
    }
    printf("arr_6: size = %zu, cap = %zu", arr_6.size(), arr_6.capacity());

    // ---------------------------------------------------------------
}
} // namespace my_code

#endif