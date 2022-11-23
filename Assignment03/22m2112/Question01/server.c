/* run using ./server <port> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <pthread.h>

int i = 1;
int sockfd[10];

void error(char *msg)
{
  perror(msg);
  exit(1);
}

void *manageclient(void *input)
{
  int index = *(int *)input;
  // looping for multiple requests from a single client
  while (1)
  {
    /* read message from client */
    char buffer[256];
    bzero(buffer, 256);
    int n = read(sockfd[index], buffer, 255);
    if (n < 0)
      error("ERROR reading from socket");

    if (n == 0)
      pthread_exit(NULL);
    printf("Here is the message: %s", buffer);

    /* send reply to client */
    n = write(sockfd[index], buffer, 18);
    if (n < 0)
      error("ERROR writing to socket");
  }
}

int main(int argc, char *argv[])
{
  int portno;
  socklen_t clilen;
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  if (argc < 2)
  {
    fprintf(stderr, "ERROR, no port provided\n");
    exit(1);
  }

  /* create socket */
  sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd[0] < 0)
    error("ERROR opening socket");

  /* fill in port number to listen on. IP address can be anything (INADDR_ANY)
   */

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  /* bind socket to this port number on this machine */
  if (bind(sockfd[0], (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");

  pthread_t th[10]; // array of thread one thread per client diff from thread pool as threads are not created beforehand
  // looping from multiple clients
  while (1)
  {
    /* listen for incoming connection requests */
    listen(sockfd[0], 5);
    clilen = sizeof(cli_addr);

    /* accept a new request, create a newsockfd */
    int newsockfd = accept(sockfd[0], (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
      error("ERROR on accept");

    // ith socfd is assigned to ith client/(terminal)
    sockfd[i] = newsockfd;
    int index = i;
    pthread_create(&th[i], NULL, &manageclient, &index); // parameter paseed to function getting excecuted by thread
    i++;
  }
  // frees up the threads and closes sockets
  while (i--)
  {
    pthread_join(th[i], NULL);
    close(sockfd[i]);
  }
  return 0;
}