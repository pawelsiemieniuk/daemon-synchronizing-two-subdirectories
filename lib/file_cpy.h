#include "dir_op.h"

#ifndef CPY
#define CPY

// Kopiowanie plikow poprzez mapowanie ich w pamieci
void copyMap(char *src_path, f_info *finf);

// Kopiowanie plikow wykorzystujac buffer
void copyNormal(char *src_path, f_info *finf);      

#endif
