#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
int niz[10];

pthread_mutex_t mutex;
pthread_cond_t paran;
int jelparan = 0;
void * pisi(void * arg)
{   
    //int n = *((int *)arg);
    pthread_mutex_lock(&mutex);
    while (!jelparan)
    {
        pthread_cond_wait(&paran,&mutex);
    }
    for (int i = 0; i < 10; i++)
    {
        printf("%d, ", niz[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
}

void* modifikuj(void * arg)
{   
    //int n = *((int *)arg);
    pthread_mutex_lock(&mutex);
    int p = rand()%10;
    niz[p] += rand()%21 - 10;
    int s = 0;
    for (int i = 0; i < 10; i++)
    {
        s += niz[i];
    }
    if (s % 2 == 0)
    {
        jelparan = 1;
        pthread_cond_signal(&paran);
    }
    
    sleep(3);
    pthread_mutex_unlock(&mutex);
}
int main(int argc, char* argv[])
{

    pthread_t niti[5];
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&paran,NULL);

    for (int i = 0; i < 10; i++)
    {
        niz[i] = rand() % 20+1;
    }
    pthread_create(&niti[4], NULL,(void*)&pisi, NULL);
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&niti[i], NULL, (void*)&modifikuj,NULL);
    }
    
    for (int i = 0; i < 4; i++)
    {
        pthread_join(niti[i], NULL);
    }
    pthread_join(niti[4], NULL);
    return 0;
}