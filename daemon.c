#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include "dir_op.h"

unsigned int sleep_time = 300; // 5min
unsigned int big_file_size = 256; // ostatecznie mozna zmienic na wieksza
bool dir_check = false;






void sig_handler(int sig) {
        printf("Dziala\n");
        if(sig == SIGUSR1)
                printf("SIGUSR1\n");
}



int main(int argc, char **argv){
        signal(SIGUSR1, sig_handler);

        dir_list *src_list = calloc(1, sizeof(dir_list));
        dir_list *dst_list = calloc(1, sizeof(dir_list));

        for(int i=1; i<argc ;i++){
                if(argv[i][0] == '-'){
                        if(argv[i][1] == 't'){
                                i++;
                                sleep_time = (unsigned int)atoi(argv[i]); 
                        }
                        else if(argv[i][1] == 'R'){
                                i++;
                                dir_check = true;
                        }
                        else if(argv[i][1] == 's'){
                                i++;
                                big_file_size = (unsigned int)atoi(argv[i]);
                        }
                        else{
                                i++;
                        }
                }
                else if(!src_list){
                        DIR *src;
                        if((src = opendir(argv[i])) == NULL){
                                printf("Unable to open source directory.\n");
                                return -1;
                        }
                        push(src_list, src, argv[i]);
                }
                else if(!dst_list){
                        dst_dir = opendir(argv[i]);
                        // jesli nunll blad
                }
		else{
                        // za duzo argumentow
                }
        }
        if(dst_dir == NULL){
                // za malo argumentow
        }
        if(source_dir_name == destination_dir_name){
                //blad
        }

        // do testow
        for(int i=0; i<30; i++){
                printf("%d\n", i);
                sleep(1);
        }



return 0;
}
