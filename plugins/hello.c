#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Hello from plugin!\n");
}

const plugin_t plugin = {
    .name = "hello",
    .run  = run,
};
