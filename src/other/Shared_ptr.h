/**
 * @file shared_ptr.h
 * @author lzc (liuzechen.coder@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-02-26
 *
 * @copyright Copyright (c) 2024
 * @note https://zhuanlan.zhihu.com/p/680068428
 * @note
 * https://github.com/silenke/interview_mini_questions/blob/master/shared_ptr/%E6%BA%90.cpp
 */
#ifndef CODE_SharedPtr_H
#define CODE_SharedPtr_H

#include <atomic>
#include <cstddef>
#include <iostream>
#include <utility>

namespace code {

class RefCount {
public:
    int use_count() { return m_count; }
    void inc_ref() { ++m_count; }
    int dec_ref() { return --m_count; }

private:
    std::atomic_int32_t m_count { 1 };
};

template <typename T>
class shared_ptr {
public:
    friend void swap(const shared_ptr& a, const shared_ptr& b) {
        std::swap(a.m_ptr, b.m_ptr);
        std::swap(a.m_ref, b.m_ref);
    }

public:
    constexpr shared_ptr() noexcept = default;

    constexpr shared_ptr(std::nullptr_t) noexcept;

    explicit shared_ptr(T* ptr) : m_ptr(ptr) {
        if (ptr) {
            m_ref = new RefCount {};
        }
    }

    shared_ptr(const shared_ptr& rhs) : m_ptr(rhs.m_ptr), m_ref(m_ref) {
        if (m_ref) {
            m_ref->dec_ref();
        }
    }

    shared_ptr(shared_ptr&& rhs) {
        m_ptr = std::exchange(rhs.m_ptr, nullptr);
        m_ref = std::exchange(rhs.m_ref, nullptr);
    }

    shared_ptr& operator=(const shared_ptr& rhs) {
        shared_ptr { rhs }.swap(*this);
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& rhs) {
        shared_ptr { std::move(rhs) }.swap(*this);
        return *this;
    }

    ~shared_ptr() {
        if (m_ref && !m_ref->dec_ref()) {
            delete m_ptr;
            delete m_ref;
        }
    }

    T* get() const noexcept { return m_ptr; }

    T* operator*() const noexcept { return m_ptr; }

    T* operator->() const noexcept { return m_ptr; }

private:
    T* m_ptr { nullptr };
    RefCount* m_ref { nullptr };
};

template <typename T, typename... Args>
auto make_shared(Args&&... args) {
    return shared_ptr<T> { new T(std::forward<Args>(args)...) };
}

} // namespace code
#endif
