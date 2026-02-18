CC     = gcc
CFLAGS = -Wall -Wextra -std=c17

TARGET  = main
TEST    = test_plugin
PLUGINS = plugins/hello_plugin.so plugins/goodbye_plugin.so

all: $(TARGET) $(PLUGINS)

$(TARGET): main.c loader.c loader.h plugin.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c loader.c -ldl

$(TEST): test_plugin.c loader.c loader.h plugin.h
	$(CC) $(CFLAGS) -o $(TEST) test_plugin.c loader.c -ldl

test: $(TEST) $(PLUGINS)
	./$(TEST)

plugins/hello_plugin.so: hello_plugin.c plugin.h | plugins
	$(CC) $(CFLAGS) -shared -fPIC -o $@ hello_plugin.c

plugins/goodbye_plugin.so: goodbye_plugin.c plugin.h | plugins
	$(CC) $(CFLAGS) -shared -fPIC -o $@ goodbye_plugin.c

plugins:
	mkdir -p plugins

clean:
	rm -f $(TARGET) $(TEST) $(PLUGINS)
	rmdir plugins 2>/dev/null || true

.PHONY: all test clean plugins
