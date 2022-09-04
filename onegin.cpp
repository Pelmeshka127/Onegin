#include <stdio.h>
#include <ctype.h>

#include "onegin.h"

void Copy_To_File (FILE * old, FILE * nw)
{
    old = fopen("old.txt", "r");
    nw = fopen("nw.txt", "w");
    int ch = 0;
    
    while ((ch = getc(old)) != EOF)
    {
        if (isalpha(ch) || ch == '\n')
        {
            putc(ch, nw);
        }
        else if (ch == ' ')
        {
            ch = '\0';
            putc('\n', nw);
        }
        else
        {
            ch = '\0';
        }
    }
}