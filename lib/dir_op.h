#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#ifndef DIR_OP
#define DIR_OP

extern char *SRC_NAME, *DST_NAME;               // sciezki bezwzgledne katalogu zrodlowego i docelowego
extern bool dir_check;                          // flaga -R przelaczajaca sprawdzanie podkatalogow

// informacje o pliku na liscie
typedef struct file_info {
        char    f_name[256];                    // nazwa pliku
        off_t   f_size;                         // rozmiar pliku w bajtach
        time_t  f_mtime;                        // data ostatniej modyfikacji w sekundach
} f_info;

// element listy plikow
typedef struct file_list {
        bool  checked;                          // czy plik w porównywaniu został sprawdzony (domyślnie 0)
        char *path;                             // sciezka do pliku
        struct f_info *file_i;

        struct f_list *next;
} f_list;

void readDir(f_list **list, char *pathname);    // wczytywanie plikow ze sciezki do listy
void copyDir(f_list **src_list);                // kopiowanie plikow na liscie z katalogu zrodlowego do katalogu docelowego
void cleanDir(f_list **dst_list);               // usuwanie zbednych plikow z katalogu docelowego

#endif