#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "text_functions.h"

void Constructor(struct Text_Info * Onegin)
{
    char open_file[]  = "old.txt";
    Onegin->file_name = open_file;
    
    if ((Onegin->f_onegin = fopen(Onegin->file_name, "r")) == NULL)
    {
        fprintf(stderr, "Ошибка. Не удалось открыть файл %s "
                        "в функции %s в файле %s",
                        Onegin->file_name, __PRETTY_FUNCTION__, __FILE__);    
    }

    Num_Str(Onegin);

    /*
    int ch = 0;
    while ((ch = getc(Onegin->f_onegin)) != EOF)
    {
        putchar(ch);
    }
    */
}

void Num_Str(struct Text_Info * Onegin)
{
    int ch = 0;
    while ((ch = getc(Onegin->f_onegin)) != EOF)
    {
        if (ch == '\n')
            Onegin->nstr++;
    }
    Onegin->nstr+=1;
    rewind(Onegin->f_onegin);
}

int Len_Str(struct Text_Info * Onegin, int num_str)
{
    return 0;
}

void Read_File(struct Text_Info * Onegin)
{
    int str = 0;
    fseek(Onegin->f_onegin, 0L, SEEK_CUR);

    Onegin->strings = (char **) calloc (Onegin->nstr, sizeof(char*));
    Onegin->strings[str] = (char *) calloc (Onegin->nstr, sizeof(char));

    while (str < Onegin->nstr)
    {
        fread(Onegin->strings[str], sizeof(char *), Onegin->nstr, Onegin->f_onegin);
        printf("%s", Onegin->strings[str]);
        str++;
    }

}



void Destructor(struct Text_Info * Onegin)
{
    fclose(Onegin->f_onegin);
    free(Onegin->strings);
    free(Onegin->point_array);
}


/*
int Str_Comporator (const char * s1, const char * s2)
{
    if (strcmp(s1, s2) == 0)
    {
        return 0;
    }
    while (*s1 != '\0' && *s2 != '\0')
    {
        if ( !(isalpha(*s1)) )
            while ( !(isalpha(*s1)) )
                s1++;
        if ( !(isalpha(*s2)) )
            while ( !(isalpha(*s2)) )
                s2++;
        if (*s1 == *s2 && isalpha(*s1) && isalpha(*s2))
        {
            s1++;
            s2++;
        }
        if (*s1 != *s2 && isalpha(*s1) && isalpha(*s2))
            break;
    }
    return *s1 - *s2;
}
*/


/*
// comporator
// qsort*

void Sorted_Strings (char *strings[], int ch, FILE * nw) // 
{
    nw = fopen("nw.txt", "r+");
    //
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

*/
