#include "dir_op.h"

#ifndef CPY
#define CPY

void copyMap(char *src_path, f_info *finf);        // kopiowanie plikow przy pomocy mmap()
void copyNormal(char *src_path, f_info *finf);      // kopiowanie plikow przy pomocy read() i write()

#endif
