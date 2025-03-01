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
//���ʵ����Ӧ��initialize
//=======================================

//���涨��̰���ߵ�������
class snake_position
{
public:

    int x,y;      //x��ʾ�У�y��ʾ��

    snake_position(){};

    void initialize(int &);//�����ʼ��


};

snake_position position[(N-2)*(N-2)+1]; //����̰�������������飬��(N-2)*(N-2)������

void snake_position::initialize(int &j)
{
        x = 1;

        y = j;
}


//���涨��̰���ߵ�����ͼ

class snake_map
{

private:

    char s[N][N];//����̰�������̣�����ǽ�ڡ�

    int grade, length;

    int gamespeed; //ǰ��ʱ����

    char direction; // ��ʼ����£������˶�

    int head,tail;

    int score;

    bool gameauto;

public:

    snake_map(int h=4,int t=1,int l=4,char d=77,int s=0):length(l),direction(d),head(h),tail(t),score(s){}

    void initialize();   //��ʼ������

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

// �������һ���ַ�
char CreateCh()
{
	char ch = 0;
	int flag = rand() % 3; // 0~2
	if (flag == 0)
		ch = rand() % 26 + 'a'; // ����Сд��ĸa~z
	else if (flag == 1)
		ch = rand() % 26 + 'A'; // ������д��ĸA~Z
	else
		ch = rand() % 10 + '0'; // ��������0~9

	return ch;
}
// ��ʼ���ṹ���Ա
void InitRain()
{
	// ��ʼ���ַ���λ�ú��ٶ�
	for (int i = 0; i < STR_NUM; ++i)
	{
		rain[i].x = i*STR_WIDTH;
		rain[i].y = rand() % HEIGHT;
		rain[i].speed = rand() % 5 + 5;
	}
	// ��ȡ����ַ���������
	for (int i = 0; i < STR_NUM; i++)
	{
		for (int j = 0; j < STR_SIZE; j++)
		{
			rain[i].str[j] = CreateCh();
		}
	}
}
// �����������
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
// �ƶ��ַ�
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
// ����ı��ַ�
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

            s[i][j]=' '; // ��ʼ��̰���������м�հײ���

    for(i=0;i<=N-1;i++)

        s[0][i] = s[N-1][i] = '-'; //��ʼ��̰������������ǽ��

    for(i=1;i<=N-2;i++)

        s[i][0] = s[i][N-1] = '|'; //��ʼ��̰������������ǽ��
}


//============================================
//���̰����������Ϣ

void snake_map::show_game()

{

    system("cls"); // ����

    int i,j;

    cout << endl;

    for(i=0;i<N;i++)
    {

        cout << '\t';

        for(j=0;j<N;j++)

            cout<<s[i][j]<<' '; // ���̰��������

        if(i==2) cout << "\t�ȼ���" << grade;

        if(i==6) cout << "\t�ٶȣ�" << gamespeed;

        if(i==10) cout << "\t�÷֣�" << score << "��" ;

        if(i==14) cout << "\t��ͣ����һ�¿ո��" ;

        if(i==18) cout << "\t�����������¿ո��" ;

        cout<<endl;
    }
}

//����ѡ��ȼ�
void snake_map::getgrade()
{
    cin>>grade;

    while( grade>7 || grade<1 )
    {
        cout << "����������1-7ѡ��ȼ�����������������Ч" << endl;

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

//����ȼ����÷�����Լ��ƺ�

void snake_map::display()
{

    cout << "\n\t\t\t\t�ȼ���" << grade;

    cout << "\n\n\n\t\t\t\t�ٶȣ�" << gamespeed;

    cout << "\n\n\n\t\t\t\t�÷֣�" << score << "��" ;

}

//���������
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

    //����м����»�ʱ�䳬���Զ�ǰ��ʱ��������ֹѭ��



        if(gameover)
        {

            getch();

            key = getch();
        }

        if(key == ' ')

        {
            while(getch()!=' '){};//����ʵ�ֵ��ǰ��ո����ͣ�����ո�������Ĺ��ܣ�����֪Ϊ��ԭ����Ҫ�����¿ո���ܼ��������Ǹ�bug��
        }

        else

            direction = key;

        switch(direction)
        {
            case 72: x= position[head].x-1; y= position[head].y;break; // ����

            case 80: x= position[head].x+1; y= position[head].y;break; // ����

            case 75: x= position[head].x; y= position[head].y-1;break; // ����

            case 77: x= position[head].x; y= position[head].y+1; // ����

        }

        if(!(direction==72||direction==80||direction==75 ||direction==77))   // �����Ƿ����

            gameover = 0;

        else if(x==0 || x==N-1 ||y==0 || y==N-1)   // ����ǽ��

            gameover = 0;

        else if(s[x][y]!=' '&&!(x==x1&&y==y1))    // ��ͷ��������

            gameover = 0;

        else if(x==x1 && y==y1)

        { // ���ף����ȼ�1

            length ++;

            if(length>=8 && gameauto)

            {

                length -= 8;

                grade ++;

                if(gamespeed>=200)

                    gamespeed -= 200; // �ı�̰����ǰ���ٶ�

                else

                    gamespeed = 100;

            }

            s[x][y]= '#';  //������ͷ

            s[position[head].x][position[head].y] = '*'; //���׺�ԭ����ͷ��Ϊ����

            head = (head+1) % ( (N-2)*(N-2) );   //ȡ��ͷ����

            position[head].x = x;

            position[head].y = y;

            show_game();

            gameover = 1;

            score += grade*20;  //�ӷ�

            setpoint();   //������

        }

        else
        { // ������

            s[position[tail].x][position[tail].y]=' ';//����β�ÿ�

            tail= (tail+1) % ( (N-2) * (N-2) );//������β����

            s[position[head].x][position[head].y]='*';  //����ͷ��Ϊ����

            head= (head+1) % ( (N-2) * (N-2) );

            position[head].x = x;

            position[head].y = y;

            s[position[head].x][position[head].y]='#'; //������ͷ

            gameover = 1;

        }
    return gameover;

}
void snake_main()
{
    char ctn = 'y';

    int nodead;

    cout<<"\n\n\n\n\n\t\t\t ��ӭ����̰������Ϸ!"<<endl;//��ӭ����;

    cout<<"\n\n\n\t\t\t ����������Ͽ�ʼ������"<<endl;//׼����ʼ;;

    getch();

    while( ctn=='y' )
    {
        system("cls"); // ����

        snake_map snake;

        snake.initialize();

        cout << "\n\n����������ѡ����Ϸ�ȼ���" << endl;

        cout << "\n\n\n\t\t\t1.�ȼ�һ���ٶ� 1000 \n\n\t\t\t2.�ȼ������ٶ� 800 \n\n\t\t\t3.�ȼ������ٶ� 600 ";

        cout << "\n\n\t\t\t4.�ȼ��ģ��ٶ� 400 \n\n\t\t\t5.�ȼ��壺�ٶ� 200 \n\n\t\t\t6.�ȼ������ٶ� 100 \n\n\t\t\t7.�Զ�����ģʽ" << endl;

        snake.getgrade();//��ȡ�ȼ�

        for(int i=1;i<=4;i++)
        {
            position[i].initialize(i);//��ʼ������
        }

        snake.setpoint();  // ������һ����

        do
        {
            snake.show_game();

            nodead = snake.updata_game();

        }while(nodead);

        system("cls"); //����



        cout << "\n\n\n\t\t\t\tGameover��\n\n"<<endl;

        snake.display();//����ȼ�/�÷����

        cout << "\n\n\n\t\t    �Ƿ�ѡ�������Ϸ������ y ������n �˳�" << endl;

        cin >> ctn;

    }

    return;
}


class Bullet;
class Tank;
class E_Bullet;
class Boss;
bool wined = false;
struct pos//������
{
 int a;
 int b;
};
class E_Bullet//���˴�����ӵ�
{
public:
 clock_t d;
 int x;
 int y;
 bool on = false;
 pos show()//�����µ�λ��
 {
 setfillcolor(RGB(255, 180, 20));
 fillrectangle(x - 5, y - 5, x + 5, y + 5);
 return pos{ x,y };
 }
 pos del()//����ԭ����λ��
 {
 setfillcolor(0);
 setlinecolor(0);
 fillrectangle(x - 5, y - 5, x + 5, y + 5);
 rectangle(x - 5, y - 5, x + 5, y + 5);
 return pos{ x,y };
 }
 pos move()//����
 {
 x -= 3;
 return pos{ x,y };
 }
};
class Bullet//��Ҵ�����ӵ���ͬ��
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
 pos move()//����
 {
 x += 3;
 return pos{ x,y };
 }
};
class Boss//����
{
public:
 bool hurting = false;
 clock_t d_hurt;
 COLORREF clr = RGB(0, 130, 125);
 int x;
 int y;
 int hp = 100;//����
 clock_t d;//�жϾ�����һ��ִ��ĳһ�������˶��
 clock_t att_d;
 bool angle = false;//����
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
 void fire(E_Bullet& but)//����
 {
 but.on = true;//����һ���ӵ�
 but.x = x - 20;
 but.y = y;
 but.d = clock();
 }
 void move()//�������µ��ƶ�
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
 void hurt()//����
 {
 hp -= 4;
 d_hurt = clock();
 setfillcolor(0);
 setlinecolor(WHITE);
 fillrectangle(160, 485, 560, 510);//����Ѫ��
 rectangle(160, 485, 160 + hp * 4, 510);
 setfillcolor(RGB(230, 0, 1));
 setlinecolor(RGB(255, 255, 255));
 fillrectangle(160, 485, 160 + hp * 4, 510);
 rectangle(160, 485, 160 + hp * 4, 510);
 hurting = true;
 if (hp <= 0)//����
 {
 wined = true;
 }
 }
};
class Tank//����࣬ͬ��
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
 initgraph(640, 550, 4);//��ʼ����Ļ
 settextcolor(RGB(0, 254, 0));
 settextstyle(20, 0, _T("����"));
 outtextxy(10, 10, _T("BOSS�����˵���!������ļ����ڱ��������!"));
 settextstyle(35, 0, _T("����"));
 outtextxy(150, 200, _T("W,S�ƶ�,K����"));
 Sleep(3000);
 setlinecolor(0);
 setfillcolor(0);
 rectangle(0, 0, 640, 550);
 fillrectangle(0, 0, 640, 550);
 setlinecolor(RGB(255, 255, 255));
 setfillcolor(RGB(255, 255, 255));
 clock_t delay = clock();//����ƶ�����ʱ
 clock_t d_f = clock();//��ҿ������ʱ
 line(0, 481, 640, 481);//�ָ����Ѫ��
 Bullet bt[BT_MAX];//��ҵ��ӵ�
 Tank tk(30, 30);//���
 Boss bo;//����
 bo.x = 580;
 bo.y = 240;
 E_Bullet ebt[BT_MAX];//���˵��ӵ�
 bo.d = clock();//��ʼ����ʱ
 bo.att_d = clock();
 tk.show();
 settextstyle(20, 0, _T("����"));
 outtextxy(10, 485, _T("BOSS������ֵ:"));
 setfillcolor(RGB(230, 0, 1));
 fillrectangle(160, 485, 560, 510);//����Ѫ��
 outtextxy(10, 520, _T("��ҵ�����ֵ:"));
 setfillcolor(RGB(0, 255, 1));
 fillrectangle(160, 515, 560, 540);//���Ѫ��
 while (1)//��ѭ��
 {
 if (wined || dead)//������˻��ߵ�������
 break;
 if (GetAsyncKeyState('W') & 0x8000)//����ƶ�
 {
 if (tk.y > 28 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y -= 3; tk.show(); delay = clock();
 }
 }
 if (GetAsyncKeyState('w') & 0x8000)//����ƶ�
 {
 if (tk.y > 28 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y -= 3; tk.show(); delay = clock();
 }
 }
 if (GetAsyncKeyState('k') & 0x8000)//��ҿ���
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
 if (GetAsyncKeyState('K') & 0x8000)//��ҿ���
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
 if (GetAsyncKeyState('S') & 0x8000)//����ƶ�
 {
 if (tk.y < 452 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y += 3; tk.show(); delay = clock();
 }
 }
 if (GetAsyncKeyState('s') & 0x8000)//����ƶ�
 if (tk.y < 452 && (clock() - delay) >= 40)
 {
 tk.del(); tk.y += 3; tk.show(); delay = clock();
 }
 for (int i = 0; i < BT_MAX; i++)//�����ӵ���ʹ�ӵ�ˢ��
 {
 if (bt[i].on == true && (clock() - bt[i].d) > 20)
 {
 bt[i].del();
 bt[i].move();
 bt[i].show();
 bt[i].d = clock();
 if (bt[i].x >= 635)
  bt[i].on = false, bt[i].del();//��������Ļ���Ҷ�
 if ((bt[i].x + 5 >= bo.x - 20 && bt[i].x - 5 <= bo.x + 20) && (bt[i].y - 5 < bo.y + 40 && bt[i].y + 5 > bo.y - 40))
  //���е���
  bt[i].on = false, bo.hurt(), bt[i].del();
 }
 }
 if (clock() - bo.att_d > 700)//�����Զ�����
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
 for (int i = 0; i < BT_MAX; i++)//�����ӵ�ˢ�£�ͬ��
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
 if (tk.hurting == true)//���������˸0.1��
 if (clock() - tk.d_hurt > 100)
 {
 tk.clr = RGB(150, 180, 210), tk.show(), tk.hurting = false;
 }
 else
 tk.clr = RGB(255, 0, 0), tk.show();
 if (bo.hurting == true)//����������˸0.1��
 if (clock() - bo.d_hurt > 100)
 {
 bo.clr = RGB(0, 130, 125), bo.show(), bo.hurting = false;
 }
 else
 bo.clr = RGB(0, 255, 0), bo.show();
 if (clock() - bo.d > 50)//�����ƶ���ʱ;
 bo.del(), bo.move(), bo.show(), bo.d = clock();
 }
 if (wined)//ʤ���ѷ�
 {
 settextcolor(RGB(0, 254, 0));
 settextstyle(35, 0, _T("����"));
 outtextxy(150, 200, _T("������boss!��Ӯ�ˣ���"));
 }
 else
 {
 settextcolor(RGB(254, 0, 0));
 settextstyle(35, 0, _T("����"));
 outtextxy(140, 200, _T("�㱻boss����ˣ�"));
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
	cout<<" �ȳ�����Ŭ��ͨ�ذɣ�                                             \n";
	Sleep(50);
	cout<<"                                                              \n";
	Sleep(50);
	cout<<" ���롰1 ����һҳ                           \n\n";
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
	cout<<" Gamesbox��Ʒ��Ϸ,��Ȩ(c) Copyright Linhonghan\n";
	Sleep(50);
	cout<<" Ŭ��ͨ�ذɣ�                                   \n";
	Sleep(50);
	cout<<"                                                \n";
	Sleep(50);
	cout<<" ���롰1 ����ʼ��Ϸ                    \n\n";
	Sleep(50);
A:
	char y=_getch();
	if(y=='1') return;
	else goto A;
}
int boss1=0,boss2=0;
struct Player { //��ҽṹ�壬����ʼ��player
	char name[21];
	int attack;
	int defense;
	int health;
	long int max_health;
	int level;
	int exp;
	int range_exp;
	long int max_exp;
} player= {"����",100,80,200,200,1,0,0,100};
struct Enemy {//�ֵĽṹ��,����ʼ�����ֹ�
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
//�֣��ø���ʯ�˾���
// �ֱ���  ����     �����װ�� ��   ��  Ѫ  ��� ���� ����װ����� ������� ���ˣ�����������Ƽ��˺���   ���ܸ�
//  gl= {"����ʯ��","ʯ����",  30, 150,1000,500, 250,      11,       7,        1,                         0},
gl= {"����ʯ��","ʯ����",30,150,1000,500,250,11,7,1,0},
zhizhu= {"��Ѩ֩��","֩�붾��",140,20,250,400,200,12,5,1,0},
ymr= {"Ұ����","����ʯ��",20,20,150,100,50,13,5,1,0},
nz= {"ţ��","ս�����",80,20,250,500,250,14,10,1,0},
strongman= {"ɭ�־���","��˵ʥ��",50,50,580,200,100,1,5,1,0},
witch= {"����","�ؼ�",35,55,250,50,50,2,4,1,1},
xiyi= {"����","��Ƭ",20,25,80,30,35,3,8,2,2},
huolong= {"�����","������ʯ",40*5,50*5,200*5,200*5,100*5,4,4,2,0},
lion= {"�ʼ�ʿ��","�з�����",100,30,380,200,100,5,5,1,0},
horse= {"���۾���","��Ѫս��",50,22,360,50,50,6,5,1,1},
bee= {"����","����",27,11,60,30,35,7,5,2,2},
bossno1= {"����Ů��","����ͨ��֤",1400,500,15000,10000,5000,15,10,1,0},
dljs= {"�������","����֮��",1200,700,20000,10000,500,10,7,1,0},
pika= {"Ƥ������","\0",300,40*8,1000,2000,1000,0,0,1,0},
dapika= {"����Ƥ��","����֮��",350,40*10,1500,3000,2000,8,6,6,0},
cl= {"���ҷ���","\0",450,50*10,2000,3500,2500,0,0,1,0},
jl= {"�ѿ�����","����",500,40*20,5000,8000,4500,9,6,6,1},
gst= {"���㹲����","����֮��",1800,65*10,15000,20000,1000,16,10,1,0},
dlkl= {"��������","����֮��",3000,30*10,12000,20000,1000,0,0,1,0},
dlfb= {".+*����籩*+.","\0",9000,1500,49000,0,500000,17,10,1,0},
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
char gongname[20]="��",fangname[20]="��";
char proof;
int lp=0,ll=0;
void AddWupin(int);
int AttackResult();
void BattleAct();  //      ____
void ChooseWupin();  //   /___/|
void DisplayState();  //  |   |/
void OrdinaryAct();     //����
int SuiJi();
int SuiJi100();
void WhetherLevelUp();
void SlowDisplay(char *);

void rain_main() {
	srand((unsigned int)time(NULL)); // ��ʼ�����������
		initgraph(WIDTH, HEIGHT);
		InitRain();
		DWORD t1, t2;
		t1 = GetTickCount();
		t2 = t1;
		while (1)
		{
			BeginBatchDraw(); // ˫�������
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
    // ģ�ⰴ��Alt��
    keybd_event(VK_MENU, 0, 0, 0);
    // ģ�ⰴ��Enter��
    keybd_event(VK_RETURN, 0, 0, 0);
    // ģ���ɿ�Enter��
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    // ģ���ɿ�Alt��
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}

int main() {
    int game_mode = 1;
    system("title Gamesbox");
    system("cls");
    sendAltEnter();
    
    if (sheng == 1) Beep(1200, 100);
    MessageBox(NULL, "��ӭ����Gamesbox��", "��Ϸ��ʼ��ʾ", MB_OK);
    main1:
    printf("(c) Copyright Linhonghan\nGamebox��ҳ\n[1] �����Ϸ\n[2] ̽����Ϸ\n[3] ̰����\n[4] ����ɱ\n[5] ħ������\n[6] 3d�Թ�\n[7] �ڿ͹���\n");
    printf("[8] �й�����(˫��)\n[9] ��ر���ս\n[10]��������\n[11]������\n\n");
    
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
        printf("��������Ϸ����!\n�������չ���˹����������������������˹�Ѷ�����ŵ˹��˹�����Ϳ�﹵��ȹ����������˰����!\n\n\n ΰ������߰�~�����������,Ӫ�ȹ���!\n\n\n�����������: (20���ַ�)\n\n\n");
        system("color 8E");
        scanf("%s", player_name);
        Sleep(300);
        strncpy(player.name, player_name, 20);
        if (strcmp(player.name, "666") == 0) {
            if (sheng == 1) Beep(5200, 300);
            printf("\n\n\n��ӡ����Ĺٷ�Ѫͳ��!�����ھ�����!\n\n\n666�����Ϊ����ѡ֮�ˣ�����ȳ������ɣ�\n\n\n");
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
    	printf("�������!");
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
void ChooseWupin() { //ѡ����Ʒ ��ʹ��
	if(sheng==1) Beep(1200,100);
	printf("��Ʒ: 1,ֹѪ��%d�� 2,���Ȱ�%d�� 3,���ϰ�ҩ%d�� 4,�������ϰ�ҩ%d�� 5,����%d�� 6,����%d�� 7,����ʽԭ�ӵ�%d�� 8,�����%d�� 9,�����%d�� 10,����ʯ%d�� 11,������ʯ%d�� 12,��������%d�� 13,����֮��%d�� 14,����ը��%d�� 0,����\n\n\n",cao,jijiubao,baiyao,superbaiyao,boom,dubiao,yuanzidan,jingyancao,jingyanbao,jingyanshi,strongman_arm,miansi,diaolingxin,zhadan);
	system("color 8A");
	switch(scanf("%d",&choose_number),choose_number) {
		case 1:
			if(cao>0) {
				printf("ʹ��ֹѪ��,HP����120\n\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				cao--;
				if(player.health+120>player.max_health)player.health=player.max_health;
				else player.health+=120;
			} else printf("û��ֹѪ����\n\n\n");
			system("color 8A");
			break;
		case 2:
			if(jijiubao>0) {
				printf("ʹ�ü��Ȱ�,HP����180\n\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				jijiubao--;
				if(player.health+180>player.max_health)player.health=player.max_health;
				else player.health+=180;
			} else printf("û�м��Ȱ���\n\n\n");
			system("color 8A");
			break;
		case 3:
			if(baiyao>0) {
				printf("ʹ�����ϰ�ҩ,HP����240\nz\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				baiyao--;
				if(player.health+240>player.max_health)player.health=player.max_health;
				else player.health+=240;
			} else printf("û�����ϰ�ҩ��\n\n\n");
			system("color 8A");
			break;
		case 4:
			if(superbaiyao>0) {
				printf("ʹ�ó������ϰ�ҩ,HP����400\n\n\n");
				system("color 8A");
				if(sheng==1) Beep(1200,100);
				superbaiyao--;
				if(player.health+400>player.max_health)player.health=player.max_health;
				else player.health+=400;
			} else printf("û�г������ϰ�ҩ��\n\n\n");
			system("color 8A");
			break;
		case 5:
			if(battle) { //��ս����(battle=1),����(battle=0)����ʹ�ù�������Ʒ
				if(boom>0) {
					printf("ʹ������,����HP����100\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					boom--;
					guai.health-=100;
					AttackResult();
				}
			} else printf("��ս��״̬,����ʹ������!\n\n\n");
			system("color 84");
			break;
		case 6:
			if(battle) { //��ս����(battle=1),����(battle=0)����ʹ�ù�������Ʒ
				if(dubiao>0) {
					printf("ʹ�ö���,����HP����200\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					dubiao--;
					guai.health-=200;
					AttackResult();
				}
			} else printf("��ս��״̬,����ʹ�ö���!\n\n\n");
			system("color 84");
			break;
		case 7:
			if(battle) { //��ս����(battle=1),����(battle=0)����ʹ�ù�������Ʒ
				if(yuanzidan>0) {
					printf("ʹ������ʽԭ�ӵ�,����HP����1500\n\n\n");
					system("color 84");
					if(sheng==1) Beep(1200,100);
					yuanzidan--;
					guai.health-=1500;
					AttackResult();
				}
			} else printf("��ս��״̬,����ʹ������ʽԭ�ӵ�!\n\n\n");
			system("color 84");
			break;
		case 8:
			if(jingyancao>0 && player.level<200) {
				printf("ʹ�þ����,�ȼ�����3��\n\n\n");
				system("color 8E");
				if(sheng==1) Beep(1200,100);
				jingyancao--;
				player.max_health=player.max_health+60;
				player.attack+=9;
				player.defense+=6;
				player.level+=3;
				player.health=player.max_health;
				printf("�ȼ���%d\n",player.level);
				system("color 8E");
				if(sheng==1) Beep(1200,100);
			} else    if(jingyancao<1) {
				printf("û�о������\n\n\n");
				system("color 8E");
			} else printf("�ȼ�����200��,��Ϊ̫�ߣ��޷�ʹ�á�\n\n\n");
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
					printf("ʹ�þ����,�ȼ�����%d��",sheng);
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					printf("�ȼ���%d\n",player.level);
					system("color 8E");
				} else {
					printf("ʹ�þ����,�ȼ�����5��\n\n\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					jingyanbao--;
					player.max_health=player.max_health+100;
					player.attack+=15;
					player.defense+=10;
					player.level+=5;
					player.health=player.max_health;
					printf("�ȼ���%d\n",player.level);
					system("color 8E");
				}
			} else if(jingyanbao<1) {
				printf("û�о������");
				system("color 8E");
			} else printf("�ȼ�����200��,��Ϊ̫�ߣ��޷�ʹ�á�\n\n\n");
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
					printf("ʹ�þ���ʯ,�ȼ�����%d��\n",sheng);
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					printf("�ȼ���%d\n",player.level);
					system("color 8E");
				} else {
					printf("ʹ�þ���ʯ,�ȼ�����10��\n");
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
				printf("û�о���ʯ��\n\n\n");
				system("color 8E");
			} else printf("�ȼ�����200��,��Ϊ̫�ߣ��޷�ʹ�á�\n\n\n");
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
					printf("ʹ�þ�����ʯ,�ȼ�����%d��",sheng);
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					printf("�ȼ���%d\n",player.level);
					system("color 8E");
				} else {
					printf("ʹ�þ�����ʯ,�ȼ�����20��\n\n\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);
					strongman_arm--;
					player.max_health=player.max_health+400;
					player.attack+=60;
					player.defense+=40;
					player.health=player.max_health;
					player.level+=20;
					printf("�ȼ���%d\n",player.level);
					system("color 8E");
				}
			} else if(strongman_arm<1) {
				printf("û�о�����ʯ�ˡ�\n\n\n");
				system("color 8E");
				if(sheng==1) Beep(1200,100);
			} else printf("�ȼ�����500��,��Ϊ̫�ߣ��޷�ʹ�á�\n\n\n");
			system("color 8E");
			break;
		case 12:
			if(miansi>0) {
				if(sheng==1) Beep(1200,100);
				cout<<"ʹ";
				Sleep(50);
				cout<<"��";
				Sleep(50);
				cout<<"��";
				Sleep(50);
				cout<<"��";
				Sleep(50);
				cout<<"��";
				Sleep(50);
				cout<<"��";
				Sleep(50);
				cout<<"HP";
				Sleep(50);
				cout<<"��";
				Sleep(50);
				system("color 8b");
				miansi--;
				if(player.health+999999>player.max_health)player.health=player.max_health;
				else player.health+=999999;
			} else printf("û������������\n\n\n");
			system("color 8b");
			break;
			break;
		case 13:
			if(diaolingxin>0) {
				printf("ʹ�õ���֮��\nHP����+100  ����+100\n\n\n");
				system("color 8b");
				if(sheng==1) Beep(1200,100);
				diaolingxin--;
				player.max_health+=100;
				player.attack+=100;
			} else printf("û�е���֮����\n\n\n");
			system("color 8b");
			break;
		case 14:
			if(battle) { //��ս����(battle=1),����(battle=0)����ʹ�ù�������Ʒ
				if(zhadan>0) {
					printf("ʹ�û���ը��,����HP����15000\n\n\n");
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
int AttackResult() { //�������:�ж��Ƿ��ʤ �Ƿ�����Ʒ �� �Ƿ�����
	if(guai.health<=0) {
		printf("ս��ʤ��!��ý��%d,����%d\n\n\n",guai.money,guai.exp);
		system("color 8C");
		if(sheng==1) Beep(1200,100);
		player.exp+=guai.exp;
		player.range_exp+=guai.exp;
		money+=guai.money;
		s=SuiJi();
		if(s<guai.wupinpro) {
			cout<<"��";
			Sleep(100);
			if(sheng==1) Beep(1200,100);
			cout<<"��";
			Sleep(100);
			cout<<"��";
			Sleep(100);
			cout<<"ʬ";
			Sleep(100);
			cout<<"��";
			Sleep(100);
			cout<<"��";
			Sleep(100);
			cout<<"��";
			Sleep(100);
			cout<<"��";
			Sleep(100);
			system("color 8C");
			printf("%s\n\n\n",guai.wupin);
			AddWupin(guai.wupin_sign);
		}
		WhetherLevelUp();
		if(strcmp(guai.name,".+*����籩*+.")==0) {
			printf("������\n\n");
			if(sheng==1) Beep(1200,100);
			system("color 8C");
		}
		return 1; //�����н���˷���1,���򷵻�0,�����ж��Ƿ������ս����Ϊ
	} else {
		int s=SuiJi();
 
		if((guai.attack+s-player.defense/3)<0) {
			player.health-=1;
			printf("%s����,���HP������ 1\n\n",guai.name);
			system("color 8C");
		} else {
			player.health-=guai.attack+s-player.defense/3;
			printf("%s����,���HP������%d\n\n",guai.name,guai.attack+s-player.defense/3);
			system("color 8C");
		}
		if(player.health<0) {
			battle=0;
			printf("%sս��!��ҵ���%d\n\n\n",player.name,player.level*500);
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
	if(player.level<=15&&l1>0) { //15������,�����㹻 ������������
		if(l1==1) {
			printf("%s",player.name);
			printf(" ����!\n\n\n������+3, ������+2, HP����+20\n\n\n");
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
			printf("������!����%d��!",l1);
			system("color 8E");
			printf("������+%d, ������+%d, HP����+%d\n\n\n",3*l1,2*l1,20*l1);
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
			printf(" ����!\n\n\n������+3, ������+2, HP����+20\n\n\n");
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
			printf("������!����%d��!",l2);
			system("color 8E");
			printf("������+%d, ������+%d, HP����+%d\n\n\n",3*l2,2*l2,20*l2);
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
			printf(" ����!\n\n\n������+3, ������+2, HP����+20\n\n\n");
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
			printf("������!����%d��!",l3);
			printf("������+%d, ������+%d, HP����+%d\n\n\n",3*l3,2*l3,20*l3);
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
void OrdinaryAct() { //������Ϊ�˵�
	while(1) {
// \(1000);
// system("cls");
		if(ui==0) {
			system("cls");
			puts("=============================================================================");
			system("color 8E");
			printf("Ҫ��ʲô?\n\n  1,�ƶ�     2,����     3,�Ի�  4,�鿴״̬ \n\n  5,װ��  6,������Ϸ    7,��̨   8,�ϳ�̨ \n\n  9,����  10,�򿪱��� \n\n");
			system("color 8E");
			if(sheng==1) Beep(1200,100);
			puts("=============================================================================");
			system("color 8E");
		} else {
			system("cls");
			puts("=============================================================================");
			system("color 8E");
			printf("Ҫ��ʲô?\n\n1,�ƶ� 2,���� 3,�Ի� 4,�鿴״̬ 5,װ�� 6,������Ϸ 7,��̨ 8,�ϳ�̨ 9,���� 10,����\n\n\n\n");
			system("color 8E");
			puts("=============================================================================");
			system("color 8E");
		}
		switch(scanf("%d",&choose_number),choose_number) {
			case 1: //��ʾ�ƶ��˵�
				printf("Ҫȥ����?\n\n\n");
				system("color 8E");
				cout<<"1,С֣�Ӿư�  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"2,ŵ�Ƿ��۾Ƶ�  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"3,�����̻�  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"4,����������  ";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"5,ð�ջ�Ұ\n\n\n";
				Sleep(150);
				system("color 8E");
				if(sheng==1) Beep(1200,100);
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						place_sign=place.bar; //��¼Ŀǰλ��-�ư�
						break;
					case 2:
						place_sign=place.hotel; //�����õ�
						printf("��ң�%d",money);
						system("color 8E");
						printf("Ҫ������? 200����� \n 1,�� 0,��\n\n\n");
						system("color 8E");
						if(sheng==1) Beep(1200,100);
						choose_number=1;
						switch(scanf("%d",&choose_number),choose_number) {
							case 1:
								if(money-200<=0) { //�ж�Ǯ�Ƿ�
									printf("Sorry,���Ǯ����~\n\n\n");
									system("color 8E");
									printf("��ң�%d",money);
									system("color 8E");
								} else {
									printf("�ú���Ϣ\nHP��\n�ڶ�����\n\n");
									system("color 8E");
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									system("color 8E");
									money-=200; //����200ס���
									player.health=player.max_health; //������
								}
								break;
							case 0:
								printf("�´�����!\n\n\n");
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
						printf("������Ҫ����ʲô���͵���Ʒ��\n\n\n");
						system("color 8E");
						if(sheng==1) Beep(1200,100);
						cout<<"1,����װ�� ";
						Sleep(50);
						cout<<"2,����װ�� ";
						Sleep(50);
						cout<<"3,һ�����˺�����\n\n\n";
						Sleep(50);
						scanf("%d",&yongju);
						switch(yongju) {
							case 1:
								printf("������Ҫ����ʲô����?\n\n\n 1,ذ�ף�300 2�����󽣣�500 3����Ѫս����1000\n\n\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								scanf("%d",&gong);
								switch(gong) {
									case 1:
										if(money>=300) {
											gong1n++;
											money=money-300;
											printf ("ذ��+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("ذ��:%d��\n",gong1n);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
											break;
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
											break;
										}
									case 2:
										if(money>=500) {
											gong2n++;
											money=money-500;
											printf ("����+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("����:%d��\n",gong2n);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
											break;
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("��ң�%d\n",money);
											system("color 8E");
											break;
										}
									case 3:
										if(money>=1000) {
											gong3n++;
											money=money-1000;
											printf ("��Ѫս��+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("��Ѫս��:%d��\n",gong3n);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
											break;
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
											break;
										}
									default:
										printf("�Բ�������ֻ���������������");
										system("color 8E");
										break;
 
								}
								break;
							case 2:
								int fang;
								printf("������Ҫ����ʲô����?\n\n\n 1,���£�300 2���ۼף�500 3���ؼף�1000\n\n\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								scanf("%d",&fang);
								switch(fang) {
									case 1:
										if(money>=300) {
											fang1n++;
											money=money-300;
											printf ("����+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("����:%d��\n",fang1n);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										}
 
										break;
									case 2:
										if(money>=500) {
											fang2n++;
											money=money-500;
											printf ("�ۼ�+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("�ۼ�:%d��\n",fang2n);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d",money);
											system("color 8E");
										}
										break;
									case 3:
										if(money>=1000) {
											fang3n++;
											money=money-1000;
											printf ("�ؼ�+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("�ؼ�:%d��\n",fang3n);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										}
									default:
										printf("�Բ�������ֻ��������Ϸ��ߡ�");
										system("color 8E");
										break;
 
								}
								printf("��ң�%d\n",money);
								system("color 8E");
								break;
							case 3:
								printf("������Ҫ����ʲôһ�����˺�������\n 1,���� 2������ 3������ʽԭ�ӵ�\n\n\n");
								system("color 8E");
								int yi;
								scanf("%d",&yi);
								switch(yi) {
									case 1:
										if(money>=300 && boom<5) {
											boom++;
											money=money-300;
											printf("����+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("���ף�%d\n",boom);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d",money);
											system("color 8E");
										}
										break;
									case 2:
										if(money>=600 && dubiao<9999999) {
											dubiao++;
											money=money-600;
											printf("����+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("���ڣ�%d\n",dubiao);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										}
										break;
									case 3:
										if(money>=1000 && yuanzidan<5) {
											yuanzidan=yuanzidan+1;
											money=money-1000;
											printf("����ʽԭ�ӵ�+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
											printf("����ʽԭ�ӵ���%d\n",yuanzidan);
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										} else {
											printf("Ǯ����!\n\n\n");
											system("color 8E");
											printf("��ң�%d\n",money);
											system("color 8E");
										}
 
										break;
								}
						}
						break;
					case 4:
						if(sheng==1) Beep(1200,100);
						printf ("��ӭ�����ٱ������У�������Ҫ��ʲô������\n\n");
						system("color 8E");
						printf("����װ��: 1,ذ��:%d�� 2,����:%d�� 3,����ʯ��:%n 4,��Ѫս��:%d�� 5,֩�붾��:%n�� 6,�з�����:%d�� 7,Ƥ���󽣣�%d��\n",gong1n,gong2n,gong7n,gong3n,gong6n,gong4n,gong5n);
						system("color 8E");
						printf("����װ��: 8,����:%d�� 9,�ۼ�:%d�� 10,ս�����:%d�� 11,�ؼ�:%d�� 12,ʯ����:%d�� 13,��˵ʥ��:%d�� 14,��������%d�� 15��������ʯ:%d��\n 0,����\n\n\n",fang1n,fang2n,fang7n,fang3n,fang6n,fang4n,fang5n,strongman_arm);
						system("color 8E");
						int pai,shu,i;
						scanf("%d",&pai);
						system("color 8E");
						switch(pai) {
							case 1:
								printf("������Ҫ���ۼ�����");
								system("color 8E");
								scanf("%d",&shu);
								if(gong1n>=shu) {
									gong1n=gong1n-shu;
									money=money+shu*240;
									printf("ذ�ף�%d\n",gong1n);
									system("color 8E");
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									system("color 8E");
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									system("color 8E");
									break;
								}
								break;
							case 2:
								printf("������Ҫ���ۼ�����\n");
								system("color 8E");
								scanf("%d",&shu);
								if(gong2n>=shu) {
									gong2n=gong2n-shu;
									money=money+shu*400;
									printf("���󽣣�%d\n",gong2n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 3:
								printf("������Ҫ���ۼ�����\n");
								system("color 8E");
								scanf("%d",&shu);
								if(gong7n>=shu) {
									gong7n=gong7n-shu;
									money=money+shu*800;
									printf("����ʯ����%d\n",gong7n);
									printf("��ң�%d\n",money);
									if(sheng==1) Beep(1200,100);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 4:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(gong3n>=shu) {
									gong3n=gong3n-shu;
									money=money+shu*800;
									printf("��Ѫս����%d\n",gong3n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 5:
								printf("������Ҫ���ۼ�����\n");
								system("color 8E");
								scanf("%d",&shu);
								if(gong6n>=shu) {
									gong6n=gong6n-shu;
									money=money+shu*1000;
									printf("֩�붾����%d\n",gong6n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 6:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(gong4n>=shu) {
									gong4n=gong4n-shu;
									money=money+shu*1500;
									printf("�з�������%d\n",gong4n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 7:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(gong5n>=shu) {
									gong5n=gong5n-shu;
									money=money+shu*3000;
									printf("Ƥ���󽣣�%d\n",gong5n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 8:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang1n>=shu) {
									fang1n=fang1n-shu;
									money=money+shu*240;
									printf("���£�%d\n",fang1n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 9:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang2n>=shu) {
									fang2n=fang2n-shu;
									money=money+shu*500;
									printf("�ۼף�%d\n",fang2n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 10:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang7n>=shu) {
									fang7n=fang7n-shu;
									money=money+shu*1000;
									printf("ս����ף�%d\n",fang7n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 11:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang3n>=shu) {
									fang3n=fang3n-shu;
									money=money+shu*800;
									printf("�ؼף�%d\n",fang3n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
								break;
							case 12:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang6n>=shu) {
									fang6n=fang6n-shu;
									money=money+shu*2000;
									printf("ʯ���ף�%d\n",fang6n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 13:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang4n>=shu) {
									fang4n=fang4n-shu;
									money=money+shu*1500;
									printf("��˵ʥ�ף�%d\n",fang4n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
 
							case 14:
								printf("������Ҫ���ۼ�����\n");
								scanf("%d",&shu);
								if(fang5n>=shu) {
									fang5n=fang5n-shu;
									money=money+shu*3000;
									printf("��������%d\n",fang5n);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
									break;
								} else {
									printf("װ�����������޷����ۣ�\n");
									break;
								}
							case 15:
								printf("������Ҫ���ۼ��ţ�");
								scanf("%d",&shu);
								if(strongman_arm>=shu) {
									strongman_arm=strongman_arm-shu;
									money=money+shu*4000;
									printf("������ʯ��%d\n",strongman_arm);
									if(sheng==1) Beep(1200,100);
									printf("��ң�%d\n",money);
								} else {
									printf("��ʯ���������޷����ۣ�\n");
									break;
								}
								break;
							case 0:
								break;
								break;
							default:
								printf("û�и�װ�����޷����ۣ�\n");
								break;
						}
						break;
					case 5:
						int yewai;
						while(1) {
							puts("=============================================================================");
							printf("Ҫȥ��ð���أ�");
							system("color 8c");
							if(sheng==1) Beep(1200,100);
							printf("\n\n");
							cout<<"1,�������� Σ�ճ̶�:��\n\n";
							Sleep(50);
							system("color 8c");
							cout<<"2,��ҫ��ԭ Σ�ճ̶�:����\n\n";
							Sleep(50);
							cout<<"3,����ɭ�� Σ�ճ̶�:����\n\n";
							Sleep(50);
							cout<<"4,��Į�� Σ�ճ̶�:�����\n\n";
							Sleep(50);
							cout<<"5,�����׶� Σ�ճ̶�:������\n\n";
							Sleep(50);
							cout<<"6,Ƥ��Ӫ�� Σ�ճ̶�:�������\n\n";
							Sleep(50);
							cout<<"7,���乬�� Σ�ճ̶�:�������\n\n";
							Sleep(50);
							cout<<"8,������Ѩ Σ�ճ̶�:��������\n\n";
							Sleep(50);
							cout<<"9,�������� Σ�ճ̶�:���������\n\n";
							Sleep(50);
							cout<<"0,�뿪\n";
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
											printf("%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<9) {
											guai=witch;
											printf("%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else {
											printf("���ﰲȫ\n\n\n");
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
											printf("%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<7) {
											battle=1;
											guai=strongman;
											printf("���ֱײ��%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else {
											battle=1;
											guai=zhizhu;
											printf("���µ�%s���˹���!\n\n\n",guai.name);
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
											printf("���ֱײ��%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<5) {
											guai=huolong;
											printf("���ȵ�%s�Ĵ��ų�����˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<8) {
											guai=gl;
											printf("ȫ������ʯ��%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else {
											guai=zhizhu;
											printf("���µ�%s�����˹���!\n\n\n",guai.name);
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
											printf("%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<5) {
											battle=1;
											guai=horse;
											printf("%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<8) {
 
											guai=ymr;
											printf("���ֱײ��%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else {
 
											guai=nz;
											printf("˧�������������%s���㿪ǹ!\n\n\n",guai.name);
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
											printf("%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<7) {
											guai=lion;
											printf("%s�����з�������ס����!\n\n\n",guai.name);
											BattleAct();
										} else {
											guai=gl;
											printf("ȫ������ʯ��%s���˹���!\n\n\n",guai.name);
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
											printf("��е���ǿ�ҵĵ���ӿ��ȫ��%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<9) {
											guai=dapika;
											printf("���һ�����죬������������%s�����ϣ�%s�ֳ�����֮�г��˹���!\n\n\n",guai.name,guai.name);
											BattleAct();
										} else {
											printf("���ﰲȫ\n\n\n");
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
											printf("һ���������Զ��ڣ��㶨��һ������%s���˹���!\n\n\n",guai.name);
											BattleAct();
										} else if(s<=8 && s>=4) {
 
											guai=huolong;
											printf("���ȵ�%s�Ĵ��ų�����˹���!\n\n\n",guai.name);
											BattleAct();
										} else {
 
											guai=jl;
											printf("һ����������ķ����������У����Ǵ�˵�е�%s���˹���!\n\n\n",guai.name);
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
											printf("%s�����з�������ס����!\n\n\n",guai.name);
											BattleAct();
										} else if(s<7||boss1==0) {
 
											if(strongman_arm>=1) {
												printf("��������:\n\n\n ����,������,���Ĳ���,����...�ٺ�,���ϵ���!������ʯ��Ҫ��,������Ҳ�������!\n\n\n");
												guai=bossno1;
												printf("˲�䣬�㱻һ�ź������֣��㱻�����˵���þ���%s���㷢�𹥻�!\n\n\n",guai.name);
												BattleAct();
											} else printf("��������:\n\n\n ������,��ð�.������о�����ʯ,�ҿ��Ը����㹫��������Ŷ~\n\n\n");
										} else {
 
											guai=nz;
											printf("˧�������������%s���㿪ǹ!\n\n\n",guai.name);
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
												printf("һ���޴�ĺڰ����壬��Χ�����Ŵ����������鷽����ɵĺ�ɫ�����ƻ���%s���㷢�𹥻�!\n\n\n",guai.name);
												BattleAct();
											} else if(s>=2 && s<=4) {
												guai=dlkl;
												printf("�ֳֵ��㽣�ĺ�ɫ�׶�%s���˹���!\n\n\n",guai.name);
												BattleAct();
											} else if(s>=5&&s<=7) {
												guai=gst;
												printf("һ���޴�Ĵ�������������㵲������%s���˹���!\n\n\n",guai.name);
												BattleAct();
											} else {
												guai=dljs;
												printf("һֻ�޴������%s���˹���!\n\n\n",guai.name);
												BattleAct();
											}
										}
										if(diaolingxinhave==0) {
											cout<<"��û�л��ܹ�����Ů�ף���ȥ���乬����ܵ���Ů�ס�" <<endl;
										}
									}
 
									break;
									if(yewai!=0) {
										system("cls");
										printf("������Ϊδ֪�����޷����롣\n\n\n");
										system("color 8E");
										break;
									}
							}
							if(yewai==0) {
								system("cls");
								break;
								printf("���뿪��Ұ��");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
							}
						}
 
				}
				break;
 
			case 2:
				ChooseWupin();
				break; //��ʾ����,������ʹ��.
			case 3: //�Ի�ѡ��
				if(sheng==1) Beep(1200,100);
				if(place_sign==place.bar) {
					printf("Ҫ��˭˵��?\n\n\n1,�췢Ů�� 2,�ͽ����� 3,�ư��ϰ� 4,ҩƷ����\n\n\n");
					system("color 8E");
					if(sheng==1) Beep(1200,100);//��ʾ�Ի�����
					switch(scanf("%d",&choose_number),choose_number) {
						case 1:
							printf("�췢Ů��:\n\n\n ��̨���Ǹ�Hunter��˧��!(~����~)\n\n\n��˵�������������,�����·��Ӧ�ú���Ϥ��!\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							break;
						case 2:
							if(fang1n<1&&gong1n<1) {
								printf("�ͽ�����:\n\n\n ��Ҫ�ȹ�����!�õ���!\n\n\n ���������������ն�,����Խ��ԽΣ��,����ذ�׺Ͳ���,�������Щ������,��ȥ��!\n\n\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								printf("%s����:��,��λ��������ð�!\n\n\n)",player.name);
								gong1n++;
								fang1n++;
							} else printf("�ͽ�����:\n\n\n ���Ͱ�,������!\n\n\n ��Ҫ�������������ŵ�!\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							break;
						case 3:
							printf("Ҫ�ȵ�ʲô?\n\n\n 1,����ͷ25��� HP+20 2,���ؼ�80��� HP+50 3,��ͷ����150��� HP+100 0,����\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							choose_number=1;
							while(choose_number) {
								switch(scanf("%d",&choose_number),choose_number) {
									case 1:
										if(money<25) {
											printf("Ǯ����!");
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
												printf("HP����");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												player.health=player.max_health;
											}
										}
										break;
									case 2:
										if(money<80) {
											printf("Ǯ����!");
											system("color 8E");
										} else {
											if(player.health+50<=player.max_health) {
												printf("HP+50.");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												money-=80;
												player.health+=50;
											} else {
												printf("HP����");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												player.health=player.max_health;
											}
										}
										break;
									case 3:
										if(money<150) {
											printf("Ǯ����!");
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
												printf("HP����");
												system("color 8E");
												if(sheng==1) Beep(1200,100);
												player.health=player.max_health;
											}
										}
										break;
									case 0:
										printf("�´�����!\n");
										system("color 8E");
										break;
									default:
										printf("�������\n\n\n");
										system("color 8E");
										break;
								}
								break;
							}
							break;
						case 4:
							printf("��Ҫ��ʲô��\n\n\n 1������ 2������ \n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							int mai;
							scanf("%d",&mai);
							if(mai==1) {
								printf("���ʲô�أ�\n1,ֹѪ�ݣ�100 HP+60\n2�����Ȱ���150 HP+80 \n3�����ϰ�ҩ��250 HP+120\n4���������ϰ�ҩ��400 HP+200 \n5������ݣ�150 ����+300 \n6���������600 ����+600\n7������ʯ��500 ����+1000 \n0,�ݰ�\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								int dongxi;
								scanf("%d",&dongxi);
								switch(dongxi) {
									case 1:
										if(money>=100&&cao<6) {
											cao++;
											money=money-100;
											printf ("ֹѪ��+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
									case 2:
										if(money>=150&&jijiubao<10) {
											jijiubao++;
											money=money-150;
											printf ("���Ȱ�+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
									case 3:
										if(money>=250&&baiyao<10) {
											baiyao++;
											money=money-250;
											printf ("���ϰ�ҩ+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
									case 4:
										if(money>=400&&superbaiyao<10) {
											superbaiyao++;
											money=money-400;
											printf ("�������ϰ�ҩ+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
 
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
									case 5:
										if(money>=150) {
											jingyancao++;
											money=money-150;
											printf ("�����+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
									case 6:
										if(money>=300) {
											jingyanbao++;
											money=money-300;
											printf ("�����+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
									case 7:
										if(money>=500) {
											jingyanshi++;
											money=money-500;
											printf ("����ʯ+1\n");
											system("color 8E");
											if(sheng==1) Beep(1200,100);
										} else {
											printf("Ǯ����!\n");
											system("color 8E");
										}
										break;
								}
							case 0:
								printf("��ң�%d\n",money);
								system("color 8E");
								printf("�ټ�����ӭ�´�������\n");
								system("color 8E");
								if(sheng==1) Beep(1200,100);
								break;
 
							}
							if(mai==2) {
								printf("ҩƷ���ˣ�ȥȥȥ������ûʱ�������ġ�\n");
								system("color 8E");
							}
					}
				} else if(place_sign==place.hotel)
					printf("���ϰ���!��...��\n\n\n����æ���أ�û������~��\n\n\n");
				else printf("�������û�˿�������\n\n\n");
				system("color 8E");
				break;
			case 4:
				DisplayState();
				break; //��ʾ״̬
			case 5: //װ��
				if(sheng==1) Beep(1200,100);
				printf("����װ��: 1,ذ��:%d�� 2,����:%d�� 3,����ʯ��:%d�� 4,��Ѫս��:%d�� 5,֩�붾��:%d�� 6,�з�����:%d�� 7,����֮�У�%d�� 8,X�з�����X��%d�� 9,����֮����%d��\n\n\n",gong1n,gong2n,gong7n,gong3n,gong6n,gong4n,gong5n,gong4Xn,mgongn);
				system("color 8E");
				printf("����װ��: 10,����:%d�� 11,�ۼ�:%d�� 12,ս�����:%d�� 13,�ؼ�:%d�� 14,ʯ����:%d�� 15,��˵ʥ��:%d�� 16,������:%d�� 17,X��˵ʥ��X:%d�� 18,����֮��:%d��\t\t0,����\n\n\n",fang1n,fang2n,fang7n,fang3n,fang6n,fang4n,fang5n,fang4Xn,mfangn);
				system("color 8E");
				printf("ѡ��Ҫװ�������������:\n\n\n");
				system("color 8E");
				switch(scanf("%d",&choose_number),choose_number) {
					case 1:
						if(gong1n>=1) {
							printf("������ذ��\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							gong=gong1;
							strcpy(gongname,"ذ��");
							system("color 8E");
						} else printf("��û��ذ�׿���װ��\n\n\n");
						system("color 8E");
						break;
					case 2:
						if(gong2n>=1) {
							printf("����������\n\n\n");
							system("color 8E");
							if(sheng==1) Beep(1200,100);
							gong=gong2;
							strcpy(gongname,"����");
							system("color 8E");
						} else printf("��û�����󽣿���װ��\n\n\n");
						system("color 8E");
						break;
					case 3:
						if(gong7n>=1) {
							printf("�����˴���ʯ��\n\n\n");
							gong=gong7;
							strcpy(gongname,"����ʯ��");
						} else printf("��û�д���ʯ������װ��\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 4:
						if(gong3n>=1) {
							printf("�����˱�Ѫս��\n\n\n");
							gong=gong3;
							strcpy(gongname,"��Ѫս��");
						} else printf("��û�б�Ѫս������װ��\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 5:
						if(gong6n>=1) {
							printf("������֩�붾��\n\n\n");
							gong=gong6;
							strcpy(gongname,"֩�붾��");
						} else printf("��û��֩�붾������װ��\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 6:
						if(gong4n>=1) {
							printf("�������з�����\n\n\n");
							gong=gong4;
							strcpy(gongname,"�з�����");
						} else printf("��û���з���������װ��\n\n\n");
						if(sheng==1) Beep(1200,100);
						break;
					case 7:
						if(gong5n>=1) {
							printf("����������֮��\n\n\n");
							if(sheng==1) Beep(1200,100);
							gong=gong5;
							strcpy(gongname,"����֮��");
						} else printf("��û������֮�п���װ��\n\n\n");
						break;
					case 8:
						if(gong4Xn>=1) {
							printf("������X�з�����X\n\n\n");
							if(sheng==1) Beep(1200,100);
							gong=gong4X;
							strcpy(gongname,"X�з�����X");
						} else printf("��û��X�з�����X����װ��\n\n\n");
						break;
					case 9:
						if(mgongn>=1) {
							printf("����������֮��\n\n\n");
							if(sheng==1) Beep(1200,100);
							gong=mgong;
							strcpy(gongname,"����֮��");
						} else printf("��û������֮������װ��\n\n\n");
						break;
					case 10:
						if(fang1n>=1) {
							printf("�����˲���\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang1;
							strcpy(fangname,"����");
						} else printf("��û�в��¿���װ��\n\n\n");
						break;
					case 11:
						if(fang2n>=1) {
							printf("�������ۼ�\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang2;
							strcpy(fangname,"�ۼ�");
						} else printf("��û���ۼ׿���װ��\n\n\n");
						break;
					case 12:
						if(fang7n>=1) {
							printf("������ս�����\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang7;
							strcpy(fangname,"ս�����");
						} else printf("��û��ս����׿���װ��\n\n\n");
						break;
					case 13:
						if(fang3n>=1) {
							printf("�������ؼ�\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang3;
							strcpy(fangname,"�ؼ�");
						} else printf("��û���ؼ׿���װ��\n\n\n");
						break;
					case 14:
						if(fang6n>=1) {
							printf("������ʯ����\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang6;
							strcpy(fangname,"ʯ����");
						} else printf("��û��ʯ���׿���װ��\n\n\n");
						break;
					case 15:
						if(fang4n>=1) {
							if(sheng==1) Beep(1200,100);
							printf("�����˴�˵ʥ��\n\n\n");
							fang=fang4;
							strcpy(fangname,"��˵ʥ��");
						} else printf("��û�д�˵ʥ�׿���װ��\n\n\n");
						break;
					case 16:
						if(fang5n>=1) {
							printf("�����˽�����\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang5;
							strcpy(fangname,"������");
						} else printf("��û�н���������װ��\n\n\n");
						break;
					case 17:
						if(fang4Xn>=1) {
							printf("������X��˵ʥ��X\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=fang4X;
							strcpy(fangname,"X��˵ʥ��X");
						} else printf("��û��X��˵ʥ��X����װ��\n\n\n");
						break;
					case 18:
						if(mfangn>=1) {
							printf("����������֮��\n\n\n");
							if(sheng==1) Beep(1200,100);
							fang=mfang;
							strcpy(fangname,"����֮��");
						} else printf("��û������֮�׿���װ��\n\n\n");
						break;
					case 0:
						printf("δ����װ��\n\n\n");
						break;
					default:
						printf("change error!");
				}
				break;
			case 6:
				if(sheng==1) Beep(1200,100);
				printf(" ���ã���ӭ���涷�Ʋ�񷣨������磩��");
				cout<<"Ϊ�˸������õ���Ϸ���飬";
				Sleep(250);
				cout<<"ztyʱ��ʱ���Ż�����Ϸ��";
				Sleep(250);
				cout<<"�Ż���ᾡ�췢�������ϡ�";
				Sleep(250);
				cout<<"������ҷ��棬";
				Sleep(250);
				cout<<"������ҵķ�ʽ���趨��������ʱ��";
				Sleep(250);
				cout<<"����";
				Sleep(250);
				cout<<"��";
				Sleep(250);
				cout<<"6";
				Sleep(250);
				cout<<"6";
				Sleep(250);
				cout<<"6";
				Sleep(250);
				cout<<"��";
				Sleep(250);
				cout<<"��������˫���ţ���";
				Sleep(250);
				cout<<"������";
				Sleep(250);
				cout<<"2.";
				Sleep(250);
				cout<<"11.";
				Sleep(250);
				cout<<"5";
				Sleep(250);
				cout<<"�汾����";
				Sleep(250);
				cout<<"�Ļ����Ͻ�����ӣ�";
				Sleep(250);
				cout<<"��Ҫ����Ϊ���������ͽ��˳���Ϸ�ĵ����������滹������������ǲ���ֹͣս��";
				Sleep(250);
				cout<<"�Ѹ�����ϣ�";
				Sleep(250);
				cout<<"ϣ�����ϲ����";
				cout<<"\n\n";
				Sleep(250);
				system("color 8E");
				break;
			case 8:
				if(sheng==1) Beep(1200,100);
				printf("�ϳ�̨��                   0:�˳�\n\n");
				system("color 8E");
				cout<<"����֮��:"<<mingshu<<"\n1�� ����֮��   ��Ҫ���ϣ�1*X�з�����X + 3*����֮��\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"2��X�з�����X  ��Ҫ���ϣ�1* �з�����  + 1*����֮��\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"3�� ����֮��   ��Ҫ���ϣ�1*X��˵ʥ��X + 3*����֮��\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"4��X��˵ʥ��X  ��Ҫ���ϣ�1* ��˵ʥ��  + 1*����֮��\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"5�� ����ը��   ��Ҫ���ϣ�5*����ԭ�ӵ� + 3*����֮��\n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"6��  ������    ��Ҫ���ϣ�5*����  \n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cout<<"7��   �ۼ�     ��Ҫ���ϣ�5*��Ƭ  \n\n";
				Sleep(150);
				if(sheng==1) Beep(1200,100);
				cin>>he;
				if(he==1)
					if(he==1&&gong4Xn>=1&&mingshu>=3) {
						gong4Xn--;
						mingshu-=3;
						mgongn++;
						cout<<"��ϲ�������֮��\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==2)
					if(he==2&&gong4n>=1&&mingshu>=1) {
						gong4n--;
						mingshu--;
						gong4Xn++;
						cout<<"��ϲ���X�з�����X\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==3)
					if(he==3&&fang4Xn>=1&&mingshu>=3) {
						fang4Xn--;
						mingshu-=3;
						mfangn++;
						cout<<"��ϲ�������֮��\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==4)
					if(he==4&&fang4n>=1&&mingshu>=1) {
						fang4n--;
						mingshu--;
						fang4Xn++;
						cout<<"��ϲ���X��˵ʥ��X\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==5)
					if(he==5&&yuanzidan>=5&&mingshu>=3) {
						yuanzidan-=5;
						mingshu-=3;
						zhadan++;
						cout<<"��ϲ��û���ը��\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==6)
					if(he==6&&ll>=5) {
						ll-=5;
						fang5n++;
						cout<<"��ϲ��ý�����\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==7)
					if(he==7&&lp>=5) {
						lp-=5;
						fang2n++;
						cout<<"��ϲ����ۼ�\n";
						if(sheng==1) Beep(1200,100);
					} else cout<<"���ϲ���\n\n";
				if(he==0) break;
				break;
			case 9:
				system("cls");
				cout<<"����        0:�˳�\n\n";
				cout<<"1:���� ";
				if(sheng==1) cout<<"��\n";
				else cout<<"��\n";
				cout<<"\n2:UI���� ";
				if(ui==1) cout<<"�ϰ�";
				else cout<<"�°�";
				cout<<"\n\n3,�˳���Ϸ";
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
					printf("ȷ���˳���Ϸ?(Y/N)\n\n\n");
					system("color 8E");
					getchar();
					proof=getchar();
					if(proof=='y'||proof=='Y') {
						printf("���س��˳�");
						system("color 8E");
						getchar();
						return;
					} else if(proof=='n'||proof=='N')printf("������Ϸ!\n\n\n");
					else printf("����!\n\n\n");
				}
				if(shen==0) break;
				break;
			case 7:
				if(sheng==1) Beep(1200,100);
				int mi;
				cout<<"============================*����̨ ���� ����Bug��*=============================\n���룺";
				cin>>mi;
				if(mi%20120913==0&&mi!=0) {
					cout<<"������ȷ����ӭ�����̨��\n\n=================================================\n��̨����\n\n1.��Ҽ�999999\n\n2.Ѫ�����޼�9999\n\n3.����Ѫ����9999\n\n4.������9999\n\n5.������9999\n\n0.�˳�\n\n=================================================\n\n "<<endl;
					cin>>htsr;
					if(htsr==1) {
						cout<<"�ɹ����Ч�� *��Ҽ�999999\n";
						if(sheng==1) Beep(1200,100);
						money+=999999;
					}
					if(htsr==2) {
						cout<<"�ɹ����Ч�� *Ѫ����9999\n";
						if(sheng==1) Beep(1200,100);
						player.health+=9999;
					}
					if(htsr==3) {
						cout<<"�ɹ����Ч�� *Ѫ�����޼�9999\n";
						if(sheng==1) Beep(1200,100);
						player.max_health+=9999;
					}
					if(htsr==4) {
						cout<<"�ɹ����Ч�� *������9999\n";
						if(sheng==1) Beep(1200,100);
						player.attack+=9999;
					}
					if(htsr==5) {
						cout<<"�ɹ����Ч�� *������9999\n";
						if(sheng==1) Beep(1200,100);
						player.defense+=9999;
					}
					if(htsr==0) {
						cout<<"�ɹ��˳�\n";
						if(sheng==1) Beep(1200,100);
						continue;
					}
				} else {
					cout<<"����������飡"<<endl;
					continue;
				}
				break;
			case 10:
				system("cls");
				printf("��Ʒ:ֹѪ��:%d�� ���Ȱ�:%d�� ���ϰ�ҩ:%d�� �������ϰ�ҩ:%d�� ����:%d�� ����:%d�� ����ʽԭ�ӵ�:%d�� �����:%d�������:%d�� ����ʯ:%d�� ������ʯ:%d�� ��������:%d�� ����֮��:%d�� ����ը��:%d�� \n�ϳɲ���:��Ƭ:%d�� ����:%d�� ����֮��:%d��\n",cao,jijiubao,baiyao,superbaiyao,boom,dubiao,yuanzidan,jingyancao,jingyanbao,jingyanshi,strongman_arm,miansi,diaolingxin,zhadan,lp,ll,mingshu);
				printf("����װ��: ذ��:%d�� ����:%d�� ����ʯ��:%d�� ��Ѫս��:%d�� ֩�붾��:%d�� �з�����:%d�� ����֮�У�%d�� X�з�����X��%d�� ����֮����%d��\n",gong1n,gong2n,gong7n,gong3n,gong6n,gong4n,gong5n,gong4Xn,mgongn);
				system("color 8E");
				printf("����װ��: ����:%d�� �ۼ�:%d�� 12,ս�����:%d�� �ؼ�:%d�� ʯ����:%d�� ��˵ʥ��:%d�� ������:%d�� X��˵ʥ��X:%d�� ����֮��:%d��\t\t\n\n\n",fang1n,fang2n,fang7n,fang3n,fang6n,fang4n,fang5n,fang4Xn,mfangn);
				system("color 8E");
				system("pause");
				break;
		}
	}
}
void DisplayState() {
	printf("%s ������:%d+%d=%d ������:%d+%d=%d HP:%d/%d \n\n\n",player.name,player.attack,gong,player.attack+gong,player.defense,fang,player.defense+fang,player.health,player.max_health);
	printf("����: %s ����: %s \n\n\n",gongname,fangname);
	printf("�ȼ�:%d ����:%d/%d ����Ҫ%d�������� ���:%d \n\n\n",player.level,player.exp,player.max_exp,player.max_exp-player.exp,money);
	system("pause");
}
void BattleAct() {
	while(1) {
		puts("=============================================================================");
		if(sheng==1) Beep(1200,100);
		printf("Ҫ��ô��?\n\n\n 1,���� 2,ʹ����Ʒ 3,�鿴״̬ 4,����\n\n\n");
		switch(scanf("%d",&choose_number),choose_number) {
			case 1:
				s=SuiJi();
				printf("%s����! %sHP����%d\n\n\n",player.name,guai.name,player.attack+s+gong-guai.defense/3);
				guai.health-=player.attack+s+gong-guai.defense/3;
				if(AttackResult())return; //��������н��(���˻����ս��)�˳�����
				else continue;
			case 2:
				ChooseWupin();
				break; //ѡ����Ʒ,����ʹ��,ս��������ʹ�ù�������Ʒ
			case 3:
				DisplayState();
				break; //��ʾ״̬
			case 4:
				s=SuiJi();
				if(s<4) { //40%�ĸ��ʿ�������
					printf("%s������~\n\n\n",player.name);
					if(sheng==1) Beep(1200,100);
					battle=0;
					return;
				} else printf("%s����ʧ��!\n\n\n",player.name);
				if(sheng==1) Beep(200,100);
				break;
			default:
				printf("�������,��������!\n\n\n");
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
Servers Location��������������������������������������������������������������������������������������������������������������������������������������������������                                           ���� timer                   1         41      ��
��                                                                                        ����                                           ���� node                    2         52      ��
��                                 ??                                                     ����                                           ���� gulp                    2         52      ��
��               ??????????????????  ?????    ?????  ??????    ??????     ???             ����                                           ���� java                    3         73      ��
��  ?????????????????????????????  ?????? ?    ????????????????    ?????????????????      ����   9      2      4      6      5      9    ���� grep                    1         16      ��
��  ?? ???????????????????????? ????  ??? ?? ?? ??????                    ??????????      ����   US1    US2    EU1    AU1    AS1    JP1  ���� netns                   0         45      ��
��   ????     ????   ????????????        ????????                         ??  ?? ??       ��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
��              ?  ?   ??????????         ??????????? ?? ?  ??        ? ????              ������Server Log����������������������������������������Percent Donut����������������������������������Storage������������������������������������������
��              ???       ??             ???????????  ??             ??????               ����starting process watchdog   ����                            ����                            ��
��                ??? ??????            ??     ??  ?? ??????         ??                   ����starting process node       ����           ?????            ����                            ��
��       ?          ??????????          ?           ?????  ? ????? ?? ??                  ����avg. wait time 0.52         ����        ????????????        ����                            ��
��                      ?????????       ?????        ???    ??  ???? ???                  ����avg. wait time 0.47         ����       ????     ?????       ����    37%          63%        ��
��                     ?  ?     ???          ??    ? ?           ?????  ???               ����avg. wait time 0.79         ����      ???         ????      ����                            ��
��                        ??       ??         ??    ? ?            ???  ??????            ����terminating server EU1      ����      ??     57%   ???      ��������������������������������������������������������������
��    ?                    ??      ?          ??   ????              ???? ???   ?  ?      ����terminating server AU1      ����      ???          ???      ��
��                          ?   ????           ?  ?? ??              ?      ??            ����terminating server US1      ����      ?????      ????       ������Throughput (bits/sec)��������������
��                         ?? ???              ????                  ?????????   ??       ����starting process tar -xvf   ����       ?????????????        ����                            ��
��                         ? ??                                            ??   ???       ����avg. wait time 0.65         ����          ????????          ����Server1:                    ��
��                         ?????                                                          ����starting process tar -xvf   ����           storage          �����x�}���}�{���}�y�}�y���y�}�����x���{�}�x�}�y�y�x���{�x�{��
��                                                                                        ����terminating server US2      ����                            ����                            ��
��                                                                                        ����terminating server JP1      ����                            ����Server2:                    ��
��                                                                                       
*/
