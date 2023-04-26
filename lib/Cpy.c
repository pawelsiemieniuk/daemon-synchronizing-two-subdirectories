#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void cpy_mmap(file_info finf)
{
    void *src_map_pos, *dst_map_pos;
    size_t fsize = finf -> f_size;

    unsigned int src_fd = open(SRC_PATH, O_RDONLY);
    unsigned int dst_fd = open(DST_PATH, O_WRONLY | O_CREAT);

    src_map_pos = mmap(0, fsize, PROT_READ, MAP_SHARED, src_fd, 0);
    dst_map_pos = mmap(0, fsize, PROT_WRITE, MAP_SHARED, dst_fd, 0);

    memcpy(dst_map_pos, src_map_pos, fsize);

    munmap(src_map_pos, fsize);
    munmap(dst_map_pos, fsize);

    close(src_fd);
    close(dst_fd);
}

void cpy_normal(file_info finf)
{
    unsigned int src_fd = open(src, O_RDONLY);
    unsigned int dst_fd = open(dst, O_WRONLY | O_CREAT);

    size_t fsize = finf -> f_size;
    size_t *buffer = calloc(1, 1);
    
    read(src_fd, buffer, fsize);
    write(dst_fd, buffer, fsize);
    
    free(buffer);
    close(src_fd);
    close(dst_fd);
}