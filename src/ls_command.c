#include "ls_command.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void my_ls(void){
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if(dir==NULL){
        perror("opendir error");
        return;
    }
    else{
        while((entry = readdir(dir))!=NULL){ //NULL이 아닐때까지 entry를 하나씩 받아오기
            if(entry->d_type==DT_DIR){
                printf("%s/\n",entry->d_name);
            }
            else{
                printf("%s\n", entry->d_name);
            }
        }
    }
    closedir(dir);
} 
// ls 했을 때 , hello가 안 나옴 ,,,,