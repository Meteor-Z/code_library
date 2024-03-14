#ifndef MY_CODE_STRING_H
#define MY_CODE_STRING_H


namespace my_code {
class String {
public:
    friend bool operator<(const String& a, const String& b) {}

public:
    String(const char* str) {
        if (str == nullptr) {
            m_data = new char[1];
            m_data[0] = '\0';
            m_size = 0;
            m_capacity = 0;
        } else {
            m_size = std::strlen(str);
            m_data = new char[m_size + 1];
            std::strcpy(m_data, str);
            
        }
    }

    String(const String&& str)
        : m_data(str.m_data), m_capacity(str.m_capacity), m_size(str.m_size) {}

    
    String(String&& rhs) {
        m_data = rhs.m_data;
        rhs.m_data = nullptr;

        m_size = rhs.m_size;
        rhs.m_size = 0;

        m_capacity = rhs.m_capacity;
        rhs.m_capacity = 0;
    }

    ~String() {
        if (m_data) {
            delete[] m_data;
        }
    }

    

private:
    char* m_data { nullptr };
    size_t m_capacity { 0 };
    size_t m_size { 0 };
};
}; // namespace my_code
#endif