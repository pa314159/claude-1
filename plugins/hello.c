#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Hello from plugin!\n");
}

Plugin plugin = {
    .name = "hello",
    .run  = run,
};
