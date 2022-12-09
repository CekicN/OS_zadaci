#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void* Broji(void *arg)
{
    int broj = *((int *)arg);
    for (int i = 0; i < broj; i++)
    {
        printf("%d\n", i);
        sleep(3);
    }
    
}
int main(int argc, char* argv[])
{
    pthread_t nit;
    int broj;
    printf("Unesi broj:");
    scanf("%d", &broj);

    while (broj != 99)
    {
        pthread_create(&nit,NULL,&Broji,&broj);
        pthread_join(nit,NULL);
        pthread_cancel(nit);
        printf("Unesi broj:");
        scanf("%d", &broj);
    }
    
    return 0;
}