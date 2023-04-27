#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "file_op.h"
#include "list_op.h"
//#include "dir_op.h"

char *SRC_NAME = NULL, *DST_NAME = NULL;
bool dir_check = false;

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
        printf("---------f\n\n");
        DIR *dir = opendir(pathname);
        struct dirent *read_file;
        printf("---------g\n\n");

        while((read_file = readdir(dir)) != NULL)
        {
                unsigned char file_type = read_file->d_type;
                char *filename = read_file->d_name;
                printf("---------b\n\n");
                char *file_path = calloc(strlen(pathname) + strlen(filename) + 1, sizeof(char));
                strcat(file_path, pathname);
                strcat(file_path, "/");
                strcat(file_path, filename);
                printf("---------c\n\n");

                struct stat *file_buff = calloc(1, sizeof(stat));
                lstat(file_path, file_buff);
                printf("---------d\n\n");
                
                if(file_type == DT_REG){
                printf("---------e\n\n");
                        (*list) = push((*list), 
                                        pathname, 
                                        filename, 
                                        file_buff->st_size, 
                                        file_buff->st_mtim.tv_sec);
                }   
                else if(dir_check && file_type == DT_DIR){
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
                if(!tmp_list->checked)
                        copyFile((*src_list)->path, (*src_list)->file_i);
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
                        char *file_path = calloc(strlen(tmp_list->path) + strlen(tmp_file->f_name), sizeof(char));
                        strcat(file_path, tmp_list->path);
                        strcat(file_path, tmp_file->f_name);

                        delFile(file_path);

                        free(file_path);
                }
                tmp_list = tmp_list->next;
        }
}
