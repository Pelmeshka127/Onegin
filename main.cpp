#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "onegin.h"

int main(void)
{
    FILE * old = NULL, * nw = NULL;
    Copy_File(old, nw);

    int const Num_str = Num_Of_Strings(old);
    int const Max_len = Max_String_Len(old);
    printf("Count of strings is %d.\n"
           "Max count of len is %d.\n"
           , Num_str, Max_len);
    int ct = 0, k = 0;
    char string[Num_str][Max_len];
    char *point_string[Num_str];
    nw = fopen("nw.txt", "r");

    while (ct < Num_str && fgets(string[ct], Max_len, nw) != NULL
           && string[ct][0] != '\0')
        {
            point_string[ct] = string[ct];
            ct++;
        }
    
    Sorted_Strings (point_string, ct, nw);

    fclose(nw);

    for (k = 0; k < ct; k++)
    {
        printf("%s\n", point_string[k]);
    }
    return 0;
}
