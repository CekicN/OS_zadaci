#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
void* Stampaj(void* arg)
{
    char *recenica = (char *)arg;
    recenica[0]=toupper(recenica[0]);
    recenica[strlen(recenica)-1] = '.';
    recenica[strlen(recenica)] = '\0';
    printf("%s", recenica);
    free(recenica);
}
void* Sortiraj(void *arg)
{
    //char *recenica = (char *)malloc(80);
    char *recenica = (char *)arg;
    char*reci = (char *)malloc(20);
    char delim[] = {' ', ','};
    
    char **nizreci = (char **)malloc(10*sizeof(char*));
    for (int i = 0; i < 10; i++)
    {
        nizreci[i] = (char *)malloc(20);
    }

    int i = 0;
    reci = strtok(recenica,delim);
    while (reci != NULL)
    {
        strcpy(nizreci[i++], reci);
        reci = strtok(NULL,delim);
    }
    free(reci);
    
    char *rec = (char *)malloc(20);
    for (int j = 0; j < i-1; j++)
    {
        for (int k = j+1; k < i; k++)
        {
            if (strcmp(nizreci[j],nizreci[k]) > 0)
            {
                strcpy(rec,nizreci[j]);
                strcpy(nizreci[j],nizreci[k]);
                strcpy(nizreci[k], rec);
            }
        }   
    }
    free(rec);
    char *recenica1 = (char *)malloc(80);
    
    strcpy(recenica1,"");
    for (int j = 0; j < i; j++)
    {
        
        strcat(recenica1,nizreci[j]);
        strcat(recenica1," ");
    }
    recenica1[strlen(recenica1)]='\0';
    strcpy(recenica,recenica1);
    


    for (int j = 0; j < 10; j++)
    {
        free(nizreci[j]);
    }
    free(nizreci);

   free(recenica1);
    
}
int main(int argc, char* argv[])
{
    char *recenica = (char *)malloc(80);
    printf("Unesi recenicu:");
    gets(recenica);
    pthread_t nit1;
    pthread_t nit2;
    
    pthread_create(&nit1,NULL,Sortiraj,recenica);
    pthread_join(nit1,NULL);
    pthread_create(&nit2,NULL,Stampaj,recenica);
    pthread_join(nit1,NULL);
    free(recenica);
    printf("KRAJ");
    return 0;
}