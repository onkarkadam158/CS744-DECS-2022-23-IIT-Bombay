#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int i = 0;

void dosome(char *name)
{
    int count = 0;
    for (i = 0; i < 5; i++)
    {
        sleep(rand() % 4);
        printf("Done pass%d for %s\n", i, name);
    }
}
int main()
{
    while (1)
    {

        int num = 0;
        scanf("%d\n", &num);
        printf("Number entered %d\n", num);

        int pid1 = fork();
        if (pid1 < 0)
        {
            printf("error creating process\n");
            return 1;
        }
        else if (pid1 == 0)
        {
            printf("Child started%d\n", (int)getpid());
            sleep(10);
            printf("Finished execution%d\n", (int)getpid());
            exit(EXIT_SUCCESS);
        }
        else
        {
            // printf("I am in parent\n");
        }

        int status;

        int pid1_res = waitpid(pid1, &status, WNOHANG);
        // if(WIFEXITED(status))
        //   printf("child terminated pid : %d\n",pid1);
        // printf("Waited for %d\n",pid1_res);
    }
    // int pid2=fork();
    // if(pid2 < 0){
    //     printf("error creating process\n");
    //     return 1;
    // }
    // else if(pid2==0){
    //     sleep(1);
    //     printf("Finished execution%d\n",(int) getpid());
    //     return 0;
    // }
    // int pid1_res = wait(NULL);
    // printf("Waited for %d\n",pid1_res);
    // int pid2_res = wait(NULL);
    // printf("Waited for %d\n",pid2_res);

    // int pid1_res=waitpid(pid1,NULL,0);
    // printf("Waited for %d\n",pid1_res);
    // int pid2_res = waitpid(pid2,NULL,0);
    // printf("Waited for %d\n",pid2_res);

    return 0;
}