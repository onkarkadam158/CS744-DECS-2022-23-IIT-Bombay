#include<stdio.h>
#include<unistd.h>


int favnum=84;

int main(int argc, char *argv[])
{
    printf("helloExec.c: \n");
        
    printf("fav num is %d\n", favnum);

    printf("My PID: %d\n", getpid());

    printf("My Arguments: \n");
    for (int  i = 0; i < argc; i++){
        printf("%s\t",argv[i]);
    }


    printf("\n");
    return 0;
}