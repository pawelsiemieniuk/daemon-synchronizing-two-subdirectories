#include <stdbool.h>
#include <string.h>

#include "file_cpy.h"
#include "dir_op.h"
#include "log.h"

unsigned int big_file_size = 256; // ostatecznie mozna zmienic na wieksza


bool fileCompare(f_info *src_file, f_info *dst_file){
    if(!strcmp(src_file->f_name, dst_file->f_name))
        return false;
    if((src_file)->f_size != (dst_file)->f_size)
        return false;
    if((src_file)->f_mtime != (dst_file)->f_mtime)
        return false;

    return true;
}

void fileListCompare(f_list **src_list, f_list **dst_list){
    f_list *src = (*src_list);
    f_list *dst = (*dst_list);
    
    while(src){
        while(dst){
            if(!dst->checked){
                if(fileCompare(src->file_i, dst->file_i)){
                    src->checked = true;
                    dst->checked = true;
                }
            }
            dst = dst->next;
        }
        src = src->next;
    }
}

void copyFile(char *path, f_info *file_i){

        if(file_i->f_size >= big_file_size){
                cpy_mmap(path, file_i); // nie muszą być oddzielne funkcje, tylko poglądowo napisałem
                logAction("cpy_mmap");
        }
        else{
                cpy_normal(path, file_i);
                logAction("cpy_normal");
        }
}

void delFile(char *pathname){
    if(remove(pathname) == 0)
    {
        logAction("del_file");
    }
}
