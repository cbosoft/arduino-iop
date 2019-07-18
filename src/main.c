#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <ardiop.h>
 
#define BUFMAX 256



static int interrupted = 0;



void sighand(int sig)
{
  interrupted = 1;
}



int main(int argc, char *argv[])
{
  const char *serial_port_path = "/dev/ttyACM0";
  char buf[BUFMAX];

  int fd = ard_openserial(serial_port_path);

  do {
    ard_readserial_line(fd, buf, BUFMAX, 1000);
    fprintf(stderr, "%s", buf);
  } while (!interrupted);

  return 0;
}
