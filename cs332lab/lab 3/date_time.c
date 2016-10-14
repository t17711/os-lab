#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char* argv[])
{
 
  int status;
  int  child_id, parent_id;

  // fork child to show time
  pid_t child = fork();

  // i will execute this command
  char * arg[]  = {"/usr/bin/date","date",NULL};
  
  if (child == 0){
    printf("Child process is : %d \n", (int)getpid());
    
    // just call date command in linux that does this;
    execl(arg[0], arg[1],arg[2]);
     printf ("\nEXECVP Failed\n");
  }
  else if (child == -1){
    printf("Fork failed\n");
  }
  
  // wait for child to end
  waitpid(child, &status, 0);
  printf("Parent process is: %d\n", (int)getpid());
}
