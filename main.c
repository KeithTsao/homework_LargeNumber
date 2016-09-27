#include <stdio.h>
#include <string.h>
#include "large_num.h"

#define LEN_MAX 83050//0x1446A，来自于100000*log(base:16,10)

struct largeNum
{
    unsigned char num[LEN_MAX];
    int len;//16进制长度，同时以该变量正负表示整数正负
};

int readInNum(struct largeNum *num);//读入一个大整数，返回整数的16进制表示长度，绝对值超过LEN_MAX表示超长
int printNum(const struct largeNum *num);

//非交换运算以前者为arg1为第一操作数
struct largeNum * add(const struct largeNum *arg1, const struct largeNum *arg2);
struct largeNum * sub(const struct largeNum *arg1, const struct largeNum *arg2);
//乘法结果允许超长
struct largeNum * mul(const struct largeNum *arg1, const struct largeNum *arg2);
//返回值是商，__remain是余数，返回超长表示除零错误
struct largeNum * div(const struct largeNum *arg1, const struct largeNum *arg2, const struct largeNum **_remain);

struct largeNum * lNumcopy(const struct largeNum * source);
//正数表示前者较大，负数表示后者较大，0表示相等，inline有待校正
inline int lNcmp(const struct largeNum *arg1, const struct largeNum *arg2);

int main(int argc, char *argv[])
{
    printf("Hello World!\n");
    return 0;
}

int readInNum(struct largeNum *num)
{

}
