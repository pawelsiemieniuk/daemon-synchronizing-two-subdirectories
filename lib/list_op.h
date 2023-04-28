
#include <sys/types.h>
#include "dir_op.h"

#ifndef LIST_OP
#define LIST_OP

f_list *push(f_list *list_head, char *path, char *name, off_t size, time_t mod_time);   // dodawanie elementu do listy
void clean(f_list *list_head);                                                          // czyszczenie listy

#endif