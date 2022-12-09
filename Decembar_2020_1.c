#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
int main(int argc, char * argv[])
{
    srand(time(0));
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    if(fork() == 0)
    {
        int p = fork();
        if(p == 0)
        {   //2
            close(fd1[1]);
            close(fd2[1]);
            close(fd2[0]);
            char *niz = (char *)malloc(20);
            read(fd1[0], niz,20);
            close(fd1[0]);
            FILE *f = fopen("KARAKTERI.txt", "w");
            fprintf(f,"%s", niz);
            free(niz);
            fclose(f);
        }
        else
        {
            //3
            close(fd1[1]);
            close(fd2[1]);
            close(fd1[0]);
            char *niz = (char *)malloc(20);
            read(fd2[0], niz,20);
            close(fd2[0]);
            printf("%s", niz);
            free(niz);
        }
    }
    else
    {
        close(fd1[0]);
        close(fd2[0]);
        char *niz = (char *)malloc(20);
        int s = 0;
        for(int i = 0; i< 20; i++)
        {
            niz[i] = (char)(rand()%256);
            s += niz[i];
        }
        if(s % 2 == 0)
        {
            write(fd1[1],niz,20);
        }
        else
        {
            write(fd2[1], niz,20);
        }
        close(fd1[1]);
        close(fd2[1]);
        free(niz);
    }
    
    return 0;
}
