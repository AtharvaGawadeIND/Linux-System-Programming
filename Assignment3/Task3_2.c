/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CheckFilePresent
//  Description   : Checks whether the given file is present in the
//                  specified directory and prints its absolute path.
//  Input         : Directory name, File name
//  Output        : Absolute path if file is found
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void CheckFilePresent(char dirname[], char filename[])
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    int found = 0;

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (strcmp(entry->d_name, filename) == 0)
        {
            char fullpath[1024];
            char abspath[1024];

            snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, filename);

            if (realpath(fullpath, abspath) != NULL)
            {
                printf("\nFile found ");
                printf("\nAbsolute Path : %s\n", abspath);
            }
            else
            {
                perror("realpath");
            }

            found = 1;
            break;
        }
    }

    closedir(dp);

    if (found == 0)
    {
        printf("File not found in the given directory.\n");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char dirname[100];
    char filename[100];

    printf("Enter directory name : \n");
    scanf("%s", dirname);

    printf("Enter file name : \n");
    scanf("%s", filename);

    CheckFilePresent(dirname, filename);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test application successfully handled by the application
//
//  Input:
//  Enter directory name : 
//  Directory
//  Enter file name : 
//  Demo.txt
//
//  Output:
//  File found
//Absolute Path : /home/atharva-gawade/Desktop/LSP/Assignment3/Directory/Demo.txt
//
/////////////////////////////////////////////////////////////////////////////////////////////////
