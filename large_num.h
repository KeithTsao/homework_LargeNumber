#ifndef LARGE_NUM_H
#define LARGE_NUM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_MAX 100000
#define ERROR_OCCUR 0x7FFFFFFF

struct largeNum
{
    unsigned char *num;
    int len;//长度，同时以该变量正负表示整数正负
};

char g_mulTable[10][10];

void initMulTable();
//读入一个大整数，返回整数的长度，绝对值为LEN_MAX表示超长，返回0表示遇到结尾，返回ERROR_OCCUR为输入错误
int readInNum(struct largeNum *num);
int printNum(const struct largeNum *num);

//非交换运算以前者为arg1为第一操作数
struct largeNum * add(struct largeNum *arg1, struct largeNum *arg2);
struct largeNum * sub(struct largeNum *arg1, struct largeNum *arg2);
//乘法结果允许超长
struct largeNum * mul(struct largeNum *arg1, struct largeNum *arg2);
//返回值是商，__remain是余数，返回超长表示除零错误
struct largeNum * divL(struct largeNum *arg1, struct largeNum *arg2, struct largeNum **_remain);

struct largeNum * lNumcopy(const struct largeNum * source);
//正数表示前者较大，负数表示后者较大，0表示相等，inline有待校正
inline int lNcmp(const struct largeNum *arg1, const struct largeNum *arg2)
{
    if(arg1->len != arg2->len)
    {
        return (arg1->len - arg2->len);
    }
    else
    {
        int i = 0;
        int flag = arg1->len>0?1:-1;
        int len = arg1->len*flag;
        while(i < len)
        {
            if(arg1->num[i] != arg2->num[i])
            {
                return ((arg1->num[i] - arg2->num[i])*flag);
            }
            else
            {
                ++i;
            }
        }
        return 0;
    }
}

inline int isNum(int c)
{
    return (c <= '9' && c >= '0');
}

inline void jumpLine()
{
    while('\n' != getchar());
    return;
}

inline void discardZero(struct largeNum * num)
{
    unsigned char *p, *q;
    int i = 0;
    int len = (num->len > 0?num->len:-num->len);
    q = p = num->num;
    while(*q == 0)
    {
        ++q;
    }
    if(q == p)
    {
        return;
    }
    else
    {
        while(i < len)
        {
            *p = *q;
            ++p, ++q;
            ++i;
        }
        return;
    }
}

#endif // LARGE_NUM_H
