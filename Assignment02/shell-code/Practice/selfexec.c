#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int height = 42;

int main(int argc, char *argv[])
{

    printf("I am in selfexec  %d\n", (int)getpid());
    height--;
    printf("Height %d \n", height);
    if (argc != 2)
    {
        printf("Pass 1 argument as an integer\n");
        exit(1);
    }
    int n = atoi(argv[1]);

    printf("--->>>%d...\n", n);

    // char *args[]={"./selfexec","Hello", "World",NULL};
    if (n != 0)
    {
        char nMinus1[10];
        sprintf(nMinus1, "%d", n - 1);
        execl(argv[0], argv[0], nMinus1, NULL);
    }

    printf("Farewell selfexec%d\n", (int)getpid());

    return 0;
}