#include <array>
#include <iostream>

int main() {
    std::array<int, 3> a { 1, 2, 3 };
    a.fill(3);
    std::cout << a[0] << ' ' << a[1] << ' ' << a[2] << std::endl;

}