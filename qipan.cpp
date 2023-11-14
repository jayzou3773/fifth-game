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
	cout << "╔";
	for (j = 0; j < col-1; j++)
		cout << "═╦";
	cout << "═╗" << endl;
	for (i = 0; i < row - 1; i++) {
		for (j = 0; j < col; j++)
			cout << "║　";
		cout << "║" << endl;
		cout << "╠═";
		for (j = 0; j < col - 1; j++)
			cout << "╬═";
		cout << "╣" << endl;
	}
	for (j = 0; j < col; j++)
		cout << "║　";
	cout << "║" << endl;
	cout << "╚";
	for (j=0;j<col-1;j++)
		cout << "═╩";
	cout << "═╝" << endl;
}
//画主棋盘
void qipan::paint_nextbeads_pan()
{
	cct_setcolor(15, 0);
	cct_gotoxy(42, 5);
	cout << "╔═╦═╦═╗";
	cct_gotoxy(42, 6);
	cout << "║  ║  ║  ║";
	cct_gotoxy(42, 7);
	cout << "╚═╩═╩═╝";
}
//画右侧出现下三个随机出现棋子的棋盘
void qipan::paint_score_pan()
{
	cct_setcolor(15, 0);
	cct_gotoxy(42, 1);
	cout << "╔═════╗";
	cct_gotoxy(42, 2);
	cout << "║得分：    ║";
	cct_gotoxy(42, 3);
	cout << "╚═════╝";
}
//画右侧分数盘
void bead::paint_xiaochu_pan(bead a)
{
	int i;
	cct_gotoxy(42, 9);
	cout << "╔";
	for (i = 0; i < 12; i++)
		cout << "═";
	cout << "╗" << endl;
	cct_gotoxy(42, 10);
	cout << "║　:73/(90.12%) 消除-0   ║" << endl;
	for (i = 0; i < 6; i++) {
		cct_gotoxy(42, 11 + i);
		cout << "║";
		cct_showstr(44, 11 + i, "○", i + 1, 15, 1);
		cct_setcolor(15, 0);
		cout << ":" << setfill('0') << setprecision(0) << setw(2) << bead::sum(i + 1, a) << "/(";
		cout << setw(5) << setfill(' ') << setprecision(2) << setiosflags(ios::fixed) << 100 * sum(i + 1, a) / (row * col) << "%) 消除-0   ║" << endl;
	}
	cct_gotoxy(42, 17);
	cout << "╚";
	for (i = 0; i < 12; i++)
		cout << "═";
	cout << "╝";
	cct_setcolor(0, 15);
}
//画右侧消除比例盘