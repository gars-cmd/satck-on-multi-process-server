FLAG = -Wall -g

all: server.o stack.o client.o client server 

server.o: server.c 
	gcc $(FLAG) -c server.c

client.o: client.c
	gcc $(FLAG) -c client.c

stack.o: stack.c
	gcc $(FLAG) -c stack.c

client: client.o stack.o
	gcc $(FLAG) -o client client.o stack.o

server: server.o stack.o
	gcc $(FLAG) -o server server.o stack.o

.PHONY: clean all

clean:
	rm -f *.o server client test
	