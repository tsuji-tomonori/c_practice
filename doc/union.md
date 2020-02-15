# 共用体

## 共用体とは

```
共用体とは, 同一のメモリ領域を異なる型の別の変数名で操作できるもの
```
共用体とは, データ型の一つで, 同じメモリ領域を複数のメンバが共有する構造となっている. このとき, メンバの型は異なっても良い. 共用体のサイズは, 最も大きなメンバのサイズとなる.

変数のメモリ領域は, 独立したメモリ領域が割り当てられていたが, 共用体では同一のメモリを共有するため, メモリの使用量を抑えることができる.

### ご利益(使用例)

* ビットフィールド
* メモリ容量に制限があって, 構造体を個別に持てない場合
* マイクロプロセッサのシミュレーションでレジスタペアの表現

など...

## 共用体の宣言

### 共用体の宣言

```c
union タグ名{
	データ型 メンバ名;
    データ型 メンバ名;
    データ型 メンバ名;
    ...
};
```

実例

```c
union TEST{
    char ch[4];
    long l;
};
```

このままでは``TEST`` というデータ型の構成が宣言されただけであるため, 変数を宣言する必要がある.

> ``int`` や ``char`` と記述するだけでは使えないことと同じ

### 変数の宣言

```c
union タグ名 変数名;
```

実例

```c
union TEST test;
```

もちろん

```c
union TEST test[10];
union TEST *test;
```

このように, 配列, ポインタの宣言をすることも可能.

### 共有体の宣言+変数の宣言

```c
union タグ名{
	データ型 メンバ名;
    データ型 メンバ名;
    データ型 メンバ名;
    ...
}変数名;
```

実例

```c
union TEST{
    char ch[4];
    long l;
}test;
```

## 共有体の初期化

実例

```c
union TEST test = {"1234"};
```

このとき, ``test`` は``char型`` であり, ``long型`` であるが, 初期化は最初のメンバである``char型`` となる.

## メンバの参照

### ポインタで宣言していない場合

```c
union TEST test;
```

このように宣言している場合

```c
共有体変数名.メンバ名;
```

実例

```c
l = test.l;
test.l = 1000000L;
```

このように「.」ピリオドを使用する.

### ポインタで宣言している場合

```c
union TEST *test;
```

このように宣言している場合

```c
共有体変数名->メンバ名;
```

実例

```c
l = test->l;
test->l = 1000000L;
```

このように「->」関節メンバ演算子を使用する.

## ここまでのまとめ

```c
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
```

```shell
$ gcc -o union_test1 union_test1.c 
$ ./union_test1
char: 1234
long: 34333231(16進数)
```

ここで, それぞれの文字コードは

| 文字 | 文字コード(16進数) |
| ---- | ------------------ |
| 1    | 31                 |
| 2    | 32                 |
| 3    | 33                 |
| 4    | 34                 |

(long は後ろから読み込んでいる?)

## 共有体と構造体の組み合わせ

### 共有体と構造体の組み合わせ

```c
struct ST{
    char prefix[3];
    char group[1];
    char publisher[4];
    char title[4];
    char check_digit[1];
};
```

と構造体を宣言している場合

```c
union ISBN13{
    char lst[14];
    struct ST st;
};
```

このように共有体を宣言することができる.

このとき, 共用体のメンバ``lst`` は14バイト, ``st`` は構造体``ST`` のサイズとなるため, 13バイト確保される. そして, 共有体はすべてのメンバを包括できるサイズである14バイトとなる.

注意点として, このままの場合, ``ST`` が見つからないため, コンパイルエラーとなる. そのため, ``ISBN13`` より先に ``ST`` を定義する必要がある. つまり,

```c
struct ST{
    char prefix[3];
    char group[1];
    char publisher[4];
    char title[4];
    char check_digit[1];
};

union ISBN13{
    char lst[14];
    struct ST st;
};
```

このようにしたらOK.

### 構造体を共有体の中で宣言

```c
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
```

このように共有体の宣言の中に含める.

## ここまでのまとめ

```c
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
```

```c
$ gcc -o union_test2 union_test2.c 
$ ./union_test2
9784758078436
978-4-7580-7843-6
```
