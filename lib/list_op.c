#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#include "dir_op.h"

struct f_list *push(f_list *list_head, char *path, char *name, off_t size, time_t mod_time){
    f_list *head = list_head;

    f_list *last = (struct f_list*)calloc(1, sizeof(f_list));
    f_info *file = (struct f_info*)calloc(1, sizeof(f_info));

    strcpy(file->f_name, name);
    file->f_size  = size;
    file->f_mtime = mod_time;

    last->checked = false;
    last->path    = path;
    last->file_i  = file;
    last->next    = NULL;
    
    if(!list_head){ return last; }

    while(head->next){ head = head->next; }

    head->next = last;

    return list_head;
}

void clean(f_list *list_head){
    if(!list_head) { return; }

    while(list_head->next){
        f_list *tmp = list_head->next;
        free(list_head->file_i);
        free(list_head);
        list_head = tmp;
    }
    free(list_head->file_i);
    free(list_head);
}