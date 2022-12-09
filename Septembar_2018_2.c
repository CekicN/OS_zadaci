#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        int x;
        close(fd[1]);
        for (int i = 0; i < 20; i++)
        {
            read(fd[0], &x, sizeof(int));
            if(x %3==0)
                printf("%d\n", x);
        }
        close(fd[0]);
        
    }
    else
    {
        int x;
        close(fd[0]);
        for(int i = 0; i < 20;i++)
        {
            x = rand()%100+100;
            write(fd[1], &x, sizeof(int));
        }
        close(fd[1]);
    }
    

    return 0;
}