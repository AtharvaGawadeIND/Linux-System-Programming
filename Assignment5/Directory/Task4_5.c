#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void DisplayFileReverse(char *fname)
{
    int fd;
    char ch;
    off_t size;

    fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        printf("File open error: %s\n", strerror(errno));
        return;
    }

    // Get file size by moving to end
    size = lseek(fd, 0, SEEK_END);

    // Read and display file in reverse order
    while (size > 0)
    {
        lseek(fd, --size, SEEK_SET);
        read(fd, &ch, 1);
        write(1, &ch, 1);   // stdout
    }

    close(fd);
}

int main(int argc, char *argv[])
{
    DisplayFileReverse(argv[1]);
    return 0;
}
