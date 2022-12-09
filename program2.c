#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main(int argc, char* argv[])
{
    int fd = atoi(argv[2]);
    char *buff = (char *)malloc(80);
    strcpy(buff,argv[1]); 

    char* rec = (char *)malloc(20);
    rec = strtok(buff," ");
    while (rec != NULL)
    {
        write(fd, rec,20);
        rec = strtok(NULL, " ");
    }
    close(fd);
    free(buff);
    free(rec);
    return 0;
}