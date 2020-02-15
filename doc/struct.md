# 構造体

## 構造体とは

```
構造体とは, char型, int型など, 複数のデータ型を組み合わせて, 新しいデータ型として扱うもの
```

### ご利益

* 複雑なデータ型の構成をもつ新しいデータ型を作成可能
* 個別のデータ型を一つにまとめて処理可能

## 構造体の宣言

### 構造体の宣言

```c
struct タグ名{
	データ型 メンバ名;
    データ型 メンバ名;
    データ型 メンバ名;
    ...
};
```

実例

```c
struct ISBN13
{
    char prefix[4];
    char group[9];
    char publisher[9];
    char title[9];
    char check_digit[2];
};
```

このままでは``ISBN13`` というデータ型の構成が宣言されただけであるため, 変数を宣言する必要がある.

> ``int`` や ``char`` と記述するだけでは使えないことと同じ

### 変数の宣言

```c
struct タグ名 変数名;
```

実例

```c
struct ISBN13 isbn;
```

もちろん

```c
struct ISBN13 isbn[2];
struct ISBN13 *isbn;
```

このように, 配列, ポインタの宣言をすることも可能.

### 構造体の宣言+変数の宣言

```c
struct タグ名{
	データ型 メンバ名;
    データ型 メンバ名;
    データ型 メンバ名;
    ...
} 変数名;
```

実例

```c
struct ISBN13
{
    char prefix[4];
    char group[9];
    char publisher[9];
    char title[9];
    char check_digit[2];
} isbn;
```

このように構造体の宣言と変数の宣言を一緒に行うことも可能.

## 構造体の初期化

実例

```c
struct ISBN13 isbn[2] =
{
    {"978", "4", "7580", "7821", "4"},
    {"978", "4", "7580", "7843", "6"}
};
```

配列と同じように初期化をする.

## メンバの参照

### ポインタで宣言していない場合

```c
struct ISBN13 isbn;
```

このように宣言している場合, メンバへの参照は,

```c
構造体変数名.メンバ名;
```

実例

```c
prefix = isbn.prefix;
isbn.prefix = "978";
```

このように「.」ピリオドを使用する.

### ポインタで宣言している場合

```c
struct ISBN13 *isbn;
```

このように宣言している場合, メンバへの参照は,

```c
構造体変数名->メンバ名;
```

実例

```c
prefix = isbn->prefix;
isbn->prefix = "978";
```

このように「->」関節メンバ演算子を使用する.

## ここまでのまとめ

ここまでの内容をもとに試しのプログラムを作成.

* ISBN-13 を格納するプログラム
* ISBNは13桁のコードで表され, 通常5つのパートからなる
* 各パートごとにその値(文字列)を保持する

```c
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
```

```shell
$ gcc -o isbn_struct isbn_struct.c
$ ./isbn_struct
978-4-7580-7821-4
978-4-7580-7843-6
```

## 構造体のアドレス

### 構造体のアドレス

```c
&構造体変数名;
```

実例

```c
&isbn;
```

このように指定する.

### 各メンバのアドレス

#### ポインタで宣言していない場合

```c
&構造体変数名.メンバ名;
```

実例

```c
&isbn.prefix;
```

#### ポインタで宣言している場合

```c
&構造体変数名->メンバ名;
```

実例

```c
&isbn->prefix;
```

## 構造体の入れ子

構造体は, メンバに構造体を指定することも可能.

実例

```c
struct JpBookCode
{
    struct ISBN13 isbn;
    char c_code[5];
    int price;
};
```

このように構造体の中に構造体を定義する.

注意点として, このままの場合, ``ISBN13`` が見つからないため, コンパイルエラーとなる. そのため, ``JpBookCode`` より先に ``ISBN13`` を定義する必要がある. つまり,

```c
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
```

とすればOK.

## ここまでのまとめ

ここまでの内容をもとに試しのプログラムを作成.

* ISBN-13, C-コード, 本体価格も格納する
* ISBN-13 については前回と同様
* C-コード は4桁の数字で構成される(今回は文字列として扱う)
* 本体価格は整数値として扱う

```c
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
```

```shell
$ gcc -o jp_book_code jp_book_code.c 
$ ./jp_book_code 
978-4-7580-7821-4, C9979, \680E
978-4-7580-7843-6, C9979, \680E
```
