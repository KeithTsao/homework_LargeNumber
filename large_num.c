#include "large_num.h"

void initMulTable()
{
    char i,j;
    for( i = 0; i < 10; ++i)
    {
        for(j = 0; j < 10; ++j)
        {
            g_mulTable[i][j] = i*j;
        }
    }
}

int readInNum(struct largeNum *num)
{
    int len;
    int flag = 1;//flag for the num is negtive(-1)/positive(1)
    int charactor;

    charactor = getchar();
    if(charactor == -1)
    {
        return 0;//输入结束
    }
    else
    {
        while(charactor == ' ' || charactor == '\n')
        {
            charactor = getchar();//去除多余空格和回车
        }
        if(charactor == '-')
        {
            flag = -1;//negative
            charactor = getchar();
        }
        else if(charactor == '+')
        {
            flag = 1;//positive
            charactor = getchar();
        }
        memset(num->num,LEN_MAX, 1);
        for(len = 0; len < LEN_MAX; ++len)
        {
            if(!isNum(charactor))
            {
                if(charactor == '\n')
                {
                    break;//行尾
                }
                else
                {
                    return ERROR_OCCUR;//非法字符
                }
            }
            else
            {
                num->num[len] = charactor-'0';
            }
        }
        if(len == 0)
        {
            return ERROR_OCCUR;
        }
        else if(len == LEN_MAX)
        {
            jumpLine();
            return ERROR_OCCUR;
        }
        else
        {
            len = flag * (len + 1);
            return len;
        }
    }
}

int printNum(const struct largeNum *num)
{
    int i;
    for(i = 0; i < num->len; ++i)
    {
        putchar('0' + num->num[i]);
    }
    putchar('\n');
    return 0;
}

struct largeNum * add(const struct largeNum *arg1, const struct largeNum *arg2)
{

}
