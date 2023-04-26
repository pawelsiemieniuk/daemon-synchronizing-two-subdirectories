#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#include "./lib/file_op.h"
#include "./lib/dir_op.h"
#include "./lib/log.h"

/* Przeniesione do file_op.h i dir_op.h

//unsigned int sleep_time = 300; // 5min
//unsigned int big_file_size = 256; // ostatecznie mozna zmienic na wieksza


char *SRC_NAME = "", *DST_NAME = "";

*/
unsigned int sleep_time = 10;  // 5min
pthread_t *bed_t;               // Wskaznik na strukture przechowujaca informacje o watku


void signalHandler(int sig) { if(sig == SIGUSR1) pthread_cancel(*bed_t); }

void *bedThread() { sleep(sleep_time); }


int main(int argc, char **argv){

        struct sigaction *new_act = calloc(1, sizeof(sigaction));
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
                        i++;
                }
                else if(!SRC_NAME){
                        /*if(stat(argv[i], NULL) == -1){
                                printf("Unable to open source directory.\n", argv[i]);
                                return -1;
                        }*/
                        SRC_NAME = argv[i];
                }
                else if(!DST_NAME){
                        /*if(stat(argv[i], NULL) == -1){
                                printf("Unable to open destination directory.\n");
                                return -1;
                        }*/
                        DST_NAME = argv[i];
                }
		else{
                        // za duzo argumentow
                        // można pominąć
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
        

        f_list *src_list = calloc(1, sizeof(f_list));
        f_list *dst_list = calloc(1, sizeof(f_list));

        bed_t = calloc(1, sizeof(pthread_t));

        while(1){
            logAction("wake_up");
            //readDir(&src_list, SRC_NAME);
            //readDir(&dst_list, DST_NAME);

            //fileListCompare(&src_list, &dst_list);
            //copyDir(&src_list);
            cleanDir(&dst_list);

            logAction("sleep");
            pthread_create(bed_t, NULL, bedThread, NULL);       // Tworzenie watku
            pthread_join(*bed_t, NULL);                         // Wstrzymanie procesu do konca watku
        }

        return 0;
}
