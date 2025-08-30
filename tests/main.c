#include <test.h>
#include <stdio.h>

int main(void) {
    test_context_t context;

    test_initialize(&context);
    test_load(&context, test_version_VERSION_A);

    if (context.result == test_result_FAILURE) {
        fprintf(stderr, "Could not load shared library file\n");
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        test_tick(&context);
        printf("%d ", test_foo(&context));
    }

    printf("\n");

    test_load(&context, test_version_VERSION_B);

    if (context.result == test_result_FAILURE) {
        fprintf(stderr, "Could not reload shared library file\n");
        return 1;
    }

    for (int i = 0; i < 20; i++) {
        test_tick(&context);
        printf("%d ", test_foo(&context));
    }

    printf("\n");

    test_unload(&context);
    test_terminate(&context);

    return 0;
}