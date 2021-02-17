#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "common.h"

struct stat getStat(const char* path)
{
    // fill with 0s by default in the case stat fails
    struct stat sb = {0};

    // the return value signifies if stat failes (e.g. file not found)
    // unimportant for us if it fails it won't touch sb
    stat(path, &sb);

    return sb;
}

int isFile(const char* path)
{
    struct stat sb = getStat(path);

    return S_ISREG(sb.st_mode)
#ifndef _WIN32
           || S_ISLNK(sb.st_mode);
#endif
           ;
}

int isDir(const char* path)
{
    struct stat sb = getStat(path);

    return S_ISDIR(sb.st_mode)
#ifndef _WIN32
           || S_ISLNK(sb.st_mode)
#endif
           ;
}

int isExe(const char* path)
{
#ifdef _WIN32
    size_t pathlen = strlen(path);

    return strncmp(path + (pathlen - strlen(EXE)), EXE, strlen(EXE)+1) == 0;
#else
    struct stat sb = getStat(path);

    return (sb.st_mode & S_IXUSR) != 0;
#endif
}

int removeDir(const char *path)
{
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;

    if (d) {
        struct dirent *p;

        r = 0;
        while (!r && (p=readdir(d))) {
            char *buf;
            size_t len;

            // Skip the names "." and ".." as we don't want to recurse on them.
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
                continue;

            len = path_len + strlen(p->d_name) + 2; 
            buf = malloc(len);

            if (buf) {
                struct stat statbuf = {0};

                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode))
                        r = removeDir(buf);
#ifndef _WIN32
                    else if (S_ISLNK(statbuf.st_mode))
                        r = unlink(buf);
#endif
                    else
                        r = remove(buf);
                }
                else // it is very likely that we found a dangling symlink which is not detected by stat
                {
                    r = unlink(buf);
                }
                free(buf);
            }
        }
        closedir(d);
    }

    if (!r)
        r = rmdir(path);

    return r;
}