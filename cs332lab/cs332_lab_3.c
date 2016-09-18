#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
// run file as gcc cs332_lab_3.c -o copy_mod
// then ./copy_mod text.txt
int main(int argc, char *argv[])
{
  int fd1;
  int fd2;
  int bytes;
  char data[100];
  if(3 != argc) // check for # of file provides
    {
      printf("\n Usage : need 2 file names \n");
      return 1;
    }
  
  fd1 = open(argv[1],O_RDONLY); // read file 1st file fd1 2nd is fd2

  // creates if doesnt exist, truncates if  does
  fd2 = open(argv[2],O_CREAT|O_RDWR|O_TRUNC);
  
  if(!( (fd1>=0) && (fd2>=0))) // if any of above failed 
    {
      perror("open"); // open failed
      return 1;
    }
  else
    {
      bytes = read(fd1,&data,100); // read 1st 100 bytes from fd1 file
      if (fd1<0){
	perror("read"); //read fom fd1 error
	return 1; 
      }
    
      while(bytes>0){ // when it reads more than 1 byte comtinue loop
	for (int i = 0;i<bytes; i++){// loop through bytes since char is 1 byte
	  if(data[i] == '1'){
	    data[i] = 'A'; // replace all '1' with 'A'
	  }
	}
	// check write, write 100 bytes than write "XYG" to file
	if (write(fd2,&data, bytes)<0 | write(fd2, "XYZ", 3)< 0 ){
	  perror("write"); // write error
	  return 1;
	}
        
	bytes = read(fd1,&data,100); // continue reading on loop
      }
    }

  close(fd1);
  close(fd2);
}

