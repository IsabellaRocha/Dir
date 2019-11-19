#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    DIR *direct;
    if (argc > 1) {
        direct = opendir(argv[1]);
        if (errno == -1) {
            printf("Error: %s", strerror(errno));
            return 0;
        }
    }
    else {
        printf("Please enter a directory");
        return 0;
    }
    if (errno == -1) {
        printf("Error: %s", strerror(errno));
        return 0;
    }
    struct dirent* dir = readdir(direct);

    printf("Statistics for directory\n");

    struct stat n;
    int size;
    while (dir) {
        int error = stat(dir->d_name, &n);
        if (error == -1) {
            printf("Error: %s", strerror(errno));
            return 0;
        }
        else {
            size += n.st_size;
        }
        dir = readdir(direct);
    }
    printf("\nTotal Directory Size: %d Bytes\n", size);

    rewinddir(direct);
    dir = readdir(direct);

    printf("\nDirectories:\n");

    while (dir) {
        if(dir->d_type == DT_DIR) {
            printf("\t%s\n", dir->d_name);
        }
        dir = readdir(direct);
    }
    rewinddir(direct);
    dir = readdir(direct);

    printf("\nRegular Files:\n");

    while (dir) {
        if(dir->d_type != DT_DIR) {
            printf("\t%s\n", dir->d_name);
        }
        dir = readdir(direct);
    }
    closedir(direct);
    return 0;
}
