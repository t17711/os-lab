#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  
  int status;// just for waitpid ==0 in c
  int child = fork(); // create process 1
  waitpid(child, &status, 0); // wait for process 1 to finish to continue
  
  if (child == 0){ // check for process 1
    printf("I am a  Child one process with pid: %d\n", getpid());
    return 0; // child 1 ends here
  }

  // not child 1
  int child2 =fork(); // create process 2
  waitpid(child2, &status, 0); // wait for child 2 to finish
  
  if (child2 == 0){ // check if this is process 2
    printf("I am a  Child two process with pid: %d\n", getpid());
    return 0; // child 2 ends here
  }

  // not child 1 or 2 i.e. parent
  printf("I am a parent process with pid: %d who created child processes with pid: %d and %d\n", getpid(),child,child2);
  

  return 0; // parent ends here
}
