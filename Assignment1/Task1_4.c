/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : DisplayFileInfo
//  Description   : Displays complete file metadata using stat(),
//  Input         : File name
//  Output        : File size, inode, permissions, hard links,
//                :  owner uig/gid file type, last modification time
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayFileInfo(char filename[])
{
    struct stat sb;

    if (stat(filename, &sb) == -1)
    {
        perror("stat");
        return;
    }

    printf("File Size %ld bytes\n", sb.st_size);
    printf("Inode Number %ld\n", sb.st_ino);
    printf("Hard Links %ld\n", sb.st_nlink);
    printf("User ID %d\n", sb.st_uid);
    printf("Group ID %d\n", sb.st_gid);
    printf("Permissions %o\n", sb.st_mode & 0777);

    if (S_ISREG(sb.st_mode))
        printf("File Type : Regular File\n");
    else if (S_ISDIR(sb.st_mode))
        printf("File Type : Directory\n");
    else
        printf("File Type :Other\n");

    printf("Last Modified  : %s", ctime(&sb.st_mtime));
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

    DisplayFileInfo(filename);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Input:
//  Enter file name : 
//
//  Output:
//  Atharva.c
//  File Size 61 bytes
//  Inode Number 3713255
//  Hard Links 1
//  User ID 1000
//  Group ID 1000
//  Permissions 664
//  File Type : Regular File
//  Last Modified  : Thu Dec 25 18:18:38 2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////
