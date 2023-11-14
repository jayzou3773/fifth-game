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
	PlaySound(TEXT("uc28y-cfxbf.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);//播放开场音乐
	
	cct_setcursor(3);
	
	b.beads_initialization();//棋子状态初始化
	cct_gotoxy(0, 0);
	cct_setcolor(0, 15);
	cct_setfontsize("新宋体", 36);
	cout << "屏幕：" << 2 * row + 5 << "行" << 70 << "列右键退出" << endl;
	cct_setcolor(15, 0);
	qp.paint_qipan();//绘制棋盘
	b.drawballs(b);//绘制初始小球
	cct_setcolor(0, 15);
	b.jifen(b, &sum1, &sum, xiaochu);
	qp.paint_nextbeads_pan();//绘制三个小球盘
	qp.paint_score_pan();//绘制得分盘
	b.paint_xiaochu_pan(b);//绘制比例盘
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
		if (!b.jifen(b, &sum1, &sum, xiaochu)) {//判断有无消除情况
			option = -1;
			b.randomappear_later(3, b, color);
			if (b.jifen(b, &sum1, &sum, xiaochu))//判断新生成会不会与原来的状态消除（尽管概率很小）
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
			b.random_color(color);//随机生成三个颜色小球
			b.draw_next3balls(color);
		}
		cct_setcolor(0, 15);
	}
	cout << "游戏结束          " << endl;
	cct_setcolor(0, 15);
	cct_cls();
	PlaySound(TEXT("y921.wav"), NULL, SND_FILENAME | SND_ASYNC );//播放结尾音乐进入排行榜
	p.rank_read(sum);
	cout << "实时排行榜" << endl;
	p.rank_write();
	system("pause");
}