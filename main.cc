#include <bits/stdc++.h>

struct Node {
    Node() { std::cout << "构造函数" << std::endl; }
    ~Node() { std::cout << "析构函数" << std::endl; }
    Node(const Node&) { std::cout << "赋值构造" << std::endl; }
    Node(Node&&) { std::cout << "移动构造" << std::endl; }
    Node& operator=(const Node&) {
        std::cout << "拷贝复制" << std::endl;
        return *this;
    }
    Node& operator=(Node&&) {
        std::cout << "移动复制" << std::endl;
        return *this;
    }
};
int main() {

    Node a;
    std::cout << &a << std::endl;

    Node b = std::move(a);
    Node&& c = std::move(a);
    std::cout << &b << std::endl;
    std::cout << &c << std::endl;
}
