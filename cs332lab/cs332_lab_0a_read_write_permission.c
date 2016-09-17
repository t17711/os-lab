#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
///adfasdfa
int main(int argc, char *argv[])
{
  char *filepath = argv[1];
  int returnval;
  // Check file existence
  returnval = access(filepath, F_OK);
  if (returnval == 0)  {
    printf("\n %s exists\n", filepath);
  }
  else{
    if (errno == ENOENT)
      printf ("%s does not exist\n", filepath);
    else if (errno == EACCES)
      printf ("%s is not accessible\n", filepath);
    return 1;
  }
  // Check read access
  returnval = access(filepath, R_OK);
  if (returnval == 0)  {
    printf("\n %s Read accessible\n", filepath);
  }
  else
  {

    printf ("Read [%s]\n",strerror(errno));
      return 1;

  }

  // Check write access
  returnval = access(filepath, W_OK);
  if (returnval == 0)
  {
    printf("\n %s write accessible\n", filepath);
  }
  else
  {

    printf ("Write [%s]\n",strerror(errno));

    return 1;

  }
  return 0;
}
