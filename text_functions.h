#ifndef TEXT_FUNCTIONS_H_
#define TEXT_FUNCTIONS_H_

struct Arr_Struct_Info {
    char * string;
    int len_str;
};

struct Text_Info {
    char * text_string;
    unsigned long n_str, n_symb;
    Arr_Struct_Info * strings;
};

/// function compares two strings in alphabetical ordee
int Right_LexCmp(const void * s1, const void * s2);

/// function compares two strings in reverse alphabetical order
int Back_LexCmp(const void * p1, const void * p2);

/// function checks opened files
void Onegin_Ctor(struct Text_Info * Onegin, FILE *, FILE *, FILE *, FILE *, 
                char *, char *, char *, char *);

/// function reads input file
int Onegin_Read(struct Text_Info * Onegin, FILE *);

/// functions finds out the number of symbols in file
int Num_Symb(FILE *, struct Text_Info * Onegin);

/// functions finds out the number of strings in file
int Num_Str(FILE *, struct Text_Info * Onegin);

/// function make strings from input file
void MakeStrings(struct Text_Info * Onegin);

/// functions sorts file using string comporator
void Onegin_Sort(struct Text_Info * Onegin, int Comp(const void *, const void *));

/// function swaps strings
void Onegin_Swap(struct Text_Info * Onegin, int i_elem, int j_elem);

/// function writes strings to the out file 
void Onegin_MakeOutfile(struct Text_Info * Onegin, FILE * fp);

/// function closes files and clear dedicated memory
void Onegin_Dtor(struct Text_Info * Onegin);

#endif
