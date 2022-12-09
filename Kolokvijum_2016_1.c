#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
int main(int argc, char* argv[])
{
    srand(time(0));
    int fd1[2];
    int fd2[2];

    pipe(fd1);
    pipe(fd2);

    if(fork() == 0)
    {
        close(fd1[1]);
        close(fd2[0]);

        char recenica[80];
        read(fd1[0], recenica, 80);
        close(fd1[0]);
        int flag = (rand() % 2)+1;

        if(flag == 2)
        {
            recenica[0] = toupper(recenica[0]);
        }
        write(fd2[1],recenica,80);
        close(fd2[1]);
    }
    else
    {
        close(fd1[0]);
        close(fd2[1]);
        char recenica[80];
        gets(recenica);

        write(fd1[1], recenica, 80);
        close(fd1[1]);
        char recenica1[80];
        read(fd2[0], recenica1, 80);
        close(fd2[0]);

        if(strcmp(recenica,recenica1) == 0)
            printf("Nije modifikovna");
        else
            printf("Modifikovana");
    }
    return 0;
}