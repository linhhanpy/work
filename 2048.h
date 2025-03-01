#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<graphics.h>
#define MAX_SIZE 4//每行格子数
#define GRID_WIDTH 100//格子宽度
#define INTERVAL 15//格子间隔
#define WIN_SIZE MAX_SIZE*GRID_WIDTH+5*INTERVAL
using namespace std;
enum  Color1//枚举颜色
{
	zero    =RGB(205,193,180),
	twoto1  =RGB(238,228,218),
	twoto2  =RGB(237,224,200),
	twoto3  =RGB(242,177,121),
	twoto4  =RGB(245,149,99),
	twoto5  =RGB(246,124,95),
	twoto6  =RGB(246,94,94),
	twoto7  =RGB(242,177,121),
	twoto8  =RGB(237,204,97),
	twoto9  =RGB(255,42,128),
	twoto10 =RGB(145,0,72),
	twoto11 =RGB(242,17,158),
	bk      =RGB(187,173,160),
};
//实现颜色与数据的链接
Color1 arr[13] = { zero,twoto1,twoto2,twoto3,twoto4,twoto5,twoto6,twoto7,twoto8,twoto9,twoto10,twoto11,bk};
int num[12] = { 0,2,4,8,16,32,64,128,256,512,1024,2048 };
POINT pos[MAX_SIZE][MAX_SIZE];
int map[MAX_SIZE][MAX_SIZE];//数据存储
char usrkey = 0;
int RandTwoFour()
{
	if (rand() % 10 == 0)
	{
		return 4;
	}
	else
	{
		return 2;
	}
}
bool IsGameOver()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (map[i][j] == 0)
			{
				return false;
			}
			if (i < MAX_SIZE - 1 && map[i][j] == map[i + 1][j])
			{
				return false;
			}
			if (j < MAX_SIZE - 1 && map[i][j] == map[i][j + 1])
			{
				return false;
			}
		}
	}
	return true;
}
void CreateNumber()
{
	while (1)
	{
		int x = rand() % MAX_SIZE;
		int y = rand() % MAX_SIZE;
		if (map[x][y] == 0)
		{
			map[x][y] = RandTwoFour();
			break;
		}
	}
}
void GameInit()
{
	srand(GetTickCount());
	//初始化数组
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			map[i][j] = 0;
		}
	}
	//初始化每个格子的坐标，左上角
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			pos[i][j].x=(j*GRID_WIDTH+(j+1)*INTERVAL);
			pos[i][j].y=(i*GRID_WIDTH+(i+1)*INTERVAL);
		}
	}
	CreateNumber();
	CreateNumber();
}
void GameDraw()
{
	//设置背景颜色
	setbkcolor(Color1::bk);
	cleardevice();
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			for (int k = 0; k < 12; k++)
			{
				if (map[i][j] == num[k])
				{
					DWORD tempcolor = arr[k];
					setfillcolor(tempcolor);
					solidrectangle(pos[i][j].x, pos[i][j].y, pos[i][j].x + GRID_WIDTH, pos[i][j].y + GRID_WIDTH);
					if (num[k] != 0)
					{
						char number[5] = " ";
						sprintf(number, "%d", num[k]);
						setbkmode(TRANSPARENT);
						settextcolor(RGB(119, 110, 101));
						settextstyle(45,0,"黑体");
						int tempx = textwidth(number);
						tempx = (GRID_WIDTH - tempx)/2;
						int tempy = textheight(number);
						tempy = (GRID_WIDTH - tempy) / 2;
						outtextxy(pos[i][j].x+tempx, pos[i][j].y+tempy,number);
					}
				}
			}
		}
	}
}
//移动方块合成数据
//向上
void Moveup()
{
	for (int j = 0; j < MAX_SIZE; j++) {
		// 先合并相邻且值相同的数字
		for (int i = 0; i < MAX_SIZE - 1; i++) {
			if (map[i][j] == map[i + 1][j]) {
				map[i][j] *= 2;
				map[i + 1][j] = 0;
			}
		}
		// 再进行移动
		for (int i = 0; i < MAX_SIZE; i++) {
			if (map[i][j] == 0) {
				for (int k = i + 1; k < MAX_SIZE; k++) {
					if (map[k][j] != 0) {
						map[i][j] = map[k][j];
						map[k][j] = 0;
						break;
					}
				}
			}
		}
	}
}
//向下
void Movedown()
{
	for (int j = 0; j < MAX_SIZE; j++) {
		// 先合并相邻且值相同的数字
		for (int i = MAX_SIZE - 1; i > 0; i--) {
			if (map[i][j] == map[i - 1][j]) {
				map[i][j] *= 2;
				map[i - 1][j] = 0;
			}
		}
		// 再进行移动
		for (int i = MAX_SIZE - 1; i >= 0; i--) {
			if (map[i][j] == 0) {
				for (int k = i - 1; k >= 0; k--) {
					if (map[k][j] != 0) {
						map[i][j] = map[k][j];
						map[k][j] = 0;
						break;
					}
				}
			}
		}
	}
}
//向左
void Moveleft()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		// 先合并相邻且值相同的数字
		for (int j = 0; j < MAX_SIZE - 1; j++) {
			if (map[i][j] == map[i][j + 1]) {
				map[i][j] *= 2;
				map[i][j + 1] = 0;
			}
		}
		// 再进行移动
		for (int j = 0; j < MAX_SIZE; j++) {
			if (map[i][j] == 0) {
				for (int k = j + 1; k < MAX_SIZE; k++) {
					if (map[i][k] != 0) {
						map[i][j] = map[i][k];
						map[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}
//向右
void Moveright()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		// 先合并相邻且值相同的数字
		for (int j = MAX_SIZE - 1; j > 0; j--) {
			if (map[i][j] == map[i][j - 1]) {
				map[i][j] *= 2;
				map[i][j - 1] = 0;
			}
		}
		// 再进行移动
		for (int j = MAX_SIZE - 1; j >= 0; j--) {
			if (map[i][j] == 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (map[i][k] != 0) {
						map[i][j] = map[i][k];
						map[i][k] = 0;
						break;
					}
				}
			}
		}
	}
}
//键盘处理数据
void KeyControl()
{
	
	usrkey = _getch();
	switch (usrkey)
	{
	case 72:
	case'w':
	case'W':
		cout << "up" << endl;
		Moveup();
		CreateNumber();
		break;
	case 80:
	case's':
	case'S':
		cout << "down" << endl;
		Movedown();
		CreateNumber();
		break;
	case 75:
	case'a':
	case'A':
		cout << "left" << endl;
		Moveleft();
		CreateNumber();
		break;
	case 77:
	case'd':
	case'D':
		cout << "right" << endl;
		Moveright();
		CreateNumber();
		break;
	}
}
int g2048_main()
{
	initgraph(WIN_SIZE,WIN_SIZE,SHOWCONSOLE);//创建窗口
	GameInit();
	while (1)
	{
		BeginBatchDraw();
		GameDraw();
		EndBatchDraw();
		KeyControl();
		IsGameOver();
	}
	system("pause");
	return 0;
}

