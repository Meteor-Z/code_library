#ifndef CODE_DESIGN_PATTERNS_RESULT_H
#define CODE_DESIGN_PATTERNS_RESULT_H

#include <stdexcept>
#include <variant>
#include <iostream>
namespace code {

template <typename T, typename E>
struct Result {
public:
    Result(const T& value) : m_is_ok(true), m_value(value) {}
    Result(const E& error) : m_is_ok(false), m_value(error) {}
    T& value() {
        if (m_is_ok) {
            return std::get<0>(m_value);
        }
        throw std::logic_error("Result is bad value");
    }
    E& error() {
        if (!m_is_ok) {
            return std::get<1>(m_value);
        }
        throw std::logic_error("Result is good value");
    }
    bool is_ok() const { return m_is_ok; }

private:
    bool m_is_ok { false };
    std::variant<T, E> m_value;
};

}; // namespace code

inline void result_test() {
    code::Result<std::string, int> a("hello");
    if (a.is_ok()) {
        std::cout << a.value() << std::endl;
    }
    code::Result<std::string, int> b(1);
    std::cout << b.error() << std::endl;
}

#endif