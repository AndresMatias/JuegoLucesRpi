#include <stdio.h>
#include <stdlib.h>
#include "termset.h"

int main(int argc, char *argv[])
{
  int fd;
  FILE *fptr;
  ssize_t n_read;
  size_t len = 0;
  char *line;

  if(argc == 2)
  {
    printf("USAGE: %s <device> <baudrate>\n", argv[0]);
    return -1;
  }

  fptr = fopen("/dev/ttyAMA0", "r");
  if(fptr == NULL)
  {
    printf("ERROR: opening %s file\n", argv[1]);
    return -1;
  }
  fd = fileno(fptr);

  if(termset(fd, 9600, &ttyold, &ttynew) == -1)
  {
    printf("ERROR: setting tty\n");
    return -1;
  }

  for(;;)
  {
    n_read = getline(&line, &len, fptr);
    if(n_read != -1)
      printf("Line: %s", line);
  }

  fclose(fptr);
  return 0;
}

