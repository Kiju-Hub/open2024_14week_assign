#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        token = strtok(input, "\n\t"); // 제일 먼저 나온 토큰
        int i=0;

        while(token !=NULL){
            argv[i++]=token; //루프를 돌면서 argv에 토큰을 하나씩 넣는다. (argv[0]에는 cat, argv[1]에는 myfile.c)
            token = strtok(NULL, "\n\t"); //반복문으로 토큰을 계속 받아낸다.

        }
        argv[i]=NULL;

        if (argv[0]==NULL){ //empty command
            continue;
        }
        
        if(strcmp(argv[0], "exit")==0){
            printf("GOOD BYE ! \n");
            exit(0);
        }


    }

    return 0;
}