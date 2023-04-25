#include <dirent.h>
#include "dir_op.h"

#ifndef FILE_OP
#define FILE_OP

unsigned int sleep_time = 300; // 5min
unsigned int big_file_size = 256; // ostatecznie mozna zmienic na wieksza

void fileListCompare(f_list **src_list, f_list **dst_list);
bool fileCompare(f_info *src_file, f_info *dst_file);
void copyFile(char *path, f_info *file_i);


#endif