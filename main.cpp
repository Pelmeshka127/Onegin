#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "text_functions.h"

int main(void)
{
    struct Text_Info Onegin = {
        .f_onegin = NULL, .file_name = NULL,
        .point_array = NULL, .strings = NULL,
        .nstr = 0,
    };

    Constructor(&Onegin);

    Read_File (&Onegin);

    Destructor(&Onegin);


    /*
    //
    struct Text_Info Onegin = {};

    // ctor 

    // read_strings
    // 

    // sort_onegin()
    // 

    // print

    // dtor 

    int const Num_str = Num_Of_Strings(old);
    int const Max_len = Max_String_Len(old);

    printf("Count of strings is %d.\n"
           "Max count of len is %d.\n"
           , Num_str, Max_len);

    int ct = 0, k = 0;             //
    char string[Num_str][Max_len]; //
    char *point_string[Num_str];
    
    nw = fopen("nw.txt", "r"); // open_file
    // errno, perror, strerr 

    // calloc char*
    // fgetc -> size -> calloc
    // fseek, rewind
    // fgets
    // fread, calloc

    while (ct < Num_str && fgets(string[ct], Max_len, nw) != NULL
           && string[ct][0] != '\0')
        {
            point_string[ct] = string[ct];
            ct++;
        }
    
    Sorted_Strings(point_string, ct, nw);  

    fclose(nw);

    for (k = 0; k < ct; k++) //name, definition
    {
        printf("%s\n", point_string[k]);
    }
    */

    return 0;
}
