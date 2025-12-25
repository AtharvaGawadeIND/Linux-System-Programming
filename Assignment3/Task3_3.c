/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : MoveAllFiles
//  Description   : Moves all regular files from source directory to
//                  destination directory. Uses rename() if possible,
//                  otherwise performs copy and delete.
//  Input         : Source directory name, Destination directory name
//  Output        : Count of moved files
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 1024

void MoveAllFiles(char srcDir[], char destDir[])
{
    DIR *dp = NULL;
    struct dirent *entry = NULL;
    struct stat sb;
    int count = 0;

    dp = opendir(srcDir);
    if (dp == NULL)
    {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        char srcPath[1024];
        char destPath[1024];

        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0)
        {
            snprintf(srcPath, sizeof(srcPath), "%s/%s", srcDir, entry->d_name);
            snprintf(destPath, sizeof(destPath), "%s/%s", destDir, entry->d_name);

            if (stat(srcPath, &sb) == 0)
            {
                if (S_ISREG(sb.st_mode))
                {
                    if (rename(srcPath, destPath) == 0)
                    {
                        count++;
                    }
                    else
                    {
                        int fdSrc = open(srcPath, O_RDONLY);
                        int fdDest = open(destPath,
                                          O_WRONLY | O_CREAT | O_TRUNC,
                                          sb.st_mode);

                        if (fdSrc != -1 && fdDest != -1)
                        {
                            char buffer[BUF_SIZE];
                            int bytesRead = 0;

                            while ((bytesRead = read(fdSrc, buffer, BUF_SIZE)) > 0)
                            {
                                write(fdDest, buffer, bytesRead);
                            }

                            close(fdSrc);
                            close(fdDest);

                            unlink(srcPath);
                            count++;
                        }
                        else
                        {
                            if (fdSrc != -1) close(fdSrc);
                            if (fdDest != -1) close(fdDest);
                        }
                    }
                }
            }
        }
    }

    closedir(dp);

    printf("Total files moved : %d\n", count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char srcDir[100];
    char destDir[100];

    printf("Enter source directory name : \n");
    scanf("%s", srcDir);

    printf("Enter destination directory name : \n");
    scanf("%s", destDir);

    MoveAllFiles(srcDir, destDir);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test application successfully handled by the application
//
//  Input :
//  Enter source directory name :
//  SrcDir
//  Enter destination directory name :
//  DestDir
//
//  Output :
//  Total files moved : 3
//
/////////////////////////////////////////////////////////////////////////////////////////////////
