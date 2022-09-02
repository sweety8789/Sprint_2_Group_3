#Makefile

all: client
 
client:	client.c
	gcc proto.h string.h client.h login.c string.c client.c -o client -Wall

clean:
	rm -f client
	
