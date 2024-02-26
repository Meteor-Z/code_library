/**
 * @file shared_ptr.h
 * @author lzc (liuzechen.coder@qq.com)
 * @brief
 * @version 0.1
 * @date 2024-02-26
 *
 * @copyright Copyright (c) 2024
 * @note https://zhuanlan.zhihu.com/p/680068428
 */
#ifndef MY_CODE_SharedPtr_H
#define MY_CODE_SharedPtr_H

#include <atomic>
#include <type_traits>
#include <utility>

namespace my_code {

template <typename T>
struct SharedPtr;

template <typename T>
struct WeakPtr;

template <class T>
struct enable_shared_from_this;

template <typename T>
constexpr bool can_enable_shared = std::is_base_of_v<enable_shared_from_this<T>, T>;

template <typename T>
struct RefCount {
    RefCount(T* raw_ptr) : m_ptr(raw_ptr) {}

    void add_ref() { m_uses++; }

    void sub_ref() {
        m_uses--;
        if (m_uses == 0) {
            destroy_resource();
            sub_wref();
        }
    }

    void add_wref() { m_weaks++; }

    void sub_wref() {
        m_weaks--;
        if (m_weaks == 0) {
            delete_this();
        }
    }

    bool try_add_ref() {
        if (m_uses == 0) {
            return false;
        }
        m_uses++;
        return true;
    }

    void destroy_resource() noexcept { delete m_ptr; }

    void delete_this() noexcept { delete this; }

    int32_t use_count() { return m_uses; }

private:
    std::atomic_int32_t m_uses { 1 };

    std::atomic_int32_t m_weaks { 1 };

    T* m_ptr { nullptr };
};

template <typename T>
struct PtrBase {
    PtrBase() = default;
    PtrBase(const PtrBase&) = delete;
    PtrBase& operator=(const PtrBase&) = delete;

    T* get() const noexcept { return m_ptr; }

    auto use_count() const noexcept { return m_ref ? m_ref->use_count() : 0; }

    template <typename T2>
    void swap(PtrBase<T2>& rhs) {
        std::swap(m_ptr, rhs.m_ptr);
        std::swap(m_ref, rhs.m_ref);
    }

    // friend class SharedPtr<T>;
    // friend class WeakPtr<T>;

    void init(T* raw_ptr) {
        m_ptr = raw_ptr;
        m_ref = new RefCount(raw_ptr);
    }

    void add_ref() const {
        if (m_ref) {
            m_ref->add_ref();
        }
    }

    void sub_ref() const {
        if (m_ref) {
            m_ref->sub_ref();
        }
    }

    void add_wref() const {
        if (m_ref) {
            m_ref->add_wref();
        }
    }

    void sub_wref() const {
        if (m_ref) {
            m_ref->sub_wref();
        }
    }

    // template <class T2>
    void copy_ptr_from(const PtrBase<T>& rhs) {
        m_ptr = rhs.m_ptr;
        m_ref = rhs.m_ref;
    }

    template <typename T2>
    void move_construct_from(PtrBase<T2>&& rhs) noexcept {
        m_ptr = std::exchange(rhs.m_ptr, nullptr);
        m_ref = std::exchange(rhs.m_ref, nullptr);
    }

    template <class T2>
    void copy_construct_from_shared(const SharedPtr<T2>& rhs) noexcept {
        rhs.add_ref();
        copy_ptr_from(rhs);
    }

    template <class T2>
    void weakly_construct_from(const PtrBase<T2>& rhs) noexcept {
        copy_ptr_from(rhs);
        add_wref();
    }

    template <class T2>
    bool construct_from_weak(const WeakPtr<T2>& rhs) noexcept {
        if (rhs.m_ref && rhs.m_ref->try_add_ref()) {
            copy_ptr_from(rhs);
            return true;
        }

        return false;
    }
    T* m_ptr { nullptr };
    RefCount<T>* m_ref { nullptr };
};

template <typename T>
struct SharedPtr : public PtrBase<T> {
public:
    using Base = PtrBase<T>;
    SharedPtr() noexcept = default;
    SharedPtr(std::nullptr_t) noexcept {} // construct empty SharedPtr
    explicit SharedPtr(T* raw_ptr) {
        Base::init(raw_ptr);
        if constexpr (can_enable_shared<T>) {
            raw_ptr->m_weak_this = *this;
        }
    }

    SharedPtr(const SharedPtr& rhs) { Base::copy_construct_from_shared(rhs); }

    SharedPtr& operator=(const SharedPtr& rhs) {
        SharedPtr(rhs).swap(*this);
        return *this;
    }

    SharedPtr(SharedPtr&& rhs) noexcept { Base::move_construct_from(std::move(rhs)); }

    SharedPtr& operator=(SharedPtr&& rhs) noexcept {
        SharedPtr(std::move(rhs)).swap(*this);
        return *this;
    }

    template <class T2>
    SharedPtr(const WeakPtr<T2>& rhs) noexcept {
        Base::construct_from_weak(rhs);
    }
    ~SharedPtr() { Base::sub_ref(); }

    T& operator*() noexcept { return *Base::m_ptr; }

    const T& operator*() const noexcept { return *Base::m_ptr; }

    T* operator->() { return &*Base::m_ptr; }
    const T* operator->() const { return &*Base::m_ptr; }

    explicit operator bool() const { return (Base::_ptr != nullptr); }
};

template <typename T>
struct WeakPtr : public PtrBase<T> {
public:
    using Base = PtrBase<T>;

    WeakPtr() noexcept = default;

    constexpr WeakPtr(std::nullptr_t) noexcept {}

    WeakPtr(const WeakPtr& rhs) { Base::_weakly_construct_from(rhs); }

    WeakPtr(const SharedPtr<T>& rhs) { Base::weakly_construct_from(rhs); }

    WeakPtr& operator=(const WeakPtr& rhs) {
        weak_ptr(rhs).swap(*this);
        return *this;
    }

    WeakPtr(WeakPtr&& rhs) noexcept { Base::move_construct_from(std::move(rhs)); }

    WeakPtr& operator=(WeakPtr&& rhs) noexcept {
        WeakPtr(std::move(rhs)).swap(*this);
        return *this;
    }

    ~WeakPtr() { Base::sub_wref(); }

    SharedPtr<T> lock() const noexcept {
        SharedPtr<T> ans;
        ans.construct_from_weak(*this);
        return ans;
    }

    bool expired() const { return Base::_ref->use_count() == 0; }
};

template <typename T, typename... Args>
SharedPtr<T> make_shared(Args&&... args) {
    return SharedPtr<T> { new T(std::forward<Args>(args)...) };
}

template <typename T>
struct enable_shared_from_this {
    mutable WeakPtr<T> m_weak_this;

protected:
    constexpr enable_shared_from_this() noexcept : m_weak_this() {}
    enable_shared_from_this(const enable_shared_from_this&) noexcept {}
    enable_shared_from_this& operator=(const enable_shared_from_this&) noexcept {
        return *this;
    }
    ~enable_shared_from_this() = default;

public:
    SharedPtr<T> shared_from_this() { return SharedPtr<T>(m_weak_this); }
    SharedPtr<T const> shared_from_this() const {
        return SharedPtr<const T>(m_weak_this);
    }
    // friend class SharedPtr<T>;
};

} // namespace my_code

#include <iostream>

struct Node : my_code::enable_shared_from_this<Node> {
    Node(int b) : a(b) {}
    int a;
};
inline void shared_ptr_test() {
    my_code::SharedPtr<int> a = my_code::make_shared<int>(1);
    std::cout << *a << std::endl;
    my_code::SharedPtr<int> b = a;
    std::cout << *b << std::endl;
    std::cout << a.use_count() << std::endl;
    std::cout << b.use_count() << std::endl;

    // -----------------------------------------

    std::cout << "test_2" << std::endl;

    my_code::SharedPtr<Node> test_2 = my_code::make_shared<Node>(1);
    std::cout << test_2->a << std::endl;
    my_code::SharedPtr<Node> test_3 = test_2->shared_from_this();
    std::cout << test_3->a << std::endl;
    std::cout << test_2.use_count() << std::endl;
    std::cout << test_3.use_count() << std::endl;
}
#endif