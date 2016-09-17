#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
// run file as gcc cs332lab1isplaycontent.c -o displaycontent
// then ./displaycontent text.txt
int main(int argc, char *argv[])
{
  int fd1;
  int fd2;
  int bytes;
  char* data[100];
  if(3 != argc)
    {
      printf("\n Usage : need 2 file names \n");
      return 1;
    }
  
  fd1 = open(argv[1],O_RDONLY);
  fd2 = open(argv[2],O_WRONLY|O_CREAT);
  if( fd1<0||fd2<0)
    {
      perror("open"); /* This will explain why */
      return 1;
    }
  else
     {
       bytes = read(fd1,data,100);
       if (fd1<0){
         perror("read"); /* This will explain why */
         return 1; 
      }
    
       while(bytes!=0){
         if ( write(fd2, data, bytes)< 0){
         perror("open"); /* This will explain why */
         return 1;
         }
         bytes = read(fd1,data,100);
       }
     }

  close(fd1);
  close(fd2);
}
