#include "large_num.h"

extern inline int isNum(int c);
extern inline int lNcmp(const struct largeNum *arg1, const struct largeNum *arg2);
extern inline void jumpLine();
extern inline void discardZero(struct largeNum * num);

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
        while(charactor == '0')
        {
            charactor = getchar();//去除多余0
        }
        num->num = (unsigned char*)malloc((LEN_MAX+1)*sizeof(char));
        if(num->num == NULL)
        {
            printf("Memory run out.");
            return 0;
        }
        memset(num->num,LEN_MAX+1, 1);
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
            charactor = getchar();
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
            num->len = flag*(len);
            return len;
        }
    }
}

int printNum(const struct largeNum *num)
{
    int i = 0;
    int len = num->len;
    if(len < 0)
    {
        putchar('-');
        len = -len;
    }

    for(; len > 0; ++i,--len)
    {
        putchar('0' + num->num[i]);
    }
    putchar('\n');
    return 0;
}

struct largeNum * add(struct largeNum *arg1, struct largeNum *arg2)
{
    int flag1 = arg1->len>0?1:-1;
    int flag2 = arg2->len>0?1:-1;
    int len1  = flag1 * arg1->len;
    int len2  = flag2 * arg2->len;
    int len_ans = len1 > len2 ? len1 : len2;
    struct largeNum *ans = NULL;
    unsigned char carrier;
    unsigned char current;
    if(flag1 != flag2)
    {
        arg2->len = -arg2->len;
        return sub(arg1, arg2);
    }
    else
    {
        ans = (struct largeNum*)malloc(sizeof(struct largeNum));
        if(ans == NULL)
        {
            return NULL;
        }
        ans->num = (unsigned char *)malloc(sizeof(char)*(len_ans + 2));
        if(ans->num == NULL)
        {
            return NULL;
        }

        memset(ans->num, 0, len_ans + 2);
        ans->len = len_ans;
        --len1, --len2;
        carrier = 0;
        while(len1 >= 0 || len2 >= 0)
        {
            current = carrier;
            if(len1 >= 0)
            {
                current += arg1->num[len1];
            }
            if(len2 >= 0)
            {
                current += arg2->num[len2];
            }

            if(current < 10)
            {
                ans->num[len_ans] = current;
                carrier = 0;
            }
            else
            {
                carrier = 1;
                ans->num[len_ans] = current - 10;
            }
            --len1, --len2, --len_ans;
        }
        if(carrier == 1)
        {
            ans->num[len_ans] = 1;
            ++(ans->len);
        }
        else
        {
            discardZero(ans);
        }
        ans->len = flag1 * ans->len;

        return ans;
    }
}

struct largeNum * sub(struct largeNum *arg1, struct largeNum *arg2)
{
    int flag1 = arg1->len>0?1:-1;
    int flag2 = arg2->len>0?1:-1;
    int len1  = flag1 * arg1->len;
    int len2  = flag2 * arg2->len;
    int len_ans = len1 > len2 ? len1 : len2;
    int cont_zeros = 0;
    int cmp_result = lNcmp(arg1, arg2);
    struct largeNum *ans = NULL;
    unsigned char carrier;
    unsigned char current;
    unsigned char undersub;

    if(flag1 != flag2)
    {
        arg2->len = -arg2->len;
        return add(arg1, arg2);
    }
    if(cmp_result == 0)
    {
        ans = (struct largeNum *) malloc(sizeof(struct largeNum));
        ans->len = 1;
        ans->num = (unsigned char *)malloc(sizeof(char)*2);
        ans->num[0] = 0;
        ans->num[1] = 0;
        return ans;
    }
    if((flag1 > 0) ^ (cmp_result > 0))
    {
        arg1->len = -arg1->len;
        arg2->len = -arg2->len;
        return sub(arg2, arg1);//保证绝对值大的减绝对值小的
    }
    else
    {
        ans = (struct largeNum *) malloc(sizeof(struct largeNum));
        if(ans == NULL)
        {
            return NULL;
        }
        ans->num = (unsigned char *)malloc(sizeof(char) * (len_ans + 1));
        if(ans->num == NULL)
        {
            return NULL;
        }

        memset(ans->num, 0, len_ans + 1);
        ans->len = len_ans;
        --len1,--len2,--len_ans;
        carrier = 0;
        while(len1 >= 0)
        {
            current = arg1->num[len1];
            undersub = len2 >= 0? arg2->num[len2]:0;
            if(current < undersub + carrier)
            {
                current = 10 + current - carrier - undersub;
                carrier = 1;
            }
            else
            {
                current = current - carrier - undersub;
                carrier = 0;
            }
            ans->num[len_ans] = current;
            if(current == 0)
            {
                ++cont_zeros;
            }
            else
            {
                cont_zeros = 0;
            }

            --len1, --len2, --len_ans;
        }
        ans->len -= cont_zeros;
        discardZero(ans);
        ans->len = flag1 * ans->len;
        return ans;
    }
}
