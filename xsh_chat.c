#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char USERNAMEA[] = "userA";
char PASSWORDA[] = "passA";
char USERNAMEB[] = "userB";
char PASSWORDB[] = "passB";

local chat (ushort in, ushort out, char *name){
	
	char message[30];
	int i;
	int exit = 0;

	while(exit == 0){
		for(i=0; i<30; i++){
			message[i] = '\0';
		}

		read(in, message, 30);

		if ( strncmp(message, "exit", 4) == 0) {
			exit =1;
			strcpy(message, "--> Left the chatroom <--\n");
		}
		fprintf(out, "%s: ", name);
		write(out, message, strlen(message));
	}
	return OK;
}

command xsh_chat(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]){

	char username[20];
	char password[20];
	
	//logged in status
	int status =0;
	
	do{
		//prompt user for login information
		fprintf(stdout, "\nUsername: ");
		read   (stdin,  username, 20);
		
		fprintf(stdout, "Password: ");
		read   (stdin,  password, 20);
		
		if((strncmp(username, USERNAMEA, 5) ==0 && strncmp(password, PASSWORDA, 5) == 0 ) || (strncmp(username, USERNAMEB, 5) == 0 && strncmp(password, PASSWORDB, 5) == 0 )){
				username[5] = '\0';
				fprintf (stdout, "\nWelcome %s to the room of chats!\n\n", username);
				fprintf (stdout, "To leave chat room, type 'exit'\n");
				status = 1;
		}else{
			fprintf (stdout, "\nIncorrect, try again!\n");
		}

		
	}while(status == 0);

	if(stdin == TTY0){
		chat (TTY0, TTY1, username);
	}
	else if(stdin == TTY1){
		chat (TTY1, TTY0, username);
	}

	return OK;
}
