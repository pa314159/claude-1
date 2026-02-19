#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Goodbye from plugin!\n");
}

Plugin plugin = {
    .name = "goodbye",
    .run  = run,
};
