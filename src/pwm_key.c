#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <termios.h> //POSIX 终端控制定义

#define START_KEY       1000
#define ESC_KEY         0x1b //定义ESC_KEY 为ESC 按键的键值

static int getch(void) //定义函数在终端上获得输入，并把输入的量（int）返回
{
    struct termios oldt,newt; //终端结构体struct termios
    int ch;

    if (!isatty(STDIN_FILENO)) { //判断串口是否与标准输入相连
        fprintf(stderr, "this problem should be run at a terminal\n");
        exit(1);
    }
    // save terminal setting
    if(tcgetattr(STDIN_FILENO, &oldt) < 0) { //获取终端的设置参数
        perror("save the terminal setting");
        exit(1);
    }

    // set terminal as need
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO ); //控制终端编辑功能参数ICANON 表示使用标准输入模式；参数ECH0 表示显示输入字符
    if(tcsetattr(STDIN_FILENO,TCSANOW, &newt) < 0) { //保存新的终端参数
        perror("set terminal");
        exit(1);
    }

    ch = getchar();

    // restore termial setting
    if(tcsetattr(STDIN_FILENO,TCSANOW,&oldt) < 0) { //恢复保存旧的终端参数
        perror("restore the termial setting");
        exit(1);
    }
    return ch;
}


int main(int argc, char *argv[])
{
    int fd, version, ret;
    struct input_event event;
    struct timeval time;

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
    while( 1 )
    {
        int key;

        ret = write(fd, &event, sizeof(struct input_event));


        printf( "\tFreq = %d\n", event.value );

        key = getch();

        event.value = START_KEY + 100 * key;
        switch(key) {
            case ESC_KEY:
            case EOF:   
                event.code = SND_BELL;
                event.value = 0; 
                ret = write(fd, &event, sizeof(struct input_event));
                close(fd);
                return 1;
            default:
                break;
        }
    }
}

