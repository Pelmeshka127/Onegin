#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "text_functions.h"

int main(void)
{
    Text_Info Onegin = {
        .f_open_onegin = NULL,
        .f_print_onegin = NULL,
        .nstr = 0,
        .point_array = NULL,
        .strings = NULL,
    };

    char s1[] = "Kiril";
    char s2[] = "Pavlovskiy";
    printf("MyComp: %d\n"
           "strcmp: %d\n",
            Str_Comporator(s1, s2), strcmp(s1, s2));


    Constructor(&Onegin);   ///

    Read_File(&Onegin);

    // close inp

    My_Sort(&Onegin);

    Print_To_File(&Onegin);

    Destructor(&Onegin);

    printf("successed\n");

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
    // errno, perror, strerr 
    // calloc char*
    // fgetc -> size -> calloc
    // fseek, rewind
    // fgets
    // fread, calloc
    */

    return 0;
}