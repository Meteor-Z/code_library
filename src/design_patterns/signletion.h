/**
 * @file signletion.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-03-15
 * @note ygg https://zhuanlan.zhihu.com/p/651173499
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef CODE_DESIGN_PATTERNS_SINGLETION_H
#define CODE_DESIGN_PATTERNS_SINGLETION_H

#include <string>
#include <iostream>

namespace code {

template <typename T>
class Singletion {
protected:
    Singletion() = default;

public:
    ~Singletion() = default;

    Singletion(const Singletion&) = delete;
    Singletion(Singletion&&) = delete;

    Singletion& operator=(const Singletion&) = delete;
    Singletion& operator=(Singletion&&) = delete;

    static T& get() {
        static T val {};
        return val;
    }
};
struct A : Singletion<A> {
    int a;
    std::string f;
    A() {
        a = 1;
        f = "hello";
    }
};
} // namespace code

inline void signletion_test() {
    auto& A = code::A::get();
    std::cout << A.a << ' ' << A.f << std::endl;
}
#endif