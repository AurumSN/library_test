#include "test_impl.h"

#ifndef VERSION_B

int test_impl_foo(test_context_t *context) {
    return context->shared.tick % 128;
}

void test_impl_tick(test_context_t *context) {
    context->shared.tick += 10;
}

#else

int test_impl_foo(test_context_t *context) {
    return -(int)(context->shared.tick % 64);
}

void test_impl_tick(test_context_t *context) {
    context->shared.tick += 5;
}

#endif