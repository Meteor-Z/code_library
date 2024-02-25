#include <bits/stdc++.h>

struct Node {
    Node(int a) : a { std::make_unique<int>(a) } {}
    ~Node() = default;

    std::shared_ptr<int> a {};
};
int main() { Node a(1); 
    std::cout << *a.a.get() << std::endl;
}