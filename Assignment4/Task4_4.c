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
//  Function Name   : MergeFiles
//  Description     : Merges multiple input files into a single output file
//                    in the order specified.
//  Input           : Character Pointer, Character Pointer Array, Integer
//  Output          : Void
//  Author          : Atharva Vinod Gawade
//  Date            : 2/12/2026
//
///////////////////////////////////////////////////////////////////////////////////////

void MergeFiles(char *outfile, char *files[], int count)
{
    int fdOut, fdIn;
    char buffer[1024];
    ssize_t iRet;
    int i;

    fdOut = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fdOut == -1)
    {
        printf("Output file error : %s\n", strerror(errno));
        return;
    }

    for (i = 0; i < count; i++)
    {
        fdIn = open(files[i], O_RDONLY);
        if (fdIn == -1)
        {
            printf("Input file error (%s) : %s\n", files[i], strerror(errno));
        }
        else
        {
            while ((iRet = read(fdIn, buffer, sizeof(buffer))) > 0)
            {
                write(fdOut, buffer, iRet);
            }

            if (iRet == -1)
            {
                printf("Read error (%s) : %s\n", files[i], strerror(errno));
            }

            close(fdIn);
        }
    }

    close(fdOut);
}

//  Time Complexity : O(N)

///////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function for the application
//
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    
    MergeFiles(argv[1], &argv[2], argc - 2);

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases handled successfully by the application
//
//  Input  :  ./myexe Destination.txt Dest2.txt sources.txt  (on Terminal command Line arguments)
//  Output :   Destination file has contents of both Dest2 and sources.txt
//
///////////////////////////////////////////////////////////////////////////////////////
