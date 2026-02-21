#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Goodbye from plugin!\n");
}

const plugin_t plugin = {
    .name = "goodbye",
    .run  = run,
};
