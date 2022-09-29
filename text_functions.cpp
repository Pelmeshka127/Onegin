#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "text_functions.h"


int Str_Comporator (const char * s1, const char * s2)
{
    if (strcmp(s1, s2) == 0)
    {
        return 0;
    }

    while (*s1 != '\0' && *s2 != '\0')
    {
        while (*s1 != 0 &&  !(isalpha(*s1)) )
            s1++;
        while (*s2 != 0 && !(isalpha(*s2)) )
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



int Constructor(struct Text_Info * Onegin, char * input_file, char * out_file)
{
    if ((Onegin->input_fonegin = fopen(input_file, "r")) == NULL)
    {
        fprintf(stderr, "Ошибка. Не удалось открыть файл %s "
                        "в функции %s в файле %s\n",
                        input_file, __PRETTY_FUNCTION__, __FILE__);

        return -1;    
    }

    if ((Onegin->out_fonegin = fopen(out_file, "w+")) == NULL)
    {
        fprintf(stderr, "Ошибка. Не удалось создать файл %s "
                        "в функции %s в файле %s\n",
                        out_file, __PRETTY_FUNCTION__, __FILE__);

        return -1;
    }
    return 0;
}


int Num_Ch_Str(struct Text_Info * Onegin)
{
    int ch = 0;

    while ((ch = getc(Onegin->input_fonegin)) != EOF)
    {
        if (ch == '\n')
        {
            Onegin->nstr++;
        }
        Onegin->nch++;
    }

    Onegin->nstr/=2;

    rewind(Onegin->input_fonegin);

    if (Onegin->nch != 0 && Onegin->nstr != 0)
    {
        return 1;
    } 
    else
    {
        printf("Ошибка при обработке данных файла\n"
        "кол-во символов в файле равно %lu, кол-во строк равно %lu\n",
        Onegin->nch, Onegin->nstr);
        return 0;
    }
}




unsigned long Read_File(struct Text_Info * Onegin)
{
    assert(Num_Ch_Str(Onegin) == 1);

    unsigned long test = 0;

    Onegin->text_string = (char *) calloc (Onegin->nch, sizeof(char));

    if ((test = fread(Onegin->text_string, sizeof(char), Onegin->nch, 
    Onegin->input_fonegin)) >= Onegin->nch)
    {
        return 0;
    }
    else
    {
        return test;
    }
    
    fclose(Onegin->input_fonegin);
    
}

int Make_Strings(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    int ch = 0, cur_len = 0, num_str = 0;
    while (num_str < Onegin->nstr)
    {
        cur_len++;
        ch++;
        if (Onegin->text_string[ch] == '\n')
        {
            Onegin->text_string[ch] = '\0';

            Strings[num_str].len_str = cur_len;
            Strings[num_str].string = &Onegin->text_string[ch - cur_len];

            num_str++;
            cur_len = 0;
            ch+=2;
        }
    }
    return 0;
}

int My_Sort(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    int i = 0, j = 0, temp_len;
    char * temp_str = 0;

    for (i = 0; i < Onegin->nstr - 1; i++)
    {
        for (j = i + 1; j < Onegin->nstr; j++)
        {
            if (Str_Comporator(Strings[i].string, Strings[j].string) > 0)
            {
                temp_str = Strings[i].string;
                temp_len = Strings[i].len_str;

                Strings[i].string = Strings[j].string;
                Strings[i].len_str = Strings[j].len_str;

                Strings[j].string = temp_str;
                Strings[j].len_str = temp_len;
            }
        }
    }
    return 0; 
}


int Make_Out_File(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    int i = 0;
    while (i < Onegin->nstr)
    {
        fwrite(Strings[i].string, sizeof(char), Strings[i].len_str, Onegin->out_fonegin);
        i++;
    }
    return 0;
}




void Destructor(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    fclose(Onegin->out_fonegin);
    free(Strings);
    free(Onegin->text_string);
}


