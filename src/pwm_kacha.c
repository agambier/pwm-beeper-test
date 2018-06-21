#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>

#include "music.h"


const tNote takephoto[ ] = 
{ 
    {H5, 200}, 
    {H3, 200}, 
    {H3-1, 10}, 
    {H3-2, 10}, 
    {H3-3, 10}, 
    {H3-4, 10}, 
    { 0, 0} // 结束 
}; 
const tNote takephoto2[ ] = 
{ 
    {M5, 200}, 
    {M3, 200}, 
    {H3-1, 10}, 
    {H3-2, 10}, 
    {H3-3, 10}, 
    {H3-4, 10}, 
    { 0, 0} // 结束 
}; 
const tNote takephoto3[ ] = 
{ 
    {L5, 200}, 
    {L3, 200}, 
    {L3-1, 20}, 
    {L3-2, 20}, 
    {L3-3, 20}, 
    {L3-4, 20}, 
    { 0, 0} // 结束 
}; 
const tNote takephoto4[ ] = 
{ 
    {H5, 200}, 
    {H3, 100}, 
    { 0, 0} // 结束 
}; 
const tNote takephoto5[ ] = 
{ 
    {H5, 100}, 
    {H3, 300}, 
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
        musicPlay(fd, takephoto);
        sleep(2);
        musicPlay(fd, takephoto2);
        sleep(2);
        musicPlay(fd, takephoto3);
        sleep(2);
        musicPlay(fd, takephoto4);
        sleep(2);
        musicPlay(fd, takephoto5);
        sleep(5);
    }

    close(fd);

    return 0;
}

