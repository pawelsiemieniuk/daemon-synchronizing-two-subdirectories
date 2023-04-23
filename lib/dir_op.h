#include <dirent.h>

#ifndef DIR_OP
#define DIR_OP

char *SRC_NAME = "", *DST_NAME = "";
bool dir_check = false;

typedef struct file_info {
        char    f_name[256];    // nazwa pliku
        off_t   f_size;         // rozmiar pliku w bajtach
        time_t  f_mtime;        // data ostatniej modyfikacji w sekundach
} f_info;

typedef struct file_list {
        bool  checked;              // czy plik w porównywaniu został sprawdzony (domyślnie 0)
        bool  type;                 // rodzaj (plik = 0/katalog = 1)
        char *path;                 // sciezka do pliku

        struct f_info file_i;

        struct f_list *next;
} f_list;

void readDir(f_list **list, char *pathname);

void copyDir(f_list *src_list);
void cleanDir(f_list *dst_list);

#endif