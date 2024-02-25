#ifndef MY_CODE_FUNCTION_H
#define MY_CODE_FUNCTION_H

#include <bits/stdc++.h>
#include <utility>

namespace my_code {
template <typename Ret, typename... Args>
class Function;

template <typename Ret, typename... Args>
class Function<Ret(Args...)> {
public:
    Function() {}
    Function(std::nullptr_t) {}

    template <typename T>
    Function(T&& func) : m_ptr { new Wrpper<T>(std::forward<T>(func)) } {}

    Function(const Function& rhs) { m_ptr = rhs.m_ptr->clone(); }

    Function& operator=(const Function& rhs) {
        if (this == &rhs) {
            return *this;
        }

        delete m_ptr;
        m_ptr = rhs.m_ptr ? rhs.m_ptr->clone() : nullptr;
        return *this;
    }

    ~Function() {
        if (m_ptr) {
            delete m_ptr;
        }
    }
    Function(Function&& rhs) { m_ptr = std::exchange(rhs.m_ptr, nullptr); }

    Ret operator()(Args... args) { return (*m_ptr)(std::forward<Args>(args)...); }

private:
    /**
     * @brief 包装类，多态中的最上层函数，最上层不变的，下层是变的
     *
     */
    struct WrpperBase {
        virtual Ret operator()(Args&&... args) = 0;
        virtual WrpperBase* clone() = 0;
        virtual ~WrpperBase() = default;
    };

    /**
     * @brief 相当于具体实现的子类内容
     *
     * @tparam Fun 函数
     */
    template <typename Fun>
    struct Wrpper : public WrpperBase {
        Wrpper(const Fun& func) : m_real_func { func } {}
        WrpperBase* clone() override { return new Wrpper<Fun>(m_real_func); }
        Ret operator()(Args&&... args) override {
            return (m_real_func(std::forward<Args>(args)...));
        }
        ~Wrpper() = default;

        Fun m_real_func; // 真正执行的底层函数
    };

private:
    WrpperBase* m_ptr { nullptr }; // 包装函数
};
} // namespace my_code
struct Node {
    int operator()() {
        std::cout << "this is Node class";
        return 111;
    }
};
inline void add() { std::cout << 2 << std::endl; }
inline void function_test() {
    my_code::Function<void()> test_1 = []() { std::cout << 1 << std::endl; };
    test_1();

    my_code::Function<void()> test_2 { test_1 };
    test_2();

    my_code::Function<void(int a, int b)> test_3 = [](int a, int b) {
        std::cout << a << ' ' << b << std::endl;
    };

    test_3(114514, 81975);

    my_code::Function<void(int a, int b)> test_4 = [](int a, int b) {
        std::cout << a * b << std::endl;
    };

    test_4(111, 222);

    test_4 = test_3;

    test_4(2, 3);

    Node node;
    my_code::Function<int()> test_5 { node };
    int number = test_5();
    std::cout << number << std::endl;
}
#endif