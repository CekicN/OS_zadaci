#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

sem_t glavni;
sem_t func;

int broj;
void* Broji(void *arg)
{
    while (1)
    {
        sem_wait(&func);
        if(broj==99)
            break;
        for (int i = 0; i < broj; i++)
        {
            printf("%d\n", i);
            sleep(3);
        }
        sem_post(&glavni);
    }
    
    
    
}
int main(int argc, char* argv[])
{
    pthread_t nit;
    sem_init(&func,0,0);
    sem_init(&glavni,0,0);
    pthread_create(&nit, NULL, &Broji,NULL);
  
    printf("Unesi broj:");
    scanf("%d", &broj);
    while (broj != 99)
    {
        sem_post(&func);
        sem_wait(&glavni);

        printf("Unesi broj:");
        scanf("%d", &broj);
    }
    sem_post(&func);

    pthread_join(nit, NULL);

    sem_destroy(&glavni);
    sem_destroy(&func);
    return 0;
}