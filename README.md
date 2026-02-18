# Plugin Loader

A minimal C plugin system using dynamic loading (`dlopen`/`dlsym`).

## Structure

```
.
├── main.c              # Entry point
├── loader.c/h          # Plugin loading logic
├── plugin.h            # Plugin interface
├── hello_plugin.c      # Example plugin
├── goodbye_plugin.c    # Example plugin
├── test_plugin.c       # Unit tests
└── Makefile
```

## Plugin Interface

Each plugin is a shared library that exports a single `Plugin` symbol:

```c
typedef struct {
    const char *name;
    void (*run)(void);
} Plugin;
```

## Build

```sh
make        # build main and plugins
make test   # build and run unit tests
make clean  # remove build artifacts
```

## Usage

```sh
./main               # load all plugins from ./plugins/
./main hello         # load ./plugins/hello_plugin.so
./main goodbye       # load ./plugins/goodbye_plugin.so
```

## Adding a Plugin

1. Create `myplugin_plugin.c`:

```c
#include <stdio.h>
#include "plugin.h"

static void run(void) {
    printf("Hello from myplugin!\n");
}

Plugin plugin = {
    .name = "myplugin",
    .run  = run,
};
```

2. Add to `Makefile`:

```makefile
plugins/myplugin_plugin.so: myplugin_plugin.c plugin.h | plugins
    $(CC) $(CFLAGS) -shared -fPIC -o $@ myplugin_plugin.c
```

3. Add to `PLUGINS` in the Makefile, then run `make`.
