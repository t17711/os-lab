#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char** argv)
{
  if (argc > 2){
    printf("Too many arguements\n");
    return 0;
  }
  /*i will call ls with -A for almost all files
  -l lists its time, size, author, author group,, permission
*/
  char* arg[] = {"ls","-l","-A",argv[1],NULL};
  int child = fork();

  if (child == 0){
    printf("The pid of child is: %d\n", (int)getpid());
    execvp (arg[0],arg);
    printf ("EXECVP Failed\n");
  }
  else if (child == -1){
    printf("Fork failed\n");
  }
}
