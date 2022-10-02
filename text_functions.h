#ifndef TEXT_FUNCTIONS_H_
#define TEXT_FUNCTIONS_H_

struct Text_Info {
    FILE * input_fonegin, * sort_fonegin, * backsort_fonegin;
    char * text_string;
    unsigned long n_str, n_symb;
};

struct Arr_Struct_Info {
    char * string;
    int len_str;
};

/// function compares two strings
int Str_Comporator(const char * s1, const char * s2);

///
int Back_Cmp(const void * p1, const void * p2);

/// function opens files
int Constructor(struct Text_Info * Onegin, char * input_file,
                char * sortout_file, char * backsortout_file);

/// function reads input file
int Read_File(struct Text_Info * Onegin);

/// function make strings from input file
int Make_Strings(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

/// function sortes strings from input file
int My_Sort(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

/// functions sortes strings in reverse order
int My_Backsort(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

/// function swaps strings
int Onegin_Swap(struct Arr_Struct_Info * Strings, int i_elem, int j_elem);

/// function writes strings to the out file 
int Make_Outfile(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings, FILE * fp);

/// function closes files and clear dedicated memory
void Destructor(struct Text_Info * Onegin, struct Arr_Struct_Info * Strings);

#endif
