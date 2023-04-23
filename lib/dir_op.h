#include<dirent.h>

#ifndef DIR_OP
#define DIR_OP

typedef struct file_info {
        char    f_name[256];    // nazwa pliku
        off_t   f_size;         // rozmiar pliku w bajtach
        time_t  f_mtime;        // data ostatniej modyfikacji w sekundach
} f_info;

typedef struct file_list {
        bool checked;               // czy plik w porównywaniu został sprawdzony (domyślnie 0)
        bool type;                  // rodzaj (plik = 0/katalog = 1)
        char *path;             // sciezka do pliku

        // zapisanie informacji o pliku lub wskaznika do katalogu w tej samej pamieci
        union data{
                struct f_info file_i;
                struct f_list *sub_dir; 
        }

        struct f_list *next;
} f_list;

#endif