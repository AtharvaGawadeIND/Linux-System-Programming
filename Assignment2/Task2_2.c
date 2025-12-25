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
//  Function Name : StringToFile
//  Description   : Accepts file name and string, appends the string
//                  to the file using write() system call and
//                  prints number of bytes written
//  Input         : File name, String
//  Output        : Bytes written
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void StringToFile(char filename[], char buffer[])
{
    int fd = 0;
    int bytesWritten = 0;

    fd = open(filename, O_WRONLY | O_CREAT , 0777);
    if (fd == -1)
    {
        perror("open");
        return;
    }

    bytesWritten = write(fd, buffer, strlen(buffer));

    if (bytesWritten == -1)
    {
        perror("write");
    }
    else
    {
        printf("Bytes written : %d\n", bytesWritten);
    }

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
    char buffer[200];

    printf("Enter file name : \n");
    scanf("%s", filename);

    printf("Enter string : \n");
    getchar();                       
    fgets(buffer, sizeof(buffer), stdin);

    StringToFile(filename, buffer);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Test cases succesfully handled by the applications
//
//  Input :
//  Enter file name :
//  Demo.txt
//  Enter string :
//  In the LSP batch
//
//  Output :
//  Bytes written : 17
//
//  Input :
//  Enter file name :
//  LSP.txt
//  Enter string :
//  Inside the LSP file
//
//  Output :
//  Bytes written : 20
//
/////////////////////////////////////////////////////////////////////////////////////////////////
