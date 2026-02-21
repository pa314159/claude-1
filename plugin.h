#ifndef PLUGIN_H
#define PLUGIN_H

typedef struct {
    const char *name;
    void (*run)(void);
} plugin_t;

#endif
