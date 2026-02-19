# Plugin Loader

A minimal C plugin system using dynamic loading (`dlopen`/`dlsym`). Built with [Claude](https://claude.ai/claude-code).

## Structure

```
.
├── main.c              # Entry point
├── loader.c/h          # Plugin loading logic
├── plugin.h            # Plugin interface
├── CMakeLists.txt
└── plugins/
    ├── hello.c         # Example plugin
    ├── goodbye.c       # Example plugin
    └── test.c          # Unit tests
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
cmake -B build
cmake --build build
ctest --test-dir build   # run unit tests
```

## Usage

```sh
./build/main             # load and run all plugins from ./build/plugins/
./build/main -l          # list available plugins without running them
./build/main --list      # same as -l
./build/main hello       # load and run ./build/plugins/hello.so
```

## Adding a Plugin

1. Create `plugins/myplugin.c`:

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

2. Add to `CMakeLists.txt`:

```cmake
add_library(myplugin SHARED plugins/myplugin.c)
set_target_properties(myplugin PROPERTIES
    PREFIX ""
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)
```

3. Rebuild with `cmake --build build`.
