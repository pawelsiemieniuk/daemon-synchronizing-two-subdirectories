#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "file_op.h"
#include "list_op.h"

char *SRC_NAME = NULL, *DST_NAME = NULL;
bool dir_check = false;

bool HasContents(char *dir_path){
        DIR *dir = opendir(dir_path);
        if(readdir(dir) == NULL) // czy katalog ma zawartosc
                return true;
        return false;
}

void readDir(f_list **list, char *pathname)
{
        DIR *dir = opendir(pathname);
        struct dirent *read_file;

        while((read_file = readdir(dir)) != NULL)
        {
                unsigned char file_type = read_file->d_type;
                char *filename = read_file->d_name;
                char *file_path = calloc(strlen(pathname) + strlen(filename) + 2, sizeof(char));
                strcat(file_path, pathname);
                strcat(file_path, "/");
                strcat(file_path, filename);

                struct stat *file_buff = calloc(1, sizeof(struct stat));
                lstat(file_path, file_buff);
                
                if(file_type == DT_REG){
                        (*list) = push((*list), 
                                        pathname, 
                                        filename, 
                                        file_buff->st_size, 
                                        file_buff->st_mtime);
                        //free(file_path); bo info zapisane w file_buff chyba?
                }   
                else if(dir_check && strcmp(filename, "..") && strcmp(filename, ".") && file_type == DT_DIR){
                        long dir_loc = telldir(dir);
                        closedir(dir);
                        readDir(list, file_path);
                        
                        dir = opendir(pathname);
                        seekdir(dir, dir_loc);
                }
                
                free(file_path);
                free(file_buff);
        }
        closedir(dir);
}

void copyDir(f_list **src_list){
        f_list *tmp_list = (*src_list);
        while(tmp_list){
                if(!(tmp_list->checked))
                        copyFile(tmp_list->path, tmp_list->file_i);
                tmp_list = tmp_list->next;
        }
}

void cleanDir(f_list **dst_list){
        f_list *tmp_list = (*dst_list);
        while(tmp_list)
        {
                if(!tmp_list->checked)
                {
                        f_info *tmp_file = tmp_list->file_i;
                        char *file_path = calloc(strlen(tmp_list->path) + strlen(tmp_file->f_name) + 2, sizeof(char));
                        char *dir_path = calloc(strlen(tmp_list->path) + 1, sizeof(char));
                        
                        strcat(dir_path, tmp_list->path);

                        strcat(file_path, dir_path);
                        strcat(file_path, "/");
                        strcat(file_path, tmp_file->f_name);

                        delFile(file_path);
                        
                        if(!HasContents(dir_path)){
                                delDir(dir_path);
                        }
                                
                }
                tmp_list = tmp_list->next;
        }
}

