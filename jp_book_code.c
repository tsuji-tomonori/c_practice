#include <stdio.h>

/* 関数宣言 */
int main(void);

/* main */
int main(void)
{
    /* 変数の定義 */
    struct ISBN13
    {
        char prefix[4];
        char group[9];
        char publisher[9];
        char title[9];
        char check_digit[2];
    };

    struct JpBookCode
    {
        struct ISBN13 isbn;
        char c_code[5];
        int price;
    };

    struct ISBN13 isbn[2] =
    {
        {"978", "4", "7580", "7821", "4"},
        {"978", "4", "7580", "7843", "6"}
    };

    struct JpBookCode jbc[2] =
    {
        {isbn[0], "9979", 680},
        {isbn[1], "9979", 680}
    };

    /* 表示 */
    for (int i = 0; i < 2; i++)
    {
        /* ISBN, C-CODE, 本体価格を表示する */
        printf("%s-%s-%s-%s-%s, C%s, \\%dE\n", 
            jbc[i].isbn.prefix, jbc[i].isbn.group, jbc[i].isbn.publisher, 
            jbc[i].isbn.title, jbc[i].isbn.check_digit, jbc[i].c_code, jbc[i].price);
    }
    
    return 0;
}