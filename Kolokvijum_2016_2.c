#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
struct grupa
{
    char naziv[20];
    int n;
};
void *modifikuj(void *arg)
{
    struct grupa *grupa = (struct grupa*)arg;
    FILE *f = fopen(grupa->naziv,"r");
    char recenica[80];
    int k = 0;
    while (!feof(f) && k < grupa->n)
    {
        fgets(recenica,80,f);
        recenica[0] = tolower(recenica[0]);
        for (int i = 1; i < strlen(recenica); i++)
        {
            recenica[i] = toupper(recenica[i]);
        }
        printf("%s\n", recenica);
        k++;
    }
    fclose(f);


}
int main(int argc, char* argv[])
{
    if(argc < 2)
        exit(1);
    pthread_t nit;
    struct grupa grupa;
    strcpy(grupa.naziv,argv[1]);
    grupa.n = atoi(argv[2]);
    pthread_create(&nit,NULL,(void *)&modifikuj,(void *)&grupa);

    pthread_join(nit,NULL);

    return 0;
}