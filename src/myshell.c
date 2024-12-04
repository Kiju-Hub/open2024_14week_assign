#include <stdio.h>
#define MAX_LINE 80

int main(){
    char input[MAX_LINE];
    while(1){
        //prompt
        printf("qkrrlwn97@BOOK-637PTB0GR1:~/myshell> ");

        //read command

        fgets(input, MAX_LINE, stdin);
        printf("%s\n", input);

    }

    return 0;
}