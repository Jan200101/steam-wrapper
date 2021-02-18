#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "common.h"

#ifndef _WIN32
struct stat getStat(const char* path)
{
    // fill with 0s by default in the case stat fails
    struct stat sb = {0};

    // the return value signifies if stat failes (e.g. file not found)
    // unimportant for us if it fails it won't touch sb
    stat(path, &sb);

    return sb;
}
#endif

int isExe(const char* path)
{
#ifdef _WIN32
    // using GetBinaryTypeA would be a saner solution
    size_t pathlen = strlen(path);

    return strncmp(path + (pathlen - strlen(EXE)), EXE, strlen(EXE)+1) == 0;
#else
    struct stat sb = getStat(path);

    return (sb.st_mode & S_IXUSR) != 0;
#endif
}
