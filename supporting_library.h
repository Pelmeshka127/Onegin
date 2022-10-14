#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef SUPPORTING_LIBRARY_H_
#define SUPPORTING_LIBRARY_H_

#define ONEGIN_ERROR() \
fprintf(stderr, "There is an error in %s, in %d: %s\n", \
                __PRETTY_FUNCTION__, __LINE__, strerror(errno))

enum Onegin_Coderr{
    Error_In_Main = -1,
    No_Error = 0,
    Cmdline_Error = 1,
    File_Is_Missed = 2,
    Reading_File_Error = 3,
    Making_Str_Error = 4,
};

/// function checks command lines argument
int Check_CmdlineArg(int argc);

/// function moves pointer of the string forward to '\0'
void Move_Strptr(const char **str);

/// function moves pointer of the string back from '\0'
void Back_Move_Strptr(const char ** str);

/// functions finds out the number of symbols in file
int Get_Num_Symb(FILE *, struct Text_Info * Onegin);

/// functions finds out the number of strings in file
int Get_Num_Str(FILE *, struct Text_Info * Onegin);

/// function make strings from input file
int Make_Strings(struct Text_Info * Onegin);

/// function swaps strings
void Onegin_Swap(struct Text_Info * Onegin, int i_elem, int j_elem);

#endif