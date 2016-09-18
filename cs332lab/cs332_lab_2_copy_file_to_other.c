#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
// same as cp
// run file as gcc cs332_lab_2_copy_file_to_other.c -o copy_to
// then ./copy_to text.txt
int main(int argc, char *argv[])
{
  int fd1;
  int fd2;
  int bytes;
  char data[100];
  if(3 != argc)
    {
      printf("\n Usage : need 2 file names \n");
      return 1;
    }
  
  fd1 = open(argv[1],O_RDONLY);
  fd2 = open(argv[2],O_CREAT|O_RDWR|O_TRUNC);
  // creates if doesnt exist, truncates it does`x`x
  if(!( (fd1>=0) && (fd2>=0))) // error in one of open
    {
      perror("open"); // open the 1st file name in argv[1]
      return 1;
    }
  else
    {
      bytes = read(fd1,&data,100); // try to read fd1 file 1st 100 bytes to data
      if (fd1<0){
	perror("read"); // read failed for fd1
	return 1; 
      }
    
      while(bytes>0){
	if (write(fd2,& data, bytes)< 0){
	  perror("open"); // write failed
	  return 1;
	}
	bytes = read(fd1,&data,100);
      }
    }

  close(fd1);
  close(fd2);
  return 0;
}
