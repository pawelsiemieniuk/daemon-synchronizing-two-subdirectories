#include <dirent.h>

#include "dir_op.h"

#ifndef FILE_OP
#define FILE_OP

// Porownywanie listy plikow z katalogu zrodlowego i docelowego
void fileListCompare(f_list **src_list, f_list **dst_list);

// Porownywanie dwoch plikow
bool fileCompare(f_info *src_file, f_info *dst_file);

// Kopiowanie pliku z katalogu zrodlowego do docelowego
void copyFile(char *path, f_info *file_i);

// Usuwanie pliku
void delFile(char *pathname);

// Usuwanie katalogu
void delDir(char *pathname);

#endif