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

#endif