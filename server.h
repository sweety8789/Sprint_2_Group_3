//header file
#ifndef LIST
#define LIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#define MAX_CLIENTS 5//maximum number of clients

//structure for client node, its a doubly linked list
typedef struct ClientNode 
{
    int data;//store data of socket
    struct ClientNode* prev;//link to prevoius node
    struct ClientNode* link;//link to next node
    char ip[16];//ip address
    char name[31];//username
} ClientList;

//node creation for client list
ClientList *newNode(int sockfd, char* ip) 
{
    ClientList *np = (ClientList *)malloc( sizeof(ClientList) );//create new node np
    np->data = sockfd;//store socket information
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);//copies the IP to the node
    strncpy(np->name, "NULL", 5);//copies name to the node
    return np;
}

#endif // LIST

