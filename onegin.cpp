#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "onegin.h"

void Copy_File (FILE * old, FILE * nw)
{
    old = fopen("old.txt", "r");
    nw  = fopen("nw.txt",  "w");
    int ch = 0;
    
    while ((ch = getc(old)) != EOF)
    {
        if (isalpha(ch) || ch == '\n' || ch == ' ')
        {
            putc(ch, nw);
        }
    }
    fclose(old);
    fclose(nw);
}

int Num_Of_Strings (FILE * nw)
{
    nw = fopen("nw.txt", "r");
    int ch = 0, count = 0;

    while ((ch = getc(nw)) != EOF)
    {
        if (ch == '\n')
        {
            count++;
        }
    }
    return count;
    fclose(nw);
}

int Max_String_Len (FILE * old)
{
    int len = 0, ch = 0, max_len = 0;
    old = fopen("old.txt", "r");

    while ((ch = getc(old)) != EOF)
    {
        len += (ch != '\n');
        if (ch == '\n')
        {
            if (len > max_len)
            {
                max_len = len;
            }
            len = 0;
        }
    }
    return max_len;
    fclose(old);
}


void Sorted_Strings (char *strings[], int ch, FILE * nw)
{
    nw = fopen("nw.txt", "r+");
    int i = 0, j = 0;
    char * temp = 0;
    
    for (i = 0; i < ch - 1; i++)
    {
        for (j = i + 1; j < ch; j++)
        {
            if (strcmp(strings[i], strings[j]) > 0)
            {
                temp = strings[i];
                strings[i] = strings[j];
                strings[j] = temp;
            }
        }
    }
    fclose(nw);
}
