#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{   
    int fd1[2];
    int fd2[2];
    if(pipe(fd1)<0)
    {
        printf("Greska kod pipe1");
        exit(1);
    }
    if(pipe(fd2)<0)
    {
        printf("Greska kod pipe2");
        exit(1);
    }
    srand(time(0));
    if(fork() == 0)
    {
        int niz[10];
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0],niz,10*sizeof(int));
        close(fd1[0]);
        for (int i = 0; i < 10; i++)
        {
            
            if (niz[i] % 3 == 0)
            {
                niz[i] += 25;
                write(fd2[1],&niz[i],sizeof(int)); 
            }
            
        }
        close(fd2[1]);
        

    }
    else
    {
        close(fd1[0]);
        close(fd2[1]);
        int niz[10];
        for (int i = 0; i < 10; i++)
        {
            niz[i] = rand()%100 + 200;
        }
        write(fd1[1],niz,10*sizeof(int));
        close(fd1[1]);
        int j = 0;
        int i = 0;
        int x;
        int niz1[10];
        while (j < 10)
        {
            int eof = read(fd2[0],&x,sizeof(int));
            if(eof != 0)
            {
                
                niz1[i++] = x;
            }
            j++;
        }
        
        close(fd2[0]);
        for (int k = 0; k < i; k++)
        {
            printf("%d, ", niz1[k]);
        }
        
    }
    return 0;
}