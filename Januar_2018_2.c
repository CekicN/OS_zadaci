#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Malo argumenata");
        exit(1);
    }
    
    int fd[2];
    pipe(fd);
    if (fork() == 0)
    {
        close(fd[1]);
        char fajl[20];
        read(fd[0], fajl, 20);
        FILE *f = fopen(fajl, "w");
        char tekst[200];
        while (read(fd[0], tekst, 200) > 0)
        {
            fputs(tekst,f);
        }
        close(fd[0]);
        fclose(f);
    }
    else
    {
        char fajl[20];
        strcpy(fajl, argv[2]);
        close(fd[0]);
        write(fd[1], fajl,20);
        FILE *f = fopen(argv[1], "r");
        char tekst[200];
        while (!feof(f))
        {
            fgets(tekst,200, f);
            write(fd[1], tekst, 200);
        }
        
        close(fd[1]);
        fclose(f);
    }
    
    
    return 0;
}