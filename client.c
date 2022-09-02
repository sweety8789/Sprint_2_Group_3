/*creating TCP socket for client side and using various system calls like send(), connect(),  close() to connect to the server */
 
//including header files for this particular code

#include"client.h"
#include "proto.h"
#include "string.h"

// Global variables
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char nickname[LENGTH_NAME] = {};

int Login();   //declaration of login function
void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

void recv_msg_handler() {
    char receiveMessage[LENGTH_SEND] = {};
    while (1) {
        int receive = recv(sockfd, receiveMessage, LENGTH_SEND, 0);
        if (receive > 0) {
            printf("\r%s\n", receiveMessage);
            str_overwrite_stdout();
        } else if (receive == 0) {
            break;
        } else { 
            // -1 
        }
    }
}

void send_msg_handler() {
    char message[LENGTH_MSG] = {};
    while (1) {
        str_overwrite_stdout();
        while (fgets(message, LENGTH_MSG, stdin) != NULL) {
            str_trim_lf(message, LENGTH_MSG);
            if (strlen(message) == 0) {
                str_overwrite_stdout();
            } else {
                break;
            }
        }
        send(sockfd, message, LENGTH_MSG, 0);
        if (strcmp(message, "exit") == 0) {
            break;
        }
    }
    catch_ctrl_c_and_exit(2);
}

/* Main function to create a TCP socket , and also creating system calls like bind() and listen() and accept connection from the client*/
int main()
{   	

    if(!Login())
        {
        	printf("Successfully Logout\n\n");
   	} 
    	
    	//if the login is successful
    else
    	{
    signal(SIGINT, catch_ctrl_c_and_exit); //sigint to stop the current process and return to its main loop 

    // Naming
    printf("Please enter your name: ");
    getchar(); 
    if (fgets(nickname, LENGTH_NAME, stdin) != NULL) 
    {
        str_trim_lf(nickname, LENGTH_NAME);
    }
    if (strlen(nickname) < 2 || strlen(nickname) >= LENGTH_NAME-1) 
    {
        printf("\nName must be more than one and less than thirty characters.\n");
        exit(EXIT_FAILURE);
    }
//Creating socket for client side
 
 /*it contains the domain(AF_INET is used for communicating with process on different host), type(sock_stream is the communication type), protocol value */
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1)    //Checking condition for socket creation
    {
        printf("Fail to create a socket.");  //error condition
        exit(EXIT_FAILURE);
    }

    // Socket information
    struct sockaddr_in server_info, client_info; // declaring a sockaddr_in in structure.
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    
//memset() used to fill block of memory with a particular value    
    memset(&server_info, 0, s_addrlen);  // contains starting address of memory to be filled, value to be filled, size of variable
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;  //info to which family it belongs (IPV4)
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");   //address creation
    server_info.sin_port = htons(8888);  //port address creation

    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    if (err == -1) 
    {
        printf("Connection to Server error!\n");
        exit(EXIT_FAILURE);
    }
    
    // Names
    getsockname(sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
    getpeername(sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
/*here the inet_ntoa() function returns the server_info and the address into dotted decimal notation and the nthos() function converts the usigned integer from network byte to host byte order*/
    printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("You are: %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    send(sockfd, nickname, LENGTH_NAME, 0);
//creating a thread for sending message
    pthread_t send_msg_thread;
    if (pthread_create(&send_msg_thread, NULL, (void *) send_msg_handler, NULL) != 0) 
    {
        printf ("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }
//creating a thread for receiving message
    pthread_t recv_msg_thread;
    if (pthread_create(&recv_msg_thread, NULL, (void *) recv_msg_handler, NULL) != 0) 
    {
        printf ("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    while (1) 
    {
        if(flag) 
        {
            printf("\nBye\n");
            printf("Successfully Logout\n\n");
            
            break;
        }
    }
    
    close(sockfd);
   } 
    return 0;
}

