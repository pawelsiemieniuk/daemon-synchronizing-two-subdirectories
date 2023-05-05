#include <sys/types.h>
#include <time.h>
#include <stdbool.h>

#ifndef VAR
#define VAR

// Sciezki bezwzgledne katalogu zrodlowego i docelowego
extern char *SRC_NAME, *DST_NAME;   

// Flaga -R przelaczajaca sprawdzanie podkatalogow
extern bool F_SUBDIR;         

// Rozmiar pliku po ktorym zostanie on zapisany przy pomocy mmap()
extern unsigned int BIG_FILE_SIZE;     

// Czas po ktorym nastapi ponowna synchronizacja
extern unsigned int SLEEP_TIME;       

// Informacje o pliku
typedef struct file_info {
        char    f_name[256];    // Nazwa pliku
        off_t   f_size;         // Rozmiar pliku w bajtach
        time_t  f_mtime;        // Data ostatniej modyfikacji w sekundach
} f_info;

// Struktura elementu listy plikow
typedef struct file_list {
        bool  checked;          // Czy plik w porownywaniu zostal sprawdzony
        char *path;             // Sciezka do pliku
        struct f_info *file_i;

        struct f_list *next;
} f_list;
#endif