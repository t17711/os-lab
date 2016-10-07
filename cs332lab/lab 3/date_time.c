#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char* argv[])
{
 
  int status;
  int  child_id, parent_id;
    
  pid_t child = fork();
  
  if (child == 0){
    printf("Child process is : %d \n", (int)getpid());
    execl ("/usr/bin/date","date",NULL);
    printf ("\nEXECVP Failed\n");
  }
  else if (child == -1){
    printf("Fork failed\n");
  }
  
  
  waitpid(child, &status, 0);
  printf("Parent process is: %d\n", (int)getpid());
}
