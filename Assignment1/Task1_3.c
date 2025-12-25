/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Required header files
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name : CheckAccess
//  Description   : Checks read/write/execute permission of a file
//                  for the current process using access()
//  Input         : File name, Mode (R / W / X)
//  Output        : Accessible / Not accessible with reason
//  Author        : Atharva Vinod Gawade
//  Date          : 25/12/2025
//
/////////////////////////////////////////////////////////////////////////////////////////////////

void CheckAccess(char filename[], char mode[])
{
    int flag = 0;

    if (strcmp(mode, "R") == 0)
    {
        flag = R_OK;
    }
    else if (strcmp(mode, "W") == 0)
    {
        flag = W_OK;
    }
    else if (strcmp(mode, "X") == 0)
    {
        flag = X_OK;
    }
    else
    {
        printf("Invalid mode\n");
        return;
    }

    if (access(filename, flag) == 0)
    {
      printf("Accessible\n");
    }
    else
    {
        perror("Not accessible");
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function
//
/////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char filename[100], mode[2];

    printf("Enter file name : \n");
    scanf("%s", filename);

    printf("Enter mode (R / W / X) : \n");
    scanf("%s", mode);

    CheckAccess(filename, mode);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Testcases successfully handled by the application
//  
//  Enter file name : 
//  Demo.txt 
//  Enter mode (R / W / X) : 
//  R
//  Output :
//  Accessible
//
//  Input :
//  Enter file name : 
//
//  Atharva.c
//  Enter mode (R / W / X) : 
//  Output :
//  Not accessible: Permission denied
// 
/////////////////////////////////////////////////////////////////////////////////////////////////
