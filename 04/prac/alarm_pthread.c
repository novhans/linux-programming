#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/wait.h>

typedef struct _{
    int seconds;
    char messages[64];
}alarm_t;

void *alarm_thread(void *data)
{
    alarm_t *alarm = (alarm_t*)data;
    pthread_detach(pthread_self());         //자기 메모리를 뗴어내는것
    sleep(alarm->seconds);
    printf("(%d) %s\n", alarm->seconds, alarm->messages);
    free(alarm);
    return 0;
}
int main()
{
    
    pthread_t thread;
    char line[128];
    alarm_t *alarm;
    while(1)
    {
        alarm = malloc(sizeof(alarm_t));
        printf("Alarm >");
        fgets(line, sizeof line, stdin);
        sscanf(line, "%d %64[^\n]", &alarm->seconds, alarm->messages);
        pthread_create(&thread, 0, alarm_thread, alarm);

    }
    return 0;
}