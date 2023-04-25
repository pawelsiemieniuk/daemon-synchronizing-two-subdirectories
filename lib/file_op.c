#include <stdbool.h>
#include "dir_op.h"
#include "log.h"

unsigned int big_file_size = 256; // ostatecznie mozna zmienic na wieksza

void fileListCompare(f_list **src_list, f_list **dst_list){

    fileCompare((*src_list)->file_i, (*dst_list)->file_i);

}

bool fileCompare(f_info *src_file, f_info *dst_file){
    if(!strcmp(src_file->f_name, dst_file->f_name))
        return false;
    if((src_file)->f_size == (dst_file)->f_size)
        return false;
    if((src_file)->f_mtime == (dst_file)->f_mtime)
        return false;

    return true;
}


void copyFile(char *path, f_info *file_i){

        if(file_i->f_size >= big_file_size){
                cpy_mmap(); // nie muszą być oddzielne funkcje, tylko poglądowo napisałem
                logAction("cpy_mmap");
        }
        else{
                cpy_normal();
                logAction("cpy_normal");
        }
}

void delFile(char *pathname){

}
