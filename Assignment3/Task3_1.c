/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CopyFile
//  Description   : Copies contents of source file into destination file
//                  using buffered read() and write() system calls.
//                  Preserves file permissions.
//  Input         : Source file name, Destination file name
//  Output        : File copied successfully
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 1024

void CopyFile(char src[], char dest[])
{
    int fdSrc = 0, fdDest = 0;
    int bytesRead = 0;
    char buffer[BUF_SIZE];
    struct stat sb;

    fdSrc = open(src, O_RDONLY);
    if (fdSrc == -1)
    {
        perror("open source");
        return;
    }


    if (stat(src, &sb) == -1)
    {
        perror("stat");
        close(fdSrc);
        return;
    }

    fdDest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, sb.st_mode);
    if (fdDest == -1)
    {
        perror("open destination");
        close(fdSrc);
        return;
    }

    while ((bytesRead = read(fdSrc, buffer, BUF_SIZE)) > 0)
    {
        write(fdDest, buffer, bytesRead);
    }

    if (bytesRead == -1)
    {
        perror("read");
    }
    chmod(dest, sb.st_mode);

    close(fdSrc);
    close(fdDest);

    printf("\nFile copied successfully.\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char src[100], dest[100];

    printf("Enter source file name : \n");
    scanf("%s", src);

    printf("Enter destination file name : \n");
    scanf("%s", dest);

    CopyFile(src, dest);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test application successfully handled by the application
//
//  Input :
//  Enter source file name :
//  AMEND.txt
//  Enter destination file name :
//  Copy.txt
//
//  Output :
//  File copied successfully.
//
/////////////////////////////////////////////////////////////////////////////////////////////////
