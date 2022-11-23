#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


int main()
{
    for (int i=1;i<5;i++){
        fork();
        printf("%d My PID Is ::%d\n" , i,(int) getpid());
    }

    //sleep(1);

    printf("---->>> My PID Is %d\n", (int) getpid());
  

    return 0;
}