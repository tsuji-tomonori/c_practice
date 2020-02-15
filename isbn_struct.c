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

    struct ISBN13 isbn[2] =
    {
        {"978", "4", "7580", "7821", "4"},
        {"978", "4", "7580", "7843", "6"}
    };

    /* 表示 */
    for (int i = 0; i < 2; i++)
    {
        /* ISBNを各ブロックごとに「-」をつけて表示 */
        printf("%s-%s-%s-%s-%s\n", isbn[i].prefix, isbn[i].group, 
            isbn[i].publisher, isbn[i].title, isbn[i].check_digit);
    }
    return 0;
}