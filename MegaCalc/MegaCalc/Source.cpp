/*
MegaCalc
超基本機能版 ver 0
N.O. 2016

多数桁の足し算を、極力簡単で解りやすい表現を
使用して実現した（c++のクラスを使用せずやや冗長な）
ソースリストである。（余分な０の表示が残っている）

*/

#include <iostream>
#include <iomanip>
#include <cctype>

#define MAXDIGIT 70  /*  最大桁数MAXDIGIT  */
using namespace std;

/*   プロトタイプ宣言   */
void reset(char*, int);
void input(char*, int);
void add(char*, char*, char*, int);
void add_digit(char, char, char, char*, char*);
void display(char*, char*, char*, int);
void lineprint(char, char*, int);
void linedraw(char, int);


int main()
{
	char a[MAXDIGIT], b[MAXDIGIT], c[MAXDIGIT];		/* char型だが文字ではなく数値を扱う */
	reset(a, MAXDIGIT);					/* 配列 a の初期化 */
	reset(b, MAXDIGIT);					/* 配列 b の初期化 */
	reset(c, MAXDIGIT);					/* 配列 c の初期化 */
	input(a, MAXDIGIT);					/* 配列 a に読み込み */
	input(b, MAXDIGIT);					/* 配列 b に読み込み */
	add(a, b, c, MAXDIGIT);					/* aとbを足して結果をcに格納する */
	display(a, b, c, MAXDIGIT);				/* aとbとcを出力 */
}

void reset(char* buf, int maxdigit)   /* maxdigitは最大桁数を表す変数 */
{
	int i;
	for (i = 0; i<maxdigit; i++)
		buf[i] = 0;			/* 配列を0で初期化 */
	return;
}

void input(char* buf, int maxdigit)   /* maxdigitは最大桁数を表す変数 */
{
	char str[MAXDIGIT];             /* 文法的にはaやbと同じchar型の配列であるが、
									　　　　　　　　　　　　　　　　　 strはaやbとは異なり、文字列を扱う */
	int i, j;
	printf("input data:");
	cin >> str;	             /* キーボードからのデータを文字列として格納 */
							 //cout << str;
	i = 0;
	while (str[i] != '\0')
		i++;			 /* 文字列の長さを測定 */
	j = 0;
	while (i>0) {
		buf[j] = str[i - 1] - '0';     /* 数字を表す文字コードを数値に換算 */
		j++;  /* bufには先頭(bufにとっての1の位)から順に数値を格納 */
		i--;  /* strでは最後尾(strではこちらが1の位)から順に文字を取り出す */
	}
	return;
}

void add(char* a, char* b, char* c, int maxdigit)   /* maxdigitは最大桁数を表す変数 */
{
	int i;
	char carry_in, carry_out; /* carry_in は下位の桁からの繰り上がり
							  carry_outは上位の桁への繰り上がり */
	i = 0;
	carry_in = 0;			/* 一桁目は下の桁からの繰り上がりが常に０ */
	while (i<maxdigit)   /* 一桁目から順に最大桁まで計算 */
	{
		add_digit(a[i], b[i], carry_in, &c[i], &carry_out); /* 一桁毎の計算 */
		carry_in = carry_out;		/* 次の桁へ繰り上がりを渡す
									繰り上がり無しの場合は０*/
		i++;
	}

	/*  数値データを文字データに変換  (教科書の緑色の見返しに記載された文字コードを参照)*/
	i = 0;
	while (i<maxdigit)
	{
		a[i] = a[i] + '0';
		b[i] = b[i] + '0';
		c[i] = c[i] + '0';
		i++;
	}

	return;
}

void add_digit(char a, char b, char carry_in, char* c, char* carry_out)
{
	*c = (a + b + carry_in) % 10;         /* その桁の答えは10で割った余り */
	*carry_out = (a + b + carry_in) / 10; /* 次の桁への繰り上がりは10で割った商 */
	return;
}

void display(char* a, char* b, char* c, int maxdigit)
{
	lineprint(' ', a, maxdigit); /* 配列aの出力 */
	lineprint('+', b, maxdigit); /* 足し算記号＋と配列bの出力 */
	linedraw('-', maxdigit + 1);  /* 横線------の出力 */
	lineprint(' ', c, maxdigit); /* 答えの配列cの出力 */
	return;
}

void lineprint(char c, char* line, int maxdigit) /* 仮引数ｃに渡された文字を１回出力し、
												 配列lineを最後尾(上位桁)から順に出力 */
{
	int i, maxdigitlimit; /* maxdigitlimitはmaxdigit個の配列の最終要素番号 */
	maxdigitlimit = maxdigit - 1;
	cout << c;
	for (i = maxdigitlimit; i >= 0; i--) {  /* 配列lineは最後尾(上位桁)から先頭に向かって出力 */
		cout << setw(1) << dec << line[i];
	}
	cout << '\n';
	return;
}

void linedraw(char c, int length) /* 仮引数ｃに渡された文字をlength回出力 */
{
	int i;
	for (i = 0; i<length; i++)
		cout << c;
	cout << '\n';
	return;
}

