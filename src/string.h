#ifndef MY_CODE_STRING_H
#define MY_CODE_STRING_H

namespace my_code {
class String {
public:
    String() = default;
    String(int num, char a);
    
    String(const String& num);
    String(String&& rhs);

    String& operator=(const String& val);
    
    String& operator=(String&& rhs);

    ~String();

private:
    char* m_ptr { nullptr };
    int m_len { 0 };
};
}; // namespace my_code
#endif