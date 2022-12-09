#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
int main(int argc, char* argv[])
{
    int fd[2];
    pipe(fd);
    if(fork() == 0)
    {
        close(fd[1]);
        char *path = (char *)malloc(20*sizeof(char));
        char *rec = (char *)malloc(20*sizeof(char));
        read(fd[0],path,20*sizeof(char));
        read(fd[0],rec,10*sizeof(char));
        close(fd[0]);
        char*recenica = (char *)malloc(100*sizeof(char));
        char*reci = (char *)malloc(20*sizeof(char));
        FILE* f = fopen(path, "r");
        int i = 1;
        char delim[] = {' ', ',', '\n', '\t'};
        while(!feof(f))
        {
            fgets(recenica,100,f);
            //printf("%s\n", recenica);
            reci = strtok(recenica,delim);
            int f = 0;
            while (reci != NULL && f == 0)
            {
                //printf("%s\n", reci);
                if (strcmp(reci,rec) == 0)
                {
                    f = 1;
                }
                
                reci = strtok(NULL,delim);
            }

            //printf("%s", reci);
            if (f == 1)
            {
                printf("U recenici: %d\n", i);
            }
            i++;
        }
        free(path);
        free(recenica);
        free(rec);
        free(reci);
    }
    else
    {
        close(fd[0]);
        char *path = (char *)malloc(20*sizeof(char));
        char *rec = (char *)malloc(20*sizeof(char));
        printf("Ucitaj putanju do datoteke:");
        scanf("%s", path);
        printf("Unesi kljucnu rec:");
        scanf("%s", rec);

        write(fd[1],path,20*sizeof(char));
        write(fd[1],rec,10*sizeof(char));
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}