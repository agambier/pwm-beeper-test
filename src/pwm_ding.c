#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>

#include "music.h"

const tNote ding[ ] = 
{ 
    {M5, T/8}, 
    {H1-10, 20}, 
    {H1-20, 20}, 
    {H1-30, 10}, 
    { 0, 0} // 结束 
}; 

const tNote ding2[ ] = 
{ 
    {H1, T/8}, 
    {M3, 20}, 
    { 0, 0} // 结束 
}; 

const tNote ding3[ ] = 
{ 
    {H3, T/8}, 
    { 0, 0} // 结束 
}; 

const tNote ding4[ ] = 
{ 
    {L5, T/8}, 
    {L1, T/64}, 
    { 0, 0} // 结束 
}; 

const tNote ding5[ ] = 
{ 
    {L5, T/8}, 
    { 0, 0} // 结束 
}; 


// 演奏乐曲
void musicPlay(int fd, const tNote note[]) 
{
    short i = 0; 
    struct input_event event;
    struct timeval time;

    event.type = EV_SND;
    event.code = SND_TONE;
    time.tv_sec = 1;
    time.tv_usec = 0;
    event.time = time;
    for (;;) 
    { 
        if (note[i].mTime == 0)
            break; 
        event.value = note[i].mName;
        write(fd, &event, sizeof(struct input_event));
        usleep(note[i].mTime * 1000); 
        i++; 
    } 
    event.value = 0000;
    write(fd, &event, sizeof(struct input_event));
}

int main(int argc, char *argv[])
{
    int fd, version, ret;

    if ((fd = open(argv[1], O_RDWR)) < 0) {
        perror("beep test fail!");
        return 1;
    }

    while (1)
    {
        musicPlay(fd, ding);
        sleep(2);
        musicPlay(fd, ding2);
        sleep(2);
        musicPlay(fd, ding3);
        sleep(2);
        musicPlay(fd, ding4);
        sleep(2);
        musicPlay(fd, ding5);
        sleep(5);
   }

    close(fd);

    return 0;
}

