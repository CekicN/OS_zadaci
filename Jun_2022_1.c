#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int n;
void * Sortiraj(void * arg)
{
    int * niz = (int*)arg;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (niz[i] > niz[j])
            {
                int pom = niz[i];
                niz[i] = niz[j];
                niz[j] = pom;
            }
            
        }
        
    }
    
}
int main(int argc, char* atgv[])
{
    pthread_t nit;
    int niz[20];
    int x;
    n = 0;
    char *c = (char *)malloc(4*sizeof(char));
    FILE*f = fopen("ulaz.txt", "r");
    while (!feof(f))
    {
        fscanf(f,"%s",c);
        x = atoi(c);
        niz[n++] = x;
    }
    pthread_create(&nit,NULL,&Sortiraj,niz);
    pthread_join(nit,NULL);

    for (int i = 0; i < n; i++)
    {
        printf("%d, ",niz[i]);
    }
    free(c);
    return 0;
}