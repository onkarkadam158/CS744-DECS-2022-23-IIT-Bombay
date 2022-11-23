Submission contain two file for Question 01 of DECS Assignment 03
1) server.c
2) client.c

open terminal run server.c by using follwing two commands

gcc server.c -o server
./server 5002

here 5002 is port number

now open another terminal and run client.c using following two commands

gcc client.c -o client
./client localhost 5002

open multiple terminals (as multiple clients) and run client. c to test the multi-client multithreading implementation.
