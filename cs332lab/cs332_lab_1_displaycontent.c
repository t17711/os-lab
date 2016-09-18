#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
// run file as gcc cs332_lab_1_displaycontent.c -o displaycontent
// then ./displaycontent text.txt
int main(int argc, char *argv[])
{
  int fd;
  int bytes;
  char* data[100];
  if(2 != argc)
    {
      printf("\n Usage : \n");
      return 1;
    }
  errno = 0;
  fd = open(argv[1],O_RDONLY); // open the 1st file name in argv[1]
  if( fd<0)
    {
      perror("open"); // cannot open file 
      return 1;
    }
  else
    {
      bytes = read(fd,data,100); // read bytes from file at fd
      if (fd<0){
	perror("read"); // read permission denied
	return 1; 
      }

      // bytes returns the number of bytes read so it is 0 when all file is read 
      while(bytes!=0){
	if ( write(1, data, bytes)< 0){ // write data of size bytes to screen to display 
	  perror("write"); //write permission denied
	  return 1;
	}

	// keep trying to reading 100 bytes at a time, if file has<100 then read remaining
	bytes = read(fd,data,100);
      }
    }

  close(fd);
}
