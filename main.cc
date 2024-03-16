#include <iostream>
#include <memory>
#include "Shared_ptr.h"

struct Node {
    void show() { std::cout << 1 << std::endl; }
};
int main() {
    code::shared_ptr<Node> a = code::make_shared<Node>();
    std::shared_ptr<Node> b = std::make_shared<Node>();
    b->show();
    a->show();
}