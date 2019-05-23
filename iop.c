#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
 
int serialport_read_until(int fd, char* buf, char until, int buf_max, int timeout) {
  char b[1];  // read expects an array, so we give it a 1-byte array
  int i=0;
  do {
    int n = read(fd, b, 1);  // read a char at a time
    if(n == -1) return -1;    // couldn't read
    if(n == 0) {
      usleep(1000);  // wait 1 msec try again
      timeout--;
      if(timeout == 0) return -2;
        continue;
    }
    buf[i] = b[0];
    i++;
  } while( b[0] != until && i < buf_max && timeout>0 );

  buf[i] = 0;  // null terminate the string
  return 0;
}
 
int main(int argc, char *argv[])
{
  int fd;
  const char *portname = "/dev/ttyACM0";
  char buf[256];
 
  fd = open(portname, O_RDWR | O_NOCTTY);
  if (fd < 0) {
    fprintf(stderr, "(%d) %s\n", errno, strerror(errno));
    exit(1);
  }

  struct termios toptions;
  tcgetattr(fd, &toptions);
  cfsetispeed(&toptions, B9600);
  cfsetospeed(&toptions, B9600);

  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  toptions.c_cflag &= ~CRTSCTS;
  toptions.c_cflag |= CREAD | CLOCAL;
  toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
  toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  toptions.c_oflag &= ~OPOST;

  toptions.c_cc[VMIN] = 1;
  toptions.c_cc[VTIME] = 0;

  tcsetattr(fd, TCSANOW, &toptions);

  usleep(1000000);
  tcflush(fd, TCIFLUSH);
  

  do {
    serialport_read_until(fd, buf, '\n', 256, 1000);
    fprintf(stdout, "%s", buf);
    fflush(stdout);
  } while (1);

  return 0;
}
