#include <assert.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#define DEBUG 1
#define HIDDENUNSHOW 1
#define PRINTTYPE 1
bool lsWithL(const char *path) {
  struct dirent *entry;
  DIR *dp = opendir(path);
  if (dp == NULL) {
    perror("opendir faied!");
    return false;
  }
  while ((entry = readdir(dp)) != NULL) { // TODO: finish tran homework2 to
    // homework3
    struct stat state_buf;
    char full_path_name[1024];
#ifdef HIDDENUNSHOW // 如果设置隐藏文件不显示,则不打印以'.'开头的隐藏文件
    if (entry->d_name[0] == '.')
      continue;
#endif /* ifdef HIDDENUNSHOW */
    sprintf(full_path_name, "%s/%s", path, entry->d_name);
    if (stat(full_path_name, &state_buf) == -1) {
      perror("stat wrong in line 23");
      continue;
    }
    printf("%c%c%c %c%c%c %c%c%c ", (state_buf.st_mode & S_IRUSR) ? 'r' : '_',
           (state_buf.st_mode & S_IWUSR) ? 'w' : '_',
           (state_buf.st_mode & S_IXUSR) ? 'x' : '_',
           (state_buf.st_mode & S_IRGRP) ? 'r' : '_',
           (state_buf.st_mode & S_IWGRP) ? 'w' : '_',
           (state_buf.st_mode & S_IXGRP) ? 'x' : '_',
           (state_buf.st_mode & S_IROTH) ? 'r' : '_',
           (state_buf.st_mode & S_IWOTH) ? 'w' : '_',
           (state_buf.st_mode & S_IXOTH) ? 'x' : '_');
    printf("%lu ", state_buf.st_nlink);
#ifdef PRINTTYPE
    if (S_ISREG(state_buf.st_mode)) {
      printf("REGFILE ");
    }
    if (S_ISDIR(state_buf.st_mode)) {
      printf("DIR ");
    }
#endif /* ifdef PRINTTYPE */
    uid_t uid = state_buf.st_uid;
    struct passwd *pw = getpwuid(uid);
    printf("%s ", pw->pw_name);
    gid_t gid = state_buf.st_gid;
    struct group *gp = getgrgid(gid);
    printf("%s ", gp->gr_name);
    printf("%ld ", state_buf.st_size);
    time_t access_time = state_buf.st_atime;
    struct tm *local_time = localtime(&access_time);
    char time_buf[1024];
    sprintf(time_buf, "%s", asctime(local_time));
    if (strlen(time_buf) > 0 && time_buf[strlen(time_buf) - 1] == '\n') {
      time_buf[strlen(time_buf) - 1] = '\0';
    }
    printf("%s ", time_buf);
    printf("%s\n", entry->d_name);
  }
  closedir(dp);
  return true;
}
int main(int argc, char *argv[]) {
  char *path = argv[1];
#ifdef DEBUG
  printf("the input path is %s\n", path);
#endif /* ifdef DEBUG */
  if (!lsWithL(path)) {
    perror("lsWithL failed!\n");
    return false;
  }
  return 0;
}
