#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>
#include <limits.h>
#include "plugin.h"
#include "loader.h"

int load_plugin(const char *path) {
    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "dlopen: %s\n", dlerror());
        return -1;
    }

    dlerror(); /* clear any previous error before dlsym */
    const plugin_t *p = dlsym(handle, "plugin");
    const char *err = dlerror(); /* NULL on success */
    if (err) {
        fprintf(stderr, "dlsym: %s\n", err);
        dlclose(handle);
        return -1;
    }

    printf("Loaded plugin: %s\n", p->name);
    p->run();
    dlclose(handle);
    return 0;
}

typedef void (*so_cb_t)(const char *path);

static void foreach_so(const char *dir, so_cb_t cb) {
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

        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", dir, name);
        cb(path);
    }

    closedir(d);
}

static void load_one(const char *path) { load_plugin(path); }

void load_plugins_from_dir(const char *dir) {
    foreach_so(dir, load_one);
}

static void print_name(const char *path) {
    void *handle = dlopen(path, RTLD_LAZY);
    if (!handle) return;

    dlerror(); /* clear any previous error before dlsym */
    const plugin_t *p = dlsym(handle, "plugin");
    if (!dlerror() && p) /* dlerror() returns NULL if dlsym succeeded */
        printf("%s\n", p->name);

    dlclose(handle);
}

void list_plugins(const char *dir) {
    foreach_so(dir, print_name);
}
