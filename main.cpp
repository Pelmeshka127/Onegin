#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "text_functions.h"

int main(void)
{
    Text_Info Onegin = {
        .input_fonegin = NULL,
        .out_fonegin = NULL,
        .nstr = 0,
        .nch = 0,
        .text_string = NULL,
    };

    Arr_Struct_Info * Strings = (Arr_Struct_Info *) calloc (Onegin.nstr, sizeof(Arr_Struct_Info));

    char input_file[] = "EugeneOnegin.txt";
    char out_file[30];
    puts("Введите название выходного файла");
    fgets(out_file, 30, stdin);

    assert(Constructor(&Onegin, input_file, out_file) == 0);   

    assert(Read_File(&Onegin) == 0);

    Make_Strings(&Onegin, Strings);

    My_Sort(&Onegin, Strings);

    Make_Out_File(&Onegin, Strings);

    puts("Prog finished successfully");
    
    Destructor(&Onegin, Strings);

    return 0;
}
