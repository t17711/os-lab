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

  int status = 0;
  // child processes
  pid_t child1, child2;

  // set file names
  char * file1 = "destination1.txt";
  char * file2 = "destination2.txt";
  char * file3 = "source.txt";

  char * proc1 = "./Prcs_P1";
  char * proc2 = "./Prcs_P2";

  // create commands
    char * gen1[] = {proc1, file1 ,NULL};
  char * gen2[] = {proc1, file2 , NULL};
  
  child1 = fork(); // create a child
 

  // create 1st file
  if (child1 == 0){
    execv(gen1[0], gen1);
    printf("EXCEV failed \n");
    return 0;
  }
  else if(child1 == -1){
    printf("Fork failed for 1\n");
    return 0 ;
  }

  // wait for previous process
  sleep(2);
  waitpid(child1, &status, 0);

  // create secod process
  child2 = fork();
   
  if (child2 == 0){
    execv(gen2[0], gen2);
    printf("EXCEV failed \n");
    return 0 ;
  }
  else if(child2 == -1){
    printf("Forlk ailed for 2\n");
    return 0 ;
  }

  // wait for processes
  waitpid(child2, &status, 0);

  // now do second process

   
  char* replace[] = {proc2, file3, file1, file2,NULL}; 
  int child = fork();

  if (child == 0){
    execv (replace[0],replace);
    printf ("EXECV Failed\n");
  }
  else if (child == -1){
    printf("Fork failed\n");
  }

}
