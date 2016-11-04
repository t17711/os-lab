#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char ** args){

	int status;
	int child_id;
	char input[50];// =malloc(50);
	int j = 0;	
 	char *q = "quit"; // to quit
	int s = strlen(q);
	while(1){
		printf("Enter a command of maximum 50 char to quit\n");
		scanf("%s",input);
			
		// check for quit
		if (memcmp (input, q,s) == 0) break;
		
		// fork if not quit
		pid_t child = fork();
		char * arg[] = {input,NULL};
		if (child == 0)
		{
			// run the arguement
			execvp(arg[0],arg);
			printf("failed to execute %s \n", input);
			exit(1);
		}
		else if(child == -1){
			printf("error in fork\n");
		}

		waitpid(child,&status,0);

	}


}
