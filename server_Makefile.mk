Makefile
all: server

server: server.c 
	gcc proto.h string.h string.c server.h server.c -o server -Wall
	
clean:
	rm -f server

