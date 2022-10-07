#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "text_functions.h"


int Right_LexCmp(const void * p1, const void * p2)
{
    const char * s1 = (const char *) p1;
    const char * s2 = (const char *) p2;

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
    return *s2 - *s1;
}


int Back_LexCmp(const void * p1, const void * p2)
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


void Onegin_Ctor(struct Text_Info * Onegin, FILE * input_file, FILE * sortout_file,
                FILE * backsortout_file, FILE * res_file, char * file1, char * file2, 
                char * file3, char * file4)
{
    if (input_file == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, file1, strerror(errno));   
    }

    if (sortout_file == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, file2, strerror(errno));

    }

    if (backsortout_file == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, file3, strerror(errno));   
    }

    if (res_file == NULL)
    {
        fprintf(stderr, "In function %s\n"
                        "Error openning file %s: %s\n", 
                        __PRETTY_FUNCTION__, file4, strerror(errno));  
    }
}


int Onegin_Read(struct Text_Info * Onegin, FILE * input_file)
{
    Num_Symb(input_file, Onegin);

    Onegin->text_string = (char *) calloc (Onegin->n_symb + 1, sizeof(char));

    if (fread(Onegin->text_string, sizeof(char), 
                      Onegin->n_symb + 1, input_file) < Onegin->n_str)
    {
        fprintf(stderr, "Error in function %s, %d: %s\n",
                __PRETTY_FUNCTION__, __LINE__, strerror(errno));
        return -1;
    }

    Num_Str(input_file, Onegin);

    MakeStrings(Onegin);

    if (Onegin->n_str == 0 || Onegin->n_symb == 0)
    {
        fprintf(stderr, "Error in fucntion %s, %d: %s\n",
                __PRETTY_FUNCTION__, __LINE__, strerror(errno));
        return -1;
    }

    if (Onegin->strings == NULL)
    {
        fprintf(stderr, "Error in function %s, %d: %s\n",
                __PRETTY_FUNCTION__, __LINE__, strerror(errno));
        return -1;
    }

    return 0;
}


int Num_Symb(FILE * fp, struct Text_Info * Onegin)
{
    if (fseek(fp, 0L, SEEK_END) == -1)
    {
        fprintf(stderr, "Error in function %s: %s\n", __PRETTY_FUNCTION__, strerror(errno));
        return -1;
    }
    Onegin->n_symb = ftell(fp);   
    rewind(fp);
    return 0;
}


int Num_Str(FILE * fp, struct Text_Info * Onegin)
{
    int cur_ch = 0;
    while (cur_ch < Onegin->n_symb)
    {
        if (Onegin->text_string[cur_ch] == '\n')
        {
            Onegin->n_str++;
        }
        cur_ch++;
    }
    return Onegin->n_str;
}


void MakeStrings(struct Text_Info * Onegin)
{
    if ((Onegin->strings = (Arr_Struct_Info *) calloc 
        (Onegin->n_str+1, sizeof(Arr_Struct_Info))) == NULL)
    {
        fprintf(stderr, "Error in function %s: %s\n", __PRETTY_FUNCTION__, strerror(errno));
    }
    
    int ch = 0, cur_len = 0, num_str = 0;
    while (num_str < Onegin->n_str)
    {
        cur_len++;
        ch++;
        if (Onegin->text_string[ch] == '\n')
        {
            Onegin->text_string[ch] = '\0';

            Onegin->strings[num_str].len_str = cur_len;
            Onegin->strings[num_str].string = &Onegin->text_string[ch - cur_len];

            num_str++;
            cur_len = 0;
            ch+=1;
        }
    }
}

void Onegin_Sort(struct Text_Info * Onegin, int Comporator(const void *, const void *))
{
    for (int i_elem = 0; i_elem < Onegin->n_str - 1; i_elem++)
        for (int j_elem = i_elem + 1; j_elem < Onegin->n_str; j_elem++)
            if (Comporator(Onegin->strings[i_elem].string, Onegin->strings[j_elem].string) < 0)
                Onegin_Swap(Onegin, i_elem, j_elem);
}

void Onegin_Swap(struct Text_Info * Onegin, int i_elem, int j_elem)
{
    char * temp_str = 0;
    int temp_len = 0;

    temp_str = Onegin->strings[i_elem].string;
    temp_len = Onegin->strings[i_elem].len_str;

    Onegin->strings[i_elem].string = Onegin->strings[j_elem].string;
    Onegin->strings[i_elem].len_str = Onegin->strings[j_elem].len_str;

    Onegin->strings[j_elem].string = temp_str;
    Onegin->strings[j_elem].len_str = temp_len;
}


void Onegin_MakeOutfile(struct Text_Info * Onegin, FILE * fp)
{
    for (int cur_str = 0; cur_str < Onegin->n_str; cur_str++)
        fprintf(fp, "%s", Onegin->strings[cur_str].string);
}


void Onegin_Dtor(struct Text_Info * Onegin)
{
    free(Onegin->strings);
    free(Onegin->text_string);
}
