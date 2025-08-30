#include "test.hpp"

#include <utility>
#include <stdexcept>

namespace test {
    static test_version_t conversion(test::version version) {
        switch (version) {
            case test::version::A:
                return test_version_VERSION_A;
            case test::version::B:
                return test_version_VERSION_B;
            default:
                return test_version_NONE;
        }
    }

    context::context(std::nullptr_t) {
        test_initialize(&m_context);
    }

    context::context(test::version version) : context{} {
        load(version);
    }

    context::context(context &&other) noexcept : m_context{ std::exchange(other.m_context, {}) } {}

    context::~context() {
        unload();
        test_terminate(&m_context);
    }

    context& context::operator=(std::nullptr_t) {
        unload();

        return *this;
    }

    context& context::operator=(test::version version) {
        load(version);

        return *this;
    }

    context& context::operator=(context &&other) noexcept {
        if (this != &other) {
            std::swap(m_context, other.m_context);
        }

        return *this;
    }

    void context::load(test::version version) {
        test_load(&m_context, conversion(version));

        if (m_context.result == test_result_FAILURE) {
            throw std::runtime_error("Could not load shared library");
        }
    }

    void context::unload() {
        test_unload(&m_context);
    }

    int context::foo() {
        return test_foo(&m_context);
    }

    void context::tick() {
        test_tick(&m_context);
    }
}