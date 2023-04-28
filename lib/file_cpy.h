#include "dir_op.h"

#ifndef CPY
#define CPY

void cpy_mmap(char *src_path, f_info *finf);        // kopiowanie plikow przy pomocy mmap()
void cpy_normal(char *src_path, f_info *finf);      // kopiowanie plikow przy pomocy read() i write()

#endif
