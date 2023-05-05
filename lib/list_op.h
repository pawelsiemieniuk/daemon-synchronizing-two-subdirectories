#include "var.h"

#ifndef LIST_OP
#define LIST_OP

// Dodawanie elementu na koniec listy
f_list *push(f_list *list_head, char *path, char *name, off_t size, time_t mod_time);

// Czyszczenie listy
void clean(f_list *list_head);

#endif