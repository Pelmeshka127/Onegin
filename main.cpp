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
        .sort_fonegin = NULL,
        .backsort_fonegin = NULL,
        .text_string = NULL,
        .n_str = 0,
        .n_symb = 0,
    };
    
    char input_file[30];
    char sortout_file[30];
    char backsortout_file[30];
    puts("Enter name of input file");
    scanf("%s", input_file);

    puts("Enter name of sorted out file");
    scanf("%s", sortout_file);

    puts("Enter name of back sorted out file");
    scanf("%s", backsortout_file);
    
    Constructor(&Onegin, input_file, sortout_file, backsortout_file);   
    
    Read_File(&Onegin);

    Arr_Struct_Info * Strings = (Arr_Struct_Info *) calloc (Onegin.n_str+1, sizeof(Arr_Struct_Info));

    Make_Strings(&Onegin, Strings);

    My_Sort(&Onegin, Strings);

    Make_Outfile(&Onegin, Strings, Onegin.sort_fonegin);
    
    My_Backsort(&Onegin, Strings);

    Make_Outfile(&Onegin, Strings, Onegin.backsort_fonegin);

    Destructor(&Onegin, Strings);
    
    puts("Prog finished successfully");

    return 0;
}
