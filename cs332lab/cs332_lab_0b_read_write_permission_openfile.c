#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
int main(int argc, char *argv[])
{
  int fd;
  errno = 0;
  if(2 != argc)
    {
      printf("\n Usage : \n");
      return 1;
    }
  // check if file can open, open read only and then create bitwire, both have to execute
  fd = open(argv[1],O_RDONLY|O_CREAT);
  if(-1 == fd) // fd is -1 so error, file exists but cannot be opened
    {
      printf("Sorry could not open file\n");
      perror("open");
      return 1;
    }
  else
    {
      printf("\nRead() or create() Successful\n");
    }

  close(fd);
 

  return 0;
}
