#include <stdio.h>
#include <assert.h>
#include "loader.h"

static int passed = 0;
static int failed = 0;

#define TEST(name, expr) do { \
    if (expr) { printf("PASS: %s\n", name); passed++; } \
    else       { printf("FAIL: %s\n", name); failed++; } \
} while (0)

int main(void) {
    TEST("load valid plugin (hello)",
         load_plugin("./plugins/hello.so") == 0);

    TEST("load valid plugin (goodbye)",
         load_plugin("./plugins/goodbye.so") == 0);

    TEST("load missing plugin returns -1",
         load_plugin("./plugins/nonexistent.so") == -1);

    TEST("load invalid path returns -1",
         load_plugin("./plugins/not_a_plugin.so") == -1);

    printf("\n%d passed, %d failed\n", passed, failed);
    return failed > 0 ? 1 : 0;
}
