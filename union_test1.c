#include <stdio.h>

/* 関数宣言 */
int main(void);

/* main */
int main(void)
{
    union TEST{
        char ch[4];
        long l;
    };

    union TEST test = {"1234"};

    printf("char: %s\n", test.ch);
    printf("long: %lx(16進数)\n", test.l);

    return 0;
}