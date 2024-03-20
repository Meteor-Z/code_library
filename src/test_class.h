#ifndef MY_CODE_TEST_CLASS_H
#define MY_CODE_TEST_CLASS_H

#include <iostream>

namespace code {
struct Node {
    Node() { std::cout << "构造函数" << std::endl; }
    ~Node() { std::cout << "析构函数" << std::endl; }
    Node(const Node&) { std::cout << "复制构造" << std::endl; }
    Node(Node&&) { std::cout << "移动构造" << std::endl; }
    Node& operator=(const Node&) { std::cout << "拷贝复制" << std::endl; }
    Node& operator=(Node&&) { std::cout << "移动复制" << std::endl; }
};
} // namespace code
#endif