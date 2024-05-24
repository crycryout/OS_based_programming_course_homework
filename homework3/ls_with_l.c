#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdbool.h>
#include<assert.h>
#include<sys/stat.h>
#define DEBUG 1
#define HIDDENUNSHOW 1
bool lsWithL(const char* path){
  struct dirent *entry;
  DIR* dp = opendir(path);
  if(dp == NULL)
  {
    perror("opendir faied!")
    return false;  
  }  
  while ((entry = readdir(dp)) != NULL) {//TODO: finish tran homework2 to 
    //homework3
    char full_path_buff[1024];
    struct stat state_buf;
    #ifdef HIDDENUNSHOW//如果设置隐藏文件不显示,则不打印以'.'开头的隐藏文件
    if(entry->d_name == '.')
      continue;
    #endif /* ifdef HIDDENUNSHOW */
    if(entry->d_name[0]=='.')//过滤掉., .. 以及隐藏文件
      continue;
    sprintf(full_path_buff,"%s/%s",path,entry->d_name);
    if(stat(full_path_buff,&state_buf) == -1)
    {
      perror("stat wrong in line 23");
      continue;
    }
    if(S_ISDIR(state_buf.st_mode))
    {
      listFiles(full_path_buff);
    }
    printf("this file/directory is :%s\n",full_path_buff);
  }
  closedir(dp);
  return true;
}

}
int main(int argc, char *argv[])
{
  
  return 0;
}
