#include <iostream>
#include "template/fibonacci.h"

int main() {
    std::cout << Fib<4>::value << std::endl;
}