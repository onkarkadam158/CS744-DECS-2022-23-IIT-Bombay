#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int i=0;

void dosome(char *name)
{
    int count=0;
    for(i=0;i<5;i++){
        sleep(rand()%4);
        printf("Done pass%d for %s\n",i,name);
    }
}
int main()
{
    
    printf("before fork : %d\n", (int) getpid());
    pid_t pid=fork();
    srand((int) pid);
    if(pid < 0)
        printf("fork failed\n");
    else if(pid==0){
        printf("I am the child%d\n",(int) getpid());
        dosome("Child");
        exit(42);
    }
    
    //parent part of code
    printf("I am parent waiting for child to end\n");
    //sleep(10);
    dosome("Parent");

    int status=0;
    pid_t childpid=wait(0);
    printf("Parent knows child %d finished with status \n",(int) childpid);
    int childReturnValue=WEXITSTATUS(status);
    printf("  Return value was%d \n",childReturnValue);
    
    sleep(60);

    return 0;
}