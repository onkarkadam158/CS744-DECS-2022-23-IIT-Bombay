/* run using ./server <port> */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <signal.h>
#include <netinet/in.h>

#include <pthread.h>
#include "http_server.cpp"
pthread_mutex_t mutexQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condQueue = PTHREAD_COND_INITIALIZER;

int open = 1;

int i = 1;
int flag = 1;
int mainsockfd;
queue<int> sockfds;

void error(char *msg)
{
  perror(msg);
}
// catching and handling SIGINT or CTRL + C signal
void SIGINT_Handler(int a)
{
  open = 0;
  close(mainsockfd);
  pthread_cond_broadcast(&condQueue);

  // exit(0);
}

void manageclient(int input)
{
  int currsockfd = input;
  /* read message from client */
  char buffer[256];
  bzero(buffer, 256);
  int n = read(currsockfd, buffer, 255);
  if (n < 0)
    printf("ERROR reading from socket");
  if (n == 0)
  {
    close(currsockfd);
  }
  // pthread_exit(NULL);

  // printf("Here is the message request: %s", buffer);
  HTTP_Response *objResp = handle_request(string(buffer));
  // cout<<objResp->get_string();
  const char *response = objResp->get_string().c_str();

  /* send reply to client */
  n = write(currsockfd, response, objResp->get_string().size());
  if (n < 0)
    printf("ERROR writing to socket");
  close(currsockfd);
  delete objResp;
}

void *threadwork(void *arg)
{
  while (open)
  {
    int currsockfd = -1;
    pthread_mutex_lock(&mutexQueue); // mutext lock for shared memeory access

    pthread_cond_wait(&condQueue, &mutexQueue); // condition variable
    if (!sockfds.empty())
    {
      currsockfd = sockfds.front(); // pop the front fd of queue FCFS
      sockfds.pop();
    }
    pthread_mutex_unlock(&mutexQueue);
    if (currsockfd != -1)
      manageclient(currsockfd); // mutext unlocking for shared memeory access
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

  int portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  signal(SIGINT, SIGINT_Handler);
  if (argc < 2)
  {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  /* create socket */

  mainsockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (mainsockfd < 0)
    printf("ERROR opening socket");

  /* fill in port number to listen on. IP address can be anything (INADDR_ANY)
   */
  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  /* bind socket to this port number on this machine */

  if (bind(mainsockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    printf("ERROR on binding");

  // creating thread pool of size thread_pool_size (default=8) initiating threads
  int thread_pool_size = 4;
  pthread_t thpool[thread_pool_size];
  for (int i = 0; i < thread_pool_size; i++)
  {
    pthread_create(&thpool[i], NULL, &threadwork, NULL); // threads get created
  }
  while (open)
  {
    // cout<<"Waiting for New request...\n";
    /* listen for incoming connection requests */

    listen(mainsockfd, 10000);
    clilen = sizeof(cli_addr);

    /* accept a new request, create a newsockfd */
    int newsockfd = accept(mainsockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
      printf("ERROR on accept");

    // here avalable thread will deal with new incoming client request
    // locking unlocking on enqueing
    pthread_mutex_lock(&mutexQueue);
    sockfds.push(newsockfd);
    pthread_cond_signal(&condQueue);
    pthread_mutex_unlock(&mutexQueue);
  }

  // pthread_mutex_destroy(&mutexQueue);
  // pthread_cond_destroy(&condQueue);

  // frees up the threads and closes sockets
  for (int i = 0; i < thread_pool_size; i++)
  {
    pthread_join(thpool[i], NULL); // threads get terminated
  }
  return 0;
}

/*
To compile the server:

g++ simple_server.cpp -o server

to run the server:
./server 5002

here 5002 is port number

now open chrome browser and got to this address
http://localhost:5002/

*/