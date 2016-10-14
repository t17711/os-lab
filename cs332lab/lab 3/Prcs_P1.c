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
      printf("\n Usage : no file name supplied\n");
      return 1;
    }
  //create file
  // with permission
  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  fd = open(argv[1],O_CREAT|O_TRUNC, mode);
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
