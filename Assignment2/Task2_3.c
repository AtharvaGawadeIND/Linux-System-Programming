/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : ListAllFiles
//  Description   : Traverses the given directory and prints names of all
//                  files present in it, skipping "." and ".." entries.
//  Input         : Directory name
//  Output        : File names
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void ListAllFiles(char dirname[])
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    printf("\nFiles in directory:\n");
    

    while ((entry = readdir(dp)) != NULL)
    {
        
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        printf("%s\n", entry->d_name);
    }

    closedir(dp);
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

    ListAllFiles(dirname);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test application successfully handled by the application
//
//  Input :
//  Enter directory name :
//  Directory
//
//  Output :
//  Files in directory:
//  ---------------------
//  Demo.txt
//  LSP.txt
//  Sample.c
//
/////////////////////////////////////////////////////////////////////////////////////////////////
