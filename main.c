#include "large_num.h"

int main(int argc, char *argv[])
{
    struct largeNum arg1, arg2, *ans;
    int end;
    while(1)
    {
        end = readInNum(&arg1);
        printf("%d\n",end);
        printNum(&arg1);
        free(arg1.num);
    }
    return 0;
}
