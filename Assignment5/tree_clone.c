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
//  Function Name   : DisplayTree
//  Description     : Displays directory structure in tree format.
//                    Does not follow symbolic link directories.
//  Input           : Character Pointer, Integer
//  Output          : Void
//  Author          : Atharva Vinod Gawade
//  Date            : 2/12/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void DisplayTree(char *path, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char fullpath[512];
    int iCnt;

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
                    
                    
                    for (iCnt = 0; iCnt < depth; iCnt++)
                    {
                        printf("    ");
                    }

                    if (S_ISLNK(sb.st_mode))
                    {
                        printf("[L] %s\n", entry->d_name);
                    }
                    else if (S_ISDIR(sb.st_mode))
                    {
                        printf("[D] %s/\n", entry->d_name);
                        DisplayTree(fullpath, depth + 1);
                    }
                    else if (S_ISREG(sb.st_mode))
                    {
                        printf("[F] %s\n", entry->d_name);
                    }
                    else
                    {
                        printf("[?] %s\n", entry->d_name);
                    }
                }
            }
        }
    }

    closedir(dp);
}


///////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function for the application
//
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    printf("[D] %s/\n", argv[1]);
    DisplayTree(argv[1], 1);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases handled successfully by the application
//
//  Input  : ./task5_2 "Directory "  (commandline argument)
//
//  Output : [D] Directory /
//   [F] Task4_5.c
//    [F] Task4_4.c
//    [F] Task4_3.c
//    [F] sources.txt
//    [F] Destination.txt
//    [F] Task4_2.c
//
///////////////////////////////////////////////////////////////////////////////////////
