#include <iostream>
#include<iomanip>
#include"cmd_console_tools.h"
#include<Windows.h>
#include"class.h"

using namespace std;
#define row 9
#define col 9

void qipan::paint_qipan()
{
	int i, j;
	cct_setcolor(15, 0);
	cout << "�X";
	for (j = 0; j < col-1; j++)
		cout << "�T�j";
	cout << "�T�[" << endl;
	for (i = 0; i < row - 1; i++) {
		for (j = 0; j < col; j++)
			cout << "�U��";
		cout << "�U" << endl;
		cout << "�d�T";
		for (j = 0; j < col - 1; j++)
			cout << "�p�T";
		cout << "�g" << endl;
	}
	for (j = 0; j < col; j++)
		cout << "�U��";
	cout << "�U" << endl;
	cout << "�^";
	for (j=0;j<col-1;j++)
		cout << "�T�m";
	cout << "�T�a" << endl;
}
//��������
void qipan::paint_nextbeads_pan()
{
	cct_setcolor(15, 0);
	cct_gotoxy(42, 5);
	cout << "�X�T�j�T�j�T�[";
	cct_gotoxy(42, 6);
	cout << "�U  �U  �U  �U";
	cct_gotoxy(42, 7);
	cout << "�^�T�m�T�m�T�a";
}
//���Ҳ��������������������ӵ�����
void qipan::paint_score_pan()
{
	cct_setcolor(15, 0);
	cct_gotoxy(42, 1);
	cout << "�X�T�T�T�T�T�[";
	cct_gotoxy(42, 2);
	cout << "�U�÷֣�    �U";
	cct_gotoxy(42, 3);
	cout << "�^�T�T�T�T�T�a";
}
//���Ҳ������
void bead::paint_xiaochu_pan(bead a)
{
	int i;
	cct_gotoxy(42, 9);
	cout << "�X";
	for (i = 0; i < 12; i++)
		cout << "�T";
	cout << "�[" << endl;
	cct_gotoxy(42, 10);
	cout << "�U��:73/(90.12%) ����-0   �U" << endl;
	for (i = 0; i < 6; i++) {
		cct_gotoxy(42, 11 + i);
		cout << "�U";
		cct_showstr(44, 11 + i, "��", i + 1, 15, 1);
		cct_setcolor(15, 0);
		cout << ":" << setfill('0') << setprecision(0) << setw(2) << bead::sum(i + 1, a) << "/(";
		cout << setw(5) << setfill(' ') << setprecision(2) << setiosflags(ios::fixed) << 100 * sum(i + 1, a) / (row * col) << "%) ����-0   �U" << endl;
	}
	cct_gotoxy(42, 17);
	cout << "�^";
	for (i = 0; i < 12; i++)
		cout << "�T";
	cout << "�a";
	cct_setcolor(0, 15);
}
//���Ҳ�����������