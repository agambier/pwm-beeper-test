#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>

#include "music.h"


// 定义乐曲：《化蝶》（梁祝） 
const tNote MyScore[ ] = 
{ 
    {L3, T/4}, 
    {L5, T/8+T/16}, 
    {L6, T/16}, 
    {M1, T/8+T/16}, 
    {M2, T/16}, 
    {L6, T/16}, 
    {M1, T/16},
    {L5, T/8}, 
    {M5, T/8+T/16}, 
    {H1, T/16}, 
    {M6, T/16}, 
    {M5, T/16}, 
    {M3, T/16}, 
    {M5, T/16}, 
    {M2, T/2}, 
    // 省略后续乐曲数据，请感兴趣的读者补充完整
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
        musicPlay(fd, MyScore);
        sleep(3);
    }

    close(fd);

    return 0;
}

