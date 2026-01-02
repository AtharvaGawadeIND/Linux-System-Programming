#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void CopyFileUsingPreadPwrite(char *src, char *dest)
{
    int fd1, fd2;
    char buffer[1024];
    ssize_t iRet;
    off_t offset = 0;

    fd1 = open(src, O_RDONLY);
    if (fd1 == -1)
    {
        printf("Source file error: %s\n", strerror(errno));
        return;
    }

    fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd2 == -1)
    {
        printf("Destination file error: %s\n", strerror(errno));
        close(fd1);
        return;
    }

    while ((iRet = pread(fd1, buffer, sizeof(buffer), offset)) > 0)
    {
        if (pwrite(fd2, buffer, iRet, offset) == -1)
        {
            printf("Write error: %s\n", strerror(errno));
            break;
        }
        offset += iRet;
    }

    if (iRet == -1)
    {
        printf("Read error: %s\n", strerror(errno));
    }

    close(fd1);
    close(fd2);
}

int main(int argc, char *argv[])
{
    CopyFileUsingPreadPwrite(argv[1], argv[2]);
    return 0;
}
