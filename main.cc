#include <vector>

struct V : std::vector<V> { };

int main() {
    std::vector<V> a;
    a.emplace_back();
    a.swap(a.front());
}