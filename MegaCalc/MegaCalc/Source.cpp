/*
MegaCalc
����{�@�\�� ver 0
N.O. 2016

�������̑����Z���A�ɗ͊ȒP�ŉ���₷���\����
�g�p���Ď��������ic++�̃N���X���g�p�������璷�ȁj
�\�[�X���X�g�ł���B�i�]���ȂO�̕\�����c���Ă���j

*/

#include <iostream>
#include <iomanip>
#include <cctype>

#define MAXDIGIT 70  /*  �ő包��MAXDIGIT  */
using namespace std;

/*   �v���g�^�C�v�錾   */
void reset(char*, int);
void input(char*, int);
void add(char*, char*, char*, int);
void add_digit(char, char, char, char*, char*);
void display(char*, char*, char*, int);
void lineprint(char, char*, int);
void linedraw(char, int);


int main()
{
	char a[MAXDIGIT], b[MAXDIGIT], c[MAXDIGIT];		/* char�^���������ł͂Ȃ����l������ */
	reset(a, MAXDIGIT);					/* �z�� a �̏����� */
	reset(b, MAXDIGIT);					/* �z�� b �̏����� */
	reset(c, MAXDIGIT);					/* �z�� c �̏����� */
	input(a, MAXDIGIT);					/* �z�� a �ɓǂݍ��� */
	input(b, MAXDIGIT);					/* �z�� b �ɓǂݍ��� */
	add(a, b, c, MAXDIGIT);					/* a��b�𑫂��Č��ʂ�c�Ɋi�[���� */
	display(a, b, c, MAXDIGIT);				/* a��b��c���o�� */
}

void reset(char* buf, int maxdigit)   /* maxdigit�͍ő包����\���ϐ� */
{
	int i;
	for (i = 0; i<maxdigit; i++)
		buf[i] = 0;			/* �z���0�ŏ����� */
	return;
}

void input(char* buf, int maxdigit)   /* maxdigit�͍ő包����\���ϐ� */
{
	char str[MAXDIGIT];             /* ���@�I�ɂ�a��b�Ɠ���char�^�̔z��ł��邪�A
									�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@ str��a��b�Ƃ͈قȂ�A����������� */
	int i, j;
	printf("input data:");
	cin >> str;	             /* �L�[�{�[�h����̃f�[�^�𕶎���Ƃ��Ċi�[ */
							 //cout << str;
	i = 0;
	while (str[i] != '\0')
		i++;			 /* ������̒����𑪒� */
	j = 0;
	while (i>0) {
		buf[j] = str[i - 1] - '0';     /* ������\�������R�[�h�𐔒l�Ɋ��Z */
		j++;  /* buf�ɂ͐擪(buf�ɂƂ��Ă�1�̈�)���珇�ɐ��l���i�[ */
		i--;  /* str�ł͍Ō��(str�ł͂����炪1�̈�)���珇�ɕ��������o�� */
	}
	return;
}

void add(char* a, char* b, char* c, int maxdigit)   /* maxdigit�͍ő包����\���ϐ� */
{
	int i;
	char carry_in, carry_out; /* carry_in �͉��ʂ̌�����̌J��オ��
							  carry_out�͏�ʂ̌��ւ̌J��オ�� */
	i = 0;
	carry_in = 0;			/* �ꌅ�ڂ͉��̌�����̌J��オ�肪��ɂO */
	while (i<maxdigit)   /* �ꌅ�ڂ��珇�ɍő包�܂Ōv�Z */
	{
		add_digit(a[i], b[i], carry_in, &c[i], &carry_out); /* �ꌅ���̌v�Z */
		carry_in = carry_out;		/* ���̌��֌J��オ���n��
									�J��オ�薳���̏ꍇ�͂O*/
		i++;
	}

	/*  ���l�f�[�^�𕶎��f�[�^�ɕϊ�  (���ȏ��̗ΐF�̌��Ԃ��ɋL�ڂ��ꂽ�����R�[�h���Q��)*/
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
	*c = (a + b + carry_in) % 10;         /* ���̌��̓�����10�Ŋ������]�� */
	*carry_out = (a + b + carry_in) / 10; /* ���̌��ւ̌J��オ���10�Ŋ������� */
	return;
}

void display(char* a, char* b, char* c, int maxdigit)
{
	lineprint(' ', a, maxdigit); /* �z��a�̏o�� */
	lineprint('+', b, maxdigit); /* �����Z�L���{�Ɣz��b�̏o�� */
	linedraw('-', maxdigit + 1);  /* ����------�̏o�� */
	lineprint(' ', c, maxdigit); /* �����̔z��c�̏o�� */
	return;
}

void lineprint(char c, char* line, int maxdigit) /* ���������ɓn���ꂽ�������P��o�͂��A
												 �z��line���Ō��(��ʌ�)���珇�ɏo�� */
{
	int i, maxdigitlimit; /* maxdigitlimit��maxdigit�̔z��̍ŏI�v�f�ԍ� */
	maxdigitlimit = maxdigit - 1;
	cout << c;
	for (i = maxdigitlimit; i >= 0; i--) {  /* �z��line�͍Ō��(��ʌ�)����擪�Ɍ������ďo�� */
		cout << setw(1) << dec << line[i];
	}
	cout << '\n';
	return;
}

void linedraw(char c, int length) /* ���������ɓn���ꂽ������length��o�� */
{
	int i;
	for (i = 0; i<length; i++)
		cout << c;
	cout << '\n';
	return;
}

