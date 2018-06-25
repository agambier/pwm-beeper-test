#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <errno.h>

#include "music.h"
#include "freadline.h"

#define MUSIC_NOTE_NUM              128


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

tNote note[128] = {0};
int main(int argc, char *argv[])
{
    FILE *fp;
    int devfd, version, ret;
    int i;

    if (argc < 3)
    {
        perror("pwm_play <musicfile> <devpath>");
        return 1;
    }

    if ((fp = fopen(argv[1], "r")) == NULL) {
        perror("open music file fail!");
        return 1;
    }
    if ((devfd = open(argv[2], O_RDWR)) < 0) {
        perror("open dev fail!");
        return 1;
    }

    // load music
    for (i = 0; i < MUSIC_NOTE_NUM; i++)
    {
        char tname[20];
        int ttime;
        int n;
        char *linestr;

        linestr = freadline(fp);
        errno = 0;
        n = sscanf(linestr, "%s %d", tname, &ttime);
        if (n == 2) {
            printf("name: %s time:%d\n", tname, ttime);
        } else if (errno != 0) {
            perror("scanf");
            break;
        } else {
            fprintf(stderr, "No matching characters\n");
            break;
        }

        note[i].mTime = ttime;
        if (strcmp(tname, "L1") == 0)
        {
            note[i].mName = L1;
        }
        else if (strcmp(tname, "L2") == 0)
        {
            note[i].mName = L2;
        }
        else if (strcmp(tname, "L3") == 0)
        {
            note[i].mName = L3;
        }
        else if (strcmp(tname, "L4") == 0)
        {
            note[i].mName = L4;
        }
        else if (strcmp(tname, "L5") == 0)
        {
            note[i].mName = L5;
        }
        else if (strcmp(tname, "L6") == 0)
        {
            note[i].mName = L6;
        }
        else if (strcmp(tname, "L7") == 0)
        {
            note[i].mName = L7;
        }
        else if (strcmp(tname, "M1") == 0)
        {
            note[i].mName = M1;
        }
        else if (strcmp(tname, "M2") == 0)
        {
            note[i].mName = M2;
        }
        else if (strcmp(tname, "M3") == 0)
        {
            note[i].mName = M3;
        }
        else if (strcmp(tname, "M4") == 0)
        {
            note[i].mName = M4;
        }
        else if (strcmp(tname, "M5") == 0)
        {
            note[i].mName = M5;
        }
        else if (strcmp(tname, "M6") == 0)
        {
            note[i].mName = M6;
        }
        else if (strcmp(tname, "M7") == 0)
        {
            note[i].mName = M7;
        }
        else if (strcmp(tname, "H1") == 0)
        {
            note[i].mName = H1;
        }
        else if (strcmp(tname, "H2") == 0)
        {
            note[i].mName = H2;
        }
        else if (strcmp(tname, "H3") == 0)
        {
            note[i].mName = H3;
        }
        else if (strcmp(tname, "H4") == 0)
        {
            note[i].mName = H4;
        }
        else if (strcmp(tname, "H5") == 0)
        {
            note[i].mName = H5;
        }
        else if (strcmp(tname, "H6") == 0)
        {
            note[i].mName = H6;
        }
        else if (strcmp(tname, "H7") == 0)
        {
            note[i].mName = H7;
        }
    }
    

    while (1)
    {
        musicPlay(devfd, note);
        sleep(3);
    }

    close(devfd);
    fclose(fp);

    return 0;
}

