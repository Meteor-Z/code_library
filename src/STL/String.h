#ifndef CODE_STRING_H
#define CODE_STRING_H

#include <cstddef>
#include <cstring>
#include <ostream>
#include <iostream>
#include <utility>

namespace code {
class String {
public:
    friend bool operator<(const String& a, const String& b) {
        return strcmp(a.m_data, b.m_data) < 0;
    }

    friend bool operator==(const String& a, const String& b) {
        return strcmp(a.m_data, b.m_data) == 0;
    }
    
    friend std::ostream& operator<<(std::ostream& ostream, const String& rhs) {
        ostream << rhs.m_data;
        return ostream;
    }

public:
    String(const char* str) {
        if (str == nullptr) {
            m_data = new char[1];
            m_data[0] = '\0';
            m_size = 0;
            m_capacity = 0;
        } else {
            m_size = std::strlen(str);
            m_capacity = m_size;

            m_data = new char[m_size + 1];
            std::strcpy(m_data, str);
        }
    }

    String(const String& str) : m_capacity(str.m_capacity), m_size(str.m_size) {
        m_data = new char[str.m_size + 1];
        strcpy(m_data, str.m_data);
    }

    String(String&& rhs) {
        m_data = std::exchange(rhs.m_data, nullptr);
        m_size = std::exchange(rhs.m_size, 0);
        m_capacity = std::exchange(rhs.m_capacity, 0);
    }

    String& operator=(const String& rhs) {
        if (this == &rhs) {
            return *this;
        }
        if (m_data) {
            delete[] m_data;
        }

        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;

        m_data = new char[m_size + 1];
        strcpy(m_data, rhs.m_data);

        return *this;
    }
    String& operator=(String&& rhs) {
        if (m_data) {
            delete[] m_data;
        }

        m_data = std::exchange(rhs.m_data, nullptr);
        m_size = std::exchange(rhs.m_size, 0);
        m_capacity = std::exchange(rhs.m_capacity, 0);

        return *this;
    }
    ~String() {
        if (m_data) {
            delete[] m_data;
        }
    }

    size_t size() { return m_size; }
    size_t capacity() { return m_capacity; }

    char* begin() const { return m_data; }

    char* end() { return m_data + m_size; }

private:
    char* m_data { nullptr };
    size_t m_capacity { 0 };
    size_t m_size { 0 };
};
}; // namespace my_code

inline void string_test() {
    // --------------------------------------------
    {
        my_code::String a = "Hello World";
        std::cout << a << std::endl;
    }
}
#endif