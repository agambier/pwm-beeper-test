#include "freadline.h"

char *freadline(FILE *stream)
{    
    int count = 0;

    /* 数组a_line最多只能存511个“有用”字符，此时最后一个存储单元存储了‘\0’*/
    /*如果一行超过511个字符，则其后字符都不会被读取*/
    while((count < _MAXLEN) && ((a_line[count++] = getc(stream)) != '\n'));

    /*读完一行字符串后在字符串后加‘\0’,否则输出的字符串可能比读入的字符串多一些字符*/
    a_line[count - 1] = '\0';

    return a_line;
}
