#include <assert.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#define DEBUG 1
#define HIDDENUNSHOW 1
bool listFiles(const char *path) {
  struct dirent *entry;
  DIR *dp = opendir(path);
  if (dp == NULL) {
    perror("opendir");
    return false;
  }
  while ((entry = readdir(dp)) != NULL) {
    char full_path_buff[1024];
    struct stat state_buf;
#ifdef HIDDENUNSHOW // 如果设置隐藏文件不显示,则不打印以'.'开头的隐藏文件
    if (entry->d_name[0] == '.')
      continue;
#endif /* ifdef HIDDENUNSHOW */
    if (entry->d_name[0] == '.' && strlen(entry->d_name) == 1 ||
        entry->d_name[0] == '.' && entry->d_name[1] == '.' &&
            strlen(entry->d_name) == 2) // 过滤掉., ..
      continue;
    sprintf(full_path_buff, "%s/%s", path, entry->d_name);
    if (stat(full_path_buff, &state_buf) == -1) {
      perror("stat wrong in line 23");
      continue;
    }
    if (S_ISDIR(state_buf.st_mode)) {
      listFiles(full_path_buff);
    }
    printf("this file/directory is :%s\n", full_path_buff);
  }
  closedir(dp);
  return true;
}
int main(int argc, char *argv[]) {
  char *path = argv[1];
  assert(path);
#ifdef DEBUG
  printf("the first argument aka the directory path is %s \n",
         path); // 设置DEBUG位通过打印
// 第一个参数:目录路径来判断命令行参数是否传递成功
#endif /* ifdef DEBUG */
  if (!listFiles(path)) {
    perror("listFiles failed!\n");
  }
  return 0;
}
