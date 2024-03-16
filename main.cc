#include <iostream>


int main() {
    int a = 1;
    int&& b = std::move(a);
    std::cout << &a <<  ' ' << &b << std::endl;
}