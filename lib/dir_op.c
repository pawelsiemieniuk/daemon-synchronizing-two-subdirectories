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

<<<<<<< Updated upstream
/*typedef struct file_info {
        char    f_name[256];    // nazwa pliku
        off_t   f_size;         // rozmiar pliku w bajtach
        time_t  f_mtime;        // data ostatniej modyfikacji w sekundach
} f_info;


typedef struct file_list {
        bool  checked;               // czy plik w porównywaniu został sprawdzony (domyślnie 0)
        bool  type;                  // rodzaj (plik = 0/katalog = 1)
        char *path;                 // sciezka do pliku
        struct f_info *file_i;

        struct f_list *next;
} f_list;
*/

void readDir(f_list **list, char *pathname)
{
        printf("path - %s\n", pathname);
=======

void readDir(f_list **list, char *pathname)
{
>>>>>>> Stashed changes
        DIR *dir = opendir(pathname);
        struct dirent *read_file;

        while((read_file = readdir(dir)) != NULL)
        {
                unsigned char file_type = read_file->d_type;
                char *filename = read_file->d_name;
<<<<<<< Updated upstream
                //int path_len = strlen(pathname) + strlen(filename) + 1;
=======
>>>>>>> Stashed changes
                char *file_path = calloc(strlen(pathname) + strlen(filename) + 1, sizeof(char));
                strcat(file_path, pathname);
                strcat(file_path, "/");
                strcat(file_path, filename);

                struct stat *file_buff = calloc(1, sizeof(struct stat));
                lstat(file_path, file_buff);
                
                if(file_type == DT_REG){
<<<<<<< Updated upstream
                        printf("--%s/%s\n\n", pathname, filename);
=======
>>>>>>> Stashed changes
                        (*list) = push((*list), 
                                        pathname, 
                                        filename, 
                                        file_buff->st_size, 
                                        file_buff->st_mtime);
                }   
                else if(dir_check && strcmp(filename, "..") && strcmp(filename, ".") && file_type == DT_DIR){
                        long dir_loc = telldir(dir);
                        closedir(dir);
<<<<<<< Updated upstream
                        printf("FILEPATH %s\n", file_path);
=======
>>>>>>> Stashed changes
                        readDir(list, file_path);
                        
                        dir = opendir(pathname);
                        seekdir(dir, dir_loc);
                }
                
                free(file_buff);
        }

        /*f_list *tmp_l = (*list);
        while(tmp_l){
                f_info *tmp_i = tmp_l->file_i;
                printf("%s/%s | %d\n", tmp_l->path, tmp_i->f_name, tmp_l->checked);
                tmp_l = tmp_l->next;
        }*/

        closedir(dir);
}

void copyDir(f_list **src_list){
        f_list *tmp_list = (*src_list);
        while(tmp_list){
                printf("PATH %s\n", tmp_list->path);
                if(!tmp_list->checked)
                        copyFile(tmp_list->path, tmp_list->file_i);
                tmp_list = tmp_list->next;
        }
}

void cleanDir(f_list **dst_list){
        f_list *tmp_list = (*dst_list);
        while(tmp_list)
        {
                printf("PATH %s\n", tmp_list->path);
                if(!tmp_list->checked)
                {
                        f_info *tmp_file = tmp_list->file_i;
                        char *file_path = calloc(strlen(tmp_list->path) + strlen(tmp_file->f_name) + 1, sizeof(char));
                        strcat(file_path, tmp_list->path);
                        strcat(file_path, "/");
                        strcat(file_path, tmp_file->f_name);

                        printf("CLEAN %s\n", file_path);
                        delFile(file_path);
                }
                tmp_list = tmp_list->next;
        }
}
