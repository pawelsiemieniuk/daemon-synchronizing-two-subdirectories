#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <utime.h>

#include "dir_op.h"
#include "log.h"
#include "var.h"

void createDir(char *pathname){
    int path_len = (int)strlen(pathname) + 1;
    int dst_len = (int)strlen(DST_NAME);

    if(path_len==dst_len) { return; }

    char *dir = calloc(path_len, sizeof(char));
    strcat(dir, DST_NAME);

    for(int i=dst_len-1; i < path_len; i++){
        if(pathname[i] == '/'){
            mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
            logAction("cpy_dir");
        }
        dir[i] = pathname[i];
    }
    mkdir(dir, S_IRWXU | S_IRWXG | S_IRWXO);
    free(dir);
}



void copyMap(char *path, f_info *finf)
{
    size_t fsize = (size_t)finf->f_size;
    char *src_map_pos, *dst_map_pos;


    char *fname = finf->f_name;
    char *src_path = calloc(strlen(path) + strlen(fname) + 2, sizeof(char));
    strcpy(src_path, path);
    strcat(src_path, "/");
    strcat(src_path, fname);
    struct utimbuf *t_buf = calloc(1, sizeof(struct utimbuf));
    t_buf->actime = finf->f_mtime;
    t_buf->modtime = finf->f_mtime;
    

    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char));  // Wyliczanie miejsca na scieżkę docelową
    strcat(dst_path, DST_NAME);
    for (int i = strlen(SRC_NAME); i < strlen(path); i++)
    {
        dst_path[i] = path[i];
    }
    if(F_SUBDIR){
        createDir(dst_path);
    }
    strcat(dst_path, "/");
    strcat(dst_path, fname);
    

    unsigned int src_fd = open(src_path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_RDWR | O_CREAT);

    ftruncate(dst_fd, fsize);

    struct stat st;
    fstat(src_fd, &st);
    fchmod(dst_fd, st.st_mode);

    src_map_pos = mmap(NULL, fsize, PROT_READ, MAP_SHARED, src_fd, 0);
    dst_map_pos = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, dst_fd, 0);

    memcpy(dst_map_pos, src_map_pos, fsize);

    munmap(src_map_pos, fsize);
    munmap(dst_map_pos, fsize);

    close(src_fd);
    close(dst_fd);

    utime(src_path, t_buf);
    utime(dst_path, t_buf);

    free(t_buf);
    free(src_path);
    free(dst_path);
}



void copyNormal(char *path, f_info *finf)
{
    size_t fsize = finf->f_size;
    char *fname = finf->f_name;
    char *buffer = calloc(fsize, sizeof(char));
    
    char *src_path = calloc(strlen(path) + strlen(fname) + 2, sizeof(char));
    strcpy(src_path, path);
    strcat(src_path, "/");
    strcat(src_path, fname);
    

    char *dst_path = calloc(strlen(DST_NAME) + strlen(path) - strlen(SRC_NAME) + strlen(fname) + 2, sizeof(char));// Wyliczanie miejsca na scieżkę docelową
    strcat(dst_path, DST_NAME);
    for (int i = strlen(SRC_NAME); i < strlen(path); i++)
    {
        dst_path[i] = path[i];
    }
    if(F_SUBDIR){
        createDir(dst_path);
    }

    strcat(dst_path, "/");
    strcat(dst_path, fname);

    unsigned int src_fd = open(src_path, O_RDONLY);
    unsigned int dst_fd = open(dst_path, O_WRONLY | O_CREAT);
    
    struct stat st;
    fstat(src_fd, &st);
    fchmod(dst_fd, st.st_mode);

    read(src_fd, buffer, fsize);
    write(dst_fd, buffer, fsize);
    
    close(src_fd);
    close(dst_fd);
    
    struct utimbuf *t_buf = calloc(1, sizeof(struct utimbuf));
    t_buf->actime = finf->f_mtime;
    t_buf->modtime = finf->f_mtime;

    utime(dst_path, t_buf);
    utime(src_path, t_buf);


    free(t_buf);
    free(src_path);
    free(dst_path);
    free(buffer);
}


