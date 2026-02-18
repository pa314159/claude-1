#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>
#include "plugin.h"
#include "loader.h"

int load_plugin(const char *path) {
    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen: %s\n", dlerror());
        return -1;
    }

    Plugin *p = dlsym(handle, "plugin");
    if (!p) {
        fprintf(stderr, "dlsym: %s\n", dlerror());
        dlclose(handle);
        return -1;
    }

    printf("Loaded plugin: %s\n", p->name);
    p->run();
    dlclose(handle);
    return 0;
}

void load_plugins_from_dir(const char *dir) {
    DIR *d = opendir(dir);
    if (!d) {
        fprintf(stderr, "opendir: cannot open '%s'\n", dir);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        const char *name = entry->d_name;
        size_t len = strlen(name);
        if (len < 4 || strcmp(name + len - 3, ".so") != 0)
            continue;

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir, name);
        load_plugin(path);
    }

    closedir(d);
}
