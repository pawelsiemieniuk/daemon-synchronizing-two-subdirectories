#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct dirList
{
	char dirName[256];
	struct dirList *next;
} dirList;

void readList(dirList *list)
{
	puts("Cale te foldery");
	int i=0;
	while(list != NULL)
	{
		printf("%d",i);	
		printf("  %s\n", list->dirName);
		i++;
		list = list->next;
	}
}

int main (int argc, char **argv)
{	
	int i=0;
	DIR *dir;				//otworzony katalog
	struct dirent *entry;	//obecnie zapisywany plik
	struct dirList *myList = NULL;
	struct dirList *current = NULL;
	
	if ((dir = opendir(argv[1])) == NULL)
    	perror("Blad podczas otwierania pliku z opendir()");		
  	else 
  	{
		puts("Znalezione pliki");
		while ((entry = readdir(dir)) != NULL)  //wczytuje plik do struktury entry 
		{
			if((strcmp(entry->d_name,".") == 0) || (strcmp(entry->d_name, "..") == 0)) {} //jakies oznaczenia hierarchi plików
			else
			{
				printf("%d",i);	
				printf("  %s  %d\n", entry->d_name, entry->d_type); // wypisuje nazwe pliku/katalogu i typ 4 = katalog 8 = plik
				i++;
				if((int)entry->d_type == 4)
				{
					if(myList == NULL)
					{
						myList = (dirList *) malloc(sizeof(dirList));
						strcpy(myList->dirName, entry->d_name);
						myList->next = NULL;
					}
					else
					{
						current = myList->next;
						while(current != NULL)
						{
							current = current->next;
						}
						current = (dirList *) malloc(sizeof(dirList));
						strcpy(current->dirName, entry->d_name);
						current->next = NULL;
					}
				}
			}
		}
		readList(myList);
		closedir(dir);
  	}
}
