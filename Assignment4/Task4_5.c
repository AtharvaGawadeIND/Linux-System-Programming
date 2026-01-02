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
//  Function Name   : DisplayFileReverse
//  Description     : Displays the contents of a file in reverse order
//  Input           : Character Pointer
//  Output          : Void
//  Author          : Atharva Vinod Gawade
//  Date            : 2/12/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void DisplayFileReverse(char *fname)
{
    int fd;
    char ch;
    off_t size;

    fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        printf("File open error : %s\n", strerror(errno));
        return;
    }

    size = lseek(fd, 0, SEEK_END);

    while (size > 0)
    {
        lseek(fd, --size, SEEK_SET);
        read(fd, &ch, 1);
        write(1, &ch, 1);   
    }

    close(fd);
}

//  Time Complexity : O(N)

///////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function for the application
//
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    DisplayFileReverse(argv[1]);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases handled successfully by the application
//
//  Input  : ./Task4_5 Destination.txt  (on Terminal command Line arguments)
//
//  Output :  edoc xunil elpmas rof elif ecruos eht si siht
//  ,olleH
//
///////////////////////////////////////////////////////////////////////////////////////
