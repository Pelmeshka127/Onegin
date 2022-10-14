#ifndef TEXT_FUNCTIONS_H_
#define TEXT_FUNCTIONS_H_

struct Onegin_Line_Info { //string, oneginLine
    char * string;
    int len_str;
};

struct Text_Info {
    char * text_string;
    unsigned long n_str, n_symb;
    Onegin_Line_Info * Strings;
};

/// function compares two strings
int Direct_LexCmp(const void * s1, const void * s2);

/// functions compares two strings in reverse alphabetical order
int Reverse_LexCmp(const void * p1, const void * p2);

/// function opens files
int Onegin_Verificator(FILE *, FILE *, FILE *, FILE *);

/// function reads input file
int Onegin_Read(struct Text_Info * Onegin, FILE *);

/// functions sorts file using string comporator
void Onegin_Sort(struct Text_Info * Onegin, int Comp(const void *, const void *));

/// function writes strings to the out file 
void Onegin_MakeOutfile(struct Text_Info * Onegin, FILE * fp);

/// function closes files and clear dedicated memory
void Onegin_Dtor(struct Text_Info * Onegin);

#endif