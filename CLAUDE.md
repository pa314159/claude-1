# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Test

```bash
cmake -B build          # Configure
cmake --build build     # Build all targets
ctest --test-dir build  # Run all tests
```

To run a single test binary directly:
```bash
./build/test_plugin
```

## Architecture

This is a minimal C plugin system using POSIX `dlopen`/`dlsym` for dynamic library loading (C17, `-Wall -Wextra`).

**Plugin contract** (`plugin.h`): Every plugin must export a `const plugin_t plugin` symbol with a `name` string and a `run` function pointer.

**Loader** (`loader.c`/`loader.h`): Provides three functions:
- `load_plugin(path)` — opens one `.so`, resolves the `plugin` symbol, calls `plugin->run()`, then closes it
- `load_plugins_from_dir(dir)` — calls `load_plugin` for every `.so` in a directory
- `list_plugins(dir)` — same directory scan but only prints names, no execution

The internal `foreach_so(dir, callback, data)` helper does the directory traversal (`opendir`/`readdir`) and is reused by both the load and list paths.

**`dlerror()` pattern** used throughout: clear error state with `dlerror()` before calling `dlsym()`, then check `dlerror()` again after — not the return value of `dlsym()` itself.

**Main** (`main.c`): CLI via `getopt_long`. No args runs all plugins from `./plugins`; a plugin name loads `./plugins/{name}.so`; `-l`/`--list` lists without executing.

**Adding a plugin**: Create `plugins/foo.c` exporting `const plugin_t plugin = { "foo", run_fn }`, then add a `add_library(foo SHARED plugins/foo.c)` block to `CMakeLists.txt` mirroring the existing `hello`/`goodbye` targets.
