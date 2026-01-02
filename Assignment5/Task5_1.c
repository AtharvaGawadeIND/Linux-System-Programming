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
#include <time.h>
#include <errno.h>

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : DisplayDirectory
//  Description     : Displays directory contents similar to ls command.
//                    Shows file name, type, permissions, size and
//                    last modified time. Skips . and .. entries.
//  Input           : Character Pointer
//  Output          : Void
//  Author          : Atharva Vinod Gawade
//  Date            : 2/12/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void DisplayDirectory(char *dirname)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char path[512];

    dp = opendir(dirname);
    if (dp == NULL)
    {
        printf("Directory open error : %s\n", strerror(errno));
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        
        if (strcmp(entry->d_name, ".") != 0)
        {
            if (strcmp(entry->d_name, "..") != 0)
            {
                
                snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

                if (stat(path, &sb) != -1)
                {
                    /* File Type */
                    if (S_ISREG(sb.st_mode))
                        printf("FILE ");
                    else if (S_ISDIR(sb.st_mode))
                        printf("DIR  ");
                    else if (S_ISLNK(sb.st_mode))
                        printf("LINK ");
                    else
                        printf("OTHER");

                    /* Permissions */
                    if (sb.st_mode & S_IRUSR) printf("r"); else printf("-");
                    if (sb.st_mode & S_IWUSR) printf("w"); else printf("-");
                    if (sb.st_mode & S_IXUSR) printf("x"); else printf("-");
                    if (sb.st_mode & S_IRGRP) printf("r"); else printf("-");
                    if (sb.st_mode & S_IWGRP) printf("w"); else printf("-");
                    if (sb.st_mode & S_IXGRP) printf("x"); else printf("-");
                    if (sb.st_mode & S_IROTH) printf("r"); else printf("-");
                    if (sb.st_mode & S_IWOTH) printf("w"); else printf("-");
                    if (sb.st_mode & S_IXOTH) printf("x"); else printf("-");


                
                    printf(" %8ld ", sb.st_size);

                    
                    
                    printf("%s", ctime(&sb.st_mtime));


                    
                    printf(" %s\n", entry->d_name);
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
    DisplayDirectory(argv[1]);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases handled successfully by the application
//
//  Input  : ./task5_1 "Directory " (commandline argument)
//  Output :    
//  FILE rw-rw-r--      693 Fri Jan  2 20:47:44 2026
//  Task4_5.c
//  FILE rw-rw-r--     1060 Fri Jan  2 20:45:20 2026
//   Task4_4.c
//  FILE rw-rw-r--     2027 Fri Jan  2 21:04:46 2026
//   Task4_3.c
//  FILE rw-rw-r--       53 Fri Jan  2 11:29:59 2026
//   sources.txt
//  FILE rw-rw-r--        1 Fri Jan  2 19:57:27 2026
//   Destination.txt
//  FILE rw-rw-r--     1058 Fri Jan  2 20:25:15 2026
//  Task4_2.c
//
///////////////////////////////////////////////////////////////////////////////////////
