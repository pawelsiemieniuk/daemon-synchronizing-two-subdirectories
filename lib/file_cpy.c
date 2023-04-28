#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <utime.h>

#include "dir_op.h"

void createDir(char *pathname){
    int path_len = strlen(pathname);
    int dst_len = strlen(DST_NAME);
    path_len -= dst_len;
    
    char *dir = calloc(path_len, sizeof(char));
    dir = DST_NAME;

    for(int i=dst_len-1; i < path_len; i++){
        if(pathname[i] == '/'){
            mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
        }
        dir[i] = pathname[i];
    }
}

void cpy_mmap(char *path, f_info *finf)
{
    void *src_map_pos, *dst_map_pos;
    size_t fsize = (size_t)finf->f_size;
    char *fname = finf->f_name;
    
    char *src_path = calloc(strlen(path) + strlen(fname) + 1, sizeof(char));
    strcpy(src_path, path);
    strcat(src_path, "/");
    strcat(src_path, fname);
    struct utimbuf *t_buf = calloc(1, sizeof(struct utimbuf));
    t_buf->actime = finf->f_mtime;
    t_buf->modtime = finf->f_mtime;
    

    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char));  // Wyliczanie miejsca na scieżkę docelową
    strcat(dst_path, DST_NAME);                                                                                     // Dopisanie początku scieżki docelowej
    for (int i = strlen(SRC_NAME); i < strlen(path); i++)                                                           // Dopisanie pośrednich katalogów
    {
        dst_path[i] = path[i];
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname); // Dopisanie nazwy pliku
    
    unsigned int src_fd = open(src_path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);

    src_map_pos = mmap(0, fsize, PROT_READ, MAP_SHARED, src_fd, 0);   // Mapowanie pliku źródłowego
    dst_map_pos = mmap(0, fsize, PROT_WRITE, MAP_SHARED, dst_fd, 0);  // Mapowanie pliku docelowego

    memcpy(dst_map_pos, src_map_pos, fsize);                          // Kopiowanie

    munmap(src_map_pos, fsize);                                       // Usuwanie mapowania
    munmap(dst_map_pos, fsize);

    close(src_fd);
    close(dst_fd);

    utime(src_path, t_buf);
    utime(dst_path, t_buf);

    free(src_path);
    free(dst_path);
}

void cpy_normal(char *path, f_info *finf)
{
    size_t *buffer = calloc(1, sizeof(size_t));
    size_t fsize = finf -> f_size;
    char *fname = finf->f_name;

    char *src_path = calloc(strlen(path) + strlen(fname) + 1, sizeof(char));
    strcpy(src_path, path);
    struct utimbuf *t_buf = calloc(1, sizeof(struct utimbuf));
    t_buf->actime = finf->f_mtime;
    t_buf->modtime = finf->f_mtime;
    strcat(src_path, "/");
    strcat(src_path, fname);
    
    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char)); // Wyliczanie miejsca na scieżkę docelową

    strcat(dst_path, DST_NAME);                             // Dopisanie początku scieżki docelowej
    for (int i = strlen(SRC_NAME); i < strlen(path); i++)   // Dopisanie pośrednich katalogów
    {
        dst_path[i] = path[i];
    }
    //createDir(dst_path);


    strcat(dst_path, "/");
    strcat(dst_path, fname);                                // Dopisanie nazwy pliku

    unsigned int src_fd = open(src_path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);
    
    read(src_fd, buffer, fsize);
    write(dst_fd, buffer, fsize);
    
    free(src_path);
    free(buffer);
    close(src_fd);
    close(dst_fd);

    utime(dst_path, t_buf);
    utime(src_path, t_buf);
}

