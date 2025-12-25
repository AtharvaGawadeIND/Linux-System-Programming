/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : DisplayFileContent
//  Description   : Opens a file, reads its complete content using read()
//                  system call, prints it on console and displays total
//                  number of bytes read.
//  Input         : File name
//  Output        : File content and total bytes read
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 110

void DisplayFileContent(char filename[])
{
    int fd = 0;
    char buffer[BUF_SIZE];
    int bytesRead = 0;
    int totalBytes = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    while ((bytesRead = read(fd, buffer, BUF_SIZE)) > 0)
    {
        write(1, buffer, bytesRead);
        totalBytes += bytesRead;
    }

    if (bytesRead == -1)
    {
        perror("read");
    }

    printf("\nTotal bytes read : %d\n", totalBytes);

    close(fd);
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char filename[100];

    printf("Enter file name : \n");
    scanf("%s", filename);

    DisplayFileContent(filename);

    return 0;
}

//
/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test application successfully handled by the application
//
//  Input:
//  Enter file name :
//  Demo.txt
//  Output:
//  India is my Country
//
//  Total bytes read : 21
//
//  ------------------------------------------------
//
//  Input:
//  Enter file name :
//  Atharva.c
//  Output:
//  open: No such file or directory
//
///////////////////////////////////////////////////////////////////////////////////////////////