#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


void my_sig(int sig_no)
{
    printf("mysig(%d)\n", sig_no);
    while( waitpid(-1, 0 , WNOHANG>0));
}
int main()
{
    int seconds;
    char line[128];
    char messages[64];

    signal( SIGCHLD, my_sig);
    while(1)
    {
        printf("Alarm >");
        fgets(line, sizeof line, stdin);
        sscanf(line, "%d %64[^\n]", &seconds, messages);
        if( fork()==0)
        {
            sleep(seconds);
            printf("(%d) %s\n", seconds, messages);
            exit(0);
        }
    }
    return 0;
}