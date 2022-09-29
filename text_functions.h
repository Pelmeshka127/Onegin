#ifndef TEXT_FUNCTIONS_H_
#define TEXT_FUNCTIONS_H_

struct Text_Info {
    FILE * input_fonegin, * out_fonegin;
    char * text_string;
    unsigned long nstr, nch;
};

struct Arr_Struct_Info {
    char * string;
    int len_str;
};

/// function compares two strings
int Str_Comporator(const char * s1, const char * s2);

/// function opens files
int Constructor(struct Text_Info * Onegin, char * input_file, char * out_file);

/// function finds out count of stings in f_open_onegin
int Num_Ch_Str(struct Text_Info * Onegin);

/// function reads input file
unsigned long Read_File(struct Text_Info * Onegin);

/// function make strings from input file
int Make_Strings(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

/// function sortes strings from input file
int My_Sort(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

/// function writes strings to the out file 
int Make_Out_File(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

/// function closes files and clear dedicated memory
void Destructor(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

#endif
