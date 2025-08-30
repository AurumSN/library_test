#include "test.h"

#include "test_impl.h"

#include <stdlib.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

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

#include <stdio.h>

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
#ifdef _WIN32
            context->dlhandle = LoadLibrary(TEXT(TEST_IMPL_A_FILEPATH));
#else
            context->dlhandle = dlopen(TEST_IMPL_A_FILEPATH, RTLD_LAZY);
#endif
            break;
        case test_version_VERSION_B:
#ifdef _WIN32
            context->dlhandle = LoadLibrary(TEXT(TEST_IMPL_B_FILEPATH));
#else
            context->dlhandle = dlopen(TEST_IMPL_B_FILEPATH, RTLD_LAZY);
#endif
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

#ifdef _WIN32
    context->foo = (test_foo_t)GetProcAddress(context->dlhandle, STRINGIFY(test_impl_foo));
    context->tick = (test_tick_t)GetProcAddress(context->dlhandle, STRINGIFY(test_impl_tick));
#else
    context->foo = (test_foo_t)dlsym(context->dlhandle, STRINGIFY(test_impl_foo));
    context->tick = (test_tick_t)dlsym(context->dlhandle, STRINGIFY(test_impl_tick));
#endif
}

void test_unload(test_context_t *context) {
    if (!context) {
        return;
    }

    if (context->dlhandle) {
        FreeLibrary(context->dlhandle);
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