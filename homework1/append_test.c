#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define SEEK_BYTES 4
#define READ_BYTES 1
#define WRITE_BYTES 1
#define PATH "test.bin"
int main() {
  char text_read[10];
  int fd = open(PATH, O_APPEND | O_RDWR);
  assert(fd > 0);
  lseek(fd, SEEK_BYTES, SEEK_SET);
  int rr = read(fd, text_read, READ_BYTES);
  assert(rr > 0);
  printf("readbytes: %s\n", text_read);
  int wr = write(fd, text_read, WRITE_BYTES);
  assert(wr > 0);
  return 0;
}
