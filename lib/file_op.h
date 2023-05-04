#include <dirent.h>

#include "dir_op.h"

#ifndef FILE_OP
#define FILE_OP

extern unsigned int big_file_size;                          // rozmiar pliku po ktorym zostanie on zapisany przy pomocy mmap()

void fileListCompare(f_list **src_list, f_list **dst_list); // porownywanie listy plikow z katalogu zrodlowego i docelowego
bool fileCompare(f_info *src_file, f_info *dst_file);       // porownywanie dwoch plikow
void copyFile(char *path, f_info *file_i);                  // kopiowanie pliku z katalogu zrodlowego do docelowego
void delFile(char *pathname);                               // usuwanie pliku
void delDir(char *pathname);

#endif