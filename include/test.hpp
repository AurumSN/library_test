#ifndef __TEST_HPP__
#define __TEST_HPP__

#include "test.h"

#include <iostream>

namespace test {
    enum class version {
        A,
        B
    };

    class context {
        test_context_t m_context;

        context(const context &other) = delete;
        context& operator=(const context &other) = delete;

    public:
        context(std::nullptr_t = nullptr);
        context(test::version version);
        context(context &&other) noexcept;

        ~context();

        context& operator=(std::nullptr_t);
        context& operator=(test::version version);
        context& operator=(context &&other) noexcept;

        void load(test::version version);
        void unload();

        int foo();
        void tick();
    };
}

#endif