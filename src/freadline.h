#ifndef _FREADLINE_H
#define _FREADLINE_H

#include <stdio.h>

/*宏定义函数*/
/*readline之后的左括号'('必须紧跟readline,之间不能有空格,否则就定义了一个对象宏,它将被替换为以'('开始的字符串*/
/*在调用函数宏时,readline与(之间可以有空格*/
#define readline() freadline(stdin)


/*保证_MAXLEN足够大,取这样的名字是为了防止被用户重定义*/
#define _MAXLEN 512

/*数组a_line用来存储读取的一行字符串*/
char a_line[_MAXLEN];

/*函数freadline的参数stream是一个文件描述符，返回值为一个指向char类型的指针*/
char *freadline(FILE *stream);

#endif

