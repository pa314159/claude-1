CC     = gcc
CFLAGS = -Wall -Wextra -std=c17

TARGET  = main
TEST    = test_plugin
PLUGINS = plugins/hello.so plugins/goodbye.so

all: $(TARGET) $(PLUGINS)

$(TARGET): main.c loader.c loader.h plugin.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c loader.c -ldl

$(TEST): plugins/test.c loader.c loader.h plugin.h
	$(CC) $(CFLAGS) -o $(TEST) plugins/test.c loader.c -ldl

test: $(TEST) $(PLUGINS)
	./$(TEST)

plugins/hello.so: plugins/hello.c plugin.h | plugins
	$(CC) $(CFLAGS) -I. -shared -fPIC -o $@ plugins/hello.c

plugins/goodbye.so: plugins/goodbye.c plugin.h | plugins
	$(CC) $(CFLAGS) -I. -shared -fPIC -o $@ plugins/goodbye.c

plugins:
	mkdir -p plugins

clean:
	rm -f $(TARGET) $(TEST) $(PLUGINS)
	rmdir plugins 2>/dev/null || true

.PHONY: all test clean plugins
