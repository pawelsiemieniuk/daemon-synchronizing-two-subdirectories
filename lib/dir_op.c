#include <dirent.h>
#include "file_op.h"

typedef struct file_info {
        char    f_name[256];    // nazwa pliku
        off_t   f_size;         // rozmiar pliku w bajtach
        time_t  f_mtime;        // data ostatniej modyfikacji w sekundach
} f_info;

typedef struct file_list {
        bool checked;               // czy plik w porównywaniu został sprawdzony (domyślnie 0)
        bool type;                  // rodzaj (plik = 0/katalog = 1)
        char *path;             // sciezka do pliku

        // zapisanie informacji o pliku lub wskaznika do katalogu w tej samej pamieci
        union data{
                struct f_info file_i;
                struct f_list *sub_dir; 
        }

        struct f_list *next;
} f_list;


readDir(f_list **list, char *pathname)
{
    // DIR *src_dir = opendir(pathname)
    // struct dirent *src_file = readdir(src_dir)

    // while(src_file)
    // {
    // unsigned char file_type = src_file->d_type
    // char filename[256] = src_file->d_name

    // struct stat *file_buff
    // char *filepath = pathname + filename
    // lstat(filepath, file_buff)

    // struct f_info *file_i
    // file_i->f_name = filename
    // file_i->f_size = file_buff->st_size
    // file_i->f_mtime = file_buff->st_mtim.tv_sec

    // struct f_list *src_list
    // if(file_type = DT_REG) 
    //    src_list->type = 0 
    // else 
    //    src_list->type = 1
    // src_list->path = pathname

    // if(src_list->type)
    //    src_list->data.file_i = file_i
    // else
    //    src_list->data.sub_dir
    //    readDir(filepath)

    // src_file = readdir(src_dir)
    // }
}

void copyDir(f_list *src_list){
        copyFile(src_list->path, src_list->file_i)
}

void cleanDir(f_list *dst_list){

}