#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int  TotalFiles = 0;
int TotalDirs  = 0;
int TotalSize = 0;

char LargestFile[256];
long long LargestSize = 0;

void DirectoryReport(char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char fullpath[512];

    /* Count directory when entered */
    TotalDirs++;

    dp = opendir(path);
    if (dp == NULL)
    {
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0)
        {
            if (strcmp(entry->d_name, "..") != 0)
            {
                snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

                if (lstat(fullpath, &sb) != -1)
                {
                    /* Regular file */
                    if (S_ISREG(sb.st_mode))
                    {
                        TotalFiles++;
                        TotalSize = TotalSize + sb.st_size;

                        if (sb.st_size > LargestSize)
                        {
                            LargestSize = sb.st_size;
                            strcpy(LargestFile, entry->d_name);
                        }
                    }
                    /* Directory */
                    else if (S_ISDIR(sb.st_mode))
                    {
                        DirectoryReport(fullpath);
                    }
                    /* Symbolic link */
                    else if (S_ISLNK(sb.st_mode))
                    {
                        /* Ignore symlink size */
                    }
                }
            }
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    DirectoryReport(argv[1]);

    printf("Files       : %ld\n", TotalFiles);
    printf("Directories : %ld\n", TotalDirs);
    printf("Total Size  : %lld bytes\n", TotalSize);
    printf("Largest     : %s (%lld bytes)\n", LargestFile, LargestSize);

    return 0;
}
