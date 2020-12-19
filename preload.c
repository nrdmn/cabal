#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

int execve(const char *path, char *const argv[], char *envp[])
{
    for (char **ptr = envp; *ptr != NULL; ptr++) {
        if (!strcmp(*ptr, "LD_PRELOAD=")) {
            (*ptr)[11] = 0;
        }
    }
    int (*orig)(const char *, char *const [], char *const []) = dlsym(RTLD_NEXT, "execve");
    return orig(path, argv, envp);
}

int open(const char *path, int oflag, int mode)
{
    int (*orig)(const char *, int, ...) = dlsym(RTLD_NEXT, "open");
    return orig(path, oflag, mode);
}

int fcntl(int fd, int cmd, void *ptr)
{
    int (*orig)(int, int, ...) = dlsym(RTLD_NEXT, "fcntl");
    return orig(fd, cmd, ptr);
}
