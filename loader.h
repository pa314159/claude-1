#ifndef LOADER_H
#define LOADER_H

int  load_plugin(const char *path);
void load_plugins_from_dir(const char *dir);
void list_plugins(const char *dir);

#endif
