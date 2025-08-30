#include <test.hpp>
#include <iostream>

int main(void) {
    test::context context;

    try {
        context = test::version::A;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        context.tick();
        std::cout << context.foo() << " ";
    }

    std::cout << std::endl;

    try {
        context = test::version::B;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        context.tick();
        std::cout << context.foo() << " ";
    }

    std::cout << std::endl;

    return 0;
}