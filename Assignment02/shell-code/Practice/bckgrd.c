#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handle_sigtstp(int sig)
{
    printf("Stop not allowed\n");
}

void handle_sigcont(int sig)
{
    printf("\nEnter some number x:");
    fflush(stdout);
}

int main(int argc, char *argv[])
{

    struct sigaction sa;
    sa.sa_handler = &handle_sigcont;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);

    // signal(SIGSTP,&handle_sigstp);

    int x;
    printf("Enter some number x:\n");
    scanf("%d", &x);
    printf("Result %d*5 = %d\n", x, x * 5);

    return 0;
}

/*
sleep 5 &  // bakgrounded
sleep 7 &

bg , fg
jobs , jobs -l all background processes
ctrl + z stopped ctrl + c terminated
nohup, if did fg even after terminal closed and opened again
*/
