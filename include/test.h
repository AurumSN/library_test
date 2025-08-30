#ifndef __TEST_H__
#define __TEST_H__

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum test_version {
    test_version_NONE,
    test_version_VERSION_A,
    test_version_VERSION_B
} test_version_t;

typedef enum test_result {
    test_result_SUCCESS,
    test_result_FAILURE
} test_result_t;

typedef struct test_context test_context_t;

typedef int (*test_foo_t)(test_context_t *);

typedef void (*test_tick_t)(test_context_t *);

struct test_context {
    test_version_t version;
    test_result_t result;
    struct {
        unsigned long long tick;
    } shared;
    void *specific;

#ifdef _WIN32
    HMODULE dlhandle;
#else
    void *dlhandle
#endif
    test_foo_t foo;
    test_tick_t tick;
};

void test_initialize(test_context_t *context);
void test_terminate(test_context_t *context);

void test_load(test_context_t *context, test_version_t new_version);
void test_unload(test_context_t *context);

int test_foo(test_context_t *context);
void test_tick(test_context_t *context);

#ifdef __cplusplus
}
#endif

#endif