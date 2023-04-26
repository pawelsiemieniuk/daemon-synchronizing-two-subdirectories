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
        DIR *src_dir = opendir(pathname);
        struct dirent *src_file;

        while((src_file = readdir(src_dir)) != NULL)
        {
                unsigned char file_type = src_file->d_type;
                char filename[256] = src_file->d_name;
                char *file_path = pathname;
                strcat(file_path, '/');
                strcat(file_path, filename);

                struct stat *file_buff = calloc(1, sizeof(stat));
                lstat(file_path, file_buff);

                
                if(file_type == DT_REG){
                        (*list) = push((*list), 
                                        pathname, 
                                        filename, 
                                        file_buff->st_size, 
                                        file_buff->st_mtim.tv_sec);
                }   
                else if(file_type == DT_DIR)
                        readDir(list, file_path);
        }
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
                        delFile((*dst_list)->path);
                }
                tmp_list = tmp_list->next;
        }
}
