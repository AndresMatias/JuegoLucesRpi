#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "termset.h"
#define BAUDRATE 9600

int main(int argc, char * argv[])
{
  int fd;                                     /* File descriptor for the port */
  char *a="Hola";
  if(argc == 3)
  {
    printf("USAGE: %s <device> <char>\n", argv[0]);
    return -1;
  }

  // Open device.
  fd = open("/dev/ttyAMA0", O_WRONLY | O_NOCTTY | O_SYNC);
  if(fd < -1)
  {
    printf("ERROR: opening serial port\n");
    return -1;
  }

  if(termset(fd, BAUDRATE, &ttyold, &ttynew) == -1)
  {
    printf("ERROR: setting tty\n");
    return -1;
  }

  write(fd, a,4 );

  close(fd);
  return 0;
}
