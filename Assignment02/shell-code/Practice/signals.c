#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{

    int pid = fork();
    if (pid < 0)
    {
        return 1;
    }
    else if (pid == 0)
    {
        while (1)
        {
            printf("Print something in child while loop\n");
            usleep(50000);
        }
    }
    else
    {
        kill(pid, SIGSTOP);
        int t;
        do
        {
            printf("Enter no of seconds to give for execution \n");
            scanf("%d", &t);
            if (t > 0)
            {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        } while (t > 0);

        // kill(pid,SIGSTOP);
        // sleep(5);
        // kill(pid,SIGCONT);
        // sleep(5);
        kill(pid, SIGKILL);
        int wc = wait(NULL);
    }

    return 0;
}