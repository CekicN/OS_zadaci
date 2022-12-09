#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
sem_t sem1;
sem_t sem2;
int br;
char **args;

void * pisi(void *arg)
{
    int i = *((int *)arg);
    int t = i;
    for(;i < br;i+=2)
    {
        if (t == 1)
        {
            sem_wait(&sem1);
        }
        else
            sem_wait(&sem2);

        printf("%s nit:%d\n",args[i],t);
        if (t == 1)
        {
            sem_post(&sem2);
        }
        else
            sem_post(&sem1);
        
    }
}
int main(int argc, char*argv[])
{
    pthread_t nit1;
    pthread_t nit2;

    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

    int arg[2];
    arg[0] = 1;
    arg[1] = 2;
    br = argc;
    args = (char **)malloc(argc*sizeof(char*));
    for (int i = 1; i < argc; i++)
    {
        args[i] = argv[i];
    }
    pthread_create(&nit1, NULL,(void *)&pisi,(void *)&arg[0]);
    pthread_create(&nit2, NULL,(void *)&pisi,(void *)&arg[1]);
    pthread_join(nit1, NULL);
    pthread_join(nit2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}