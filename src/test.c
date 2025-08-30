#include "test.h"

#include "test_impl.h"

#include <stdlib.h>
#include <dlfcn.h>

#ifndef TEST_IMPL_A_FILEPATH
#ifdef _WIN32
#define TEST_IMPL_A_FILEPATH "./libtest_impl_a.dll"
#else
#define TEST_IMPL_A_FILEPATH "./libtest_impl_a.so"
#endif
#endif

#ifndef TEST_IMPL_B_FILEPATH
#ifdef _WIN32
#define TEST_IMPL_B_FILEPATH "./libtest_impl_b.dll"
#else
#define TEST_IMPL_B_FILEPATH "./libtest_impl_b.so"
#endif
#endif

#ifndef STRINGIFY
#define STRINGIFY(X) #X
#endif

void test_initialize(test_context_t *context) {
    if (!context) {
        return;
    }

    context->shared.tick = 0;

    context->version = test_version_NONE;
    context->result = test_result_SUCCESS;
    context->specific = NULL;
    context->dlhandle = NULL;
    context->foo = NULL;
    context->tick = NULL;
}

void test_terminate(test_context_t *context) {
    if (!context) {
        return;
    }

    context->shared.tick = 0;
}

void test_load(test_context_t *context, test_version_t new_version) {
    if (!context) {
        return;
    }

    test_unload(context);

    switch (new_version) {
        case test_version_VERSION_A:
            context->dlhandle = dlopen(TEST_IMPL_A_FILEPATH, RTLD_LAZY);
            break;
        case test_version_VERSION_B:
            context->dlhandle = dlopen(TEST_IMPL_B_FILEPATH, RTLD_LAZY);
            break;
        default:
            return;
    }

    if (!context->dlhandle) {
        context->result = test_result_FAILURE;
        return;
    }

    context->version = new_version;
    context->specific = NULL;

    context->foo = (test_foo_t)dlsym(context->dlhandle, STRINGIFY(test_impl_foo));
    context->tick = (test_tick_t)dlsym(context->dlhandle, STRINGIFY(test_impl_tick));
}

void test_unload(test_context_t *context) {
    if (!context) {
        return;
    }

    if (context->dlhandle) {
        dlclose(context->dlhandle);
    }

    if (context->specific) {
        free(context->specific);
    }

    context->version = test_version_NONE;
    context->result = test_result_SUCCESS;
    context->specific = NULL;
    context->dlhandle = NULL;
    context->foo = NULL;
    context->tick = NULL;
}

int test_foo(test_context_t *context) {
    if (!context->foo || context->result == test_result_FAILURE) {
        context->result = test_result_FAILURE;
        return 0;
    }

    return context->foo(context);
}

void test_tick(test_context_t *context) {
    if (!context->tick || context->result == test_result_FAILURE) {
        context->result = test_result_FAILURE;
        return;
    }

    context->tick(context);
}