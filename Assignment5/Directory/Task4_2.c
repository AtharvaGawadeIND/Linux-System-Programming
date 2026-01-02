#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

void CopyFileWithOffset(char *src , char *dest, int offest)
{
    int fd1 , fd2 ;
    char buffer[1024];
    ssize_t iRet;

    fd1 = open(src , O_RDONLY);
    if (fd1 == -1 )
    {
        printf("Source file error %s\n", strerror(errno));
        return;
    }

    fd2 = open(dest , O_WRONLY | O_CREAT | O_TRUNC , 0777);
    if(fd2 == -1)
    {
    
        printf ("Destination file is error : %s\n", strerror(errno));
            return;
    
    }



    
    while ( (iRet = pread(fd1 , buffer , sizeof(buffer),offest)) > 0 )
    {
        ssize_t wRet = write(fd2 , buffer , iRet);
        offest += iRet;

        if(wRet == -1)
        {
            printf("Write error %s\n", strerror(errno));
        }
    }

    if(iRet == -1)
    {
        printf("Read error : %s\n",strerror(errno));
    }
}

int main(int argc , char *argv[])
{

    int offset = atoi(argv[3]);

    CopyFileWithOffest(argv[1], argv[2],offset);
    return 0 ; 
}
