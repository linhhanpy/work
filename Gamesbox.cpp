/*
	(c) Copyright 2025 Lin Honghan
	Gamesbox
*/
#include "hk.h"
#include "sgs.h"
#include "harrypotter.h"
#include "3d.h"
#include "Cchess.h"
#include "fight.h"
#include "num.h"

#include<stdio.h>
#include<iostream>
#include<ctime>
#include<bits/stdc++.h>
#include<conio.h>
#include<time.h>
#include<cmath>
#include <easyx.h>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#define  N 22

using namespace std;

    int gameover;

    int x1, y1;

    int x,y;

    long start;
//=======================================
//类的实现与应用initialize
//=======================================

//下面定义贪吃蛇的坐标类
class snake_position
{
public:

    int x,y;      //x表示行，y表示列

    snake_position(){};

    void initialize(int &);//坐标初始化


};

snake_position position[(N-2)*(N-2)+1]; //定义贪吃蛇坐标类数组，有(N-2)*(N-2)个坐标

void snake_position::initialize(int &j)
{
        x = 1;

        y = j;
}


//下面定义贪吃蛇的棋盘图

class snake_map
{

private:

    char s[N][N];//定义贪吃蛇棋盘，包括墙壁。

    int grade, length;

    int gamespeed; //前进时间间隔

    char direction; // 初始情况下，向右运动

    int head,tail;

    int score;

    bool gameauto;

public:

    snake_map(int h=4,int t=1,int l=4,char d=77,int s=0):length(l),direction(d),head(h),tail(t),score(s){}

    void initialize();   //初始化函数

    void show_game();

    int updata_game();

    void setpoint();

    void getgrade();

    void display();


};

#define WIDTH 960
#define HEIGHT 640
#define STR_SIZE 20
#define STR_NUM 128
#define STR_WIDTH 15


typedef struct Rain
{
	int x;
	int y;
	int speed;
	TCHAR str[STR_SIZE];
}Rain; 
Rain rain[STR_NUM];

// 随机生成一个字符
char CreateCh()
{
	char ch = 0;
	int flag = rand() % 3; // 0~2
	if (flag == 0)
		ch = rand() % 26 + 'a'; // 产生小写字母a~z
	else if (flag == 1)
		ch = rand() % 26 + 'A'; // 产生大写字母A~Z
	else
		ch = rand() % 10 + '0'; // 产生数字0~9

	return ch;
}
// 初始化结构体成员
void InitRain()
{
	// 初始化字符的位置和速度
	for (int i = 0; i < STR_NUM; ++i)
	{
		rain[i].x = i*STR_WIDTH;
		rain[i].y = rand() % HEIGHT;
		rain[i].speed = rand() % 5 + 5;
	}
	// 获取随机字符填充进数组
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			rain[i].str[j] = CreateCh();
		}
	}
}
// 输出到窗口中
void DrawRain()
{
	cleardevice();
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			outtextxy(rain[i].x, rain[i].y-STR_WIDTH*j, rain[i].str[j]);
			settextcolor(RGB(0, 255-j*13, 0));
		}
	}
}
// 移动字符
void MoveRain()
{
	for (int i = 0; i < STR_NUM; i++)
	{
		rain[i].y += rain[i].speed;
		if (rain[i].y- STR_WIDTH*STR_SIZE > HEIGHT)
		{
			rain[i].y = 0;
		}
	}
}
// 随机改变字符
void ChangeCh()
{
	for (int i = 0; i < STR_NUM; i++)
	{
		rain[rand() % STR_NUM].str[rand() % STR_SIZE] = CreateCh();
	}
}

void snake_map::initialize()
{
    int i,j;

    for(i=1;i<=3;i++)

        s[1][i] = '*';

    s[1][4] = '#';

    for(i=1;i<=N-2;i++)

        for(j=1;j<=N-2;j++)

            s[i][j]=' '; // 初始化贪吃蛇棋盘中间空白部分

    for(i=0;i<=N-1;i++)

        s[0][i] = s[N-1][i] = '-'; //初始化贪吃蛇棋盘上下墙壁

    for(i=1;i<=N-2;i++)

        s[i][0] = s[i][N-1] = '|'; //初始化贪吃蛇棋盘左右墙壁
}


//============================================
//输出贪吃蛇棋盘信息

void snake_map::show_game()

{

    system("cls"); // 清屏

    int i,j;

    cout << endl;

    for(i=0;i<N;i++)
    {

        cout << '\t';

        for(j=0;j<N;j++)

            cout<<s[i][j]<<' '; // 输出贪吃蛇棋盘

        if(i==2) cout << "\t等级：" << grade;

        if(i==6) cout << "\t速度：" << gamespeed;

        if(i==10) cout << "\t得分：" << score << "分" ;

        if(i==14) cout << "\t暂停：按一下空格键" ;

        if(i==18) cout << "\t继续：按两下空格键" ;

        cout<<endl;
    }
}

//输入选择等级
void snake_map::getgrade()
{
    cin>>grade;

    while( grade>7 || grade<1 )
    {
        cout << "请输入数字1-7选择等级，输入其他数字无效" << endl;

        cin >> grade;
    }
    switch(grade)
    {
        case 1: gamespeed = 1000;gameauto = 0;break;

        case 2: gamespeed = 800;gameauto = 0;break;

        case 3: gamespeed = 600;gameauto = 0;break;

        case 4: gamespeed = 400;gameauto = 0;break;

        case 5: gamespeed = 200;gameauto = 0;break;

        case 6: gamespeed = 100;gameauto = 0;break;

        case 7: grade = 1;gamespeed = 1000;gameauto = 1;break;

    }

}

//输出等级，得分情况以及称号

void snake_map::display()
{

    cout << "\n\t\t\t\t等级：" << grade;

    cout << "\n\n\n\t\t\t\t速度：" << gamespeed;

    cout << "\n\n\n\t\t\t\t得分：" << score << "分" ;

}

//随机产生米
void snake_map::setpoint()
{
    srand(time(0));

    do
    {

        x1 = rand() % (N-2) + 1;

        y1 = rand() % (N-2) + 1;

    }while(s[x1][y1]!=' ');

    s[x1][y1]='*';
}

char key;

int snake_map::updata_game()
{
    gameover = 1;

    key = direction;

    start = clock();

    while((gameover=(clock()-start<=gamespeed))&&!kbhit());

    //如果有键按下或时间超过自动前进时间间隔则终止循环



        if(gameover)
        {

            getch();

            key = getch();
        }

        if(key == ' ')

        {
            while(getch()!=' '){};//这里实现的是按空格键暂停，按空格键继续的功能，但不知为何原因，需要按两下空格才能继续。这是个bug。
        }

        else

            direction = key;

        switch(direction)
        {
            case 72: x= position[head].x-1; y= position[head].y;break; // 向上

            case 80: x= position[head].x+1; y= position[head].y;break; // 向下

            case 75: x= position[head].x; y= position[head].y-1;break; // 向左

            case 77: x= position[head].x; y= position[head].y+1; // 向右

        }

        if(!(direction==72||direction==80||direction==75 ||direction==77))   // 按键非方向键

            gameover = 0;

        else if(x==0 || x==N-1 ||y==0 || y==N-1)   // 碰到墙壁

            gameover = 0;

        else if(s[x][y]!=' '&&!(x==x1&&y==y1))    // 蛇头碰到蛇身

            gameover = 0;

        else if(x==x1 && y==y1)

        { // 吃米，长度加1

            length ++;

            if(length>=8 && gameauto)

            {

                length -= 8;

                grade ++;

                if(gamespeed>=200)

                    gamespeed -= 200; // 改变贪吃蛇前进速度

                else

                    gamespeed = 100;

            }

            s[x][y]= '#';  //更新蛇头

            s[position[head].x][position[head].y] = '*'; //吃米后将原先蛇头变为蛇身

            head = (head+1) % ( (N-2)*(N-2) );   //取蛇头坐标

            position[head].x = x;

            position[head].y = y;

            show_game();

            gameover = 1;

            score += grade*20;  //加分

            setpoint();   //产生米

        }

        else
        { // 不吃米

            s[position[tail].x][position[tail].y]=' ';//将蛇尾置空

            tail= (tail+1) % ( (N-2) * (N-2) );//更新蛇尾坐标

            s[position[head].x][position[head].y]='*';  //将蛇头更为蛇身

            head= (head+1) % ( (N-2) * (N-2) );

            position[head].x = x;

            position[head].y = y;

            s[position[head].x][position[head].y]='#'; //更新蛇头

            gameover = 1;

        }
    return gameover;

}
void snake_main()
{
    char ctn = 'y';

    int nodead;

    cout<<"\n\n\n\n\n\t\t\t 欢迎进入贪吃蛇游戏!"<<endl;//欢迎界面;

    cout<<"\n\n\n\t\t\t 按任意键马上开始。。。"<<endl;//准备开始;;

    getch();

    while( ctn=='y' )
    {
        system("cls"); // 清屏

        snake_map snake;

        snake.initialize();

        cout << "\n\n请输入数字选择游戏等级：" << endl;

        cout << "\n\n\n\t\t\t1.等级一：速度 1000 \n\n\t\t\t2.等级二：速度 800 \n\n\t\t\t3.等级三：速度 600 ";

        cout << "\n\n\t\t\t4.等级四：速度 400 \n\n\t\t\t5.等级五：速度 200 \n\n\t\t\t6.等级六：速度 100 \n\n\t\t\t7.自动升级模式" << endl;

        snake.getgrade();//获取等级

        for(int i=1;i<=4;i++)
        {
            position[i].initialize(i);//初始化坐标
        }

        snake.setpoint();  // 产生第一个米

        do
        {
            snake.show_game();

            nodead = snake.updata_game();

        }while(nodead);

        system("cls"); //清屏



        cout << "\n\n\n\t\t\t\tGameover！\n\n"<<endl;

        snake.display();//输出等级/得分情况

        cout << "\n\n\n\t\t    是否选择继续游戏？输入 y 继续，n 退出" << endl;

        cin >> ctn;

    }

    return;
}


class Bullet;
class Tank;
class E_Bullet;
class Boss;
bool wined = false;
struct pos//坐标类
{
 int a;
 int b;
};
class E_Bullet//敌人打出的子弹
{
public:
 clock_t d;
 int x;
 int y;
 bool on = false;
 pos show()//画出新的位置
 {
 setfillcolor(RGB(255, 180, 20));
 fillrectangle(x - 5, y - 5, x + 5, y + 5);
 return pos{ x,y };
 }
 pos del()//覆盖原来的位置
 {
 setfillcolor(0);
 setlinecolor(0);
 fillrectangle(x - 5, y - 5, x + 5, y + 5);
 rectangle(x - 5, y - 5, x + 5, y + 5);
 return pos{ x,y };
 }
 pos move()//左移
 {
 x -= 3;
 return pos{ x,y };
 }
};
class Bullet//玩家打出的子弹，同上
{
public:
 clock_t d;
 int x;
 int y;
 bool on = false;
 pos show()
 {
 setfillcolor(RGB(150, 180, 210));
 fillrectangle(x - 5, y - 5, x + 5, y + 5);
 return pos{ x,y };
 }
 pos del()
 {
 setfillcolor(0);
 setlinecolor(0);
 fillrectangle(x - 5, y - 5, x + 5, y + 5);
 rectangle(x - 5, y - 5, x + 5, y + 5);
 return pos{ x,y };
 }
 pos move()//右移
 {
 x += 3;
 return pos{ x,y };
 }
};
class Boss//敌人
{
public:
 bool hurting = false;
 clock_t d_hurt;
 COLORREF clr = RGB(0, 130, 125);
 int x;
 int y;
 int hp = 100;//生命
 clock_t d;//判断举例上一次执行某一函数过了多久
 clock_t att_d;
 bool angle = false;//方向
 pos show()
 {
 setfillcolor(clr);
 fillrectangle(x - 20, y - 40, x + 20, y + 40);
 return pos{ x,y };
 }
 pos del()
 {
 setfillcolor(0);
 setlinecolor(0);
 rectangle(x - 20, y - 40, x + 20, y + 40);
 fillrectangle(x - 20, y - 40, x + 20, y + 40);
 return pos{ x,y };
 }
 void fire(E_Bullet& but)//攻击
 {
 but.on = true;//放置一个子弹
 but.x = x - 20;
 but.y = y;
 but.d = clock();
 }
 void move()//上上下下得移动
 {
 if (angle == true)
 y -= 5;
 if (angle == false)
 y += 5;
 if (y >= 440)
 angle = true;
 if (y <= 40)
 angle = false;
 }
 void hurt()//受伤
 {
 hp -= 4;
 d_hurt = clock();
 setfillcolor(0);
 setlinecolor(WHITE);
 fillrectangle(160, 485, 560, 510);//更新血条
 rectangle(160, 485, 160 + hp * 4, 510);
 setfillcolor(RGB(230, 0, 1));
 setlinecolor(RGB(255, 255, 255));
 fillrectangle(160, 485, 160 + hp * 4, 510);
 rectangle(160, 485, 160 + hp * 4, 510);
 hurting = true;
 if (hp <= 0)//死亡
 {
 wined = true;
 }
 }
};
class Tank//玩家类，同上
{
public:
 bool hurting = false;
 int hp = 100;
 int x;
 COLORREF clr = RGB(150, 180, 210);
 int y;
 clock_t d_hurt;
 Tank() {}
 Tank(int _x, int _y) { x = _x; y = _y; }
 Tank operator=(pos p) { x = p.a; y = p.a; }
 pos show()
 {
 setfillcolor(clr);
 fillrectangle(x - 25, y - 25, x + 25, y + 25);
 setfillcolor(RGB(100, 200, 180));
 fillrectangle(x, y + 5, x + 40, y - 5);
 return pos{ x,y };
 }
 pos del()
 {
 setfillcolor(0);
 setlinecolor(0);
 fillrectangle(x - 25, y - 25, x + 25, y + 25);
 rectangle(x - 25, y - 25, x + 25, y + 25);
 fillrectangle(x, y + 5, x + 40, y - 5);
 rectangle(x, y + 5, x + 40, y - 5);
 return pos{ x,y };
 }
 void fire(Bullet& but)
 {
 but.on = true;
 but.x = x + 45;
 but.y = y;
 but.d = clock();
 but.show();
 }
 void hurt()
 {
 hp -= 2;
 d_hurt = clock();
 setfillcolor(0);
 setlinecolor(WHITE);
 fillrectangle(160, 515, 560, 540);
 rectangle(160, 515, 560, 540);
 rectangle(160, 515, 160 + hp * 4, 540);
 setfillcolor(RGB(0, 255, 1));
 setlinecolor(RGB(255, 255, 255));
 fillrectangle(160, 515, 160 + hp * 4, 540);
 rectangle(160, 515, 160 + hp * 4, 540);
 hurting = true;
 if (hp <= 0)
 dead = true;
 }
};
#define BT_MAX 8
void shoot_main()
{
 initgraph(640, 550, 4);//初始化屏幕
 settextcolor(RGB(0, 254, 0));
 settextstyle(20, 0, _T("黑体"));
 outtextxy(10, 10, _T("BOSS入侵了地球!拿起你的激光炮保护地球吧!"));
 settextstyle(35, 0, _T("黑体"));
 outtextxy(150, 200, _T("W,S移动,K攻击"));
 Sleep(3000);
 setlinecolor(0);
 setfillcolor(0);
 rectangle(0, 0, 640, 550);
 fillrectangle(0, 0, 640, 550);
 setlinecolor(RGB(255, 255, 255));
 setfillcolor(RGB(255, 255, 255));
 clock_t delay = clock();//玩家移动的延时
 clock_t d_f = clock();//玩家开火的延时
 line(0, 481, 640, 481);//分割画面与血条
 Bullet bt[BT_MAX];//玩家的子弹
 Tank tk(30, 30);//玩家
 Boss bo;//敌人
 bo.x = 580;
 bo.y = 240;
 E_Bullet ebt[BT_MAX];//敌人的子弹
 bo.d = clock();//初始化延时
 bo.att_d = clock();
 tk.show();
 settextstyle(20, 0, _T("黑体"));
 outtextxy(10, 485, _T("BOSS的生命值:"));
 setfillcolor(RGB(230, 0, 1));
 fillrectangle(160, 485, 560, 510);//敌人血条
 outtextxy(10, 520, _T("玩家的生命值:"));
 setfillcolor(RGB(0, 255, 1));
 fillrectangle(160, 515, 560, 540);//玩家血条
 while (1)//主循环
 {
 if (wined || dead)//玩家死了或者敌人死了
 break;
 if (GetAsyncKeyState('W') & 0x8000)//玩家移动
 {
 if (tk.y > 28 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y -= 3; tk.show(); delay = clock();
 }
 }
 if (GetAsyncKeyState('w') & 0x8000)//玩家移动
 {
 if (tk.y > 28 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y -= 3; tk.show(); delay = clock();
 }
 }
 if (GetAsyncKeyState('k') & 0x8000)//玩家开火
 {
 for (int i = 0; i < BT_MAX; i++)
 {
 if (bt[i].on == false && (clock() - d_f) > 800)
 {
  bt[i].on = true;
  tk.fire(bt[i]);
  d_f = clock();
  break;
 }
 }
 }
 if (GetAsyncKeyState('K') & 0x8000)//玩家开火
 {
 for (int i = 0; i < BT_MAX; i++)
 {
 if (bt[i].on == false && (clock() - d_f) > 800)
 {
  tk.fire(bt[i]);
  d_f = clock();
  break;
 }
 }
 }
 if (GetAsyncKeyState('S') & 0x8000)//玩家移动
 {
 if (tk.y < 452 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y += 3; tk.show(); delay = clock();
 }
 }
 if (GetAsyncKeyState('s') & 0x8000)//玩家移动
 if (tk.y < 452 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y += 3; tk.show(); delay = clock();
 }
 for (int i = 0; i < BT_MAX; i++)//遍历子弹，使子弹刷新
 {
 if (bt[i].on == true && (clock() - bt[i].d) > 20)
 {
 bt[i].del();
 bt[i].move();
 bt[i].show();
 bt[i].d = clock();
 if (bt[i].x >= 635)
  bt[i].on = false, bt[i].del();//到达了屏幕最右端
 if ((bt[i].x + 5 >= bo.x - 20 && bt[i].x - 5 <= bo.x + 20) && (bt[i].y - 5 < bo.y + 40 && bt[i].y + 5 > bo.y - 40))
  //击中敌人
  bt[i].on = false, bo.hurt(), bt[i].del();
 }
 }
 if (clock() - bo.att_d > 700)//敌人自动开火
 {
 for (int i = 0; i < BT_MAX; i++)
 {
 if (ebt[i].on == false)
 {
  bo.fire(ebt[i]); break;
 }
 }
 bo.att_d = clock();
 }
 for (int i = 0; i < BT_MAX; i++)//敌人子弹刷新，同上
 {
 if (ebt[i].on == true && (clock() - ebt[i].d > 20))
 {
 ebt[i].del();
 ebt[i].move();
 ebt[i].show();
 ebt[i].d = clock();
 if (ebt[i].x < 5)
  ebt[i].del(), ebt[i].on = false;
 if (ebt[i].x - 5 < tk.x + 25 && ebt[i].x + 5 > tk.x - 25 && ebt[i].y - 5 < tk.y + 25 && ebt[i].y + 5 > tk.y - 25)
 {
  ebt[i].on = false, tk.hurt(), ebt[i].del();
 }
 }
 }
 if (tk.hurting == true)//玩家受伤闪烁0.1秒
 if (clock() - tk.d_hurt > 100)
 {
 tk.clr = RGB(150, 180, 210), tk.show(), tk.hurting = false;
 }
 else
 tk.clr = RGB(255, 0, 0), tk.show();
 if (bo.hurting == true)//敌人受伤闪烁0.1秒
 if (clock() - bo.d_hurt > 100)
 {
 bo.clr = RGB(0, 130, 125), bo.show(), bo.hurting = false;
 }
 else
 bo.clr = RGB(0, 255, 0), bo.show();
 if (clock() - bo.d > 50)//敌人移动延时;
 bo.del(), bo.move(), bo.show(), bo.d = clock();
 }
 if (wined)//胜负已分
 {
 settextcolor(RGB(0, 254, 0));
 settextstyle(35, 0, _T("黑体"));
 outtextxy(150, 200, _T("你打败了boss!你赢了！！"));
 }
 else
 {
 settextcolor(RGB(254, 0, 0));
 settextstyle(35, 0, _T("黑体"));
 outtextxy(140, 200, _T("你被boss打败了！"));
 }
 Sleep(5000);
 closegraph();
 return;
}
int shen=0;
int ui=0;
int sheng=1;
void SetColorAndBackground(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void Bling() {
	for(int i=0; i<=5; i++) {
		system("color 1A");
		Sleep(20);
		if(sheng==1) if(sheng==1) Beep(1200,50);
		system("color 2B");
		Sleep(20);
		system("color 3C");
		Sleep(20);
		system("color 4D");
		Sleep(20);
		if(sheng==1) Beep(1200,50);
		system("color 5D");
		Sleep(20);
		system("color 6E");
		Sleep(20);
		system("color 7F");
		Sleep(20);
		if(sheng==1) Beep(1200,50);
	}
}
void Start() {
	if(sheng==1) Beep(3200,50);
	cout<<" 救出公主努力通关吧！                                             \n";
	Sleep(50);
	cout<<"                                                              \n";
	Sleep(50);
	cout<<" 输入“1 ”下一页                           \n\n";
	Sleep(50);
A:
	char y=_getch();
	if(y=='1') return;
	else goto A;
}
void Start2() {
	system("color 8E");
	system("cls");
	if(sheng==1) Beep(3200,50);
	cout<<" Gamesbox精品游戏,版权(c) Copyright Linhonghan\n";
	Sleep(50);
	cout<<" 努力通关吧！                                   \n";
	Sleep(50);
	cout<<"                                                \n";
	Sleep(50);
	cout<<" 输入“1 ”开始游戏                    \n\n";
	Sleep(50);
A:
	char y=_getch();
	if(y=='1') return;
	else goto A;
}
int boss1=0,boss2=0;
struct Player { //玩家结构体，并初始化player
	char name[21];
	int attack;
	int defense;
	int health;
	long int max_health;
	int level;
	int exp;
	int range_exp;
	long int max_exp;
} player= {"勇者",100,80,200,200,1,0,0,100};
struct Enemy {//怪的结构体,并初始化各种怪
	char name[20];
	char wupin[20];
	int attack;
	int defense;
	int health;
	int money;
	long int exp;
	int wupin_sign;
	int wupinpro;
	int double_attack;
	int miss;
}
//怪，拿格伦石人举例
// 怪变量  怪名     掉落的装备 攻   防  血  金币 经验 掉落装备编号 掉落概率 真伤（被防御后的破甲伤害）   不能改
//  gl= {"格伦石人","石铠甲",  30, 150,1000,500, 250,      11,       7,        1,                         0},
gl= {"格伦石人","石铠甲",30,150,1000,500,250,11,7,1,0},
zhizhu= {"洞穴蜘蛛","蜘蛛毒剑",140,20,250,400,200,12,5,1,0},
ymr= {"野蛮人","粗制石剑",20,20,150,100,50,13,5,1,0},
nz= {"牛仔","战斗马甲",80,20,250,500,250,14,10,1,0},
strongman= {"森林巨人","传说圣甲",50,50,580,200,100,1,5,1,0},
witch= {"兽人","重甲",35,55,250,50,50,2,4,1,1},
xiyi= {"毒蜴","鳞片",20,25,80,30,35,3,8,2,2},
huolong= {"喷火龙","巨龙晶石",40*5,50*5,200*5,200*5,100*5,4,4,2,0},
lion= {"皇家士兵","尚方宝剑",100,30,380,200,100,5,5,1,0},
horse= {"独眼巨人","碧血战锤",50,22,360,50,50,6,5,1,1},
bee= {"剑客","西洋剑",27,11,60,30,35,7,5,2,2},
bossno1= {"凋零女巫","凋零通行证",1400,500,15000,10000,5000,15,10,1,0},
dljs= {"凋零巨兽","凋零之心",1200,700,20000,10000,500,10,7,1,0},
pika= {"皮卡超人","\0",300,40*8,1000,2000,1000,0,0,1,0},
dapika= {"雷霆皮卡","雷霆之刃",350,40*10,1500,3000,2000,8,6,6,0},
cl= {"熔岩飞龙","\0",450,50*10,2000,3500,2500,0,0,1,0},
jl= {"裂凯金龙","龙鳞",500,40*20,5000,8000,4500,9,6,6,1},
gst= {"凋零共生体","命令之书",1800,65*10,15000,20000,1000,16,10,1,0},
dlkl= {"凋零骷髅","凋零之骨",3000,30*10,12000,20000,1000,0,0,1,0},
dlfb= {".+*凋零风暴*+.","\0",9000,1500,49000,0,500000,17,10,1,0},
guai= {"\0","\0",0,0,0,0,0,0,0,0,0};
struct Place {
	int bar,hotel,forest1,forest2,forest3,grass1,grass2,grass3,te1,te2,te3,te4;
} place= {1,2,3,4,5,6,7,8,9,10,11,12};
int max_exp=0;
int htsr;
int he=0;
int choose_number=0,strongman_arm=0,battle=0,place_sign=10;
int s=0;
int cao=3,jijiubao=3,baiyao=3,superbaiyao=3,miansi=1,boom=3,dubiao=2,yuanzidan=1;
int fang=0,fang1=10,fang1n=0,fang2=120,fang2n=0,fang3=40,fang3n=0,fang4=100,fang4n=0,fang5=600,fang5n=0,fang6=150,fang6n=0,fang7=60,fang7n=0,fang4X=550,fang4Xn=0,mfang=1000,mfangn=0;
int gong=0,gong1=10,gong1n=0,gong2=20,gong2n=0,gong3=45,gong3n=0,gong4=100,gong4n=0,gong5=300,gong5n=0,gong6=150,gong6n=0,gong7=45,gong7n=0,gong4X=500,gong4Xn=0,mgong=1000,mgongn=0;
int jingyancao=0,jingyanbao=0,jingyanshi=0,htmmcs=5;
int diaolingxinhave=0,diaolingxin=0,mingshu=0,zhadan=0;
char gongname[20]="无",fangname[20]="无";
char proof;
int lp=0,ll=0;
void AddWupin(int);
int AttackResult();
void BattleAct();  //      ____
void ChooseWupin();  //   /___/|
void DisplayState();  //  |   |/
void OrdinaryAct();     //▔▔
int SuiJi();
int SuiJi100();
void WhetherLevelUp();
void SlowDisplay(char *);

void rain_main() {
	srand((unsigned int)time(NULL)); // 初始化随机数种子
		initgraph(WIDTH, HEIGHT);
		InitRain();
		DWORD t1, t2;
		t1 = GetTickCount();
		t2 = t1;
		while (1)
		{
			BeginBatchDraw(); // 双缓冲机制
			DrawRain();
			ChangeCh();
			if (t2 - t1 > 20)
			{
				MoveRain();
				t1 = t2;
			}
			t2 = GetTickCount();
			EndBatchDraw();
		}
	getchar();
	closegraph();
	return;
}

void sendAltEnter() {
    // 模拟按下Alt键
    keybd_event(VK_MENU, 0, 0, 0);
    // 模拟按下Enter键
    keybd_event(VK_RETURN, 0, 0, 0);
    // 模拟松开Enter键
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    // 模拟松开Alt键
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}

int main() {
    int game_mode = 1;
    system("title Gamesbox");
    system("cls");
    sendAltEnter();
    
    if (sheng == 1) Beep(1200, 100);
    MessageBox(NULL, "欢迎来到Gamesbox！", "游戏开始提示", MB_OK);
    main1:
    printf("(c) Copyright Linhonghan\nGamebox主页\n[1] 射击游戏\n[2] 探险游戏\n[3] 贪吃蛇\n[4] 三国杀\n[5] 魔法世界\n[6] 3d迷宫\n[7] 黑客攻防\n");
    printf("[8] 中国象棋(双人)\n[9] 阵地保卫战\n[10]数字塔防\n[11]代码雨\n\n");
    
    cin >> game_mode;
    if (game_mode == 1) {
        shoot_main();
    } else if (game_mode == 2) {
        int i = 0, j = 0, k = 0;
        Start();
        Bling();
        Start2();
        Bling();
        int kaishi;
        char player_name[21];
        Sleep(300);
        if (sheng == 1) Beep(1200, 100);
        system("cls");
        printf("这里是游戏世界!\n克契晋赫苟阿斯弗国的黎哈漓嘉茜丽·卡洛斯费尔·阿诺斯夫斯基·巴克锕蒂娜公主被神秘人绑架了!\n\n\n 伟大滴勇者啊~拿起你的武器,营救公主!\n\n\n输入你的名字: (20个字符)\n\n\n");
        system("color 8E");
        scanf("%s", player_name);
        Sleep(300);
        strncpy(player.name, player_name, 20);
        if (strcmp(player.name, "666") == 0) {
            if (sheng == 1) Beep(5200, 300);
            printf("\n\n\n封印多年的官方血统啊!你终于觉醒了!\n\n\n666，你成为了天选之人，请你救出公主吧！\n\n\n");
            player.attack = 99999;
            player.defense = 99999;
            player.health = 999999;
            player.max_health = 999999;
            system("pause");
        }
        getchar();
        OrdinaryAct();
    } else if (game_mode == 3) {
        snake_main();
    } else if (game_mode == 4) {
        sgs_main();
    } else if (game_mode == 5) {
        harrypotter_main();
    } else if (game_mode == 6) {
        mg_main();
    } else if (game_mode == 7) {
    	hk_main();
    } else if (game_mode == 8) {
        Cchess_main();
    } else if (game_mode == 9) {
        fight_main();
    } else if (game_mode == 10) {
        num_main();
    } else if (game_mode == 11) {
        rain_main();
    } else {
    	printf("输入错误!");
    	goto main1;
	}
	system("cls");
    goto main1;
    return 0;
}


int SuiJi() {
	srand((unsigned)time(NULL));
	return rand()%10;
}
int SuiJi100() {
	srand((unsigned)time(NULL));
	return rand()%100;
}
void ChooseWupin() { //选择物品 并使用
	if(sheng==1) Beep(1200,100);
	printf("物品: 1,止血草%d个 2,急救包%d个 3,云南白药%d个 4,超级云南白药%d个 5,手雷%d个 6,毒标%d个 7,手抛式原子弹%d个 8,经验草%d个 9,经验包%d个 10,经验石%d个 11,巨龙晶石%d个 12,免死金牌%d个 13,凋零之心%d个 14,毁灭炸弹%d个 0,返回\n\n\n",cao,jijiubao,baiyao,superbaiyao,boom,dubiao,yuanzidan,jingyancao,jingyanbao,jingyanshi,strongman_arm,miansi,diaolingxin,zhadan);
	system("color 8A");
	switch(scanf("%d",&choose_number),choose_number) {
		case 1:
			if(cao>0) {
				printf("使用止血草,HP增加120\n\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				cao--;
				if(player.health+120>player.max_health)player.health=player.max_health;
				else player.health+=120;
			} else printf("没有止血草了\n\n\n");
			system("color 8A");
			break;
		case 2:
			if(jijiubao>0) {
				printf("使用急救包,HP增加180\n\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				jijiubao--;
				if(player.health+180>player.max_health)player.health=player.max_health;
				else player.health+=180;
			} else printf("没有急救包了\n\n\n");
			system("color 8A");
			break;
		case 3:
			if(baiyao>0) {
				printf("使用云南白药,HP增加240\nz\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				baiyao--;
				if(player.health+240>player.max_health)player.health=player.max_health;
				else player.health+=240;
			} else printf("没有云南白药了\n\n\n");
			system("color 8A");
			break;
		case 4:
			if(superbaiyao>0) {
				printf("使用超级云南白药,HP增加400\n\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				superbaiyao--;
				if(player.health+400>player.max_health)player.health=player.max_health;
				else player.health+=400;
			} else printf("没有超级云南白药了\n\n\n");
			system("color 8A");
			break;
		case 5:
			if(battle) { //在战斗中(battle=1),否则(battle=0)不能使用攻击性物品
				if(boom>0) {
					printf("使用手雷,敌人HP减少100\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					boom--;
					guai.health-=100;
					AttackResult();
				}
			} else printf("非战斗状态,不能使用手雷!\n\n\n");
			system("color 84");
			break;
		case 6:
			if(battle) { //在战斗中(battle=1),否则(battle=0)不能使用攻击性物品
				if(dubiao>0) {
					printf("使用毒标,敌人HP减少200\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					dubiao--;
					guai.health-=200;
					AttackResult();
				}
			} else printf("非战斗状态,不能使用毒标!\n\n\n");
			system("color 84");
			break;
		case 7:
			if(battle) { //在战斗中(battle=1),否则(battle=0)不能使用攻击性物品
				if(yuanzidan>0) {
					printf("使用手抛式原子弹,敌人HP减少1500\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					yuanzidan--;
					guai.health-=1500;
					AttackResult();
				}
			} else printf("非战斗状态,不能使用手抛式原子弹!\n\n\n");
			system("color 84");
			break;
		case 8:
			if(jingyancao>0 && player.level<200) {
				printf("使用经验草,等级增加3级\n\n\n");
				system("color 8E");
				if(sheng==1) Beep(1200,100);
				jingyancao--;
				player.max_health=player.max_health+60;
				player.attack+=9;
				player.defense+=6;
				player.level+=3;
				player.health=player.max_health;
				printf("等级：%d\n",player.level);
				system("color 8E");
				if(sheng==1) Beep(1200,100);
			} else    if(jingyancao<1) {
				printf("没有经验草了\n\n\n");
				system("color 8E");
			} else printf("等级超过200级,修为太高，无法使用。\n\n\n");
			system("color 8E");
			break;
		case 9:
			if(jingyanbao>0 && player.level<200) {
				if(player.level>197&&player.level<200) {
					int sheng;
					sheng=100-player.level;
					player.level+=sheng;
					jingyanbao--;
					player.max_health=player.max_health+sheng*20;
					player.attack+=sheng*3;
					player.defense+=sheng*2;
					player.health=player.max_health;
					printf("使用经验包,等级增加%d级",sheng);
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					printf("等级：%d\n",player.level);
					system("color 8E");
				} else {
					printf("使用经验包,等级增加5级\n\n\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					jingyanbao--;
					player.max_health=player.max_health+100;
					player.attack+=15;
					player.defense+=10;
					player.level+=5;
					player.health=player.max_health;
					printf("等级：%d\n",player.level);
					system("color 8E");
				}
			} else if(jingyanbao<1) {
				printf("没有经验包了");
				system("color 8E");
			} else printf("等级超过200级,修为太高，无法使用。\n\n\n");
			system("color 8E");
			break;
		case 10:
			if(jingyanshi>0 && player.level<200) {
				if(player.level>192&&player.level<200) {
					int sheng;
					sheng=100-player.level;
					player.level+=sheng;
					player.max_health+=sheng*20;
					player.attack+=sheng*3;
					player.defense+=sheng*2;
					player.health=player.max_health;
					printf("使用经验石,等级增加%d级\n",sheng);
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					printf("等级：%d\n",player.level);
					system("color 8E");
				} else {
					printf("使用经验石,等级增加10级\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					jingyanshi--;
					player.max_health=player.max_health+200;
					player.attack+=30;
					player.defense+=20;
					player.level+=10;
					player.health=player.max_health;
				}
			} else if(jingyanshi<1) {
				printf("没有经验石了\n\n\n");
				system("color 8E");
			} else printf("等级超过200级,修为太高，无法使用。\n\n\n");
			system("color 8E");
			break;
		case 11:
			if(strongman_arm>0 && player.level<500) {
				if(player.level>482&&player.level<500) {
					int sheng;
					sheng=500-player.level;
					player.level+=sheng;
					player.max_health=player.max_health+sheng*20;
					player.attack+=sheng*3;
					player.defense+=sheng*2;
					player.health=player.max_health;
					printf("使用巨龙晶石,等级增加%d级",sheng);
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					printf("等级：%d\n",player.level);
					system("color 8E");
				} else {
					printf("使用巨龙晶石,等级增加20级\n\n\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					strongman_arm--;
					player.max_health=player.max_health+400;
					player.attack+=60;
					player.defense+=40;
					player.health=player.max_health;
					player.level+=20;
					printf("等级：%d\n",player.level);
					system("color 8E");
				}
			} else if(strongman_arm<1) {
				printf("没有巨龙晶石了。\n\n\n");
				system("color 8E");
				if(sheng==1) Beep(1200,100);
			} else printf("等级超过500级,修为太高，无法使用。\n\n\n");
			system("color 8E");
			break;
		case 12:
			if(miansi>0) {
				if(sheng==1) Beep(1200,100);
				cout<<"使";
				Sleep(50);
				cout<<"用";
				Sleep(50);
				cout<<"免";
				Sleep(50);
				cout<<"死";
				Sleep(50);
				cout<<"金";
				Sleep(50);
				cout<<"牌";
				Sleep(50);
				cout<<"HP";
				Sleep(50);
				cout<<"满";
				Sleep(50);
				system("color 8b");
				miansi--;
				if(player.health+999999>player.max_health)player.health=player.max_health;
				else player.health+=999999;
			} else printf("没有免死金牌了\n\n\n");
			system("color 8b");
			break;
			break;
		case 13:
			if(diaolingxin>0) {
				printf("使用凋零之心\nHP上限+100  攻击+100\n\n\n");
				system("color 8b");
				if(sheng==1) Beep(1200,100);
				diaolingxin--;
				player.max_health+=100;
				player.attack+=100;
			} else printf("没有凋零之心了\n\n\n");
			system("color 8b");
			break;
		case 14:
			if(battle) { //在战斗中(battle=1),否则(battle=0)不能使用攻击性物品
				if(zhadan>0) {
					printf("使用毁灭炸弹,敌人HP减少15000\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					zhadan--;
					guai.health-=15000;
					AttackResult();
				}
			}
		case 0:
			break;
		default:
			printf("ChooseWupin error!\n\n\n");
	}
}
int AttackResult() { //攻击结果:判断是否获胜 是否获得物品 和 是否升级
	if(guai.health<=0) {
		printf("战斗胜利!获得金币%d,经验%d\n\n\n",guai.money,guai.exp);
		system("color 8C");
		if(sheng==1) Beep(1200,100);
		player.exp+=guai.exp;
		player.range_exp+=guai.exp;
		money+=guai.money;
		s=SuiJi();
		if(s<guai.wupinpro) {
			cout<<"从";
			Sleep(100);
			if(sheng==1) Beep(1200,100);
			cout<<"敌";
			Sleep(100);
			cout<<"人";
			Sleep(100);
			cout<<"尸";
			Sleep(100);
			cout<<"骸";
			Sleep(100);
			cout<<"中";
			Sleep(100);
			cout<<"发";
			Sleep(100);
			cout<<"现";
			Sleep(100);
			system("color 8C");
			printf("%s\n\n\n",guai.wupin);
			AddWupin(guai.wupin_sign);
		}
		WhetherLevelUp();
		if(strcmp(guai.name,".+*凋零风暴*+.")==0) {
			printf("结束了\n\n");
			if(sheng==1) Beep(1200,100);
			system("color 8C");
		}
		return 1; //攻击有结果了返回1,否则返回0,用于判断是否继续做战斗行为
	} else {
		int s=SuiJi();
 
		if((guai.attack+s-player.defense/3)<0) {
			player.health-=1;
			printf("%s反击,你的HP减少了 1\n\n",guai.name);
			system("color 8C");
		} else {
			player.health-=guai.attack+s-player.defense/3;
			printf("%s反击,你的HP减少了%d\n\n",guai.name,guai.attack+s-player.defense/3);
			system("color 8C");
		}
		if(player.health<0) {
			battle=0;
			printf("%s战死!金币掉落%d\n\n\n",player.name,player.level*500);
			system("color CC");
			money-=player.level*500;
			player.health=player.max_health/5;
			OrdinaryAct();//
			return 1;
		}
	}
	return 0;
}
void AddWupin(int wupin_sign) {
 
	switch(wupin_sign) {
		case 1:
			fang4n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 2:
			fang3n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 3:
			lp++;
			if(sheng==1) Beep(1200,100);
			break;
		case 4:
			strongman_arm++;
			if(sheng==1) Beep(1200,100);
			break;
		case 5:
			gong4n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 6:
			gong3n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 7:
			gong2n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 8:
			gong5n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 9:
			ll++;
			if(sheng==1) Beep(1200,100);
			break;
		case 10:
			diaolingxin++;
			if(sheng==1) Beep(1200,100);
			break;
		case 11:
			fang6n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 12:
			gong6n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 13:
			gong7n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 14:
			fang7n++;
			if(sheng==1) Beep(1200,100);
			break;
		case 15:
			diaolingxinhave++;
			if(sheng==1) Beep(1200,100);
			boss1++;
			break;
		case 16:
			mingshu++;
			if(sheng==1) Beep(1200,100);
			break;
		case 17:
			boss2++;
			if(sheng==1) Beep(1200,100);
			break;
		default:
			printf("AddWupin error\n\n\n");
	}
 
}
void WhetherLevelUp() {
	int i=0,j=0;
	int l1=player.range_exp/150;
	int l2=player.range_exp/300;
	int l3=player.range_exp/600;
	if(player.level<=15&&l1>0) { //15级以下,经验足够 都满足则升级
		if(l1==1) {
			printf("%s",player.name);
			printf(" 升级!\n\n\n攻击力+3, 防御力+2, HP上限+20\n\n\n");
			system("color 8E");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3;
			player.defense+=2;
			player.max_health+=20;
			player.health=player.max_health;
			player.level++;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=100;
		} else {
			printf("好厉害!连升%d级!",l1);
			system("color 8E");
			printf("攻击力+%d, 防御力+%d, HP上限+%d\n\n\n",3*l1,2*l1,20*l1);
			system("color 8E");
			player.exp=(player.exp+guai.exp) || player.exp-((player.exp+guai.exp) || player.exp)%100;
			player.attack+=3*l1;
			player.defense+=2*l1;
			player.max_health+=20*l1;
			player.health=player.max_health;
			player.level+=l1;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=100*l1;
		}
	} else if(player.level<=40&&l2>0) {
		if(l2==1) {
			printf("%s",player.name);
			printf(" 升级!\n\n\n攻击力+3, 防御力+2, HP上限+20\n\n\n");
			system("color 8E");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3;
			player.defense+=2;
			player.max_health+=20;
			player.health=player.max_health;
			player.level++;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=300;
		} else {
			printf("好厉害!连升%d级!",l2);
			system("color 8E");
			printf("攻击力+%d, 防御力+%d, HP上限+%d\n\n\n",3*l2,2*l2,20*l2);
			system("color 8E");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3*l2;
			player.defense+=2*l2;
			player.max_health+=20*l2;
			player.health=player.max_health;
			player.level+=l2;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=300*l2;
		}
	} else if(l3>0) {
		if(l3==1) {
			printf("%s",player.name);
			printf(" 升级!\n\n\n攻击力+3, 防御力+2, HP上限+20\n\n\n");
			system("color 8E");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3;
			player.defense+=2;
			player.max_health+=20;
			player.health=player.max_health;
			player.level++;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=600;
		} else {
			printf("好厉害!连升%d级!",l3);
			printf("攻击力+%d, 防御力+%d, HP上限+%d\n\n\n",3*l3,2*l3,20*l3);
			system("color 8E");
			player.exp=player.exp+guai.exp-(player.exp+guai.exp)%100;
			player.attack+=3*l3;
			player.defense+=2*l3;
			player.max_health+=20*l3;
			player.health=player.max_health;
			player.level+=l3;
			player.range_exp=0;
			player.exp=player.max_exp;
			player.max_exp+=600*l3;
		}
	}
}
void OrdinaryAct() { //正常行为菜单
	while(1) {
// \(1000);
// system("cls");
		if(ui==0) {
			system("cls");
			puts("=============================================================================");
			system("color 8E");
			printf("要做什么?\n\n  1,移动     2,道具     3,对话  4,查看状态 \n\n  5,装备  6,关于游戏    7,后台   8,合成台 \n\n  9,设置  10,打开背包 \n\n");
			system("color 8E");
			if(sheng==1) Beep(1200,100);
			puts("=============================================================================");
			system("color 8E");
		} else {
			system("cls");
			puts("=============================================================================");
			system("color 8E");
			printf("要做什么?\n\n1,移动 2,道具 3,对话 4,查看状态 5,装备 6,关于游戏 7,后台 8,合成台 9,设置 10,背包\n\n\n\n");
			system("color 8E");
			puts("=============================================================================");
			system("color 8E");
		}
		switch(scanf("%d",&choose_number),choose_number) {
			case 1: //显示移动菜单
				printf("要去哪里?\n\n\n");
				system("color 8E");
				cout<<"1,小郑子酒吧  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"2,诺亚方舟酒店  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"3,北朝商会  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"4,红玉拍卖行  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"5,冒险荒野\n\n\n";
				Sleep(150);
				system("color 8E");
				if(sheng==1) Beep(1200,100);
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						place_sign=place.bar; //记录目前位置-酒吧
						break;
					case 2:
						place_sign=place.hotel; //进入旅店
						printf("金币：%d",money);
						system("color 8E");
						printf("要开房吗? 200个金币 \n 1,是 0,否\n\n\n");
						system("color 8E");
						if(sheng==1) Beep(1200,100);
						choose_number=1;
						switch(scanf("%d",&choose_number),choose_number) {
							case 1:
								if(money-200<=0) { //判断钱是否够
									printf("Sorry,你的钱不够~\n\n\n");
									system("color 8E");
									printf("金币：%d",money);
									system("color 8E");
								} else {
									printf("好好休息\nHP满\n第二天了\n\n");
									system("color 8E");
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									system("color 8E");
									money-=200; //花费200住店费
									player.health=player.max_health; //体力满
								}
								break;
							case 0:
								printf("下次再来!\n\n\n");
								system("color 8E");
								break;
							default:
								printf("hotel talk error!\n\n\n");
								system("color 8E");
						}
						place_sign=0;
						break;
					case 3:
						int yongju,gong,fang;
						printf("请问您要购买什么类型的物品？\n\n\n");
						system("color 8E");
						if(sheng==1) Beep(1200,100);
						cout<<"1,攻击装备 ";
						Sleep(50);
						cout<<"2,防御装备 ";
						Sleep(50);
						cout<<"3,一次性伤害武器\n\n\n";
						Sleep(50);
						scanf("%d",&yongju);
						switch(yongju) {
							case 1:
								printf("请问您要购买什么武器?\n\n\n 1,匕首￥300 2，西洋剑￥500 3，碧血战锤￥1000\n\n\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								scanf("%d",&gong);
								switch(gong) {
									case 1:
										if(money>=300) {
											gong1n++;
											money=money-300;
											printf ("匕首+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("匕首:%d个\n",gong1n);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
											break;
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
											break;
										}
									case 2:
										if(money>=500) {
											gong2n++;
											money=money-500;
											printf ("西洋剑+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("西洋剑:%d个\n",gong2n);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
											break;
										} else {
											printf("钱不够!\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("金币：%d\n",money);
											system("color 8E");
											break;
										}
									case 3:
										if(money>=1000) {
											gong3n++;
											money=money-1000;
											printf ("碧血战锤+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("碧血战锤:%d个\n",gong3n);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
											break;
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
											break;
										}
									default:
										printf("对不起，我们只会打造以上武器。");
										system("color 8E");
										break;
 
								}
								break;
							case 2:
								int fang;
								printf("请问您要购买什么防具?\n\n\n 1,布衣￥300 2，鳞甲￥500 3，重甲￥1000\n\n\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								scanf("%d",&fang);
								switch(fang) {
									case 1:
										if(money>=300) {
											fang1n++;
											money=money-300;
											printf ("布衣+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("布衣:%d个\n",fang1n);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										}
 
										break;
									case 2:
										if(money>=500) {
											fang2n++;
											money=money-500;
											printf ("鳞甲+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("鳞甲:%d个\n",fang2n);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d",money);
											system("color 8E");
										}
										break;
									case 3:
										if(money>=1000) {
											fang3n++;
											money=money-1000;
											printf ("重甲+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("重甲:%d个\n",fang3n);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										}
									default:
										printf("对不起，我们只会打造以上防具。");
										system("color 8E");
										break;
 
								}
								printf("金币：%d\n",money);
								system("color 8E");
								break;
							case 3:
								printf("请问您要购买什么一次性伤害武器？\n 1,手雷 2，毒镖 3，手抛式原子弹\n\n\n");
								system("color 8E");
								int yi;
								scanf("%d",&yi);
								switch(yi) {
									case 1:
										if(money>=300 && boom<5) {
											boom++;
											money=money-300;
											printf("手雷+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("手雷：%d\n",boom);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d",money);
											system("color 8E");
										}
										break;
									case 2:
										if(money>=600 && dubiao<9999999) {
											dubiao++;
											money=money-600;
											printf("毒镖+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("毒镖：%d\n",dubiao);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										} else {
											printf("钱不够!\n");
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										}
										break;
									case 3:
										if(money>=1000 && yuanzidan<5) {
											yuanzidan=yuanzidan+1;
											money=money-1000;
											printf("手抛式原子弹+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("手抛式原子弹：%d\n",yuanzidan);
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										} else {
											printf("钱不够!\n\n\n");
											system("color 8E");
											printf("金币：%d\n",money);
											system("color 8E");
										}
 
										break;
								}
						}
						break;
					case 4:
						if(sheng==1) Beep(1200,100);
						printf ("欢迎您光临本拍卖行，请问您要卖什么东西？\n\n");
						system("color 8E");
						printf("攻击装备: 1,匕首:%d个 2,西洋剑:%d个 3,粗制石剑:%n 4,碧血战锤:%d个 5,蜘蛛毒剑:%n个 6,尚方宝剑:%d个 7,皮卡大剑：%d个\n",gong1n,gong2n,gong7n,gong3n,gong6n,gong4n,gong5n);
						system("color 8E");
						printf("防御装备: 8,布衣:%d个 9,鳞甲:%d个 10,战斗马甲:%d个 11,重甲:%d个 12,石铠甲:%d个 13,传说圣甲:%d个 14,金龙铠：%d个 15，巨龙晶石:%d个\n 0,返回\n\n\n",fang1n,fang2n,fang7n,fang3n,fang6n,fang4n,fang5n,strongman_arm);
						system("color 8E");
						int pai,shu,i;
						scanf("%d",&pai);
						system("color 8E");
						switch(pai) {
							case 1:
								printf("请问您要出售几件？");
								system("color 8E");
								scanf("%d",&shu);
								if(gong1n>=shu) {
									gong1n=gong1n-shu;
									money=money+shu*240;
									printf("匕首：%d\n",gong1n);
									system("color 8E");
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									system("color 8E");
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									system("color 8E");
									break;
								}
								break;
							case 2:
								printf("请问您要出售几件？\n");
								system("color 8E");
								scanf("%d",&shu);
								if(gong2n>=shu) {
									gong2n=gong2n-shu;
									money=money+shu*400;
									printf("西洋剑：%d\n",gong2n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 3:
								printf("请问您要出售几件？\n");
								system("color 8E");
								scanf("%d",&shu);
								if(gong7n>=shu) {
									gong7n=gong7n-shu;
									money=money+shu*800;
									printf("粗制石剑：%d\n",gong7n);
									printf("金币：%d\n",money);
									if(sheng==1) Beep(1200,100);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 4:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(gong3n>=shu) {
									gong3n=gong3n-shu;
									money=money+shu*800;
									printf("碧血战锤：%d\n",gong3n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 5:
								printf("请问您要出售几件？\n");
								system("color 8E");
								scanf("%d",&shu);
								if(gong6n>=shu) {
									gong6n=gong6n-shu;
									money=money+shu*1000;
									printf("蜘蛛毒剑：%d\n",gong6n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 6:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(gong4n>=shu) {
									gong4n=gong4n-shu;
									money=money+shu*1500;
									printf("尚方宝剑：%d\n",gong4n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 7:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(gong5n>=shu) {
									gong5n=gong5n-shu;
									money=money+shu*3000;
									printf("皮卡大剑：%d\n",gong5n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 8:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang1n>=shu) {
									fang1n=fang1n-shu;
									money=money+shu*240;
									printf("布衣：%d\n",fang1n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 9:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang2n>=shu) {
									fang2n=fang2n-shu;
									money=money+shu*500;
									printf("鳞甲：%d\n",fang2n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 10:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang7n>=shu) {
									fang7n=fang7n-shu;
									money=money+shu*1000;
									printf("战斗马甲：%d\n",fang7n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 11:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang3n>=shu) {
									fang3n=fang3n-shu;
									money=money+shu*800;
									printf("重甲：%d\n",fang3n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
								break;
							case 12:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang6n>=shu) {
									fang6n=fang6n-shu;
									money=money+shu*2000;
									printf("石凯甲：%d\n",fang6n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 13:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang4n>=shu) {
									fang4n=fang4n-shu;
									money=money+shu*1500;
									printf("传说圣甲：%d\n",fang4n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
 
							case 14:
								printf("请问您要出售几件？\n");
								scanf("%d",&shu);
								if(fang5n>=shu) {
									fang5n=fang5n-shu;
									money=money+shu*3000;
									printf("金龙铠：%d\n",fang5n);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
									break;
								} else {
									printf("装备数不够，无法出售！\n");
									break;
								}
							case 15:
								printf("请问您要出售几颗？");
								scanf("%d",&shu);
								if(strongman_arm>=shu) {
									strongman_arm=strongman_arm-shu;
									money=money+shu*4000;
									printf("巨龙晶石：%d\n",strongman_arm);
									if(sheng==1) Beep(1200,100);
									printf("金币：%d\n",money);
								} else {
									printf("晶石数不够，无法出售！\n");
									break;
								}
								break;
							case 0:
								break;
								break;
							default:
								printf("没有该装备，无法出售！\n");
								break;
						}
						break;
					case 5:
						int yewai;
						while(1) {
							puts("=============================================================================");
							printf("要去哪冒险呢？");
							system("color 8c");
							if(sheng==1) Beep(1200,100);
							printf("\n\n");
							cout<<"1,神秘沼泽 危险程度:★\n\n";
							Sleep(50);
							system("color 8c");
							cout<<"2,星耀草原 危险程度:★★★\n\n";
							Sleep(50);
							cout<<"3,诡异森林 危险程度:★★★\n\n";
							Sleep(50);
							cout<<"4,荒漠矿场 危险程度:★★★★\n\n";
							Sleep(50);
							cout<<"5,炽热炎洞 危险程度:★★★★★\n\n";
							Sleep(50);
							cout<<"6,皮卡营地 危险程度:★★★★★★\n\n";
							Sleep(50);
							cout<<"7,花朵宫殿 危险程度:★★★★★★\n\n";
							Sleep(50);
							cout<<"8,熔岩龙穴 危险程度:★★★★★★★\n\n";
							Sleep(50);
							cout<<"9,凋零宇宙 危险程度:★★★★★★★★\n\n";
							Sleep(50);
							cout<<"0,离开\n";
							Sleep(150);
							system("color 8c");
							puts("=============================================================================");
							scanf("%d",&yewai);
							switch(yewai) {
								case 1:
									battle=1;
									while(battle==1) {
										system("cls");
										place_sign=place.forest1;
										s=SuiJi();
										if(s<7) {
											guai=xiyi;
											printf("%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<9) {
											guai=witch;
											printf("%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else {
											printf("这里安全\n\n\n");
										}
									}
									break;
								case 3:
									battle=1;
									while(battle==1) {
										system("cls");
										place_sign=place.forest2;
										s=SuiJi();
										if(s<4) {
											guai=witch;
											printf("%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<7) {
											battle=1;
											guai=strongman;
											printf("横冲直撞的%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else {
											battle=1;
											guai=zhizhu;
											printf("可怕的%s爬了过来!\n\n\n",guai.name);
											BattleAct();
										}
									}
									break;
								case 5:
									battle=1;
									while(battle==1) {
										system("cls");
										place_sign=place.forest3;
										s=SuiJi();
										if(s<=3) {
											guai=strongman;
											printf("横冲直撞的%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<5) {
											guai=huolong;
											printf("炽热的%s拍打着翅膀扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<8) {
											guai=gl;
											printf("全身长满矿石的%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else {
											guai=zhizhu;
											printf("可怕的%s扑爬了过来!\n\n\n",guai.name);
											BattleAct();
										}
									}
									break;
								case 2:
									battle=1;
									while(battle==1) {
										system("cls");
										place_sign=place.grass1;
										s=SuiJi();
										if(s<=3) {
 
											guai=bee;
											printf("%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<5) {
											battle=1;
											guai=horse;
											printf("%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<8) {
 
											guai=ymr;
											printf("横冲直撞的%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else {
 
											guai=nz;
											printf("帅气但令人讨厌的%s向你开枪!\n\n\n",guai.name);
											BattleAct();
										}
									}
 
									break;
								case 4:
									battle=1;
									while(battle==1) {
										system("cls");
										place_sign=place.grass2;
										s=SuiJi();
										if(s<5) {
											guai=horse;
											printf("%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<7) {
											guai=lion;
											printf("%s举着尚方宝剑拦住了你!\n\n\n",guai.name);
											BattleAct();
										} else {
											guai=gl;
											printf("全身长满矿石的%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										}
									}
 
									break;
								case 6:
									battle=1;
									while(battle==1) {
										system("cls");
										s=SuiJi();
										if(s<7) {
											guai=pika;
											printf("你感到了强烈的电流涌入全身，%s走了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<9) {
											guai=dapika;
											printf("天空一声巨响，三道闪电劈到%s的身上，%s手持雷霆之刃冲了过来!\n\n\n",guai.name,guai.name);
											BattleAct();
										} else {
											printf("这里安全\n\n\n");
										}
									}
 
									break;
								case 8:
									battle=1;
									while(battle==1) {
										system("cls");
										s=SuiJi();
										if(s<=3) {
 
											guai=cl;
											printf("一条飞龙横卧洞内，你定睛一看，是%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else if(s<=8 && s>=4) {
 
											guai=huolong;
											printf("炽热的%s拍打着翅膀扑了过来!\n\n\n",guai.name);
											BattleAct();
										} else {
 
											guai=jl;
											printf("一条金光闪闪的飞龙盘旋空中，，是传说中的%s扑了过来!\n\n\n",guai.name);
											BattleAct();
										}
									}
 
									break;
								case 7:
									battle=1;
									while(battle==1) {
										system("cls");
										place_sign=place.grass3;
										s=SuiJi();
										if(s<5) {
 
											guai=lion;
											printf("%s举着尚方宝剑拦住了你!\n\n\n",guai.name);
											BattleAct();
										} else if(s<7||boss1==0) {
 
											if(strongman_arm>=1) {
												printf("神秘老人:\n\n\n 哈哈,年轻人,做的不错,不过...嘿嘿,你上当啦!巨龙晶石我要了,公主你也别想带走!\n\n\n");
												guai=bossno1;
												printf("瞬间，你被一团黑雾笼罩，你被拉入了凋零幻境，%s向你发起攻击!\n\n\n",guai.name);
												BattleAct();
											} else printf("神秘老人:\n\n\n 年轻人,你好啊.如果你有巨龙晶石,我可以告诉你公主的下落哦~\n\n\n");
										} else {
 
											guai=nz;
											printf("帅气但令人讨厌的%s向你开枪!\n\n\n",guai.name);
											BattleAct();
										}
									}
 
									break;
								case 9:
									battle=1;
									while(battle==1) {
										system("cls");
										s=SuiJi();
										if(diaolingxinhave!=0) {
											if(s==1&&boss2==0) {
												guai=dlfb;
												printf("一个巨大的黑暗物体，周围环绕着大量的由破碎方块组成的黑色颗粒云环的%s向你发起攻击!\n\n\n",guai.name);
												BattleAct();
											} else if(s>=2 && s<=4) {
												guai=dlkl;
												printf("手持凋零剑的黑色凶恶%s扑了过来!\n\n\n",guai.name);
												BattleAct();
											} else if(s>=5&&s<=7) {
												guai=gst;
												printf("一个巨大的触手向你打来，你挡了下来%s扑了过来!\n\n\n",guai.name);
												BattleAct();
											} else {
												guai=dljs;
												printf("一只巨大的猛兽%s冲了过来!\n\n\n",guai.name);
												BattleAct();
											}
										}
										if(diaolingxinhave==0) {
											cout<<"你没有击败过凋零女巫，请去花朵宫殿击败凋零女巫。" <<endl;
										}
									}
 
									break;
									if(yewai!=0) {
										system("cls");
										printf("该区域为未知区域，无法进入。\n\n\n");
										system("color 8E");
										break;
									}
							}
							if(yewai==0) {
								system("cls");
								break;
								printf("已离开荒野。");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
							}
						}
 
				}
				break;
 
			case 2:
				ChooseWupin();
				break; //显示道具,并可以使用.
			case 3: //对话选项
				if(sheng==1) Beep(1200,100);
				if(place_sign==place.bar) {
					printf("要和谁说话?\n\n\n1,红发女郎 2,赏金猎人 3,酒吧老板 4,药品商人\n\n\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);//显示对话人物
					switch(scanf("%d",&choose_number),choose_number) {
						case 1:
							printf("红发女郎:\n\n\n 吧台边那个Hunter好帅啊!(~脸红~)\n\n\n听说他经常外出打猎,外面的路他应该很熟悉的!\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							break;
						case 2:
							if(fang1n<1&&gong1n<1) {
								printf("赏金猎人:\n\n\n 你要救公主啊!好胆量!\n\n\n 不过外面的世界很险恶,而且越深越危险,这是匕首和布衣,对你会有些帮助的,拿去吧!\n\n\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								printf("%s心想:哇,这位大叔人真好啊!\n\n\n)",player.name);
								gong1n++;
								fang1n++;
							} else printf("赏金猎人:\n\n\n 加油吧,年轻人!\n\n\n 不要被外面世界所吓倒!\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							break;
						case 3:
							printf("要喝点什么?\n\n\n 1,二锅头25金币 HP+20 2,伏特加80金币 HP+50 3,人头马面150金币 HP+100 0,返回\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							choose_number=1;
							while(choose_number) {
								switch(scanf("%d",&choose_number),choose_number) {
									case 1:
										if(money<25) {
											printf("钱不够!");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											if(player.health+20<=player.max_health) {
												printf("HP+20.");
												system("color 8E");
												money-=25;
												if(sheng==1) Beep(1200,100);
												player.health+=20;
											} else {
												printf("HP满了");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												player.health=player.max_health;
											}
										}
										break;
									case 2:
										if(money<80) {
											printf("钱不够!");
											system("color 8E");
										} else {
											if(player.health+50<=player.max_health) {
												printf("HP+50.");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												money-=80;
												player.health+=50;
											} else {
												printf("HP满了");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												player.health=player.max_health;
											}
										}
										break;
									case 3:
										if(money<150) {
											printf("钱不够!");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											if(player.health+100<=player.max_health) {
												printf("HP+100.");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												money-=150;
												player.health+=100;
											} else {
												printf("HP满了");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												player.health=player.max_health;
											}
										}
										break;
									case 0:
										printf("下次再来!\n");
										system("color 8E");
										break;
									default:
										printf("输入错误\n\n\n");
										system("color 8E");
										break;
								}
								break;
							}
							break;
						case 4:
							printf("你要干什么？\n\n\n 1，买东西 2，聊天 \n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							int mai;
							scanf("%d",&mai);
							if(mai==1) {
								printf("买点什么呢？\n1,止血草￥100 HP+60\n2，急救包￥150 HP+80 \n3，云南白药￥250 HP+120\n4，超级云南白药￥400 HP+200 \n5，经验草￥150 经验+300 \n6，经验包￥600 经验+600\n7，经验石￥500 经验+1000 \n0,拜拜\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								int dongxi;
								scanf("%d",&dongxi);
								switch(dongxi) {
									case 1:
										if(money>=100&&cao<6) {
											cao++;
											money=money-100;
											printf ("止血草+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
									case 2:
										if(money>=150&&jijiubao<10) {
											jijiubao++;
											money=money-150;
											printf ("急救包+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
									case 3:
										if(money>=250&&baiyao<10) {
											baiyao++;
											money=money-250;
											printf ("云南白药+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
									case 4:
										if(money>=400&&superbaiyao<10) {
											superbaiyao++;
											money=money-400;
											printf ("超级云南白药+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
 
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
									case 5:
										if(money>=150) {
											jingyancao++;
											money=money-150;
											printf ("经验草+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
									case 6:
										if(money>=300) {
											jingyanbao++;
											money=money-300;
											printf ("经验包+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
									case 7:
										if(money>=500) {
											jingyanshi++;
											money=money-500;
											printf ("经验石+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("钱不够!\n");
											system("color 8E");
										}
										break;
								}
							case 0:
								printf("金币：%d\n",money);
								system("color 8E");
								printf("再见，欢迎下次再来！\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								break;
 
							}
							if(mai==2) {
								printf("药品商人：去去去，老子没时间陪你聊。\n");
								system("color 8E");
							}
					}
				} else if(place_sign==place.hotel)
					printf("“老板娘!我...”\n\n\n“我忙着呢，没空理你~”\n\n\n");
				else printf("这里好像没人可以聊天\n\n\n");
				system("color 8E");
				break;
			case 4:
				DisplayState();
				break; //显示状态
			case 5: //装备
				if(sheng==1) Beep(1200,100);
				printf("攻击装备: 1,匕首:%d个 2,西洋剑:%d个 3,粗制石剑:%d个 4,碧血战锤:%d个 5,蜘蛛毒剑:%d个 6,尚方宝剑:%d个 7,雷霆之刃：%d个 8,X尚方宝剑X：%d个 9,命令之剑：%d个\n\n\n",gong1n,gong2n,gong7n,gong3n,gong6n,gong4n,gong5n,gong4Xn,mgongn);
				system("color 8E");
				printf("防御装备: 10,布衣:%d个 11,鳞甲:%d个 12,战斗马甲:%d个 13,重甲:%d个 14,石铠甲:%d个 15,传说圣甲:%d个 16,金龙铠:%d个 17,X传说圣甲X:%d个 18,命令之甲:%d个\t\t0,返回\n\n\n",fang1n,fang2n,fang7n,fang3n,fang6n,fang4n,fang5n,fang4Xn,mfangn);
				system("color 8E");
				printf("选择要装备的武器或防具:\n\n\n");
				system("color 8E");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(gong1n>=1) {
							printf("拿起了匕首\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							gong=gong1;
							strcpy(gongname,"匕首");
							system("color 8E");
						} else printf("你没有匕首可以装备\n\n\n");
						system("color 8E");
						break;
					case 2:
						if(gong2n>=1) {
							printf("拿起了西洋剑\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							gong=gong2;
							strcpy(gongname,"西洋剑");
							system("color 8E");
						} else printf("你没有西洋剑可以装备\n\n\n");
						system("color 8E");
						break;
					case 3:
						if(gong7n>=1) {
							printf("拿起了粗制石剑\n\n\n");
							gong=gong7;
							strcpy(gongname,"粗制石剑");
						} else printf("你没有粗制石剑可以装备\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 4:
						if(gong3n>=1) {
							printf("拿起了碧血战锤\n\n\n");
							gong=gong3;
							strcpy(gongname,"碧血战锤");
						} else printf("你没有碧血战锤可以装备\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 5:
						if(gong6n>=1) {
							printf("拿起了蜘蛛毒剑\n\n\n");
							gong=gong6;
							strcpy(gongname,"蜘蛛毒剑");
						} else printf("你没有蜘蛛毒剑可以装备\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 6:
						if(gong4n>=1) {
							printf("拿起了尚方宝剑\n\n\n");
							gong=gong4;
							strcpy(gongname,"尚方宝剑");
						} else printf("你没有尚方宝剑可以装备\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 7:
						if(gong5n>=1) {
							printf("拿起了雷霆之刃\n\n\n");
							if(sheng==1) Beep(1200,100);
							gong=gong5;
							strcpy(gongname,"雷霆之刃");
						} else printf("你没有雷霆之刃可以装备\n\n\n");
						break;
					case 8:
						if(gong4Xn>=1) {
							printf("拿起了X尚方宝剑X\n\n\n");
							if(sheng==1) Beep(1200,100);
							gong=gong4X;
							strcpy(gongname,"X尚方宝剑X");
						} else printf("你没有X尚方宝剑X可以装备\n\n\n");
						break;
					case 9:
						if(mgongn>=1) {
							printf("拿起了命令之剑\n\n\n");
							if(sheng==1) Beep(1200,100);
							gong=mgong;
							strcpy(gongname,"命令之剑");
						} else printf("你没有命令之剑可以装备\n\n\n");
						break;
					case 10:
						if(fang1n>=1) {
							printf("穿上了布衣\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang1;
							strcpy(fangname,"布衣");
						} else printf("你没有布衣可以装备\n\n\n");
						break;
					case 11:
						if(fang2n>=1) {
							printf("穿上了鳞甲\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang2;
							strcpy(fangname,"鳞甲");
						} else printf("你没有鳞甲可以装备\n\n\n");
						break;
					case 12:
						if(fang7n>=1) {
							printf("穿上了战斗马甲\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang7;
							strcpy(fangname,"战斗马甲");
						} else printf("你没有战斗马甲可以装备\n\n\n");
						break;
					case 13:
						if(fang3n>=1) {
							printf("穿上了重甲\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang3;
							strcpy(fangname,"重甲");
						} else printf("你没有重甲可以装备\n\n\n");
						break;
					case 14:
						if(fang6n>=1) {
							printf("穿上了石铠甲\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang6;
							strcpy(fangname,"石凯甲");
						} else printf("你没有石凯甲可以装备\n\n\n");
						break;
					case 15:
						if(fang4n>=1) {
							if(sheng==1) Beep(1200,100);
							printf("穿上了传说圣甲\n\n\n");
							fang=fang4;
							strcpy(fangname,"传说圣甲");
						} else printf("你没有传说圣甲可以装备\n\n\n");
						break;
					case 16:
						if(fang5n>=1) {
							printf("穿上了金龙铠\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang5;
							strcpy(fangname,"金龙铠");
						} else printf("你没有金龙铠可以装备\n\n\n");
						break;
					case 17:
						if(fang4Xn>=1) {
							printf("穿上了X传说圣甲X\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang4X;
							strcpy(fangname,"X传说圣甲X");
						} else printf("你没有X传说圣甲X可以装备\n\n\n");
						break;
					case 18:
						if(mfangn>=1) {
							printf("穿上了命令之甲\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=mfang;
							strcpy(fangname,"命令之甲");
						} else printf("你没有命令之甲可以装备\n\n\n");
						break;
					case 0:
						printf("未更换装备\n\n\n");
						break;
					default:
						printf("change error!");
				}
				break;
			case 6:
				if(sheng==1) Beep(1200,100);
				printf(" 您好，欢迎您玩斗破苍穹（苍穹世界）。");
				cout<<"为了给您更好的游戏体验，";
				Sleep(250);
				cout<<"zty时不时会优化本游戏，";
				Sleep(250);
				cout<<"优化后会尽快发布在网上。";
				Sleep(250);
				cout<<"关于外挂方面，";
				Sleep(250);
				cout<<"开启外挂的方式是设定勇者姓名时，";
				Sleep(250);
				cout<<"输入";
				Sleep(250);
				cout<<"“";
				Sleep(250);
				cout<<"6";
				Sleep(250);
				cout<<"6";
				Sleep(250);
				cout<<"6";
				Sleep(250);
				cout<<"”";
				Sleep(250);
				cout<<"（不包括双引号）。";
				Sleep(250);
				cout<<"我们在";
				Sleep(250);
				cout<<"2.";
				Sleep(250);
				cout<<"11.";
				Sleep(250);
				cout<<"5";
				Sleep(250);
				cout<<"版本内容";
				Sleep(250);
				cout<<"的基础上进行添加，";
				Sleep(250);
				cout<<"主要内容为新增背包和将退出游戏改到了设置里面还有如果不逃跑是不会停止战斗";
				Sleep(250);
				cout<<"已更新完毕，";
				Sleep(250);
				cout<<"希望大家喜欢。";
				cout<<"\n\n";
				Sleep(250);
				system("color 8E");
				break;
			case 8:
				if(sheng==1) Beep(1200,100);
				printf("合成台：                   0:退出\n\n");
				system("color 8E");
				cout<<"命令之书:"<<mingshu<<"\n1： 命令之剑   需要材料：1*X尚方宝剑X + 3*命令之书\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"2：X尚方宝剑X  需要材料：1* 尚方宝剑  + 1*命令之书\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"3： 命令之甲   需要材料：1*X传说圣甲X + 3*命令之书\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"4：X传说圣甲X  需要材料：1* 传说圣甲  + 1*命令之书\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"5： 毁灭炸弹   需要材料：5*手抛原子弹 + 3*命令之书\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"6：  金龙铠    需要材料：5*龙鳞  \n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"7：   鳞甲     需要材料：5*鳞片  \n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cin>>he;
				if(he==1)
					if(he==1&&gong4Xn>=1&&mingshu>=3) {
						gong4Xn--;
						mingshu-=3;
						mgongn++;
						cout<<"恭喜获得命令之剑\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==2)
					if(he==2&&gong4n>=1&&mingshu>=1) {
						gong4n--;
						mingshu--;
						gong4Xn++;
						cout<<"恭喜获得X尚方宝剑X\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==3)
					if(he==3&&fang4Xn>=1&&mingshu>=3) {
						fang4Xn--;
						mingshu-=3;
						mfangn++;
						cout<<"恭喜获得命令之甲\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==4)
					if(he==4&&fang4n>=1&&mingshu>=1) {
						fang4n--;
						mingshu--;
						fang4Xn++;
						cout<<"恭喜获得X传说圣甲X\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==5)
					if(he==5&&yuanzidan>=5&&mingshu>=3) {
						yuanzidan-=5;
						mingshu-=3;
						zhadan++;
						cout<<"恭喜获得毁灭炸弹\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==6)
					if(he==6&&ll>=5) {
						ll-=5;
						fang5n++;
						cout<<"恭喜获得金龙铠\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==7)
					if(he==7&&lp>=5) {
						lp-=5;
						fang2n++;
						cout<<"恭喜获得鳞甲\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"材料不足\n\n";
				if(he==0) break;
				break;
			case 9:
				system("cls");
				cout<<"设置        0:退出\n\n";
				cout<<"1:声音 ";
				if(sheng==1) cout<<"开\n";
				else cout<<"关\n";
				cout<<"\n2:UI界面 ";
				if(ui==1) cout<<"老版";
				else cout<<"新版";
				cout<<"\n\n3,退出游戏";
				cin>>shen;
				if(shen==1) {
					if(sheng==1) sheng=0;
					else sheng=1;
				}
				if(shen==2) {
					if(ui==1) ui=0;
					else ui=1;
				}
				if(shen==3) {
					printf("确定退出游戏?(Y/N)\n\n\n");
					system("color 8E");
					getchar();
					proof=getchar();
					if(proof=='y'||proof=='Y') {
						printf("按回车退出");
						system("color 8E");
						getchar();
						return;
					} else if(proof=='n'||proof=='N')printf("继续游戏!\n\n\n");
					else printf("继续!\n\n\n");
				}
				if(shen==0) break;
				break;
			case 7:
				if(sheng==1) Beep(1200,100);
				int mi;
				cout<<"============================*【后台 开挂 测试Bug】*=============================\n密码：";
				cin>>mi;
				if(mi%20120913==0&&mi!=0) {
					cout<<"输入正确！欢迎进入后台！\n\n=================================================\n后台服务：\n\n1.金币加999999\n\n2.血量上限加9999\n\n3.现有血量加9999\n\n4.攻击加9999\n\n5.防御加9999\n\n0.退出\n\n=================================================\n\n "<<endl;
					cin>>htsr;
					if(htsr==1) {
						cout<<"成功获得效果 *金币加999999\n";
						if(sheng==1) Beep(1200,100);
						money+=999999;
					}
					if(htsr==2) {
						cout<<"成功获得效果 *血量加9999\n";
						if(sheng==1) Beep(1200,100);
						player.health+=9999;
					}
					if(htsr==3) {
						cout<<"成功获得效果 *血量上限加9999\n";
						if(sheng==1) Beep(1200,100);
						player.max_health+=9999;
					}
					if(htsr==4) {
						cout<<"成功获得效果 *攻击加9999\n";
						if(sheng==1) Beep(1200,100);
						player.attack+=9999;
					}
					if(htsr==5) {
						cout<<"成功获得效果 *防御加9999\n";
						if(sheng==1) Beep(1200,100);
						player.defense+=9999;
					}
					if(htsr==0) {
						cout<<"成功退出\n";
						if(sheng==1) Beep(1200,100);
						continue;
					}
				} else {
					cout<<"输入错误！请检查！"<<endl;
					continue;
				}
				break;
			case 10:
				system("cls");
				printf("物品:止血草:%d个 急救包:%d个 云南白药:%d个 超级云南白药:%d个 手雷:%d个 毒标:%d个 手抛式原子弹:%d个 经验草:%d个经验包:%d个 经验石:%d个 巨龙晶石:%d个 免死金牌:%d个 凋零之心:%d个 毁灭炸弹:%d个 \n合成材料:鳞片:%d个 龙鳞:%d个 命令之书:%d个\n",cao,jijiubao,baiyao,superbaiyao,boom,dubiao,yuanzidan,jingyancao,jingyanbao,jingyanshi,strongman_arm,miansi,diaolingxin,zhadan,lp,ll,mingshu);
				printf("攻击装备: 匕首:%d个 西洋剑:%d个 粗制石剑:%d个 碧血战锤:%d个 蜘蛛毒剑:%d个 尚方宝剑:%d个 雷霆之刃：%d个 X尚方宝剑X：%d个 命令之剑：%d个\n",gong1n,gong2n,gong7n,gong3n,gong6n,gong4n,gong5n,gong4Xn,mgongn);
				system("color 8E");
				printf("防御装备: 布衣:%d个 鳞甲:%d个 12,战斗马甲:%d个 重甲:%d个 石铠甲:%d个 传说圣甲:%d个 金龙铠:%d个 X传说圣甲X:%d个 命令之甲:%d个\t\t\n\n\n",fang1n,fang2n,fang7n,fang3n,fang6n,fang4n,fang5n,fang4Xn,mfangn);
				system("color 8E");
				system("pause");
				break;
		}
	}
}
void DisplayState() {
	printf("%s 攻击力:%d+%d=%d 防御力:%d+%d=%d HP:%d/%d \n\n\n",player.name,player.attack,gong,player.attack+gong,player.defense,fang,player.defense+fang,player.health,player.max_health);
	printf("武器: %s 防具: %s \n\n\n",gongname,fangname);
	printf("等级:%d 经验:%d/%d 还需要%d经验升级 金币:%d \n\n\n",player.level,player.exp,player.max_exp,player.max_exp-player.exp,money);
	system("pause");
}
void BattleAct() {
	while(1) {
		puts("=============================================================================");
		if(sheng==1) Beep(1200,100);
		printf("要怎么办?\n\n\n 1,攻击 2,使用物品 3,查看状态 4,逃跑\n\n\n");
		switch(scanf("%d",&choose_number),choose_number) {
			case 1:
				s=SuiJi();
				printf("%s攻击! %sHP减少%d\n\n\n",player.name,guai.name,player.attack+s+gong-guai.defense/3);
				guai.health-=player.attack+s+gong-guai.defense/3;
				if(AttackResult())return; //如果攻击有结果(敌人或玩家战死)退出函数
				else continue;
			case 2:
				ChooseWupin();
				break; //选择物品,可以使用,战斗中允许使用攻击性物品
			case 3:
				DisplayState();
				break; //显示状态
			case 4:
				s=SuiJi();
				if(s<4) { //40%的概率可以逃跑
					printf("%s逃跑了~\n\n\n",player.name);
					if(sheng==1) Beep(1200,100);
					battle=0;
					return;
				} else printf("%s逃跑失败!\n\n\n",player.name);
				if(sheng==1) Beep(200,100);
				break;
			default:
				printf("输入错误,重新输入!\n\n\n");
				if(sheng==1) Beep(200,100);
		}
	}
}
void printf(char *p) {
	while(1) {
		if(*p!=0)
			printf("%c",*p++);
		else
			break;
		Sleep(100);
	}
}
/*
Servers Location───────────────────────────────────────────────────────────────────────┐│                                           ││ timer                   1         41      │
│                                                                                        ││                                           ││ node                    2         52      │
│                                 ??                                                     ││                                           ││ gulp                    2         52      │
│               ??????????????????  ?????    ?????  ??????    ??????     ???             ││                                           ││ java                    3         73      │
│  ?????????????????????????????  ?????? ?    ????????????????    ?????????????????      ││   9      2      4      6      5      9    ││ grep                    1         16      │
│  ?? ???????????????????????? ????  ??? ?? ?? ??????                    ??????????      ││   US1    US2    EU1    AU1    AS1    JP1  ││ netns                   0         45      │
│   ????     ????   ????????????        ????????                         ??  ?? ??       │└───────────────────────────────────────────┘└───────────────────────────────────────────┘
│              ?  ?   ??????????         ??????????? ?? ?  ??        ? ????              │┌─Server Log─────────────────┐┌─Percent Donut──────────────┐┌─Storage────────────────────┐
│              ???       ??             ???????????  ??             ??????               ││starting process watchdog   ││                            ││                            │
│                ??? ??????            ??     ??  ?? ??????         ??                   ││starting process node       ││           ?????            ││                            │
│       ?          ??????????          ?           ?????  ? ????? ?? ??                  ││avg. wait time 0.52         ││        ????????????        ││                            │
│                      ?????????       ?????        ???    ??  ???? ???                  ││avg. wait time 0.47         ││       ????     ?????       ││    37%          63%        │
│                     ?  ?     ???          ??    ? ?           ?????  ???               ││avg. wait time 0.79         ││      ???         ????      ││                            │
│                        ??       ??         ??    ? ?            ???  ??????            ││terminating server EU1      ││      ??     57%   ???      │└────────────────────────────┘
│    ?                    ??      ?          ??   ????              ???? ???   ?  ?      ││terminating server AU1      ││      ???          ???      │
│                          ?   ????           ?  ?? ??              ?      ??            ││terminating server US1      ││      ?????      ????       │┌─Throughput (bits/sec)──────┐
│                         ?? ???              ????                  ?????????   ??       ││starting process tar -xvf   ││       ?????????????        ││                            │
│                         ? ??                                            ??   ???       ││avg. wait time 0.65         ││          ????????          ││Server1:                    │
│                         ?????                                                          ││starting process tar -xvf   ││           storage          ││▁▆█▆▄█▆▂▆▂█▂▆██▁█▄▆▁▆▂▂▁█▄▁▄│
│                                                                                        ││terminating server US2      ││                            ││                            │
│                                                                                        ││terminating server JP1      ││                            ││Server2:                    │
│                                                                                       
*/
