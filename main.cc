#include "src/demo/epoll_demo.h"

int main() {
    Result<std::string, int> a("hello");
    if (a.is_ok()) {
        std::cout << a.value() << std::endl;
    }
    Result<std::string, int> b(1);
    std::cout << b.error() << std::endl;
}