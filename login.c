//including header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "proto.h"  

/*assigning the  password to client for login*/
char pass[20] = PRE_PASS;


int intoAcc()
{
        /*variable to get choice from the user*/
    	int choice;
    	/*clear the screen of terminal*/
    	system("clear");

/*Label for admin*/
   adm:

    	//display admin panel.
    	printf("\n\t\t\t********************************************\n");
    	printf("\n\t\t\t|    ---     ~!! Chat Room !!~     ---        |\n");
    	printf("\n\n\t\t[1] Enter Chat Box\n\t\t[2] Exit\n\n\n\t\t Enter your choice:");
        //Enter the user choice:
    	scanf("%d", &choice); 	


    	//start switch_cases:
    	switch(choice)
    	{
		//To get enter chat room
    		case 1:
			return 1;
	
		//To exit from the program
    		case 2:
        		return 0;
        	default:
        	printf("Please enter the correct option!");
        	goto adm;
    	}
    	
}

/*Function to login */
int Login()
{
    	int attempts = 6;//validate the attempts of password entered

    	char client_room[10];//variable to store meeting room name

/*for indicating locations in the code*/
   label:

    	system("clear");

    	printf("\n\t\t\t->> Welcome to ChatRoom\n\t\t\t Enter your Meeting name: ");
    
    	//takes client_room as input the proceeds to nextline
    	scanf("%[^\n]s", client_room);

	//The function is used to compare two strings:
	//If meeting name entered incorrect:
 	if(strcmp(client_room, "grp3") != 0)
    	{
        	getchar();//reads a single character from user
        	printf("Wrong Meeting name!, please try again\n\n");

       	 	getchar();

        	goto label;//jump to the statement
    	}
    	
    	//if username entered is correct
    	else
    	{
       		char user_pass[20]; //variable to store password of meeting
    	
    	label2:
        	printf("\n\t\t\t>> Type password: ");
        	scanf("%s", user_pass);

        	//if password entered is incorrect.
        	if(strcmp(user_pass, pass) != 0)
        	{
            		attempts--;
			
			//if password is entered incorrect for 5 times
            		if(attempts == 0)
		    	{
		        	getchar();
		        	printf("\n\n");
		        
		        	printf("Too many wrong password ....");
		        	getchar();
		        	exit(0);
		    	}

            		printf("\n\t\t\t->>> Wrong password .login attempt remaining %d", attempts);

           	 	printf("\n\n");
            		getchar();

          

            		goto label2;
        	}

        	else
        	{
            		return intoAcc(); 		//redirect to the main account:
        	}
    	}
}

