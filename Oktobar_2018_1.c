#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<string.h>
sem_t sem1;
sem_t sem2;
FILE *fa;
void *Prva(void * arg)
{
    char * fajl = arg;
    FILE* f= fopen(fajl, "r");
    fa = fopen("zbir.txt", "w");
    char* linija = (char*)malloc(80);
    char *li = (char*)malloc(80);
    char broj[2];
    
    int i = 1;
    while (!feof(f))
    {
        strcpy(li, "");
        strcat(li,fajl);
        strcat(li,":");
        sprintf(broj,"%d", i);
        strcat(li, broj);
        strcat(li,":");

        sem_wait(&sem1);
        fgets(linija,80,f);
        strcat(li,linija);
        li[strlen(li)] = '\0';

        fputs(li,fa);
        i++;
        sem_post(&sem2);
    }
    
    fclose(f);
    free(linija);
    free(li);
}
void* Druga(void * arg)
{
    char * fajl = arg;
    FILE* f= fopen(fajl, "r");
    char* linija = (char*)malloc(80);
    char *li = (char*)malloc(80);
    char broj[2];
    
    int i = 1;
    while (!feof(f))
    {
        strcpy(li, "");
        strcat(li,fajl);
        strcat(li,":");
        sprintf(broj,"%d", i);
        strcat(li, broj);
        strcat(li,":");

        sem_wait(&sem2);
        fgets(linija,80,f);
        strcat(li,linija);
        li[strlen(li)] = '\0';

        fputs(li,fa);
        i++;
        sem_post(&sem1);
    }
    fclose(f);
    fclose(fa);
    free(linija);
    free(li);
}
int main(int argc, char* argv[])
{
    pthread_t nit1;
    pthread_t nit2;
    if (argc < 2)
    {
        exit(1);
    }
    
    char *file1 = (char *)malloc(20);
    char *file2 = (char *)malloc(20);

    strcpy(file1, argv[1]);
    strcpy(file2, argv[2]);

    sem_init(&sem1, 0,1);
    sem_init(&sem2, 0,0);

    pthread_create(&nit1, NULL, (void*)&Prva, (void *)file1);
    pthread_create(&nit2, NULL, (void*)&Druga, (void *)file2);

    pthread_join(nit1, NULL);
    pthread_join(nit2, NULL);
    
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}