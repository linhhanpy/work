#include <iostream>
#include <memory.h>
#include <math.h>
#include<windows.h>
#include<winuser.h>
#include<conio.h>
#include <stdlib.h>
#include <stdio.h>
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s on line %d\n", __FILE__, GetLastError(), api, __LINE__);}
#pragma once

namespace color//�����ռ�Ϊcolor����ֹ���ֳ�ͻ
{
    //��ɫ�������壬��Ϊ���룬ǰ��ɫ������ɫ
    static const WORD bgMask(BACKGROUND_BLUE |
        BACKGROUND_GREEN |
        BACKGROUND_RED |
        BACKGROUND_INTENSITY);
    static const WORD fgMask(FOREGROUND_BLUE |
        FOREGROUND_GREEN |
        FOREGROUND_RED |
        FOREGROUND_INTENSITY);

    static const WORD fgBlack(0);
    static const WORD fgLoRed(FOREGROUND_RED);
    static const WORD fgLoGreen(FOREGROUND_GREEN);
    static const WORD fgLoBlue(FOREGROUND_BLUE);
    static const WORD fgLoCyan(fgLoGreen | fgLoBlue);
    static const WORD fgLoMagenta(fgLoRed | fgLoBlue);
    static const WORD fgLoYellow(fgLoRed | fgLoGreen);
    static const WORD fgLoWhite(fgLoRed | fgLoGreen | fgLoBlue);
    static const WORD fgGray(fgBlack | FOREGROUND_INTENSITY);
    static const WORD fgHiWhite(fgLoWhite | FOREGROUND_INTENSITY);
    static const WORD fgHiBlue(fgLoBlue | FOREGROUND_INTENSITY);
    static const WORD fgHiGreen(fgLoGreen | FOREGROUND_INTENSITY);
    static const WORD fgHiRed(fgLoRed | FOREGROUND_INTENSITY);
    static const WORD fgHiCyan(fgLoCyan | FOREGROUND_INTENSITY);
    static const WORD fgHiMagenta(fgLoMagenta | FOREGROUND_INTENSITY);
    static const WORD fgHiYellow(fgLoYellow | FOREGROUND_INTENSITY);
    static const WORD bgBlack(0);
    static const WORD bgLoRed(BACKGROUND_RED);
    static const WORD bgLoGreen(BACKGROUND_GREEN);
    static const WORD bgLoBlue(BACKGROUND_BLUE);
    static const WORD bgLoCyan(bgLoGreen | bgLoBlue);
    static const WORD bgLoMagenta(bgLoRed | bgLoBlue);
    static const WORD bgLoYellow(bgLoRed | bgLoGreen);
    static const WORD bgLoWhite(bgLoRed | bgLoGreen | bgLoBlue);
    static const WORD bgGray(bgBlack | BACKGROUND_INTENSITY);
    static const WORD bgHiWhite(bgLoWhite | BACKGROUND_INTENSITY);
    static const WORD bgHiBlue(bgLoBlue | BACKGROUND_INTENSITY);
    static const WORD bgHiGreen(bgLoGreen | BACKGROUND_INTENSITY);
    static const WORD bgHiRed(bgLoRed | BACKGROUND_INTENSITY);
    static const WORD bgHiCyan(bgLoCyan | BACKGROUND_INTENSITY);
    static const WORD bgHiMagenta(bgLoMagenta | BACKGROUND_INTENSITY);
    static const WORD bgHiYellow(bgLoYellow | BACKGROUND_INTENSITY);
    //������ɫ��ʵ�ֺ�������Ҫ�ǵ���win32��API��һЩλ���㡣
    void setConsoleColor(WORD mask, WORD c)
    {
        static HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        if(hStdout==NULL)return;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hStdout, &csbi);
        csbi.wAttributes &= ~mask;
        csbi.wAttributes |= c;
        SetConsoleTextAttribute(hStdout, csbi.wAttributes);
    }
    //�õ�ģ����Ϊ��ͨ�ã�����cout,cerr����Ⱦɫ��wcout��wcerr��Ҳ������ɫ���Լ��������ֻҪ����ģ�嶼���ԡ�
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_white(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgLoWhite);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_blue(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgHiBlue);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_green(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgHiGreen);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_red(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgHiRed);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_cyan(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgHiCyan);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_magenta(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgHiMagenta);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_yellow(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgHiYellow);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& fg_black(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(fgMask, fgBlack);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_white(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgLoWhite);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_blue(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgHiBlue);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_green(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgHiGreen);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_red(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgHiRed);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_cyan(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgHiCyan);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_magenta(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgHiMagenta);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_yellow(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgHiYellow);
        return os;
    }
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& bg_black(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgBlack);
        return os;
    }
    //�����Ļ����ԭ��ɫ
    template<typename charT, typename traits>
    inline std::basic_ostream<charT, traits>& clr(std::basic_ostream<charT, traits>& os)
    {
        os.flush();
        setConsoleColor(bgMask, bgBlack);
        setConsoleColor(fgMask, fgLoWhite);
        system("cls");
        return os;
    }
}


void MyCls(HANDLE) ;
void clrscr(void)
{
HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
MyCls(hStdOut);
return;
}
void MyCls(HANDLE hConsole)
{
COORD coordScreen={0,0};//�����������귵�ص���Ļ���Ͻ�����
BOOL bSuccess;
DWORD cCharsWritten;
CONSOLE_SCREEN_BUFFER_INFO csbi;//���滺������Ϣ
DWORD dwConSize;//��ǰ�����������ɵ��ַ���
bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//��û�������Ϣ
PERR(bSuccess,"GetConsoleScreenBufferInfo");
dwConSize=csbi.dwSize.X * csbi.dwSize.Y;//�����������ַ���Ŀ
//�ÿո���仺����
bSuccess=FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
PERR(bSuccess,"FillConsoleOutputCharacter");
bSuccess=GetConsoleScreenBufferInfo(hConsole,&csbi);//��û�������Ϣ
PERR(bSuccess,"ConsoleScreenBufferInfo");
//��仺��������
bSuccess=FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
PERR(bSuccess,"FillConsoleOutputAttribute");
//��귵����Ļ���Ͻ�����
bSuccess=SetConsoleCursorPosition(hConsole,coordScreen);
PERR(bSuccess,"SetConsoleCursorPosition");
return;
}
using namespace color;
using namespace std;//�洢�ṹ��chess���ǻ��࣬�������Ǹ������ӣ���chessboard������chess��ָ����ø�������
class chessboard;
//�����Ʋ���

//
bool turn=0;
class chess{
private:
    int id;//�ȼ�
public:
    chess(int i):id(i){}
    int get(){return id;}
    virtual bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy)=0;
    virtual ~chess(){};//������
};

class chessboard{
private:
    chess *c[10][9];//��ָ����ø������ӣ�ʵ�ֶ�̬
    char chessword[15][4]={"˧","��","��","ʿ","܇","�R","��","","��","�R","܇","ʿ","��","��","��"};//����
public:
    chessboard(){memset(c, 0, sizeof(c));};//��ָ���ʼ��Ϊ��ָ��
    void init();
    chess* get(int x,int y){return c[x][y];}
    int getid(int x,int y){ if(c[x][y]!=NULL) return c[x][y]->get();return 0;}
    void show();
    void play();
    bool move(int startx,int starty,int aimx,int aimy);
    ~chessboard();//��������
    static bool end;//�жϽ���
    static int player;
};

bool chessboard::end=true;
int chessboard::player=-1;

bool chessboard::move(int startx,int starty,int aimx,int aimy){
    if(startx>=0&&startx<10&&starty>=0&&starty<9//�����жϴ���ĵ��Ƿ���Ϲ���
       &&aimx>=0&&aimx<10&&aimy>=0&&aimy<9
       &&getid(startx,starty)&&getid(startx,starty)*player>0
       &&c[startx][starty]->judge_move(*this,startx,starty,aimx,aimy)){
        if(c[aimx][aimy]!=NULL) delete c[aimx][aimy];//����
        c[aimx][aimy]=c[startx][starty];
        c[startx][starty]=NULL;
    player*=-1;
    if(turn==0)
		turn=1;
    else
		turn=0;
    return true;
    }
    //cout<<"�߷����󣬲����Ϲ���"<<endl;
    return false;
}

class horse : public chess{//���ʵ��
public:
    horse(int i) : chess((i==0?-2:2)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&(tempx*tempx+tempy*tempy==5)&&!cb.get(startx+tempx/2,starty+tempy/2))
        return true;
        return false;
    }
};

class soldier : public chess{//�����䣩��ʵ��
public:
    soldier(int c) : chess((c==0?-1:1)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&sid*tempx<=0){
            if(abs(tempx)==1&&tempy==0) return true;
            if(abs(tempy)==1&&tempx==0)
                if((startx/5==0&&sid>0)||(startx/5==1&&sid<0)) return true;
            return false;
        }
        return false;
    }
};

class general : public chess{//˧��������ʵ��
public:
    general(int c) : chess((c==0?-7:7)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&tempy*tempy+tempx*tempx==1&&aimx%7>=0&&aimx%7<=2&&aimy>=3&&aimy<=5)
            return true;
        return false;
    }
    ~general(){chessboard::end=false;}
};

class elephant : public chess{//���ࣩ��ʵ��
public:
    elephant(int c) : chess((c==0?-6:6)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&tempy*tempy+tempx*tempx==8&&startx/5==aimx/5&&!cb.get(startx+tempx/2,starty+tempy/2))
            return true;
        return false;
    }
};

class cannon : public chess{//�ڵ�ʵ��
public:
    cannon(int c) : chess((c==0?-5:5)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&!(tempx&&tempy)&&(tempx+tempy)){
            int tot=0;
            if(tempx!=0){
                int sign=tempx>0?1:-1;
                for(int i=1;i<abs(tempx);i++)
                    if(cb.get(startx+sign*i,starty)) tot++;
            }
            else{
                int sign=tempy>0?1:-1;
                for(int i=1;i<abs(tempy);i++)
                    if(cb.get(startx,starty+sign*i)) tot++;
            }
            if(!aid)
            {if(!tot) return true;}
            else
            {if(tot==1) return true;}
        }
        return false;
    }
};

class guard: public chess{//ʿ���ˣ���ʵ��
public:
    guard(int c) : chess((c==0?-4:4)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&tempy*tempy+tempx*tempx==2&&aimx%7>=0&&aimx%7<=2&&aimy>=3&&aimy<=5)
            return true;
        return false;
    }
};

class rook : public chess{//����ʵ��
public:
    rook(int c) : chess((c==0?-3:3)){}
    bool judge_move(chessboard &cb,int startx,int starty,int aimx,int aimy){
        int tempx=aimx-startx,tempy=aimy-starty;
        int sid=cb.getid(startx, starty),aid=cb.getid(aimx, aimy);
        if(sid*aid<=0&&!(tempx&&tempy)&&(tempx+tempy)){
            if(tempx!=0){
                int sign=tempx>0?1:-1;
                for(int i=1;i<abs(tempx);i++)
                    if(cb.get(startx+sign*i,starty)) return false;
            }
            else{
                int sign=tempy>0?1:-1;
                for(int i=1;i<abs(tempy);i++)
                    if(cb.get(startx,starty+sign*i)) return false;
            }
                return true;
        }
        return false;
    }
};

chessboard :: ~chessboard(){
    for(int i=0;i<10;i++)
        for(int j=0;j<9;j++)
            if(c[i][j]!=NULL){
                delete c[i][j];
                c[i][j]=NULL;
            }
}

void chessboard :: init(){//��ʼ�������ӵ�����
    c[0][0]=new rook(0);        c[0][8]=new rook(0);
    c[0][1]=new horse(0);       c[0][7]=new horse(0);
    c[0][2]=new elephant(0);    c[0][6]=new elephant(0);
    c[0][3]=new guard(0);       c[0][5]=new guard(0);
    c[0][4]=new general(0);     c[9][4]=new general(1);
    c[2][1]=new cannon(0);      c[2][7]=new cannon(0);
    c[3][0]=new soldier(0);     c[3][2]=new soldier(0);
    c[3][4]=new soldier(0);     c[3][6]=new soldier(0);
    c[3][8]=new soldier(0);     c[6][8]=new soldier(1);
    c[6][0]=new soldier(1);     c[6][2]=new soldier(1);
    c[6][4]=new soldier(1);     c[6][6]=new soldier(1);
    c[7][1]=new cannon(1);      c[7][7]=new cannon(1);
    c[9][0]=new rook(1);        c[9][8]=new rook(1);
    c[9][1]=new horse(1);       c[9][7]=new horse(1);
    c[9][2]=new elephant(1);    c[9][6]=new elephant(1);
    c[9][3]=new guard(1);       c[9][5]=new guard(1);
}

void chessboard :: show(){
    cout<<fg_yellow<<"    ��һ�����������߰�"<<endl<<endl;
    char num[10][4]={"��","һ","��","��","��","��","��","��","��","��"};
    for(int i=0;i<6/*10*/;i++){
        if(i==5) cout<<fg_white<<"   ������ �� �� �硪��"<<endl;
        cout<<fg_yellow<<num[i]<<"  ";
        for(int j=0;j<9;j++){
            if(c[i][j]!=NULL)
            {
            	if(c[i][j]->get()>0)
           			cout<<fg_red<<chessword[c[i][j]->get()+7];
				else
					cout<<fg_green<<chessword[c[i][j]->get()+7];
            }
            else if((i==1&&j==4)||(i==8&&j==4))
                cout<<fg_yellow<<"��";
            else
                cout<<fg_yellow<<"ʮ";
        }
        cout<<endl;
    }

    for(int i=6;i<10/*10*/;i++){
        cout<<fg_yellow<<num[i]<<"  ";
        for(int j=0;j<9;j++){
            if(c[i][j]!=NULL)
            {
            	if(c[i][j]->get()>0)
           			cout<<fg_red<<chessword[c[i][j]->get()+7];
				else
					cout<<fg_green<<chessword[c[i][j]->get()+7];
            }
            else if((i==1&&j==4)||(i==8&&j==4))
                cout<<fg_yellow<<"��";
            else
                cout<<fg_yellow<<"ʮ";
        }
        cout<<endl;
    }


}

void chessboard::play(){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	INPUT_RECORD mouseRec;
	DWORD res;
    this->init();
    this->show();
   do{
       int startx,starty,aimx,aimy;
        int sid,aid;
        do{
            sid=aid=0;
            if(turn==0)
            {
            	clrscr();
        		this->show();
            	cout<<fg_blue<<"���̷��ж�" <<endl;
            	//turn=1;
			}
			else
			{
				clrscr();
        		this->show();
				cout<<fg_blue<<"��췽�ж�"<<endl;
				//turn=0;
			}

        repeat:
		while(1){
		Sleep(110);
		//this->show();
		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED){
			//system("cls");
			//this->show();
			if(mouseRec.Event.MouseEvent.dwMousePosition.X%2==1)
				starty=(mouseRec.Event.MouseEvent.dwMousePosition.X-5)/2;
			else
				starty=(mouseRec.Event.MouseEvent.dwMousePosition.X-4)/2;
			if(mouseRec.Event.MouseEvent.dwMousePosition.Y<7)
				startx=mouseRec.Event.MouseEvent.dwMousePosition.Y-2;
			else
				startx=mouseRec.Event.MouseEvent.dwMousePosition.Y-3;
			if(c[startx][starty]==NULL)
				goto repeat;
			//cout<<"startx:"<<startx<<endl;
			//cout<<"starty:"<<starty<<endl;
			break;
		}
		}
		cout<<"please give me next position"<<endl;
		while(1){
		Sleep(110);
		//this->show();
		ReadConsoleInput(hIn, &mouseRec, 1, &res);
		if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED){
			//system("cls");
			//this->show();
			if(mouseRec.Event.MouseEvent.dwMousePosition.X%2==1)
				aimy=(mouseRec.Event.MouseEvent.dwMousePosition.X-5)/2;
			else
				aimy=(mouseRec.Event.MouseEvent.dwMousePosition.X-4)/2;
			if(mouseRec.Event.MouseEvent.dwMousePosition.Y<7)
				aimx=mouseRec.Event.MouseEvent.dwMousePosition.Y-2;
			else
				aimx=mouseRec.Event.MouseEvent.dwMousePosition.Y-3;

			//cout<<"aimx:"<<aimx<<endl;
			//cout<<"aimy:"<<aimy<<endl;
			break;
		}
		}

			//cin>>startx>>starty>>aimx>>aimy;
        }while(!this->move(startx,starty,aimx,aimy));
        //clrscr();
        //this->show();
    }while(chessboard::end);
    if(chessboard::player==1)
    	cout<<"������Ӯ�����̷�"<<endl;
    else
		cout<<"������Ӯ���Ǻ췽" <<endl;
}

void Cchess_main(){
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE; //�Ƴ����ٱ༭ģʽ
	//mode &= ~ENABLE_INSERT_MODE; //�Ƴ�����ģʽ
	//mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
    chessboard C;
    C.play();
    system("pause");
    return;
}

