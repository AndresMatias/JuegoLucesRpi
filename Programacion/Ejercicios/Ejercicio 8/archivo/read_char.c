#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "termset.h"

#define SIZE 10

int main(int argc, char * argv[])
{
  int i, fd;
  unsigned char buf[SIZE];
  ssize_t n_read;


  // Open device.
  fd = open("/dev/ttyAMA0", O_RDONLY | O_NOCTTY | O_SYNC);
  if(fd < -1)
  {
    printf("ERROR: opening serial port\n");
    return -1;
  }

  if(termset(fd, 9600, &ttyold, &ttynew) == -1)
  {
    printf("ERROR: setting tty\n");
    return -1;
  }
  /*printf("Puerto: %s tty\n",argv[0]);
  printf("Ruta: %s tty\n",argv[1]);
  printf("Velocidad: %d tty\n",atoi(argv[2]));*/
  for(;;)
  {
    n_read = read(fd, buf, SIZE);
    for(i = 0; i < n_read; i++)
      printf("%c ", buf[i]);
    printf("\n");
  }

  close(fd);
  return 0;
}

