/* run using ./server <port> */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bits/stdc++.h>

#include <netinet/in.h>

#include <pthread.h>
#include "http_server.cpp"

int i = 1;
int sockfd; // client listening socketd fd

void error(char *msg)
{
  perror(msg);
  exit(1);
}

// managing request of a client
void *manageclient(void *input)
{
  int sockfd = *(int *)input;

  /* read message from client */
  char buffer[256];
  bzero(buffer, 256);
  int n = read(sockfd, buffer, 255);
  if (n < 0)
    printf("ERROR reading from socket");

  // printf("Here is the message request: %s", buffer);
  HTTP_Response *objResp = handle_request(string(buffer));

  // cout<<objResp->get_string();
  const char *response = objResp->get_string().c_str();

  /* send reply to client */
  n = write(sockfd, response, objResp->get_string().size());
  if (n < 0)
    printf("ERROR writing to socket");
  close(sockfd);
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

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    printf("ERROR opening socket");

  /* fill in port number to listen on. IP address can be anything (INADDR_ANY)
   */

  bzero((char *)&serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);

  /* bind socket to this port number on this machine */

  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    printf("ERROR on binding");

  /* listen for incoming connection requests */
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);

  // looping on multiple requests from multiple clients one thread per request
  while (1)
  {
    /* accept a new request, create a newsockfd */
    int newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
      printf("ERROR on accept");

    // sockfd[i]=newsockfd;
    int index = newsockfd;
    pthread_t th;

    pthread_create(&th, NULL, &manageclient, &index); // creating thread allocating it to manageclient
    pthread_detach(th);
  }
  // frees up the threads and closes sockets
  // while(i--){
  //   pthread_join(th[i],NULL);
  //   close(sockfd[i]);
  // }
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