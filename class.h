#pragma once
#include <iostream>
#include<iomanip>
#include"cmd_console_tools.h"
#include<Windows.h>
#include<string>

#define row 9
#define col 9

using namespace std;
struct path {
	int x;
	int y;
};
class qipan {
public:
	
	void paint_qipan();
	void paint_nextbeads_pan();
	void paint_score_pan();
	
	
	friend class bead;
};

class bead {
private:
	int beads[row][col];
	int newbeads[3];
public:
	void randomappear_first(int n, int a[9][9]);
	void randomappear_later(int n, bead a, int color[]);
	void drawballs(bead a);
	void random_color(int color[]);
	void beads_initialization();
	void mouse_move(bead a, int* exit);
	void balls_move(bead a, int* length, struct path road[]);
	bool dfs_seekroad(bead a, int x1, int x2, int y1, int y2, int visit[9][9], int* length, struct path road[]);
	void ball_percent(bead a, int xiaochu[]);
	void draw_next3balls(int color[]);
	int jifen(bead a, int* sum1, int* sum, int xiaochu[]);
	int judge_end(bead a);
	void paint_xiaochu_pan(bead a);
	double sum(int number, bead a);
	friend class player;
};
typedef struct inf
{
	string name;
	int score;
}info;

class player {
public:
	void rank_read(int score);
	void rank_write();
};







