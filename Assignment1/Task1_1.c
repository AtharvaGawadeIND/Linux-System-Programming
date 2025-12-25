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
//  Function name : OpenFileInMode
//  Description   : Accepts filename and mode (R,W,RW,A) from user 
//                : Converts mode in flags(O_RDONLY, O_WRONLY,O_RDWR,O_APPEND | O_CREAT).
//                : Open file accordingly and display fd.
//  Input         : Character array
//  Output        : File descriptor or error message
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void OpenFileInMode(char filename[], char mode[])
{
    int fd = 0;

    fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror("Error in opening the file");
    }
    else
    {
        printf("File opened successfully\n");
        printf("File Descriptor of the file is : %d\n", fd);

        close(fd);
    }
} // End of OpenFile

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char filename[101];

    printf("Enter the file name : \n");
    scanf("%s", filename);

    OpenFile(filename);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases successfully handled by the application
//
//  Input :
//  Enter the file name :
//  data.txt
//
//  Output :
//  File opened successfully
//  File Descriptor of the file is : 3
//
//  Input :
//  Enter the file name : 
//  Atharva.c 
//  
//  Output:
//  Error in opening the file: No such file or directory
//
/////////////////////////////////////////////////////////////////////////////////////////////////
