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

  // file pointers
  int fd1;
  int fd2;
  int fd3;
  
  int bytes; // to read byte
  char data1[100]; // hold data for 1st write 
  char data2[50]; // hold data for 2nd write

  if(4 != argc) // check for # of file provides
    {
      printf("\n Usage : need 3 file names \n");
      return 1;
    }
    
  fd1 = open(argv[1],O_RDONLY); // read source file 

  // read write existing file, truncates if  does
  fd2 = open(argv[2], O_RDWR|O_TRUNC);

  // read write existing file, truncates if  does
  fd3 = open(argv[3], O_RDWR|O_TRUNC);

  
  if(!( (fd1>=0) && (fd2>=0) && (fd3 >=0 ))) // if any of above failed 
    {
      perror("open"); // open failed
      return 1;
    }

  // all file exist so
  else
    {
      bytes =1;
        while(bytes>0){ // when it reads more than 1 byte comtinue loop

	/* step 1 */
	/* copy 1st 100 char replacing 1 with A to file 2 */

	bytes = read(fd1,&data1,100); // read 1st 100 bytes from fd1 file
	if (bytes<0){
	  perror("read"); //read fom fd1 error
	  return 1; 
	}
	
	for (int i = 0;i<bytes; i++){// loop through bytes since char is 1 byte
	  if(data1[i] == '1'){
	    data1[i] = 'A'; // replace all '1' with 'A'
	  }
	}
	
	// check write, write 100 bytes than write "XYG" to file
	// write to file 1
	if (write(fd2,&data1, bytes)<0 ){
	  perror("write"); // write error
	  return 1;
	}
	
	/* step 2*/
	/* copy 2nd 50 char replacing 2 with B to file 3 */

      bytes = read(fd1,&data2,50); // read 1st 100 bytes from fd1 file
      if (bytes<0){
	perror("read"); //read fom fd1 error
	return 1; 
      }

	for (int i = 0;i<bytes; i++){// loop through bytes since char is 1 byte
	  if(data2[i] == '2'){
	    data2[i] = 'B'; // replace all '1' with 'A'
	  }
	}
	
	// check write, write 100 bytes than write "XYG" to file
	// write to file 1
	if (write(fd3,&data2, bytes)< 0 ){
	  perror("write"); // write error
	  return 1;
	}
      }
	printf("write successful\n");
    }

  close(fd1);
  close(fd2);
  close(fd3);
}

