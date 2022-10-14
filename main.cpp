#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

#include "text_functions.h"
#include "supporting_library.h"

int main(int argc, char ** argv)
{
    Text_Info Onegin = {};

    if (Check_CmdlineArg(argc) == Cmdline_Error)
        return Error_In_Main;

    FILE *input_file       = fopen(argv[1], "rb");
    FILE *sortout_file     = fopen(argv[2], "wb");
    FILE *backsortout_file = fopen(argv[3], "wb");
    FILE *res_file         = fopen(argv[4], "wb");
    
    if (Onegin_Verificator(input_file, sortout_file, backsortout_file, res_file) == File_Is_Missed)
        return Error_In_Main;
    
    if (Onegin_Read(&Onegin, input_file) == Reading_File_Error)
        return Error_In_Main;

    /// adding orig text to res file
    Onegin_MakeOutfile(&Onegin, res_file);

    Onegin_Sort(&Onegin, Direct_LexCmp);

    /// adding fisrt sorted text to the sortout_file
    Onegin_MakeOutfile(&Onegin, sortout_file);

    /// adding fisrt sorted text to the res file
    Onegin_MakeOutfile(&Onegin, res_file); 
    
    Onegin_Sort(&Onegin, Reverse_LexCmp);

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
    
    if (fclose(res_file) != 0)
        fprintf(stderr, "Error, file %s wasn't closed %s\n", argv[4], strerror(errno));
    
    printf("Prog finished successfully\n");

    return 0;
}