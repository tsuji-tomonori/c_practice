#include <stdio.h>

/* 関数宣言 */
int main(void);

/* main */
int main(void)
{
    union ISBN13{
        char lst[14];
        struct ST
        {
            char prefix[3];
            char group[1];
            char publisher[4];
            char title[4];
            char check_digit[1];
        }st;
    };

    union ISBN13 isbn = {"9784758078436"};
    
    printf("%s\n", isbn.lst);
    printf("%c%c%c-%c-%c%c%c%c-%c%c%c%c-%c\n", 
            isbn.st.prefix[0], isbn.st.prefix[1], isbn.st.prefix[2], 
            isbn.st.group[0], 
            isbn.st.publisher[0], isbn.st.publisher[1], isbn.st.publisher[2],
                isbn.st.publisher[3], 
            isbn.st.title[0], isbn.st.title[1], isbn.st.title[2], isbn.st.title[3], 
            isbn.st.check_digit[0]);

    return 0;
}