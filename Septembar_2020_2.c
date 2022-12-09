#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[])
{
    FILE* f = fopen(argv[2], "w");
    int fd[2];
    pipe(fd);
    if(argc < 2)
        exit(1);
    if(fork() == 0)
    {

        char *buff[16] = {0};
        close(fd[0]);
        for (int i = 1; i < argc-1; i++)
        {
            buff[i-1] = argv[i];
        }
        printf("%s", buff[0]);
        dup2(fd[1],STDOUT_FILENO);
        if(execvp(buff[0], buff) == -1)
        {
            printf("Greska");
            exit(1);
        }
        close(fd[1]);

    }
    else
    {
        wait(NULL);
        close(fd[1]);
        char c;
        while(read(fd[0], &c, 1) > 0)
        {
            if(c == 'b')
                c = 'B';
            fputc(c,f);
        }
        close(fd[0]);
    }
    fclose(f);
    return 0;
}