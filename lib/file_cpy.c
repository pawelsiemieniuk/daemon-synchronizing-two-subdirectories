#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void cpy_mmap(file_info finf, char *src_path)
{
    void *src_map_pos, *dst_map_pos;
    size_t fsize = finf -> f_size;
    char *fname = finf->f_name;
    char *dst_path = calloc(strlen(DST_PATH) + strlen(src_path) - strlen(SRC_PATH) + strlen(fname) + 2);

    strcat(dst_path, DST_PATH);
    for (int i = strlen(SRC_PATH); i < strlen(src_path); i++)
    {
        strcat(dst_path, src_path[i]);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname);
    
    unsigned int src_fd = open(src_path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);

    src_map_pos = mmap(0, fsize, PROT_READ, MAP_SHARED, src_fd, 0);
    dst_map_pos = mmap(0, fsize, PROT_WRITE, MAP_SHARED, dst_fd, 0);

    memcpy(dst_map_pos, src_map_pos, fsize);

    munmap(src_map_pos, fsize);
    munmap(dst_map_pos, fsize);

    close(src_fd);
    close(dst_fd);

    free(fname);
    free(dst_path);
}

void cpy_normal(file_info finf, char *src_path)
{
    size_t *buffer = calloc(1, 1);
    size_t fsize = finf -> f_size;
    char *fname = finf->f_name;
    char *dst_path = calloc(strlen(DST_PATH) + strlen(src_path) - strlen(SRC_PATH) + strlen(fname) + 2);

    strcat(dst_path, DST_PATH);
    for (int i = strlen(SRC_PATH); i < strlen(src_path); i++)
    {
        strcat(dst_path, src_path[i]);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname);

    unsigned int src_fd = open(src_path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);
    
    read(src_fd, buffer, fsize);
    write(dst_fd, buffer, fsize);
    
    free(buffer);
    close(src_fd);
    close(dst_fd);
}
