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
//  Function Name : FindLargestFile
//  Description   : Traverses the given directory and finds the largest
//                  regular file present in it.
//  Input         : Directory name
//  Output        : Largest file name and its size
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void FindLargestFile(char dirname[])
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat fileStat;

    char largestFile[200] = "";
    long maxSize = 0;

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        char filepath[300];
        snprintf(filepath, sizeof(filepath), "%s/%s", dirname, entry->d_name);

        if (stat(filepath, &fileStat) == 0)
        {
            if (S_ISREG(fileStat.st_mode))
            {
                if (fileStat.st_size > maxSize)
                {
                    maxSize = fileStat.st_size;
                    strcpy(largestFile, entry->d_name);
             }
            }
    }
    }

    closedir(dp);

    if (maxSize > 0)
    {
        printf("\nLargest File Name : %s", largestFile);
        printf("\nFile Size : %d bytes\n", maxSize);
    }
    else
    {
        printf("No regular files found in directory.\n");
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

    printf("Enter directory name : \n");
    scanf("%s", dirname);

    FindLargestFile(dirname);

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
//  Largest File Name : Demo.txt
//   File Size : 21 bytes
//
/////////////////////////////////////////////////////////////////////////////////////////////////
