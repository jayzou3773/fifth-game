#pragma comment(lib,"WinMM.lib")
#include <iostream>
#include<iomanip>
#include"cmd_console_tools.h"
#include<Windows.h>
#include"class.h"
#include<wingdi.h>
#include<conio.h>
#include<Mmsystem.h>

using namespace std;
#define row 9
#define col 9

double bead::sum(int number, bead a)
{
	int i, j;
	double sum_number = 0;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			if (beads[i][j] == number)
				sum_number++;
		}
	return sum_number;
}
//�����ϸ���ɫ����������numberΪ��ɫ
void bead::randomappear_first(int n, int a[9][9])
{
	srand((unsigned int)(time(NULL)));
	while (n > 0) {
		int i = rand() % row;
		int j = rand() % col;
		if (a[i][j] == 0) {//�հ�λ�òſɼ���
			a[i][j] = 1 + rand() % 6;
			n--;
		}
	}
}
//��ʼ����£����λ�ò����������ɫ������
void bead::randomappear_later(int n, bead a, int color[])
{
	int sum = 0;
	srand((unsigned int)(time(NULL)));
	for (int m = 0; m < row; m++)
		for (int n = 0; n < col; n++) {
			if (beads[m][n] == 0)
				sum++;
		}
	if (n > sum)
		n = sum;//�����Ͽ�λ������С��3ʱ
	while (n > 0) {
		int i = rand() % row, j = rand() % col;
		if (beads[i][j] == 0) {
			beads[i][j] = color[n - 1];
			n--;
		}
	}
}
//֮��ÿһ�������û����������������̵������λ���������������ɫ������
void bead::random_color(int color[])
{
	srand((unsigned int)(time(NULL)));
	for (int i = 0; i < 3; i++)
		color[i] = rand() % 6 + 1;
}
//��color���鸳ֵ�����ɫ
void bead::drawballs(bead a)
{
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
		{
			if (beads[i][j] > 0)
			{
				cct_setcolor(beads[i][j], 15);
				cct_gotoxy(2 + j * 4, 2 + i * 2);
				cout << "��";
			}
			else
			{
				cct_setcolor(15, 0);
				cct_gotoxy(2 + j * 4, 2 + i * 2);
				cout << "��";
			}
		}
	cct_setcolor(15, 0);
	cct_gotoxy(0, 2 * row + 2);

}
//�������ϻ�������
void bead::beads_initialization()
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			beads[i][j] = 0;
	randomappear_first(7,beads);
}
//���������ʼ��
void bead::mouse_move(bead a, int* exit)
{
	struct path road[100];
	int x = 0, y = 0, mx, my, maction, keycode1, keycode2, flag = 0, i, j;
	while (1) {
		flag = 0;
		int visit[9][9] = { 0 }, length = 0;
		cct_enable_mouse();
		cct_read_keyboard_and_mouse(mx, my, maction, keycode1, keycode2);
		for (i = 0; i < row; i++)
			for (j = 0; j < col; j++) {

				if ((mx == 2 + j * 4 || mx == 3 + j * 4) && mx <= 40 && my == 2 + i * 2)
					flag = 1;
			}
		cct_gotoxy(0, 2 * row + 2);
		if (flag == 1)//ʵʱ��ʾ��������̵�λ��
		{
			cout << "��ǰλ��" << (my - 2) / 2 + 1 << "��" << ((mx - 2) / 4) + 1 << "��       ";
		}
		else {
			cct_disable_mouse();
		}
		if (maction == MOUSE_LEFT_BUTTON_CLICK && beads[(my - 2) / 2][(mx - 2) / 4] > 0 && flag == 1) {//������������ԭ������
			int posx, posy;
			if (x > 0 && y > 0 && (x != mx || y != my) && (beads[(y - 2) / 2][(x - 2) / 4] > 0))
			{
				posx = (x - 2) / 4;
				posy = (y - 2) / 2;
				cct_setcolor(beads[(y - 2) / 2][(x - 2) / 4], 15);
				cct_gotoxy(2 + posx * 4, 2 + posy * 2);
				cout << "��";
			}
			PlaySound(TEXT("y1703.wav"), NULL, SND_FILENAME | SND_ASYNC );
			posx = (mx - 2) / 4;
			posy = (my - 2) / 2;
			if (2 + posx * 4 <= 40)
				cct_setcolor(beads[(my - 2) / 2][(mx - 2) / 4], 15);
			cct_gotoxy(2 + posx * 4, 2 + posy * 2);
			cout << "��";//����������任Ч��
			x = mx;
			y = my;
		}
		if (maction == MOUSE_LEFT_BUTTON_CLICK && beads[(my - 2) / 2][(mx - 2) / 4] == 0) {
			if ((beads[(y - 2) / 2][(x - 2) / 4] > 0 && dfs_seekroad( a, (x - 2) / 4, (mx - 2) / 4, (y - 2) / 2, (my - 2) / 2, visit, &length, road)))
			{
				PlaySound(TEXT("y1703.wav"), NULL, SND_FILENAME | SND_ASYNC );
				cct_gotoxy(0, 2 * row + 2);
				cout << "��" << (my - 2) / 2 + 1 << "��" << ((x - 2) / 4) + 1 << "������" << (my - 2) / 2 + 1 << "��" << ((mx - 2) / 4) + 1 << "��";
				balls_move( a, &length, road);
				beads[(my - 2) / 2][(mx - 2) / 4] = beads[(y - 2) / 2][(x - 2) / 4];
				beads[(y - 2) / 2][(x - 2) / 4] = 0;
				cct_setcolor(0, 15);
				cct_gotoxy(0, 2 * row + 2);
				break;
			}
			else
			{
				cct_setcolor(0, 15);
				cct_gotoxy(0, 2 * row + 2);
				cout << "�޷��ҵ�·��       ";
				Sleep(3);
			}
		}
		if (maction == MOUSE_RIGHT_BUTTON_CLICK && flag == 1)
		{
			cct_gotoxy(0, 2 * row + 2);
			*exit = 1;
			break;
		}
		cct_setcolor(0, 15);
	}
}
//�������ĺ��������һ��������ٴε����λ�ã������ͨ·���ʵ���ƶ��������ʱ���б仯����ʾ�򱻵���������Ҽ��������ʱ���˳���Ϸ���������а�
void bead::balls_move(bead a, int* length, struct path road[])
{
	int j;
	for (int i = 0; i < *length - 1; i++) {
		if (road[i].x < road[i + 1].x)
			for (j = 0; j < 4; j = j + 2)
			{
				Sleep(20);
				if (j == 2)
					cct_showstr(2 + road[i].x * 4 + j, 2 + road[i].y * 2, "�U", 15, 0, 1);
				else
					cct_showstr(2 + road[i].x * 4 + j, 2 + road[i].y * 2, "��", 15, 0, 1);
				cct_showstr(2 + road[i].x * 4 + j + 2, 2 + road[i].y * 2, "��", beads[road[0].y][road[0].x], 15, 1);
			}
		if (road[i].x > road[i + 1].x)
			for (j = 0; j < 4; j = j + 2)
			{
				Sleep(20);
				if (j == 2)
					cct_showstr(2 + road[i].x * 4 - j, 2 + road[i].y * 2, "�U", 15, 0, 1);
				else
					cct_showstr(2 + road[i].x * 4 - j, 2 + road[i].y * 2, "��", 15, 0, 1);
				cct_showstr(2 + road[i].x * 4 - j - 2, 2 + road[i].y * 2, "��", beads[road[0].y][road[0].x], 15, 1);
			}
		if (road[i].y < road[i + 1].y)
			for (j = 0; j < 2; j++)
			{
				Sleep(20);
				if (j == 1)
					cct_showstr(2 + road[i].x * 4, 2 + road[i].y * 2 + j, "�T", 15, 0, 1);
				else
					cct_showstr(2 + road[i].x * 4, 2 + road[i].y * 2 + j, "��", 15, 0, 1);
				cct_showstr(2 + road[i].x * 4, 2 + road[i].y * 2 + j + 1, "��", beads[road[0].y][road[0].x], 15, 1);
			}
		if (road[i].y > road[i + 1].y)
			for (j = 0; j < 2; j++)
			{
				Sleep(20);
				if (j == 1)
					cct_showstr(2 + road[i].x * 4, 2 + road[i].y * 2 - j, "�T", 15, 0, 1);
				else
					cct_showstr(2 + road[i].x * 4, 2 + road[i].y * 2 - j, "��", 15, 0, 1);
				cct_showstr(2 + road[i].x * 4, 2 + road[i].y * 2 - j - 1, "��", beads[road[0].y][road[0].x], 15, 1);
			}
	}
}
//ͨ��dfs�㷨�ҵ���·��������ʾС���ƶ�
bool bead::dfs_seekroad(bead a, int x1, int x2, int y1, int y2, int visit[9][9], int* length, struct path road[])
{
	int* p, m, n;
	p = length;
	visit[y1][x1] = 1;
	road[*p].x = x1;
	road[*p].y = y1;
	(*p)++;
	if (x1 == x2 && y1 == y2)
		return true;
	//���ݳ������ӵ����λ�����÷��������Ӷ����������Ч��
	if (x1 < x2)
		m = 1;
	else if (x1 > x2)
		m = -1;
	else
		m = 0;
	if (y1 < y2)
		n = 1;
	else if (y1 > y2)
		n = -1;
	else
		n = 0;
	if (m == 0) {
		int dx[4] = { 0,1,-1,0 }, dy[4] = { n,0,0,-n };
		for (int i = 0; i < 4; i++) {
			int tx = x1 + dx[i];
			int ty = y1 + dy[i];
			if (!visit[ty][tx] && tx < col && ty < row && tx >= 0 && ty >= 0 && beads[ty][tx] == 0) {
				if (dfs_seekroad( a, tx, x2, ty, y2, visit, length, road))
					return true;
			}
		}
	}
	if (n == 0) {
		int dx[4] = { m,0,0,-m }, dy[4] = { 0,1,-1,0 };
		for (int i = 0; i < 4; i++) {
			int tx = x1 + dx[i];
			int ty = y1 + dy[i];
			if (!visit[ty][tx] && tx < col && ty < row && tx >= 0 && ty >= 0 && beads[ty][tx] == 0) {
				if (dfs_seekroad( a, tx, x2, ty, y2, visit, length, road))
					return true;
			}
		}
	}
	if (m != 0 && n != 0) {
		int dx[4] = { m,0,-m,0 }, dy[4] = { 0,n,0,-n };
		for (int i = 0; i < 4; i++) {
			int tx = x1 + dx[i];
			int ty = y1 + dy[i];
			if (!visit[ty][tx] && tx < col && ty < row && tx >= 0 && ty >= 0 && beads[ty][tx] == 0) {
				if (dfs_seekroad( a, tx, x2, ty, y2, visit, length, road))
					return true;
			}
		}
	}
	(*p)--;
	return false;
}
//����dfs�㷨Ѱ��·����ͬʱͨ���趨�����������ȼ����Ż��㷨
void bead::ball_percent(bead a, int xiaochu[])
{
	int i, j;
	double sum[8] = { 0 };
	cct_setcolor(15, 0);
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			sum[beads[i][j]]++;
	for (i = 0; i < 7; i++) {
		cct_gotoxy(47, 10 + i);
		cout << setfill('0') << setprecision(0) << setw(2) << sum[i];
	}
	for (i = 0; i < 7; i++) {
		cct_gotoxy(51, 10 + i);
		cout << setw(5) << setfill(' ') << setiosflags(ios::fixed) << setprecision(2) << 100 * sum[i] / (row * col);
	}
	for (i = 0; i < 6; i++) {
		cct_gotoxy(64, 11 + i);
		cout << setprecision(0) << xiaochu[i];
	}
}
//���Ҳ�ʵʱ��ʾ����ɫС��ĸ�����������������
void bead::draw_next3balls(int color[])
{
	for (int i = 0; i < 3; i++)
		cct_showstr(44 + i * 4, 6, "��", color[i], 15, 1);
}
//���Ҳ�С����ʾ������С�����ɫ
int bead::jifen(bead a, int* sum1, int* sum, int xiaochu[])
{
	int flag = 0, i, j, k, l, n = 1, number[9][9] = { 0 }, q, w;
	for (i = 0; i < row; i++)
		for (j = 0; j < col - 4; j++) {
			n = 1;
			for (k = j + 1; k < col && beads[i][k] == beads[i][k - 1] && beads[i][k] != 0; k++)
				n++;
			if (n >= 5) {
				for (k = j; k < j + n; k++)
					number[i][k]++;
				break;
			}
		}
	//ͬһ�������޵÷�
	for (j = 0; j < col; j++)
		for (i = 0; i < row - 4; i++) {
			n = 1;
			for (k = i + 1; k < row && beads[k][j] == beads[k - 1][j] && beads[k][j] != 0; k++)
				n++;
			if (n >= 5) {
				for (k = i; k < i + n; k++)
					number[k][j]++;
				break;
			}
		}
	//ͬһ�������޵÷�
	for (i = 0, j = 0; i < row; i++) {
		for (q = i, w = j; q < row - 4 && w < col - 4; q++, w++)
		{
			n = 1;
			for (k = q + 1, l = w + 1; k < row && l < col && beads[k][l] == beads[k - 1][l - 1] && beads[k][l] != 0; k++, l++)
				n++;
			if (n >= 5) {
				for (k = q, l = w; k < q + n && l < w + n; k++, l++)
					number[k][l]++;
			}
		}
	}
	//ͬһб�У�\���������޵÷�
	for (i = 0, j = 1; j < col; j++) {
		for (q = i, w = j; q < row - 4 && w < col - 4; q++, w++)
		{
			n = 1;
			for (k = q + 1, l = w + 1; k < row && l < col && beads[k][l] == beads[k - 1][l - 1] && beads[k][l] != 0; k++, l++)
				n++;
			if (n >= 5)
				for (k = q, l = w; k < q + n && j < w + n; k++, l++)
					number[k][l]++;
		}
	}
	//ͬһб�У�\���������޵÷�
	for (i = 0, j = col - 1; j > 0; j--) {
		for (q = i, w = j; q < row - 4 && w >3; q++, w--)
		{
			n = 1;
			for (k = q + 1, l = w - 1; k < row && l >=0 && beads[k][l] == beads[k - 1][l + 1] && beads[k][l] != 0; k++, l--)
				n++;
			if (n >= 5) {
				for (k = q, l = w; k < q + n && l < w + n; k++, l--)
					number[k][l]++;
			}
		}
	}
	//ͬһб�У�/���������޵÷�
	for (i = 1, j = col - 1; i < row; i++) {
		for (q = i, w = j; q < row - 4 && w >3; q++, w--)
		{
			n = 1;
			for (k = q + 1, l = w - 1; k < row && l >=0 && beads[k][l] == beads[k - 1][l + 1] && beads[k][l] != 0; k++, l--)
				n++;
			if (n >= 5) {
				for (k = q, l = w; k < q + n && l < w + n; k++, l--)
					number[k][l]++;
			}
		}
	}
	//ͬһб�У�/���������޵÷�
	n = 0;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			if (number[i][j] > 0)
			{
				xiaochu[beads[i][j] - 1]++;
				beads[i][j] = 0;
				n += number[i][j];
				flag = 1;
			}
		}
	if (n == 0)
		*sum1 = 0;
	else
		*sum1 = 2*n;
	*sum += *sum1;
	return flag;
}
//���ƶ�֮����ʾ�����͵÷����
int bead::judge_end(bead a)
{
	int i, j, flag = 1;
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++) {
			if (beads[i][j] == 0)
			{
				flag = 0;
				break;
			}
		}
	return flag;
}
//�ж������Ƿ��Ѿ���ռ��