/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : DeleteEmptyFiles
//  Description   : Traverses the given directory and deletes all empty
//                  regular files (size = 0 bytes).
//  Input         : Directory name
//  Output        : Names of deleted files and total count
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DeleteEmptyFiles(char dirname[])
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat sb;
    int count = 0;

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    printf("\nDeleted Files:\n");

    while ((entry = readdir(dp)) != NULL)
    {
        char filepath[1024];

        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

            if (stat(filepath, &sb) == 0)
            {
                if (S_ISREG(sb.st_mode) && sb.st_size == 0)
                {
                    if (unlink(filepath) == 0)
                    {
                        printf("%s\n", entry->d_name);
                        count++;
                    }
            }
            }
        }
 }

    closedir(dp);

    printf("\nTotal empty files deleted : %d\n", count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char dirname[100];

    printf("Enter directory name : \n");
    scanf("%s", dirname);

    DeleteEmptyFiles(dirname);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test application successfully handled by the application
//
//  Input :
//  Enter directory name :
//  SRC
//
//  Output :
//  Deleted Files:
//  Empty.c
//
//  Total empty files deleted : 1
//
/////////////////////////////////////////////////////////////////////////////////////////////////
