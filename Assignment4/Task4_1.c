///////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
///////////////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name   : CopyFile
//  Description     : Copies contents of one file into another file
//  Input           : Character Pointer, Character Pointer
//  Output          : Void
//  Author          : Atharva Vinod Gawade
//  Date            : 1/12/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void CopyFile(char *src , char *dest)
{
    int fd1 , fd2;
    char buffer[201];
    ssize_t iRet;

    fd1 = open(src , O_RDONLY);
    if (fd1 == -1)
    {
        printf("Source file error : %s\n", strerror(errno));
        return;
    }

    fd2 = open(dest , O_WRONLY | O_CREAT | O_TRUNC , 0777);
    if (fd2 == -1)
    {
        printf("Destination file error : %s\n", strerror(errno));
        close(fd1);
        return;
    }

    while ((iRet = read(fd1 , buffer , sizeof(buffer))) > 0)
    {
        ssize_t wRet = write(fd2 , buffer , iRet);

        if (wRet == -1)
        {
            printf("Write error : %s\n", strerror(errno));
            break;
        }
    }

    if (iRet == -1)
    {
        printf("Read error : %s\n", strerror(errno));
    }

    close(fd1);
    close(fd2);
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function for the application
//
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc , char *argv[])
{
    CopyFile(argv[1], argv[2]);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases handled successfully by the application
//
//  Input  : (on Terminal command Line arguments)
//         : ./myeexe sources.txt Destination.txt

//
//  Output : Contents of sources.txt copied into Destination.txt
//
///////////////////////////////////////////////////////////////////////////////////////
