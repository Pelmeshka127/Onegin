#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "onegin.h"

int main(void)
{
    FILE * old = NULL, * nw = NULL;
    char word[20];
    int ch = 0;

    Copy_To_File(old, nw);

    assert((nw = fopen("nw.txt", "r")) != NULL);

    for (int i = 0; i < 2000; i++)
    {
        fgets(word, 20, nw);
        printf("%s", word);
    }

    return 0;
}