#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
int main(int argc, char*argv[])
{
    srand(time(0));
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        int niz[10];
        close(fd[1]);
        read(fd[0],niz,10*sizeof(int));
        close(fd[0]);

        for (int i = 0; i < 10; i++)
        {
            if(niz[i] % 2 != 0)
            {
                printf("%d\n", niz[i]);
            }
            else
                printf("Paran broj");
        }
        
    }
    else
    {
        close(fd[0]);
        int niz[10];
        for (int i = 0; i < 10; i++)
        {
            niz[i] = rand() % 100;
        }
        
        write(fd[1],niz,10*sizeof(int));
        close(fd[1]);
    }
    
    return 0;
}