#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char* argv[])
{
    
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        char* rec = (char *)malloc(20);
        close(fd[1]);
        while (read(fd[0], rec, 20) > 0)
        {
            printf("%s\n", rec);
        }
        close(fd[1]);
        free(rec);
        
    }
    else
    {
        close(fd[0]);
        char buff[80];
        strcpy(buff, "");
        for(int i = argc; i > 0; i--)
        {
            strcat(buff,argv[i]);
            strcat(buff, " ");
        }
        char buf[20];
        sprintf(buf,"%d", fd[1]);
        printf("%s", buff);
        execl("program2", "program2",buff, buf,NULL);

    }
    
}