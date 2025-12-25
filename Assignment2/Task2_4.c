/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : ListFilesWithType
//  Description   : Traverses the given directory and prints each file
//                  along with its type using lstat() system call.
//  Input         : Directory name
//  Output        : File name and its type
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void ListFilesWithType(char dirname[])
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat sb;

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    printf("\nFile Name\t\tType\n");

    while ((entry = readdir(dp)) != NULL)
    {
        char path[4055];

        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (lstat(path, &sb) == -1)
        {
            perror("lstat");
        }
        else
        {
            printf("%-20s : ", entry->d_name);

            if (S_ISREG(sb.st_mode))
                printf("Regular File\n");
            else if (S_ISDIR(sb.st_mode))
                printf("Directory\n");
            else if (S_ISLNK(sb.st_mode))
                printf("Symbolic Link\n");
            else if (S_ISFIFO(sb.st_mode))
                printf("FIFO\n");
            else if (S_ISSOCK(sb.st_mode))
                printf("Socket\n");
            else if (S_ISCHR(sb.st_mode))
                printf("Character Device\n");
            else if (S_ISBLK(sb.st_mode))
                printf("Block Device\n");
            else
                printf("Unknown Type\n");
        }
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

    ListFilesWithType(dirname);

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
//  File Name            Type
//  LSP.txt              : Regular File
//  .                    : Directory
//  ..                   : Directory
//  Demo.txt             : Regular File
//
/////////////////////////////////////////////////////////////////////////////////////////////////
