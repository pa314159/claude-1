#include <stdio.h>
#include <getopt.h>
#include "loader.h"

static const struct option long_opts[] = {
    { "list", no_argument, NULL, 'l' },
    { NULL,   0,           NULL,  0  },
};

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt_long(argc, argv, "l", long_opts, NULL)) != -1) {
        switch (opt) {
            case 'l':
                list_plugins("./plugins");
                return 0;
            default:
                fprintf(stderr, "Usage: %s [-l|--list] [plugin]\n", argv[0]);
                return 1;
        }
    }

    if (optind < argc) {
        char path[1024];
        snprintf(path, sizeof(path), "./plugins/%s_plugin.so", argv[optind]);
        load_plugin(path);
    } else {
        load_plugins_from_dir("./plugins");
    }

    return 0;
}
