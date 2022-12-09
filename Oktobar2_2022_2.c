#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char* argv[])
{
    
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        
    }
    else
    {
        close(fd[0]);
        char *buff = (char *)malloc(80);
        sprintf(buff,"%d",fd[1]);
        
        execl("program2", "program2",,buff,NULL);

    }
    
}