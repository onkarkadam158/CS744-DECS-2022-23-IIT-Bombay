--------------------------------------------------------------------------------------------
First compile and run the server code:

To compile the server:

g++ simple_server.cpp -o server

to run the server:
taskset -a -c 0 ./server 5002

here 5002 is port number

now open chrome browser and got to this address you can see an basic HTML Page (Optional) 
http://localhost:5002/

----------------------------------------------------------------------------------------------

Now to run load_gen.c (For single experiment)
compile: gcc load_gen.c -o load
(run using: taskset -a -c 1 ./load_gen localhost <server port> <number of concurrent users> <think time (in s)> <test duration (in s)> ) (Optional)

To generate a load for multiple experiments I wrote a bash scripts which will run load_gen for multiple time for different set of inputs.
The result of all experiments will be stored in dataresult.csv

-----------------------------------------------------------------------------------------------

To plot the graph I wrote a python code in print_graph.py file.
Once you have generated result for experiments, run this file with following command to generate a graph

python3 print_graph.py

a graph will be printed.

-----------------------------------------------------------------------------------------------

Valgrind Testing:
Run following command in terminal to check the memory leaks problems
valgrind --leak-check=full ./server 8000

and this should output following:
All heap blocks were freed -- no leaks are possible
with all memory leaks equals to zero for example:
Possibly lost=0
Definitely lost=0
etc.
