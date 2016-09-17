#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
  int fd;
  if(2 != argc)
    {
      printf("\n Usage : \n");
      return 1;
    }
  
  fd = open(argv[1],O_RDONLY|O_CREAT);
  if(-1 == fd)
    {
      perror("open");
      return 1;
    }
  else
    {
      printf("\n read or  create() Successful\n");
    }

  close(fd);
 

  return 0;
}
