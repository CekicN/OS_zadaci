#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sem1;
sem_t sem2;
void *Upisi(void * arg)
{
    int i = *((int *)arg);
    int f = i;
    printf("%d", i);
    FILE *fa;
    
    for ( ; i < 20; i+=2)
    {
        if (f == 1)
        {
            sem_wait(&sem1);
        }
        else
            sem_wait(&sem2);
        fa = fopen("izlaz.txt", "a");
        fprintf(fa,"%d\n", i);
        fclose(fa);
        if(f == 1)
        {
            sem_post(&sem2);
        }
        else
            sem_post(&sem1);
        
    }
    

}
int main(int argc, char* argv[])
{
    pthread_t nit1;
    pthread_t nit2;

    sem_init(&sem1,0,1);
    sem_init(&sem2,0,0);
    int arg[2];
    arg[0] = 1;
    arg[1] = 2;
    pthread_create(&nit1,NULL,(void *)&Upisi,(void *)&arg[0]);
    pthread_create(&nit2,NULL,(void *)&Upisi,(void *)&arg[1]);
    pthread_join(nit1,NULL);
    pthread_join(nit2,NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    
    return 0;
}