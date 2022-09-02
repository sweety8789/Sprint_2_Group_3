#include <stdio.h>
#include "string.h"

//to remove extra whitespaces 
void str_trim_lf (char* arr, int length) 
{
    int i;
    for (i = 0; i < length; i++) 
    {
        if (arr[i] == '\n') 
        {
            arr[i] = '\0';
            break;
        }
    }
}

//to print > symbol for initiating sending of message in the screen
void str_overwrite_stdout() 
{
    printf("\r%s", "> ");
    fflush(stdout);
}

