#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<assert.h>
#define SEEK_BYTES 4
#define READ_BYTES 3
#define WRITE_BYTES 5
#define PATH "testfile.txt"
int main(){
    char textRead[10];
    int fd = open(PATH, O_APPEND | O_RDWR);
    lseek(fd, SEEK_BYTES, SEEK_SET);
    int rr = read(fd, textRead, READ_BYTES);
    assert(rr > 0);
    printf("readbytes: %s\n", textRead);
    int wr = write(fd, textRead, WRITE_BYTES);
    assert(wr > 0);
    return 0;
}
