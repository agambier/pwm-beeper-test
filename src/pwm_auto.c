#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <termios.h> //POSIX 终端控制定义

#define START_PWM   250

int main(int argc, char *argv[])
{
    int fd, version, ret;
    struct input_event event;
    struct timeval time;
    int i;

    if ((fd = open(argv[1], O_RDWR)) < 0) {
        perror("beep test");
        return 1;
    }

    event.type = EV_SND;
    event.code = SND_TONE;
    event.value = 1000;
    time.tv_sec = 1;
    time.tv_usec = 0;
    event.time = time;

    for (i = 0; i < 60; i++)
    {
        event.value = START_PWM + 50 * i;
        printf( "\tFreq = %d\n", event.value );

        ret = write(fd, &event, sizeof(struct input_event));
        usleep(500 * 1000);
    }
    event.code = SND_BELL;
    event.value = 0000;     
    ret = write(fd, &event, sizeof(struct input_event));
    close(fd);
}

