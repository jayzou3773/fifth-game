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



int main()
{
	qipan qp;
	bead b;
	player p;
	int option, color[3], xiaochu[7] = { 0 }, sum1 = 0, sum = 0, exit = 0;
	cct_cls();
	PlaySound(TEXT("uc28y-cfxbf.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//���ſ�������
	
	cct_setcursor(3);
	
	b.beads_initialization();//����״̬��ʼ��
	cct_gotoxy(0, 0);
	cct_setcolor(0, 15);
	cct_setfontsize("������", 36);
	cout << "��Ļ��" << 2 * row + 5 << "��" << 70 << "���Ҽ��˳�" << endl;
	cct_setcolor(15, 0);
	qp.paint_qipan();//��������
	b.drawballs(b);//���Ƴ�ʼС��
	cct_setcolor(0, 15);
	b.jifen(b, &sum1, &sum, xiaochu);
	qp.paint_nextbeads_pan();//��������С����
	qp.paint_score_pan();//���Ƶ÷���
	b.paint_xiaochu_pan(b);//���Ʊ�����
	cct_gotoxy(0, row * 2 + 1);
	b.random_color(color);
	b.draw_next3balls(color);
	cct_setcolor(15, 0);
	cct_gotoxy(50, 2);
	cout << sum;
	while (!b.judge_end(b)) {
		b.mouse_move(b, &exit);
		if (exit == 1)
			break;
		if (!b.jifen(b, &sum1, &sum, xiaochu)) {//�ж������������
			option = -1;
			b.randomappear_later(3, b, color);
			if (b.jifen(b, &sum1, &sum, xiaochu))//�ж������ɻ᲻����ԭ����״̬���������ܸ��ʺ�С��
			{
				option = -2;
					b.drawballs(b);
					b.ball_percent(b, xiaochu);
					cct_gotoxy(50, 2);
					cout << sum;
			}
			b.drawballs(b);
			b.ball_percent(b, xiaochu);
		}
		else {
			PlaySound(TEXT("14487.wav"), NULL, SND_FILENAME | SND_ASYNC );
			option = -2;
			b.drawballs(b);
			b.ball_percent(b, xiaochu);
			cct_gotoxy(50, 2);
			cout << sum;
		}
		if (option == -1) {
			b.random_color(color);//�������������ɫС��
			b.draw_next3balls(color);
		}
		cct_setcolor(0, 15);
	}
	cout << "��Ϸ����          " << endl;
	cct_setcolor(0, 15);
	cct_cls();
	PlaySound(TEXT("y921.wav"), NULL, SND_FILENAME | SND_ASYNC );//���Ž�β���ֽ������а�
	p.rank_read(sum);
	cout << "ʵʱ���а�" << endl;
	p.rank_write();
	system("pause");
}