#include "large_num.h"

int main(int argc, char *argv[])
{
    struct largeNum arg1, arg2, *ans, *remain;
    int end;
    char op;

    initMulTable();

    while(1)
    {
        end = readInNum(&arg1);
        if(end == ERROR_OCCUR)
        {
            printf("error input!\n");
            jumpLine();
            jumpLine();
            continue;
        }
        if(end == 0) break;

        end = readInNum(&arg2);
        if(end == ERROR_OCCUR)
        {
            printf("error input!\n");
            jumpLine();
            free(arg1.num);
            continue;
        }
        if(end == 0) break;

        op = getchar();
        switch(op)
        {
        case '+':
            ans = add(&arg1, &arg2);
            putsNum(ans);
            break;
        case '-':
            ans = sub(&arg1, &arg2);
            putsNum(ans);
            break;
        case '*':
            ans = mul(&arg1, &arg2);
            putsNum(ans);
            break;
        case '/':
            ans = divL(&arg1, &arg2, &remain);
            print2Num(ans,remain);
            if(NULL != remain)
            {
                if(NULL != remain->num)
                    free(remain->num);
                free(remain);
            }
            break;
        default:
            printf("error input!\n");
            free(arg1.num);
            free(arg2.num);
            continue;

        }
        free(arg1.num);
        free(arg2.num);
        if(NULL != ans)
        {
            if(NULL != ans->num)
                free(ans->num);
            free(ans);
        }
    }
    return 0;
}
