#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "file_cpy.h"
#include "dir_op.h"
#include "log.h"
#include "var.h"


bool fileCompare(f_info *src_file, f_info *dst_file){
    if(strcmp(src_file->f_name, dst_file->f_name))
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
    f_info *f_i, *d_i;
    while(src){
        while(dst){
            if(!dst->checked){
                f_i = (f_info*)src->file_i;
                d_i = (f_info*)dst->file_i;
                if(fileCompare((f_info*)src->file_i, (f_info*)dst->file_i)){
                    src->checked = true;
                    dst->checked = true;
                }
            }
            dst = (f_list*)dst->next;
        }
        dst = (*dst_list);
        src = (f_list*)src->next;
    }
}

void copyFile(char *path, f_info *file_i){
        if(file_i->f_size >= BIG_FILE_SIZE){
                copyMap(path, file_i);
                logAction("cpy_mmap");
        }
        else{
                copyNormal(path, file_i);
                logAction("cpy_normal");
        }
}

void delFile(char *pathname){
    if(unlink(pathname) == 0)
        logAction("del_file");
}

void delDir(char *pathname){
    if(rmdir(pathname) == 0)
        logAction("del_dir");
}
