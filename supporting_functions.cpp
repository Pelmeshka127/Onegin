#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>

#include "supporting_library.h"
#include "text_functions.h"

int Check_CmdlineArg(int argc)
{
    if (argc != 5)
    {
        ONEGIN_ERROR();
        fprintf(stderr, "Error: wrong number of command line args: %d\n", argc);
        return Cmdline_Error;
    }
    return No_Error;
}

void Move_Strptr(const char **str)
{
    while (**str != '\0' && !(isalpha(**str)))
        (*str)++;
}

void Back_Move_Strptr(const char ** str)
{
    while (**str != '\0' && !(isalpha(**str)))
        (*str)--;
}

int Get_Num_Symb(FILE * fp, struct Text_Info * Onegin)
{
    if (fseek(fp, 0L, SEEK_END) == -1)
    {
        ONEGIN_ERROR();
        return Making_Str_Error;
    }
    Onegin->n_symb = ftell(fp);   
    rewind(fp);
    return No_Error;
}


int Get_Num_Str(FILE * fp, struct Text_Info * Onegin)
{
    int cur_ch = 0;
    while (cur_ch < Onegin->n_symb)
    {
        if (Onegin->text_string[cur_ch++] == '\n')
        {
            Onegin->n_str++;
        }
    }
    return Onegin->n_str;
}


int Make_Strings(struct Text_Info * Onegin)
{
    if ((Onegin->Strings = (Onegin_Line_Info *)calloc (Onegin->n_str+1, sizeof(Onegin_Line_Info))) == NULL)
    {
        ONEGIN_ERROR();
        return Making_Str_Error;
    }
    
    int ch = 0, cur_len = 0, num_str = 0;
    while (num_str < Onegin->n_str)
    {
        cur_len++;
        ch++;
        if (Onegin->text_string[ch] == '\n')
        {
            Onegin->text_string[ch] = '\0';

            Onegin->Strings[num_str].len_str = cur_len;
            Onegin->Strings[num_str].string = &Onegin->text_string[ch - cur_len];

            num_str++;
            cur_len = 0;
            ch++;
        }
    }
    return No_Error;
}


void Onegin_Swap(struct Text_Info * Onegin, int i_elem, int j_elem)
{
    char * temp_str = 0;
    int temp_len = 0;

    temp_str = Onegin->Strings[i_elem].string;
    temp_len = Onegin->Strings[i_elem].len_str; //!TODO swap functions in C

    Onegin->Strings[i_elem].string = Onegin->Strings[j_elem].string;
    Onegin->Strings[i_elem].len_str = Onegin->Strings[j_elem].len_str;

    Onegin->Strings[j_elem].string = temp_str;
    Onegin->Strings[j_elem].len_str = temp_len;
}