#ifndef __TEST_IMPL_H__
#define __TEST_IMPL_H__

#include "test.h"

#ifndef EXPORT
#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

EXPORT int test_impl_foo(test_context_t *context);

EXPORT void test_impl_tick(test_context_t *context);

#ifdef __cplusplus
}
#endif

#endif