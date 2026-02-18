#include <stdio.h>
#include <string.h>
#include "loader.h"

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--list") == 0) {
        list_plugins("./plugins");
    } else if (argc > 1) {
        char path[1024];
        snprintf(path, sizeof(path), "./plugins/%s_plugin.so", argv[1]);
        load_plugin(path);
    } else {
        load_plugins_from_dir("./plugins");
    }
    return 0;
}
