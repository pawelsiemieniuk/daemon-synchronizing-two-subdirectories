#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>

#include "./lib/file_op.h"
#include "./lib/list_op.h"
#include "./lib/dir_op.h"
#include "./lib/log.h"


unsigned int sleep_time = 300;  // czas po ktorym nastapi ponowna synchronizacja
pthread_t *bed_t;               // wskaznik na strukture przechowujaca informacje o watku


void signalHandler(int sig) { if(sig == SIGUSR1) pthread_cancel(*bed_t); }

void *bedThread() { sleep(sleep_time); }


int main(int argc, char **argv){
        struct sigaction *new_act = calloc(1, sizeof(struct sigaction));
        new_act->sa_handler = signalHandler;

        sigaction(SIGUSR1, new_act, NULL);

        for(int i=1; i<argc ;i++){
                if(argv[i][0] == '-'){
                        if(argv[i][1] == 't')
                                sleep_time = (unsigned int)atoi(argv[++i]);
                        else if(argv[i][1] == 'R')
                                dir_check = true;
                        else if(argv[i][1] == 's')
                                big_file_size = (unsigned int)atoi(argv[++i]);
                }
                else if(!SRC_NAME){
                        SRC_NAME = realpath(argv[i], NULL);
                }
                else if(!DST_NAME){
                        DST_NAME = realpath(argv[i], NULL);
                }
        }

        if(!DST_NAME){
            printf("Not enough arguments.\n");
            return -1;
        }
        if(SRC_NAME == DST_NAME){
            printf("Source directory and destination directory are the same. Please provide correct paths.\n");
            return -1;
        }
        

        f_list *src_list;
        f_list *dst_list;

        bed_t = calloc(1, sizeof(pthread_t));


        while(1){
            src_list = (f_list *)calloc(1, sizeof(f_list));
            dst_list = (f_list *)calloc(1, sizeof(f_list));
            src_list = NULL;
            dst_list = NULL;

            logAction("wake_up");

            readDir(&src_list, SRC_NAME);
            readDir(&dst_list, DST_NAME);

            fileListCompare(&src_list, &dst_list);
                
            copyDir(&src_list);
            cleanDir(&dst_list);

            clean(src_list);
            
            logAction("sleep");

            pthread_create(bed_t, NULL, bedThread, NULL);       // tworzenie watku
            pthread_join(*bed_t, NULL);                         // wstrzymanie procesu do zakonczenia watku
        }

        return 0;
}
