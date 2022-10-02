#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "text_functions.h"


int Str_Comporator(const char * s1, const char * s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        while (*s1 != 0 &&  !(isalpha(*s1)) )
        {
            s1++;
        }
        while (*s2 != 0 && !(isalpha(*s2)) )
        {
            s2++;
        }
        if (*s1 == *s2 && isalpha(*s1) && isalpha(*s2))
        {
            s1++;
            s2++;
        }
        if (*s1 == '\0' && *s2 == '\0')
        {
            return 0;
        }
        if (*s1 != *s2 && isalpha(*s1) && isalpha(*s2))
        {
            break;
        }
    }
    return *s1 - *s2;
}


int Back_Cmp(const void * p1, const void * p2)
{
    const char * s1 = (const char *) p1;
    const char * s2 = (const char *) p2;

    const char * start_s1 = s1;
    const char * start_s2 = s2;

    int len1 = 0, len2 = 0;

    while (*s1 != '\0')
    {
        s1++;
        len1++;
    }

    while (*s2 != '\0')
    {
        s2++;
        len2++;
    }

    s1--;
    s2--;

    while(len1-- != 0 && len2-- != 0)
    {
        if (len1 ==0 && len2 == 0)
        {
            return 0;
        }
        while (*s1 != 0 && !(isalpha(*s1)) )
        {
            s1--;
        }
        while (*s2 != 0 && !(isalpha(*s2)) )
        {
            s2--;
        }
        if (*s1 == *s2 && isalpha(*s1) && isalpha(*s2))
        {
            s1--;
            s2--;
        }
        if (*s1 != *s2 && isalpha(*s1) && isalpha(*s2))
        {
            break;
        }
    }
    return *s1 - *s2;
}


int Constructor(struct Text_Info * Onegin, char * input_file,
                char * sortout_file, char * backsortout_file)
{
    if ((Onegin->input_fonegin = fopen(input_file, "r")) == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, input_file, strerror(errno));
        return -1;    
    }

    if ((Onegin->sort_fonegin = fopen(sortout_file, "w+")) == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, sortout_file, strerror(errno));

        return -1;
    }

    if ((Onegin->backsort_fonegin = fopen(backsortout_file, "w+")) == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, backsortout_file, strerror(errno));
        return -1;      
    }
    return 0;
}


int Read_File(struct Text_Info * Onegin)
{
    fseek(Onegin->input_fonegin, 0L, SEEK_END);
    Onegin->n_symb = ftell(Onegin->input_fonegin);   
    rewind(Onegin->input_fonegin);

    Onegin->text_string = (char *) calloc (Onegin->n_symb + 1, sizeof(char));

    fread(Onegin->text_string, sizeof(char), Onegin->n_symb + 1, 
    Onegin->input_fonegin);

    int elem = 0;
    while (elem < Onegin->n_symb)
    {
        if (Onegin->text_string[elem] == '\n')
        {
            Onegin->n_str++;
        }
        elem++;
    }
    Onegin->n_str/=2;

    if (Onegin->n_str != 0 && Onegin->n_symb != 0)
    {
        return 0;
    }
    else
    {
        fprintf(stderr, "Ошибка при записи данных файла \n"
                        "количество символов в файле равно: :%lu\n"
                        "количество строк в файле равно: :%lu\n",
                        Onegin->n_symb, Onegin->n_str);

        return -1;
    }
}



int Make_Strings(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    int ch = 0, cur_len = 0, num_str = 0;
    while (num_str < Onegin->n_str)
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
    int i_elem = 0, j_elem = 0;

    for (i_elem = 0; i_elem < Onegin->n_str - 1; i_elem++)
    {
        for (j_elem = i_elem + 1; j_elem < Onegin->n_str; j_elem++)
        {
            if (Str_Comporator(Strings[i_elem].string, Strings[j_elem].string) > 0)
            {
                Onegin_Swap(Strings, i_elem, j_elem);
            }
        }
    }
    return 0; 
}

int My_Backsort(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    int i_elem = 0, j_elem = 0;

    for (i_elem = 0; i_elem < Onegin->n_str - 1; i_elem++)
    {
        for (j_elem = i_elem + 1; j_elem < Onegin->n_str; j_elem++)
        {
            if (Back_Cmp(Strings[i_elem].string, Strings[j_elem].string) < 0)
            {
                Onegin_Swap(Strings, i_elem, j_elem);
            }
        }
    }
    return 0; 
}

int Onegin_Swap(struct Arr_Struct_Info * Strings, int i_elem, int j_elem)
{
    char * temp_str = 0;
    int temp_len = 0;

    temp_str = Strings[i_elem].string;
    temp_len = Strings[i_elem].len_str;

    Strings[i_elem].string = Strings[j_elem].string;
    Strings[i_elem].len_str = Strings[j_elem].len_str;

    Strings[j_elem].string = temp_str;
    Strings[j_elem].len_str = temp_len;

    return 0;
}


int Make_Outfile(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings, FILE * fp)
{
    int i = 0;
    while (i < Onegin->n_str)
    {
        fwrite(Strings[i].string, sizeof(char), Strings[i].len_str, fp);
        i++;
    }
    return 0;
}


void Destructor(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings)
{
    fclose(Onegin->input_fonegin);
    fclose(Onegin->sort_fonegin);
    fclose(Onegin->backsort_fonegin);
    free(Strings);
    free(Onegin->text_string);
}
