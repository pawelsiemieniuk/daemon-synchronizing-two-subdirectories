#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "dir_op.h"

void cpy_mmap(char *path, f_info *finf)
{
    void *src_map_pos, *dst_map_pos;
    size_t fsize = finf -> f_size;
    char *fname = finf->f_name;
    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char)); // Wyliczanie miejsca na scieżkę docelową

    strcat(dst_path, DST_NAME); // Dopisanie początku scieżki docelowej
    for (int i = strlen(SRC_NAME); i < strlen(path); i++) // Dopisanie pośrednich katalogów
    {
        strcat(dst_path, path[i]);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname); // Dopisanie nazwy pliku
    
    unsigned int src_fd = open(path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);

    src_map_pos = mmap(0, fsize, PROT_READ, MAP_SHARED, src_fd, 0); // Mapowanie pliku źródłowego
    dst_map_pos = mmap(0, fsize, PROT_WRITE, MAP_SHARED, dst_fd, 0); // Mapowanie pliku docelowego

    memcpy(dst_map_pos, src_map_pos, fsize); // Kopiowanie

    munmap(src_map_pos, fsize); // Usuwanie mapowania
    munmap(dst_map_pos, fsize);

    close(src_fd);
    close(dst_fd);

    //free(fname);
    free(dst_path);
}

void cpy_normal(char *path, f_info *finf)
{
    size_t *buffer = calloc(1, 1);
    size_t fsize = finf -> f_size;
    char *fname = finf->f_name;
    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char)); // Wyliczanie miejsca na scieżkę docelową

    strcat(dst_path, DST_NAME); // Dopisanie początku scieżki docelowej
    for (int i = strlen(SRC_NAME); i < strlen(path); i++) // Dopisanie pośrednich katalogów
    {
        strcat(dst_path, path[i]);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname); // Dopisanie nazwy pliku

    unsigned int src_fd = open(path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);
    
    read(src_fd, buffer, fsize);
    write(dst_fd, buffer, fsize);
    
    close(src_fd);
    close(dst_fd);
    
    free(buffer);
    free(dst_path);
    free(fname);
}
