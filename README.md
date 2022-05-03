## Matala5
---
- In this assignment we will make a multithreading server to handle multiple client with thread and make them interact with a stack in the server.
- We use our own implementation of malloc, free, calloc. 


### How to run:
---
1. First unzip the folder.
2. Open a terminal into the folder of the assignment 
3. run `make all` to create the executable files 
4. run the server `./server`
5. open a new terminal in the same directory to run the client 
6. in the client terminal run `./client localhost` to connect to the server in the same computer or run `./client [PRIVATE IP ADDRESS]`  with your IP address to connect into the same LAN.
> Note : the client connection is not persistent, it will stop after one order is made


### List of possible commands:
---
- `PUSH [word]` To add a word to the server stack.
- `TOP` To show the element at the top of the stack.
- `POP` To remove the element at the top of the stack.
- `RESET` To clear all the stack.
- `EXIT` To exit the program to the client and also to the server.
- `SHOW` Show the all stack to the server.

>	Note: all the commands must be in UPPERCASE



