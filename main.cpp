#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

#include "text_functions.h"

int main(int argc, char ** argv)
{
    Text_Info Onegin = {};

    FILE * input_file = NULL, * sortout_file = NULL, * backsortout_file = NULL, * res_file = NULL;

    input_file = fopen(argv[1], "rb");
    sortout_file = fopen(argv[2], "wb");
    backsortout_file = fopen(argv[3], "wb");
    res_file = fopen(argv[4], "wb");
    
    Onegin_Ctor(&Onegin, input_file, sortout_file, backsortout_file, res_file, 
                argv[1], argv[2], argv[3], argv[4]);   
    
    if (Onegin_Read(&Onegin, input_file) == -1)
    {
        fprintf(stderr, "Error while calling Onegin_Read\n");
    }

    /// adding orig text to res file
    Onegin_MakeOutfile(&Onegin, res_file);

    Onegin_Sort(&Onegin, Right_LexCmp);

    /// adding fisrt sorted text to the sortout_file
    Onegin_MakeOutfile(&Onegin, sortout_file);
    /// adding fisrt sorted text to the res file
    Onegin_MakeOutfile(&Onegin, res_file); 
    
    Onegin_Sort(&Onegin, Back_LexCmp); 

    /// adding second sorted text to the backsortout_file
    Onegin_MakeOutfile(&Onegin, backsortout_file);
    /// adding second sorted text to the res file
    Onegin_MakeOutfile(&Onegin, res_file);

    Onegin_Dtor(&Onegin);

    if (fclose(input_file) != 0)
        fprintf(stderr, "Error, file %s wasn't closed %s\n", argv[1], strerror(errno));

    if (fclose(sortout_file) != 0)
        fprintf(stderr, "Error, file %s wasn't closed %s\n", argv[2], strerror(errno));

    if (fclose(backsortout_file) != 0)
        fprintf(stderr, "Error, file %s wasn't closed %s\n", argv[3], strerror(errno));
    
    puts("Prog finished successfully");

    return 0;
}
