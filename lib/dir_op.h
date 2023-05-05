#include "var.h"

#ifndef DIR_OP
#define DIR_OP

// Wczytywanie plikow ze sciezki do listy
void readDir(f_list **list, char *pathname);

// Kopiowanie plikow na liscie z katalogu zrodlowego do katalogu docelowego
void copyDir(f_list **src_list);

// Usuwanie zbednych plikow z katalogu docelowego
void cleanDir(f_list **dst_list);

#endif