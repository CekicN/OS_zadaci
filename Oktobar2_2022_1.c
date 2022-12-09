#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
void* Broji(void* arg)
{
    int n = *((int *)arg);
    for (int i = n; i > 0; i--)
    {
        printf("%d\n", i);
        sleep(1);
    }
    
}
int main(int argc, char* argv[])
{
    int x;
    char *t;
    t = (char *)malloc(4* sizeof(char));
    pthread_t nit;
    printf("Unesi broj:");
    scanf("%s", t);
    while (strcmp(t,"KRAJ") != 0)
    {
        x = atoi(t);
        pthread_create(&nit,NULL,&Broji,&x);
        pthread_join(nit,NULL);
        pthread_cancel(nit);
        printf("Unesi broj:");
        scanf("%s", t);
    }
    
    
    free(t);
    return 0;
}