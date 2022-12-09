#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
int main(int argc, char * argv[])
{
    srand(time(0));
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    if (fork() == 0)
    {
        close(fd1[1]);
        close(fd2[0]);
        int niz[5];
        read(fd1[0],niz,5*sizeof(int));
        for(int i = 0; i < 5; i++)
        {
            if(niz[i] % 2 == 0)
            {
                write(fd2[1], &niz[i], sizeof(int));
            }
        }
        close(fd2[1]);
    }
    else
    {
        close(fd1[0]);
        close(fd2[1]);
        int niz[5];
        for (int i = 0; i < 5; i++)
        {
            niz[i] = rand() % 100;
        }

        write(fd1[1], niz,5*sizeof(int));
        close(fd1[1]);
        int s = 0;
        int niz1[5];
        int x;
        for (int i = 0; i < 5; i++)
        {
            if (read(fd2[0], &x,sizeof(int)) != 0)
                niz1[s++] = x;
        }
        printf("%d\n", s);
        close(fd2[0]);
    }
    
    return 0;
}