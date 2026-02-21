#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Hello from plugin!\n");
}

plugin_t plugin = {
    .name = "hello",
    .run  = run,
};
