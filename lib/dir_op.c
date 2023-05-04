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
                }   
                else if(dir_check && strcmp(filename, "..") && strcmp(filename, ".") && file_type == DT_DIR){
                        long dir_loc = telldir(dir);
                        closedir(dir);
                        readDir(list, file_path);
                        
                        dir = opendir(pathname);
                        seekdir(dir, dir_loc);
                }
                
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
                        strcat(file_path, tmp_list->path);
                        strcat(file_path, "/");
                        strcat(file_path, tmp_file->f_name);

                        if(HasContents(file_path)){
                                tmp_list = delDir (tmp_list->next);
                        }
                        else            
                                delFile(file_path);
                }
                tmp_list = tmp_list->next;
        }
}

f_list delDir(f_list *tmp_list){
        while(!tmp_list->checked)
        {
                f_info *tmp_file = tmp_list->file_i;
                char *file_path = calloc(strlen(tmp_list->path) + strlen(tmp_file->f_name) + 2, sizeof(char));
                strcat(file_path, tmp_list->path);
                strcat(file_path, "/");
                strcat(file_path, tmp_file->f_name);
                if(HasContents(file_path)){
                        tmp_list = delDir (file_path);
                }
                else            
                        delFile(file_path);

                tmp_list = tmp_list->next;
        }
        return tmp_list;
}

bool HasContents(char *file_path){
        DIR *dir;
        if((dir = opendir(file_path)) == NULL) // czy plik jest katalogiem
        {
                return false;
                free(dir);
        } 
                
        if(readdir(dir) == NULL) // czy katalog ma zawartosc
                return true;
        return false;

}
