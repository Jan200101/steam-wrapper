#ifndef COMMON_H
#define COMMON_H

#ifdef __GNUC__
#define UNUSED __attribute__((__unused__))
#else
#define UNUSED
#endif

#ifdef _WIN32
#define EXE ".exe"
#define SEPERATOR '\\'
#else
#define EXE
#define SEPERATOR '/'
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct stat getStat(const char* path);
int isFile(const char* path);
int isDir(const char* path);
int isExe(const char* path);

int removeDir(const char *path);

#ifdef __cplusplus
}
#endif

#endif