#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>

int main() {
    DIR *direct = opendir("DIR");
    struct dirent* dir;

    printf("Statistics for directory\n");

    struct stat n;
    int size;
    while (direct) {
        dir = readdir(direct);
        if (dir->d_type != DT_DIR) {
            int error = stat(dir, &n);
            if (error == -1) {
                printf("Error: %s", strerror(errno));
                return 0;
            }
            else {
                size += n.st_size;
            }
        }
    }
    printf("\nTotal Directory Size: %d Bytes\n", size);
    rewinddir(direct);
    printf("\nDirectories:\n");
    while (direct) {
        dir = readdir(direct);
        if(dir->d_type == DT_DIR) {
            printf("\t%s\n", dir->d_name);
        }
    }
    rewinddir(direct);
    printf("\nRegular Files:\n");
    while (direct) {
        dir = readdir(direct);
        if(dir->d_type != DT_DIR) {
            printf("\t%s\n", dir->d_name);
        }
    }
    closedir(dir);
    return 0;
}
