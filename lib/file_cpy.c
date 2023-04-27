#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <utime.h>

#include "dir_op.h"

void cpy_mmap(char *path, f_info *finf)
{
    void *src_map_pos, *dst_map_pos;
    size_t fsize = finf->f_size;
    char *fname = finf->f_name;

    char *src_path = calloc(strlen(path) + strlen(fname) + 1, sizeof(char));
    strcpy(src_path, path);
    strcat(src_path, "/");
    strcat(src_path, fname);
    struct utimbuf t_buf;
    t_buf.actime = finf->f_mtime;
    t_buf.modtime = finf->f_mtime;

    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char));
    strcat(dst_path, DST_NAME);
    for (int i = strlen(SRC_NAME); i < strlen(path); i++)
    {
        strcat(dst_path, path[i]);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname);
    
    unsigned int src_fd = open(path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);

    src_map_pos = mmap(0, fsize, PROT_READ, MAP_SHARED, src_fd, 0);
    dst_map_pos = mmap(0, fsize, PROT_WRITE, MAP_SHARED, dst_fd, 0);

    memcpy(dst_map_pos, src_map_pos, fsize);

    utime(src_path, &t_buf);

    munmap(src_map_pos, fsize);
    munmap(dst_map_pos, fsize);

    close(src_fd);
    close(dst_fd);


    free(src_path);
    free(dst_path);
}

void cpy_normal(char *path, f_info *finf)
{
    size_t *buffer = calloc(1, 1);
    size_t fsize = finf -> f_size;
    char *fname = finf->f_name;
    
    char *src_path = calloc(strlen(path) + strlen(fname) + 1, sizeof(char));
    strcpy(src_path, path);
    strcat(src_path, "/");
    strcat(src_path, fname);
    struct utimbuf *t_buf = calloc(1, sizeof(struct utimbuf));
    t_buf->actime = finf->f_mtime;
    t_buf->modtime = finf->f_mtime;

    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char));
    strcat(dst_path, DST_NAME);
    for (int i = strlen(SRC_NAME); i < strlen(path); i++)
    {
        strcat(dst_path, path[i]);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname);

    unsigned int src_fd = open(path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);
    
    read(src_fd, buffer, fsize);
    write(dst_fd, buffer, fsize);
    
    utime(src_path, t_buf);
    
    free(src_path);
    free(buffer);
    close(src_fd);
    close(dst_fd);
}
