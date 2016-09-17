#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
// run file as gcc cs332lab1isplaycontent.c -o displaycontent
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
  fd = open(argv[1],O_RDONLY);
  if( fd<0)
    {
      perror("open"); /* This will explain why */
      return 1;
    }
  else
     {
       bytes = read(fd,data,100);
       if (fd<0){
         perror("read"); /* This will explain why */
         return 1; 
      }
    
       while(bytes!=0){
         if ( write(1, data, bytes)< 0){
         perror("open"); /* This will explain why */
         return 1;
         }
         bytes = read(fd,data,100);
       }
    }

  close(fd);
}
