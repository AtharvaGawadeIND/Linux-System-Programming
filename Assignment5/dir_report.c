///////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
///////////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

///////////////////////////////////////////////////////////////////////////////////////
//
//  Global variables used by the application
//
///////////////////////////////////////////////////////////////////////////////////////

long TotalFiles = 0;
long TotalDirs  = 0;
long long TotalSize = 0;

char LargestFile[256];
long long LargestSize = 0;

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DirectoryReport
//  Description     : Travels directory structure and calculates
//                    total number of files, total number of directories,
//                    total size of regular files and largest file details.
//                    Symbolic link sizes are ignored.
//  Input           : Character Pointer
//  Output          : Void
//  Author          : Atharva Vinod Gawade
//  Date            : 2/12/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void DirectoryReport(char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char fullpath[512];

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
                
                    else if (S_ISDIR(sb.st_mode))
                    {
                        DirectoryReport(fullpath);
                    }
                
                    else if (S_ISLNK(sb.st_mode))
                    {
                
                    }
                }
            }
        }
    }

    closedir(dp);
}

//  Time Complexity : O(N)

///////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function for the application
//
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    DirectoryReport(argv[1]);

    printf("Files       : %ld\n", TotalFiles);
    printf("Directories : %ld\n", TotalDirs);
    printf("Total Size  : %lld bytes\n", TotalSize);
    printf("Largest     : %s (%lld bytes)\n", LargestFile, LargestSize);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases handled successfully by the application
//
//  Input  :  gcc Task5_3.c -o task5_3 (commandline argument)
//  Output : Files : 6
//  Directories : 1
//  Total Size  : 4892 bytes
//  Largest     : Task4_3.c (2027 bytes)
//
///////////////////////////////////////////////////////////////////////////////////////
