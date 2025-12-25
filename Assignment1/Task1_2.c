/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : OpenFileInMode
//  Description   : Accepts file name and mode, converts mode to open() flags,
//                  opens file accordingly and displays file descriptor
//  Input         : Character array, Character array
//  Output        : File descriptor or error message
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void OpenFileInMode(char filename[], char mode[])
{
    int fd = 0;
    int flag = 0;

    if (strcmp(mode, "R") == 0)
    {
        flag = O_RDONLY;
    }
    else if (strcmp(mode, "W") == 0)
    {
        flag = O_WRONLY | O_CREAT | O_TRUNC;
    }
    else if (strcmp(mode, "RW") == 0)
    {
        flag = O_RDWR | O_CREAT;
    }
    else if (strcmp(mode, "A") == 0)
    {
        flag = O_WRONLY | O_APPEND | O_CREAT;
    }
    else
    {
        printf("Invalid mode\n");
        return;
    }

    fd = open(filename, flag, 0777);

    if (fd == -1)
    {
        perror("Error opening file");
    }
    else
    {
        printf("File opened successfully\n");
        printf("File Descriptor : %d\n", fd);
        close(fd);
    }
} // End of OpenFileInMode

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char filename[101];
    char mode[11];

    printf("Enter file name : \n");
    scanf("%s", filename);

    printf("Enter mode (R / W / RW / A) : \n");
    scanf("%s", mode);

    OpenFileInMode(filename, mode);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases successfully handled by the application
//
//  Input  :
//  Enter file name :
//  data.txt
//  Enter mode (R / W / RW / A) :
//  R
//
//  Output :
//  File opened successfully
//  File Descriptor : 3
//
/////////////////////////////////////////////////////////////////////////////////////////////////
