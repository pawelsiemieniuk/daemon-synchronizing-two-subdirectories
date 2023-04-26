
#include "dir_op.h"

f_list *push(f_list *list_head, char *path, char *name, off_t size, time_t mod_time){
    f_list *head = list_head;

    f_list *last = calloc(1, sizeof(f_list));
    f_info *file = calloc(1, sizeof(f_info));

    file->f_name  = name;
    file->f_size  = size;
    file->f_mtime = mod_time;

    last->checked = false;
    last->path    = path;
    last->file_i  = file;
    last->next    = NULL;

    if(!list_head){ return last; }

    while(head->next){ head = head->next; }

    head->next = last;

    return head;
}

void clean(f_list *list_head){
    
}