#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int mails=0;
pthread_mutex_t mutex;
// void* routine() {
//     for(int i=0;i<2000000;i++)  //Race condition
//     {
//         pthread_mutex_lock(&mutex);
//         mails++;
//         pthread_mutex_unlock(&mutex);
//     }
        

void* routine() {
    for(int i=0;i<200000;i++)  //Race condition
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
        
}
int main(int argc, char* argv[]) {
    // pthread_t p1, p2;
    // pthread_mutex_init(&mutex,NULL);
    // if (pthread_create(&p1, NULL, &routine, NULL) != 0) {
    //     return 1;
    // }
    // if (pthread_create(&p2, NULL, &routine, NULL) != 0) {
    //     return 2;
    // }
    // if (pthread_join(p1, NULL) != 0) {
    //     return 3;
    // }
    // if (pthread_join(p2, NULL) != 0) {
    //     return 4;
    // }
    // pthread_mutex_destroy(&mutex);
    // printf("No. of miails %d\n",mails);


    // THread array
    int n=4;
    pthread_t th[n];
    for(int i=0;i<n;i++){
        if(pthread_create(&th[i],NULL,&routine,NULL)){
            perror("cannotcreate thread\n");
            return 1;
        }
        printf("Thread %d has started\n",i);
        printf("No. of miails %d\n",mails);


    }
    for(int i=0;i<n;i++){
        if(pthread_join(th[i],NULL)){
            return 2;
        }
        printf("Thread %d has ended\n",i);
    }
    pthread_mutex_destroy(&mutex);
    printf("No. of miails %d\n",mails);
    return 0;
}