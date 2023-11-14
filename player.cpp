#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<iomanip>
#include"cmd_console_tools.h"
#include<Windows.h>
#include"class.h"
#include<wingdi.h>
#include<conio.h>
#include<fstream>
#include<string>
using namespace std;


void player::rank_read(int score)
{
	ifstream in;
	info user[9];
	for (int i = 0; i < 9; i++)
		user[i].score = 0;
	int i = 0;
	in.open("rank.txt", ios::in);
	if (!in.is_open()) {
		cout << "排名文件打开失败！" << endl;
		return;
	}
	else {
		cout << "请输入您的大名:" ;
		char name[20];
		cin >> name;
		char ch;
		while (in.peek()!=EOF) {
			int j = 0;
			while (in.peek() == ' ')
				in.get();
			in.clear();
			getline(in, user[i].name, ' ');
			while (in.peek() == ' ')
				in.get();
			while (in.peek() != ' '&&in.peek()!=EOF&&in.peek()!='\n')
			{
				ch = in.get();
				user[i].score = user[i].score * 10 + ch - '0';
			}
			while (in.peek() == ' ')
				in.get();
			i++;
		}
		if (i == 9)
		{
			for (int m = 0; m < 9; m++) {
				if (score >= user[m].score) {
					for (int x = 9; x > m; x--)
					{
						user[x].name = user[x - 1].name;
						user[x].score = user[x - 1].score;
					}
					user[m].name = name;
					user[m].score = score;
					break;
				}
			}
		}
		else {
			for (int m = 0; m < i; m++) {
				if (score >= user[m].score) {
					for (int x=i;x>m;x--)
					{
						user[x].name = user[x-1].name;
						user[x].score = user[x-1].score;
					}
					user[m].name = name;
					user[m].score = score;
					break;
				}
			}
		}
	}
	in.close();
	ofstream outfile("rank.txt",ios::out);
	for (int m = 0; m < i; m++)
	{
		outfile<<user[m].name;
		outfile << " ";
		outfile << user[m].score << " ";
	}
	outfile << user[i].name << " " << user[i].score;
	outfile.close();
}
//根据分数和输入昵称写入rank.txt
void player::rank_write() 
{
	ifstream in;
	info user[9];
	for (int i = 0; i < 9; i++)
		user[i].score = 0;
	int i = 0;
	in.open("rank.txt", ios::in);
	if (!in.is_open()) {
		cout << "排名文件打开失败！" << endl;
		return;
	}
	else {
		char ch;
		while (in.peek() != EOF) {
			int j = 0;
			while (in.peek() == ' ')
				in.get();
			in.clear();
			getline(in, user[i].name, ' ');
			while (in.peek() == ' ')
				in.get();
			while (in.peek() != ' ' && in.peek() != EOF && in.peek() != '\n')
			{
				ch = in.get();
				user[i].score = user[i].score * 10 + ch - '0';
			}
			i++;
		}
		for (int m = 0; m < i; m++)
			cout << m + 1 << " " << user[m].name << " " << user[m].score << endl;
	}
}
//根据rank.txt输出排行榜