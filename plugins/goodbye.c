#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Goodbye from plugin!\n");
}

plugin_t plugin = {
    .name = "goodbye",
    .run  = run,
};
