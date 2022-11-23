#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int favnum = 42;

int main(int argc, char *argv[])
{

    printf("I am in execDemo%d\n", (int)getpid());

    printf("fav num is %d\n", favnum);

    // with L comma separated arguments
    // with V Vector ie and array of strings
    // with p is for path normal search path for executable
    char *args[] = {"./helloExec", "Hello", "World", NULL};
    execvp("./helloExec", args);

    // execl(args[0],"Hello", "World");

    printf("Farewell execdemo%d\n", (int)getpid());

    printf("\n");
    return 0;
}