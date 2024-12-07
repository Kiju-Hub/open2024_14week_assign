#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>   // pid_t 정의
#include <sys/wait.h>    
#include "ls_command.h"

#define MAX_LINE 80
#define MAX_ARGS 10
int main(){
    char input[MAX_LINE];
    char *token;
    char *argv[MAX_ARGS];


    while(1){
        //prompt
        printf("qkrrlwn97@BOOK-637PTB0GR1:~/myshell> ");

        //read command
        

        fgets(input, MAX_LINE, stdin);
        printf("%s\n", input);

        //tokenize input
        token = strtok(input, "\n\t "); // 제일 먼저 나온 토큰
        int i=0;

        while(token !=NULL){
            argv[i++]=token; //루프를 돌면서 argv에 토큰을 하나씩 넣는다. (argv[0]에는 cat, argv[1]에는 myfile.c)
            token = strtok(NULL, "\n\t "); //반복문으로 토큰을 계속 받아낸다.

        }
        argv[i]=NULL;

        if (argv[0]==NULL){ //empty command
            continue;
        }
        
        if(strcmp(argv[0], "exit")==0){
            printf("GOOD BYE ! \n");
            exit(0);
        }

        else if(strcmp(argv[0],"cd")==0){
            chdir(argv[1]);
        }

        else if(strcmp(argv[0],"pwd")==0){
            getcwd(input,MAX_LINE);
            printf("%s\n",input);
        }

        else if(strcmp(argv[0], "ls")==0){
            my_ls();
        }

        else if(strcmp(argv[0],"cat")==0){
            //내가 구현해야함 cat은 argv[1]을 받아들여야겠지?
            if (argv[1] == NULL) { // 파일 이름이 제공되지 않은 경우
            printf("Usage: cat <filename>\n");
            continue;
            }
            FILE *file = fopen(argv[1], "r");
            if (file == NULL) { // 파일 열기에 실패한 경우
                perror("Error opening file"); // 에러 메시지 출력
                continue; // 다음 명령으로 넘어감
            }
            char line[MAX_LINE];
            while(fgets(line,sizeof(line),file)!=NULL){
                printf("%s",line);
            }
            fclose(file);
        }

        else{
            if(access(argv[0],X_OK)==0){
                // printf("execute %s\n",argv[0]);
                pid_t pid = fork();
                if (pid == 0) { // 자식 프로세스
                    execvp(argv[0], argv); // 외부 프로그램 실행
                    perror("Error executing program");
                    exit(1);
                } else if (pid > 0) { // 부모 프로세스
                    int status;
                    waitpid(pid, &status, 0); // 자식 프로세스 종료 대기
                } else { // fork 실패
                    perror("Error forking process");
                }
            }
            else{
                printf("command not found: %s\n", argv[0]);
            }
        }

    }

    return 0;
}