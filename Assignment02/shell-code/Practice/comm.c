#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handle_sigusr1(int sig)
{
    printf("Remember multiplication is repetitive addition\n ");
}
int main(int argc, char *argv[])
{

    int pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0)
    {
        // child process
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else
    {
        struct sigaction sa;
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);
        // parent process
        int x;
        printf("What is result of 3*5:\n");
        scanf("%d", &x);
        if (x == 15)
            printf("Right!!\n");
        else
            printf("Wrong\n");
        wait(NULL);
    }
    return 0;
}