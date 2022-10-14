#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "text_functions.h"
#include "supporting_library.h"

int Direct_LexCmp(const void * p1, const void * p2)
{
    const char * str1 = (const char *) p1;
    const char * str2 = (const char *) p2;

    while (*str1 != '\0' && *str2 != '\0')
    {
        Move_Strptr(&str1);
        Move_Strptr(&str2);
        
        if (*str1 == *str2 && isalpha(*str1) && isalpha(*str2))
        {
            str1++;
            str2++;
        }
        if (*str1 != *str2 && isalpha(*str1) && isalpha(*str2))
        {
            break;
        }
        if (*str1 == '\0' && *str2 == '\0')
        {
            return 0;
        }
    }
    return *str2 - *str1;
}


int Reverse_LexCmp(const void * p1, const void * p2)
{ 
    const char * str1 = (const char *) p1;
    const char * str2 = (const char *) p2;

    int len1 = 0, len2 = 0;

    while (*str1 != '\0')
    {
        str1++;
        len1++;
    }

    while (*str2 != '\0')
    {
        str2++;
        len2++;
    }

    str1--;
    str2--;

    while(len1-- != 0 && len2-- != 0)
    {
        if (len1 ==0 && len2 == 0)
        {
            return 0;
        }

        Back_Move_Strptr(&str1);
        Back_Move_Strptr(&str2);
        
        if (*str1 == *str2 && isalpha(*str1) && isalpha(*str2))
        {
            str1--;
            str2--;
        }
        if (*str1 != *str2 && isalpha(*str1) && isalpha(*str2))
        {
            break;
        }
    }
    return *str1 - *str2;
}


int Onegin_Verificator(FILE * input_file, FILE * sortout_file, FILE * backsortout_file, FILE * res_file)
{
    if (input_file == NULL || sortout_file == NULL || backsortout_file == NULL || res_file == NULL)
    {
        ONEGIN_ERROR();
        return File_Is_Missed;
    }
    return No_Error;
}


int Onegin_Read(struct Text_Info * Onegin, FILE * input_file) 
{
    if (Get_Num_Symb(input_file, Onegin) == Making_Str_Error) 
        return Reading_File_Error;

    Onegin->text_string = (char *)calloc (Onegin->n_symb + 1, sizeof(char));

    if (Onegin->text_string == NULL)
    {
        ONEGIN_ERROR();
        return Reading_File_Error;
    }

    if (fread(Onegin->text_string, sizeof(char), Onegin->n_symb + 1, input_file) < Onegin->n_str)
    {
        ONEGIN_ERROR();
        return Reading_File_Error;
    }

    Get_Num_Str(input_file, Onegin);

    Make_Strings(Onegin);

    if (Onegin->n_str == 0 || Onegin->n_symb == 0)
    {
        fprintf(stderr, "Error: number of srings Onegin->Strings is %lu\n"
                        "number of symols in Onegin->Strings is %lu\n", Onegin->n_str, Onegin->n_symb);
        return Reading_File_Error;
    }

    if (Onegin->Strings == NULL)
        return Reading_File_Error;

    return No_Error;
}


void Onegin_Sort(struct Text_Info * Onegin, int Comporator(const void *, const void *))
{
    for (int i = 0; i < Onegin->n_str - 1; i++)
        for (int j = i + 1; j < Onegin->n_str; j++)
            if (Comporator(Onegin->Strings[i].string, Onegin->Strings[j].string) < 0)
                Onegin_Swap(Onegin, i, j);
}



void Onegin_MakeOutfile(struct Text_Info * Onegin, FILE * fp)
{
    for (int cur_str = 0; cur_str < Onegin->n_str; cur_str++)
        fprintf(fp, "%s", Onegin->Strings[cur_str].string);
}


void Onegin_Dtor(struct Text_Info * Onegin)
{
    free(Onegin->Strings);
    free(Onegin->text_string);
}