#ifndef TEXT_FUNCTIONS_H_
#define TEXT_FUNCTIONS_H_

int Str_Comporator(const char * s1, const char * s2);

struct Text_Info {
    FILE * f_onegin;
    char * file_name;
    char ** strings; 
    char * point_array;
    int nstr;
};

void Constructor(struct Text_Info * Onegin);

void Num_Str(struct Text_Info * Onegin);

int Len_Str(struct Text_Info * Onegin, int num_str);

void Read_File(struct Text_Info * Onegin);

void My_Sort(struct Text_Info * Onegin);

void Destructor(struct Text_Info * Onegin);

#endif
