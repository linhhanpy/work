#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <ctime>
#include <time.h>
#include <stdio.h>
using namespace std;

int D_Of_C, OK, ane, xy, D_Of_C1, OK1, ane1, xy1, nowM, MoralValue;
int ict = 0, nowlevel = 0;
int bag[44] = { 20000000,100,100000,1000,10000,10000,100000,100000,100000,100000,100000,100000,100,100,111,100,11,111,111,1,2,6,3,4,6777,55,54,43,654,43,43,43};
//0�齱ȯ 1����ʯR 2����ʯSR 3����ʯSSR 4����ʯSSS 5����ʯX
//6�������츴�� 7������������ 8�������赹�� 9�����������Ӱ 10����������ͣ 11������ʯ���� 12������ָ��� 13�������ٻ��� 14������������ 15���������뷢 16������������ 17���������� 18������������
//19����ҩˮ 20����ҩˮ 21����ҩˮ 22����ҩˮ 23ȫ��ҩˮ
//24è���Ӻ��� 25����ͷ�� 26����ˮ�ֵ���ë 27������ 28����β�� 29�����ë 30������βë 31���� 32ҹ���β��
//33��ľ 34����ľ 35����ľ 36ɽ�ľ���� 37��ľ 38еľ 39ɽë�ľ 40��ľ 41ӣ��ľ 42�һ���ľ
//43�ٶ�ҩˮ
string Material1name[9] = { "è���Ӻ���","����ͷ��","����ˮ�ֵ���ë","������","����β��","�����ë","������βë","����","ҹ���β��" };
string Material2name[10] = { "��ľ","����ľ","����ľ","ɽ�ľ����","��ľ","еľ","ɽë�ľ","��ľ","ӣ��ľ","�һ���ľ" };
unsigned long long health = 1000, maxhealth = 1000, money=0, attack = 250, defense = 10, experience = 0, camp, level = 1, amm = 0, f = 0, speed = 0;
string Nwand = "����";
int LE1 = 1, LE2 = 1, Sl[13];
bool dead = false;
string wandname[100] = { "����ħ��","����ħ��","�����ľħ��","����ħ��","����ľħ��","����ľħ��","��ɼľħ��","��ħ��" };
unsigned long long wandpower[100] = { 200,500,1100,1300,2400,5000,9000,18000000000000000000ULL }, wand[100], wandi = 8, wandnamei = 8, wandpoweri = 8;
string name, password;
int choose()
{
	system("cls");
	cout << "��ѡ��������Ӫ��" << endl;
	cout << "0, ����.HarryPotter" << endl;
	cout << "1, ����ħ LordVoldemort" << endl;
	cin >> camp;
	if (camp != 0 && camp != 1) {
		cout << "�������";
		Sleep(250);
		choose();
	}
	else {
		if (MessageBox(0, TEXT("��ȷ����"), TEXT("��ѡ��"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) return 0;
		choose();
	}
	return 0;
}
int login()
{
	string DN, DPW;
	bool isn = false;
	cout << "�������˺ź�����" << endl;
	cout << "�˺ţ�";
	cin >> name;
	cout << "���룺";
	cin >> password;
	ifstream fin("data2.txt");
	while(fin >> DN) {
		if (DN == name) {
			fin >> DPW;
			if (DPW != password) {
				cout << "�������" << endl; isn = true;
				system("cls"); login();
			}
			else {
				fin >> money >> attack >> defense >> health >> level >> experience >> LE1 >> LE2  >> camp >> maxhealth;
				fin >> D_Of_C >> OK >> ane >> xy >> D_Of_C1 >> OK1 >> ane1 >> xy1 >> nowM;
				fin >> bag[0] >> bag[1] >> bag[2] >> bag[3] >> bag[4] >> bag[5] >> bag[6] >> bag[7];
				fin >> bag[8] >> bag[9] >> bag[10] >> bag[11] >> bag[12] >> bag[13] >> bag[14] >> bag[15];
				fin >> bag[16] >> bag[17] >> bag[18] >> bag[19] >> bag[20] >> bag[21] >> bag[22] >> bag[23];
				fin >> bag[24] >> bag[25] >> bag[26] >> bag[27] >> bag[28] >> bag[29] >> bag[30] >> bag[31];
				fin >> bag[32] >> bag[33] >> bag[34] >> bag[35] >> bag[36] >> bag[37] >> bag[38] >> bag[39];
				fin >> bag[40] >> bag[41] >> bag[42] >> bag[43];
				fin >> Sl[0] >> Sl[1] >> Sl[2] >> Sl[3] >> Sl[4] >> Sl[5] >> Sl[6] >> Sl[7] >> Sl[8] >> Sl[9] >> Sl[10] >> Sl[11] >> Sl[12];
				for (int i = 0; i < 100; i++) {
					fin >> wandname[i];
					fin >> wandpower[i];
					fin >> wand[i];
				}
				fin >> Nwand >> amm >> f >> wandi >> wandnamei >> wandpoweri >> ict >> speed >> nowlevel;
				isn = true;
			}
		}
	}
	if (!isn) {
		cout << "�޴��û���" << endl;
		login();
	}
	cout << "����ɹ���" << endl;
	Sleep(1000);
	return 0;
}
int save()
{
	ofstream outfile("data2.txt", ios::binary | ios::app | ios::in | ios::out);
	outfile << name << " " << password << " " << money << " " << attack << " " << defense << " " << health << " " << level << " " << experience << " " << LE1 << " " << LE2 << " " << camp << " " << maxhealth << " ";
	outfile << D_Of_C << " " << OK << " " << ane << " " << xy << " " << D_Of_C1 << " " << OK1 << " " << ane1 << " " << xy1 << " " << nowM << " ";
	outfile << bag[0] << " " << bag[1] << " " << bag[2] << " " << bag[3] << " " << bag[4] << " " << bag[5] << " " << bag[6] << " " << bag[7] << " ";
	outfile << bag[8] << " " << bag[9] << " " << bag[10] << " " << bag[11] << " " << bag[12] << " " << bag[13] << " " << bag[14] << " " << bag[15] << " ";
	outfile << bag[16] << " " << bag[17] << " " << bag[18] << " " << bag[19] << " " << bag[20] << " " << bag[21] << " " << bag[22] << " " << bag[23] << " ";
	outfile << bag[24] << " " << bag[25] << " " << bag[26] << " " << bag[27] << " " << bag[28] << " " << bag[29] << " " << bag[30] << " " << bag[31] << " ";
	outfile << bag[32] << " " << bag[33] << " " << bag[34] << " " << bag[35] << " " << bag[36] << " " << bag[37] << " " << bag[38] << " " << bag[39] << " ";
	outfile << bag[40] << " " << bag[41] << " " << bag[42] << " " << bag[43] << " ";
	outfile << Sl[0] << " " << Sl[1] << " " << Sl[2] << " " << Sl[3] << " " << Sl[4] << " " << Sl[5] << " " << Sl[6] << " " << Sl[7] << " " << Sl[8] << " " << Sl[9] << " " << Sl[10] << " " << Sl[11] << " " << Sl[12] << " ";
	for (int i = 0; i < 100; i++) {
		outfile << wandname[i] << " ";
		outfile << wandpower[i] << " ";
		outfile << wand[i] << " ";
	}
	outfile << Nwand << " " << amm << " " << f << " " << wandi << " " << wandnamei << " " << wandpoweri << " " << ict << " " << speed << " " << nowlevel << endl;
	outfile.close();
	return 0;
}
int Reg()
{
	string DN, DPW;
	cout << "�������˺ź�����  " << endl;
	cout << "�˺ţ�";
	cin >> name;
	cout << endl << "���룺";
	cin >> password;
	ifstream fin("data2.txt");
	while(fin >> DN) {
		if (DN == name) {
			cout << "�û����ѱ�ʹ��=====����������";
			Reg();
		}
	}
	choose();
	return 0;
}
int monsterfight(string Hname, int hisH, int hisA, int hisD, int hisS, int hisSP)
{
	int mhealth = 10000, mdefense = 1000, mattack = 10000, mspeed = 500;
	int hfaint = 0;
	int mfaint = 0;
	dead = false;
	int ha = hisA;
	while (1) {
		if (hfaint > 0) hfaint -= 1;
		if (mfaint > 0) {
			if (rand() % 3 == 0)
			{
				mfaint = 0;
				cout << "ʯ��ʹ�ü�������ͣ��ֹͣ��ħ�䣡" << endl;
			}
			else mfaint -= 1;
		}
		if (mfaint <= 0) {
			if (rand() % 3) {
				cout << "ʯ��ʹ�ü��ܿ�츴�� ��������200" << endl;
				mhealth += 200;
			}
			if (rand() % 3) {
				cout << "ʯ��ʹ�ü������׻��� ��������100 ��������50" << endl;
				mhealth += 100;
				mdefense += 50;
			}
			if (rand() % 3) {
				cout << "ʯ��ʹ�ü��������Ӱ ��������200 �Է���Ѫ200��" << endl;
				hisH -= 200;
				mattack += 200;
			}
			Sleep(1000);
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > hisSP) {
				if (attack + ran > hisD) {
					cout << "ʯ�ַ������ " << Hname << "��Ѫ" << mattack - hisD + ran << "�� ʣ��" << hisH - (mattack - hisD + ran) << "��" << endl;
					hisH -= mattack - hisD + ran;
				}
				else cout << "ʯ�ַ������ " << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			else {
				if (rand() % 2) cout << "ʯ��һ�����˹�ȥ����û������" << endl;
				else {
					cout << "ʯ��һ�����˹�ȥ����ֻ��������" << endl;
					if ((mattack / 3) + ran > hisD) {
						cout << Hname << "��Ѫ" << (mattack / 3) + ran - hisD << "�� ʣ��" << hisH - ((mattack / 3) + ran - hisD) << "��" << endl;
						hisH -= (mattack / 3) + ran - hisD;
					}
					else cout << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
				}
			}
		}
		Sleep(1000);
		if (hisH <= 0) {
			if (hisS == 20 && rand() % 3 == 0) {
				cout << "�Է��������ܣ��ָ���� ��Ѫ����" << endl;
				hisH = ha; Sleep(1000);
			}
			else {
				cout << "�Է�����" << endl;
				return 0;
			}
		}
		if (hfaint <= 0) {
			if (hisS != 0) {
				if (rand() % 3 == 0) {
					if (hisS == 14) {
						cout << "�Է��������ܣ���츴��  ������200" << endl;
						hisH += 200;
					}
					if (hisS == 15) {
						cout << "�Է��������ܣ����׻���  ������50 ��������50" << endl;
						hisH += 50;
						hisD += 50;
					}
					if (hisS == 17) {
						cout << "�Է��������������Ӱ ��������200 ��Ѫ200��" << endl;
						health -= 200;
						hisA += 200;
					}
				}
				Sleep(1000);
			}
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > mspeed) {
				if (hisA + ran > defense) {
					cout << Hname << "������� " << "ʯ�ֿ�Ѫ" << hisA - defense + ran << "�� ʣ��" << mhealth - (hisA - defense + ran) << "��" << endl;
					mhealth -= hisA - defense + ran;
				}
				else cout << Hname << "������� " << "ʯ�ֿ�Ѫ0�� ʣ��" << mhealth << "��" << endl;
			}
			else {
				if (rand() % 2) cout << Hname << "һ�����˹�������û������" << endl;
				else {
					cout << "�Է�һ�����˹�������ֻ������ʯ�ֵ���" << endl;
					if ((hisA / 3) + ran > hisD) {
						cout << "ʯ�ֿ�Ѫ" << (hisA / 3) + ran - defense << "�� ʣ��" << mhealth - ((hisA / 3) + ran - defense) << "��" << endl;
						mhealth -= ((hisA / 3) + ran - defense);
					}
					else cout << "ʯ�ֿ�Ѫ0�� ʣ��" << mhealth << "��" << endl;
				}
			}
			Sleep(1000);
			if (mhealth <= 0) {
				cout << "ʯ������" << endl;
				return hisH;
			}
		}
	}
	return 0;
}
int fight1(string Hname, int hisH, int hisA, int hisD, int hisS, int hisSP)
{
	int hfaint = 0, hhurt = 0, hbeat = 0;
	int mfaint = 0, mhurt = 0;
	dead = false;
	int ha = hisA;
	int his = hisA + hisD + hisH;
	while (1) {
		if (hfaint > 0) {
			if (rand() % 3 == 0) {
				cout << "�Է�ʹ�ü��ܣ�����ͣ��ֹͣ��ħ��" << endl;
				hfaint = 1;
			}
			hfaint -= 1;
		}
		if (hbeat == 1) {
			if (rand() % 10 == 0) {
				cout << "�Է�һ�㣬��������ʯͷ" << endl;
				hbeat = 0;
			}
			else {
				cout << "�Է�����������ʯͷ����ײ�����ı����� ��Ѫ50��" << endl;
				hisH -= 50;
			}
		}
		if (mfaint > 0) {
			if (Sl[6]) mfaint = 0;
			else mfaint -= 1;
		}
		if (mhurt > 0) {
			if (Sl[6]) mhurt = 0;
			else mhurt -= 1;
			cout << "�������һ�ѵ��̴���һ�� ��Ѫ200��" << endl;
			health -= 200;
		}
		if (mfaint <= 0) {
			if (rand() % 3 && Sl[0]) {
				cout << "��ʹ�ü��ܿ�츴�� ��������200" << endl;
				health += 200;
			}
			if (rand() % 3 && Sl[1]) {
				cout << "��ʹ�ü������׻��� ��������100 ��������50" << endl;
				health += 100; defense += 50;
			}
			if (rand() % 3 && Sl[2]) {
				cout << "��ʹ�ü��ܻ�赹�� " << Hname << "һ�غ�֮�ڲ��ܹ���" << endl;
				hfaint += 1;
			}
			if (rand() % 3 && Sl[3]) {
				cout << "��ʹ�ü��������Ӱ ��������200 ��Ѫ200��" << endl;
				hisH -= 200; attack += 200;
			}
			if (rand() % 3 && Sl[5]) {
				if (rand() % 10) {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "���غ�֮�ڲ��ܹ���" << endl;
					hfaint += 2;
				}
				else {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "ʮ�غ�֮�ڲ��ܹ���" << endl;
					hfaint += 10;
				}
			}
			if (rand() % 4 == 0 && Sl[7])
			{
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
				hisH = monsterfight(Hname, hisH, hisA, hisD, hisS, hisSP);
				if (hisH < 1) return 0;
				if (Sl[0]) {
					cout << "�ڶԷ���ʯ�ֵ�ս���У����Ѿ��ָ���2000����" << endl;
					if (maxhealth < health + 2000) health = maxhealth;
					else health += 2000;
				}
			}
			if (rand() % 4 == 0 && Sl[8]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
			}
			if (rand() % 3 && Sl[9]) {
				cout << "��ʹ�ü������뷢�������ʮ��ʯͷ" << endl;
				hbeat = 1;
			}
			if (rand() % 3 && Sl[10]) {
				cout << "��ʹ�ü��������䣡�Է�����ʹ5�غ�" << endl;
				hhurt += 5;
			}
			if (rand() % 3 && Sl[11]) {
				cout << "���ǳ��ϣ���ʹ�ö���䣬��ͼ��" << Hname << "�Լ������Լ���" << endl;
				Sleep((rand() % 1000) + 1000);
				cout << Hname << "��������ˣ���ʼ�����Լ�" << endl;
				Sleep(700);
				int ran = rand() % 40 - 20;
				if (hisA + ran > hisD) {
					cout << "�Է�������� �Լ���Ѫ" << hisH - hisD + ran << "�� ʣ��" << hisH - (hisA - hisD + ran) << "��" << endl;
					hisH -= hisA - hisD + ran;
				}
				else cout << "�Է�������� �Լ���Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			if (rand() % 2 && Sl[12]) {
				cout << "��ʹ�ü��ܰ��ߴ����� " << Hname << "��Ѫ" << hisH - hisH / 4 << "��" << endl;
				hisH /= 4;
			}
			Sleep(1000);
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > hisSP) {
				if (attack + ran > hisD) {
					cout << "�㷢����� " << Hname << "��Ѫ" << attack - hisD + ran << "�� ʣ��" << hisH - (attack - hisD + ran) << "��" << endl;
					hisH -= attack - hisD + ran;
				}
				else cout << "�㷢����� " << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			else {
				if (rand() % 2) cout << "��һ�����˹�ȥ����û������" << endl;
				else {
					cout << "��һ�����˹�ȥ����ֻ��������" << endl;
					if ((attack / 3) + ran > hisD) {
						cout << Hname << "��Ѫ" << (attack / 3) + ran - hisD << "�� ʣ��" << hisH - ((attack / 3) + ran - hisD) << "��" << endl;
						hisH -= (attack / 3) + ran - hisD;
					}
					else cout << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
				}
			}
		}
		Sleep(700);
		if (hhurt > 0) {
			hhurt -= 1;
			cout << "�Է���������������䣬�������Ĵ���� ��Ѫ200��" << endl;
			hisH -= 200;
		}
		if (hisH <= 0) {
			if (hisS == 20 && rand() % 3 == 0) {
				cout << "�Է��������ܣ��ָ���� ��Ѫ����" << endl;
				hisH = ha;
				Sleep(1000);
			}
			else {
				cout << "�Է�����\n���" << (his / 30) << "����" << endl;
				experience += (his / 30);
				if (ane == 3) D_Of_C++;
				if (ane1 == 3) D_Of_C1++;
				return 0;
			}
		}
		if (hfaint <= 0) {
			if (rand() % 3 == 0) {
				if (hisS == 14) {
					cout << "�Է��������ܣ���츴��  ������200" << endl;
					hisH += 200;
				}
				if (hisS == 15) {
					cout << "�Է��������ܣ����׻���  ������50 ��������50" << endl;
					hisH += 50; hisD += 50;
				}
				if (hisS == 17) {
					cout << "�Է��������������Ӱ ��������200 ��Ѫ200��" << endl;
					health -= 200; hisA += 200;
				}
				Sleep(1000);
			}
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > speed) {
				if (hisA + ran > defense) {
					cout << Hname << "������� " << "���Ѫ" << hisA - defense + ran << "�� ʣ��" << health - (hisA - defense + ran) << "��" << endl;
					health -= hisA - defense + ran;
				}
				else cout << Hname << "������� " << "���Ѫ0�� ʣ��" << health << "��" << endl;
			}
			else {
				if (rand() % 2) cout << Hname << "һ�����˹�������û������" << endl;
				else {
					cout << "�Է�һ�����˹�������ֻ�����������" << endl;
					if ((hisA / 3) + ran > hisD) {
						cout << "���Ѫ" << (hisA / 3) + ran - defense << "�� ʣ��" << health - ((hisA / 3) + ran - defense) << "��" << endl;
						health -= ((hisA / 3) + ran - defense);
					}
					else cout << "���Ѫ0�� ʣ��" << health << "��" << endl;
				}
			}
			Sleep(700);
			if (health <= 0) {
				if (Sl[6] && rand() % 2) {
					cout << "�㷢�����ܣ��ָ���� ��Ѫ����" << endl;
					health = maxhealth;
					Sleep(1000);
				}
				else {
					cout << "������";
					health = 20;
					dead = true;
					return 0;
				}
			}
		}
	}
	return 0;
}
int fight2(string Hname, int hisH, int hisA, int hisD, int hisS, int hisSP)
{
	int hfaint = 0, hhurt = 0, hbeat = 0;
	int mfaint = 0, mhurt = 0;
	dead = false;
	int ha = hisA;
	int his = hisA + hisD + hisH;
	while (1) {
		if (hfaint > 0) {
			if (rand() % 3 == 0) {
				cout << "�Է�ʹ�ü��ܣ�����ͣ��ֹͣ��ħ��";
				hfaint = 1;
			}
			hfaint -= 1;
		}
		if (hbeat == 1) {
			if (rand() % 10 == 0) {
				cout << "�Է�һ�㣬��������ʯͷ" << endl;
				hbeat = 0;
			}
			else {
				cout << "�Է�����������ʯͷ����ײ�����ı����� ��Ѫ50��" << endl;
				hisH -= 50;
			}
		}
		if (mfaint > 0) {
			if (Sl[6]) mfaint = 0;
			else mfaint -= 1;
		}
		if (mhurt > 0) {
			if (Sl[6]) mhurt = 0;
			else mhurt -= 1;
			cout << "�������һ�ѵ��̴���һ�� ��Ѫ200��" << endl;
			health -= 200;
		}
		if (mfaint <= 0) {
			if (rand() % 3 && Sl[0]) {
				cout << "��ʹ�ü��ܿ�츴�� ��������200" << endl;
				health += 200;
			}
			if (rand() % 3 && Sl[1]) {
				cout << "��ʹ�ü������׻��� ��������100 ��������50" << endl;
				health += 100;
				defense += 50;
			}
			if (rand() % 3 && Sl[2]) {
				cout << "��ʹ�ü��ܻ�赹�� " << Hname << "һ�غ�֮�ڲ��ܹ���" << endl;
				hfaint += 1;
			}
			if (rand() % 3 && Sl[3]) {
				cout << "��ʹ�ü��������Ӱ ��������200 ��Ѫ200��" << endl;
				hisH -= 200;
				attack += 200;
			}
			if (rand() % 3 && Sl[5]) {
				if (rand() % 10) {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "���غ�֮�ڲ��ܹ���" << endl;
					hfaint += 2;
				}
				else {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "ʮ�غ�֮�ڲ��ܹ���" << endl;
					hfaint += 10;
				}
			}
			if (rand() % 4 == 0 && Sl[7]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
				hisH = monsterfight(Hname, hisH, hisA, hisD, hisS, hisSP);
				if (hisH < 1) return 0;
				if (Sl[0]) {
					cout << "�ڶԷ���ʯ�ֵ�ս���У����Ѿ��ָ���2000����" << endl;
					if (maxhealth < health + 2000) health = maxhealth;
					else health += 2000;
				}
				Sleep(1000);
			}
			if (rand() % 4 == 0 && Sl[8]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
			}
			if (rand() % 3 && Sl[9]) {
				cout << "��ʹ�ü������뷢�������ʮ��ʯͷ" << endl;
				hbeat = 1;
			}
			if (rand() % 3 && Sl[10]) {
				cout << "��ʹ�ü��������䣡�Է�����ʹ5�غ�" << endl;
				hhurt += 5;
			}
			if (rand() % 3 && Sl[11]) {
				cout << "���ǳ��ϣ���ʹ�ö���䣬��ͼ��" << Hname << "�Լ������Լ���" << endl;
				Sleep((rand() % 1000) + 1000);
				cout << Hname << "��������ˣ���ʼ�����Լ�" << endl;
				Sleep(700);
				int ran = rand() % 40 - 20;
				if (hisA + ran > hisD) {
					cout << "�Է�������� �Լ���Ѫ" << hisH - hisD + ran << "�� ʣ��" << hisH - (hisA - hisD + ran) << "��" << endl;
					hisH -= hisA - hisD + ran;
				}
				else cout << "�Է�������� �Լ���Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			if (rand() % 2 && Sl[12]) {
				cout << "��ʹ�ü��ܰ��ߴ����� " << Hname << "��Ѫ" << hisH - hisH / 4 << "��" << endl;
				hisH /= 4;
			}
			Sleep(1000);
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > hisSP) {
				if (attack + ran > hisD) {
					cout << "�㷢����� " << Hname << "��Ѫ" << attack - hisD + ran << "�� ʣ��" << hisH - (attack - hisD + ran) << "��" << endl;
					hisH -= attack - hisD + ran;
				}
				else cout << "�㷢����� " << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			else {
				if (rand() % 2) cout << "��һ�����˹�ȥ����û������" << endl;
				else {
					cout << "��һ�����˹�ȥ����ֻ��������" << endl;
					if ((attack / 3) + ran > hisD) {
						cout << Hname << "��Ѫ" << (attack / 3) + ran - hisD << "�� ʣ��" << hisH - ((attack / 3) + ran - hisD) << "��" << endl;
						hisH -= (attack / 3) + ran - hisD;
					}
					else cout << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
				}
			}
		}
		Sleep(700);
		if (hhurt > 0) {
			hhurt -= 1;
			cout << "�Է���������������䣬�������Ĵ���� ��Ѫ200��" << endl;
			hisH -= 200;
		}
		if (hisH <= 0) {
			if (hisS == 20 && rand() % 3 == 0) {
				cout << "�Է��������ܣ��ָ���� ��Ѫ����" << endl;
				hisH = ha;
				Sleep(1000);
			}
			else {
				cout << "�Է�����\n���" << (his / 200) << "���" << endl;
				money += (his / 200);
				if (ane == 3) D_Of_C++;
				if (ane1 == 3) D_Of_C1++;
				return 0;
			}
		}
		if (hfaint <= 0) {
			if (rand() % 3 == 0) {
				if (hisS == 14) {
					cout << "�Է��������ܣ���츴��  ������200" << endl;
					hisH += 200;
				}
				if (hisS == 15) {
					cout << "�Է��������ܣ����׻���  ������50 ��������50" << endl;
					hisH += 50; hisD += 50;
				}
				if (hisS == 17) {
					cout << "�Է��������������Ӱ ��������200 ��Ѫ200��" << endl;
					health -= 200; hisA += 200;
				}
				Sleep(1000);
			}
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > speed) {
				if (hisA + ran > defense) {
					cout << Hname << "������� " << "���Ѫ" << hisA - defense + ran << "�� ʣ��" << health - (hisA - defense + ran) << "��" << endl;
					health -= hisA - defense + ran;
				}
				else cout << Hname << "������� " << "���Ѫ0�� ʣ��" << health << "��" << endl;
			}
			else {
				if (rand() % 2) cout << Hname << "һ�����˹�������û������" << endl;
				else {
					cout << "�Է�һ�����˹�������ֻ�����������" << endl;
					if ((hisA / 3) + ran > hisD) {
						cout << "���Ѫ" << (hisA / 3) + ran - defense << "�� ʣ��" << health - ((hisA / 3) + ran - defense) << "��" << endl;
						health -= ((hisA / 3) + ran - defense);
					}
					else cout << "���Ѫ0�� ʣ��" << health << "��" << endl;
				}
			}
			Sleep(700);
			if (health <= 0) {
				if (Sl[6] && rand() % 2) {
					cout << "�㷢�����ܣ��ָ���� ��Ѫ����" << endl;
					health = maxhealth;
					Sleep(1000);
				}
				else {
					cout << "������";
					health = 20;
					dead = true;
					return 0;
				}
			}
		}
	}
	return 0;
}
int fight(string Hname, int hisH, int hisA, int hisD, int hisS, int hisSP)
{
	int hfaint = 0, hhurt = 0, hbeat = 0;
	int mfaint = 0, mhurt = 0;
	dead = false;
	int ha = hisA;
	int his = hisA + hisD + hisH;
	while (1)
	{
		if (hfaint > 0) {
			if (rand() % 3 == 0) {
				cout << "�Է�ʹ�ü��ܣ�����ͣ��ֹͣ��ħ��" << endl;
				hfaint = 0;
			}
			else hfaint -= 1;
		}
		if (hbeat == 1) {
			if (rand() % 10 == 0) {
				cout << "�Է�һ�㣬��������ʯͷ" << endl;
				hbeat = 0;
			}
			else {
				cout << "�Է�����������ʯͷ����ײ�����ı����� ��Ѫ50��" << endl;
				hisH -= 50;
			}
		}
		if (mfaint > 0) {
			if (Sl[6]) mfaint = 0;
			else mfaint -= 1;
		}
		if (mhurt > 0) {
			if (Sl[6]) mhurt = 0;
			else mhurt -= 1;
			cout << "�������һ�ѵ��̴���һ�� ��Ѫ200��" << endl;
			health -= 200;
		}
		if (mfaint <= 0) {
			if (rand() % 3 && Sl[0]) {
				cout << "��ʹ�ü��ܿ�츴�� ��������200" << endl;
				health += 200;
			}
			if (rand() % 3 && Sl[1]) {
				cout << "��ʹ�ü������׻��� ��������100 ��������50" << endl;
				health += 100;
				defense += 50;
			}
			if (rand() % 3 && Sl[2]) {
				cout << "��ʹ�ü��ܻ�赹�� " << Hname << "һ�غ�֮�ڲ��ܹ���" << endl;
				hfaint += 1;
			}
			if (rand() % 3 && Sl[3]) {
				cout << "��ʹ�ü��������Ӱ ��������200 ��Ѫ200��" << endl;
				hisH -= 200; attack += 200;
			}
			if (rand() % 3 && Sl[5]) {
				if (rand() % 10) {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "���غ�֮�ڲ��ܹ���" << endl;
					hfaint += 2;
				}
				else {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "ʮ�غ�֮�ڲ��ܹ���" << endl;
					hfaint += 10;
				}
			}
			if (rand() % 4 == 0 && Sl[7]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
				hisH = monsterfight(Hname, hisH, hisA, hisD, hisS, hisSP);
				if (hisH < 1) return 0;
				if (Sl[0]) {
					cout << "�ڶԷ���ʯ�ֵ�ս���У����Ѿ��ָ���2000����" << endl;
					if (maxhealth < health + 2000) health = maxhealth;
					else health += 2000;
				}
			}
			if (rand() % 4 == 0 && Sl[8]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
			}
			if (rand() % 3 && Sl[9]) {
				cout << "��ʹ�ü������뷢�������ʮ��ʯͷ" << endl;
				hbeat = 1;
			}
			if (rand() % 3 && Sl[10]) {
				cout << "��ʹ�ü��������䣡�Է�����ʹ5�غ�" << endl;
				hhurt += 5;
			}
			if (rand() % 3 && Sl[11]) {
				cout << "���ǳ��ϣ���ʹ�ö���䣬��ͼ��" << Hname << "�Լ������Լ���" << endl;
				Sleep((rand() % 1000) + 1000);
				cout << Hname << "��������ˣ���ʼ�����Լ�" << endl;
				Sleep(700);
				int ran = rand() % 40 - 20;
				if (hisA + ran > hisD) {
					cout << "�Է�������� �Լ���Ѫ" << hisH- hisD + ran << "�� ʣ��" << hisH - (hisA - hisD + ran) << "��" << endl;
					hisH -= hisA - hisD + ran;
				}
				else cout << "�Է�������� �Լ���Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			if (rand() % 2 && Sl[12]) {
				cout << "��ʹ�ü��ܰ��ߴ����� " << Hname << "��Ѫ" << hisH - hisH / 4 << "��" << endl;
				hisH /= 4;
			}
			Sleep(1000);
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > hisSP) {
				if (attack + ran > hisD) {
					cout << "�㷢����� " << Hname << "��Ѫ" << attack - hisD + ran << "�� ʣ��" << hisH - (attack - hisD + ran) << "��" << endl;
					hisH -= attack - hisD + ran;
				}
				else cout << "�㷢����� " << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			else {
				if (rand() % 2) cout << "��һ�����˹�ȥ����û������" << endl;
				else {
					cout << "��һ�����˹�ȥ����ֻ��������" << endl;
					if ((attack / 3) + ran > hisD) {
						cout << Hname << "��Ѫ" << (attack / 3) + ran - hisD << "�� ʣ��" << hisH - ((attack / 3) + ran - hisD) << "��" << endl;
						hisH -= (attack / 3) + ran - hisD;
					}
					else cout << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
				}
			}
		}
		Sleep(700);
		if (hhurt > 0) {
			hhurt -= 1;
			cout << "�Է���������������䣬�������Ĵ���� ��Ѫ200��" << endl;
			hisH -= 200;
		}
		if (hisH <= 0) {
			if (hisS == 20 && rand() % 3 == 0) {
				cout << "�Է��������ܣ��ָ���� ��Ѫ����" << endl;
				hisH = ha;
				Sleep(1000);
			}
			else {
				cout << "�Է�����\n���" << his / 30 << "Ԫ" << endl;
				money += his / 30;
				experience += (his / 30) * 10;
				if (ane == 3) D_Of_C++;
				if (ane1 == 3) D_Of_C1++;
				return 0;
			}
		}
		if (hfaint <= 0) {
			if (rand() % 3 == 0) {
				if (hisS == 14) {
					cout << "�Է��������ܣ���츴��  ������200" << endl;
					hisH += 200;
				}
				if (hisS == 15) {
					cout << "�Է��������ܣ����׻���  ������50 ��������50" << endl;
					hisH += 50;
					hisD += 50;
				}
				if (hisS == 17)
				{
					cout << "�Է��������������Ӱ ��������200 ��Ѫ200��" << endl;
					health -= 200;
					hisA += 200;
				}
				Sleep(1000);
			}
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > speed) {
				if (hisA + ran > defense) {
					cout << Hname << "������� " << "���Ѫ" << hisA - defense + ran << "�� ʣ��" << health - (hisA - defense + ran) << "��" << endl;
					health -= hisA - defense + ran;
				}
				else cout << Hname << "������� " << "���Ѫ0�� ʣ��" << health << "��" << endl;
			}
			else {
				if (rand() % 2) cout << Hname << "һ�����˹�������û������" << endl;
				else {
					cout << "�Է�һ�����˹�������ֻ�����������" << endl;
					if ((hisA / 3) + ran > hisD) {
						cout <<"���Ѫ" << (hisA / 3) + ran - defense << "�� ʣ��" << health - ((hisA / 3) + ran - defense) << "��" << endl;
						health -= ((hisA / 3) + ran - defense);
					}
					else cout << "���Ѫ0�� ʣ��" << health << "��" << endl;
				}
			}
			Sleep(700);
			if (health <= 0) {
				if (Sl[6] && rand() % 2) {
					cout << "�㷢�����ܣ��ָ���� ��Ѫ����" << endl;
					health = maxhealth;
					Sleep(1000);
				}
				else {
					cout << "������" << endl;
					health = 20;
					dead = true;
					return 0;
				}
			}
		}
	}
	return 0;
}
int street()
{
	switch (rand() % 6)
	{
	case 0:
		if (camp) {
			int f;
			cout << "�������˿��֡�����ά" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("����ά", 500, 110, 0, 14, 1000);
				if (!dead && rand() % 2) {
					if (rand() % 4 == 0) {
						cout << "���һƿ����ҩˮ" << endl;
						bag[22] += 1;
					}
					else if (rand() % 4 == 1) {
						cout << "���һƿ����ҩˮ" << endl;
						bag[21] += 1;
					}
					else if (rand() % 4 == 2) {
						cout << "���һƿ����ҩˮ" << endl;
						bag[19] += 1;
					}
					else {
						cout << "���һƿ����ҩˮ" << endl;
						bag[20] += 1;
					}
				}
			}
		}
		else {
			int f;
			cout << "����������ɭ�ء�������" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("������", 500, 110, 0, 15, 1000);
				if (!dead && rand() % 2) {
					if (rand() % 4 == 0) {
						cout << "���һƿ����ҩˮ" << endl;
						bag[22] += 1;
					}
					else if (rand() % 4 == 1) {
						cout << "���һƿ����ҩˮ" << endl;
						bag[21] += 1;
					}
					else if (rand() % 4 == 2) {
						cout << "���һƿ����ҩˮ" << endl;
						bag[19] += 1;
					}
					else {
						cout << "���һƿ����ҩˮ" << endl;
						bag[20] += 1;
					}
				}
			}
		}
		break;
	case 1:
		if (camp) {
			int f;
			cout << "�������˺�����������" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("������", 2000, 500, 15, 15, 1000);
				if (!dead && rand() % 3 != 0) {
					if (rand() % 5 == 0) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[22] += 2;
					}
					else if (rand() % 5 == 1) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[21] += 2;
					}
					else if (rand() % 5 == 2) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[19] += 2;
					}
					else if (rand() % 5 == 3) {
						cout << "���һƿȫ��ҩˮ" << endl;
						bag[23] += 1;
					}
					else {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[20] += 2;
					}
				}
			}
		}
		else {
			int f;
			cout << "�������˵����ơ������" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("�����", 2000, 500, 15, 15, 1000);
				if (!dead && rand() % 3 != 0) {
					if (rand() % 5 == 0) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[22] += 2;
					}
					else if (rand() % 5 == 1) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[21] += 2;
					}
					else if (rand() % 5 == 2) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[19] += 2;
					}
					else if (rand() % 5 == 3) {
						cout << "���һƿȫ��ҩˮ" << endl;
						bag[23] += 1;
					}
					else {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[20] += 2;
					}
				}
			}
		}
		break;
	case 2:
		if (camp) {
			int f;
			cout << "��������С�����ǲ�����" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("������", 5000, 700, 50, 16, 1500);
				if (!dead && rand() % 4 != 0) {
					if (rand() % 5 == 0) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[22] += 3;
					}
					else if (rand() % 5 == 1) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[21] += 3;
					}
					else if (rand() % 5 == 2) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[19] += 3;
					}
					else if (rand() % 5 == 3) {
						cout << "�����ƿȫ��ҩˮ" << endl;
						bag[23] += 2;
					}
					else {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[20] += 3;
					}
				}
			}
		}
		else {
			int f;
			cout << "�������˰¹�˹�ء�¬�����" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("¬�����", 5000, 700, 50, 15, 1500);
				if (!dead && rand() % 4 != 0) {
					if (rand() % 5 == 0) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[22] += 3;
					}
					else if (rand() % 5 == 1) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[21] += 3;
					}
					else if (rand() % 5 == 2) {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[19] += 3;
					}
					else if (rand() % 5 == 3) {
						cout << "�����ƿȫ��ҩˮ" << endl;
						bag[23] += 2;
					}
					else {
						cout << "�����ƿ����ҩˮ" << endl;
						bag[20] += 3;
					}
				}
			}
		}
		break;
	case 3:
		if (camp) {
			int f;
			cout << "�������˰���˹�С��µ�" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("�µ�", 10000, 1200, 250, 17, 2000);
				if (!dead) {
					if (rand() % 3) {
						if (rand() % 2) {
							cout << "��ü����������Ӱ" << endl;
							bag[9]++;
						}
						else {
							cout << "��ü������츴��" << endl;
							bag[6]++;
						}
					}
					if (rand() % 4) {
						if (rand() % 5 == 0) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[22] += 4;
						}
						else if (rand() % 5 == 1) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[21] += 4;
						}
						else if (rand() % 5 == 2) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[19] += 4;
						}
						else if (rand() % 5 == 3) {
							cout << "�����ƿȫ��ҩˮ" << endl;
							bag[23] += 3;
						}
						else {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[20] += 4;
						}
					}
				}
			}
		}
		else {
			int f;
			cout << "��������¬��˹�������" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("�����", 10000, 1200, 250, 17, 2000);
				if (!dead) {
					if (rand() % 3) {
						if (rand() % 2) {
							cout << "��ü����������Ӱ" << endl;
							bag[9]++;
						}
						else {
							cout << "��ü������츴��" << endl;
							bag[6]++;
						}
					}
					if (rand() % 4) {
						if (rand() % 5 == 0) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[22] += 4;
						}
						else if (rand() % 5 == 1) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[21] += 4;
						}
						else if (rand() % 5 == 2) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[19] += 4;
						}
						else if (rand() % 5 == 3) {
							cout << "�����ƿȫ��ҩˮ" << endl;
							bag[23] += 3;
						}
						else {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[20] += 4;
						}
					}
				}
			}
		}
		if (!dead)
			if (ane1 == 2) D_Of_C1++;
		break;
	case 4:
		if (camp) {
			int f;
			cout << "����������ķ˹��¬ƽ" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("¬ƽ", 100000, 12000, 2500, 17, 4000);
				if (!dead) {
					if (rand() % 3) {
						if (rand() % 2) {
							cout << "��ü�����ָ����" << endl;
							bag[12]++;
						}
						else {
							cout << "��ü����鰢�ߴ�����" << endl;
							bag[18]++;
						}
					}
					if (rand() % 5) {
						if (rand() % 5 == 0) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[22] += 4;
						}
						else if (rand() % 5 == 1) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[21] += 4;
						}
						else if (rand() % 5 == 2) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[19] += 4;
						}
						else if (rand() % 5 == 3) {
							cout << "�����ƿȫ��ҩˮ" << endl;
							bag[23] += 3;
						}
						else {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[20] += 4;
						}
					}
				}
			}
		}
		else {
			int f;
			cout << "����������������������" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("�������", 100000, 12000, 2500, 170, 4000);
				if (!dead) {
					if (rand() % 3) {
						if (rand() % 2) {
							cout << "��ü�����ָ����" << endl;
							bag[12]++;
						}
						else {
							cout << "��ü����鰢�ߴ�����" << endl;
							bag[18]++;
						}
					}
					if (rand() % 5) {
						if (rand() % 5 == 0) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[22] += 4;
						}
						else if (rand() % 5 == 1) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[21] += 4;
						}
						else if (rand() % 5 == 2) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[19] += 4;
						}
						else if (rand() % 5 == 3) {
							cout << "�����ƿȫ��ҩˮ" << endl;
							bag[23] += 3;
						}
						else {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[20] += 4;
						}
					}
				}
			}
		}
		break;
	case 5:
		if (camp) {
			int f;
			cout << "�������˰���˼���˲�����" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("�˲�����", 300000, 36000, 7500, 20, 5000);
				if (!dead) {
					if (rand() % 3) {
						if (rand() % 2) {
							cout << "��ü�����ָ����" << endl;
							bag[12]++;
						}
						else {
							cout << "��ü����鰢�ߴ�����" << endl;
							bag[18]++;
						}
					}
					if (rand() % 5) {
						if (rand() % 5 == 0) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[22] += 4;
						}
						else if (rand() % 5 == 1) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[21] += 4;
						}
						else if (rand() % 5 == 2) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[19] += 4;
						}
						else if (rand() % 5 == 3) {
							cout << "�����ƿȫ��ҩˮ" << endl;
							bag[23] += 3;
						}
						else {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[20] += 4;
						}
					}
				}
			}
		}
		else {
			int f;
			cout << "���������ɼ���" << endl;
			cout << "1����/2����" << endl;
			cin >> f;
			if (f == 1) {
				fight("�ɼ���", 300000, 36000, 7500, 20, 5000);
				if (!dead) {
					if (rand() % 3) {
						if (rand() % 2) {
							cout << "��ü�����ָ����" << endl;
							bag[12]++;
						}
						else {
							cout << "��ü����鰢�ߴ�����" << endl;
							bag[18]++;
						}
					}
					if (rand() % 5) {
						if (rand() % 5 == 0) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[22] += 4;
						}
						else if (rand() % 5 == 1) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[21] += 4;
						}
						else if (rand() % 5 == 2) {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[19] += 4;
						}
						else if (rand() % 5 == 3) {
							cout << "�����ƿȫ��ҩˮ" << endl;
							bag[23] += 3;
						}
						else {
							cout << "�����ƿ����ҩˮ" << endl;
							bag[20] += 4;
						}
					}
				}
			}
		}
		if (!dead)
			if (ane1 == 0) D_Of_C1++;
		break;
	}
	Sleep(1000);
	return 0;
}
int buy(int p, int m)
{
	if (money < m) {
		cout << "ûǮ�����ȥ��" << endl;
		if (camp) {
			cout << "1���� 2����" << endl;
			int a;
			cin >> a;
			if (a == 1) {
				fight("Ա��", 1000, 100, 10, 0, 1000);
				if (dead) return 0;
				cout << "����һ��Ա�����˹���" << endl;
				fight("Ա��", 1000, 100, 10, 14, 1000);
				if (dead) return 0;
				cout << "����һ��Ա�����˹���" << endl;
				fight("Ա��", 1000, 100, 10, 14, 2000);
				if (dead) return 0;
				cout << "Ա��ͷ���˹���" << endl;
				fight("Ա��ͷ", 5000, 5000, 10, 14, 2000);
				if (dead) return 0;
				cout << "�������˹���" << endl;
				fight("����", 10000, 1000, 100, 15, 4000);
				if (dead) return 0;
				cout << "���100Ԫ" << endl;
				money += 100;
				if (rand() % 10 < 3) {
					Sleep(3000);
					cout << "�㷭�˰��죬�����ҵ�����Ҫ���Ķ���" << endl;
					bag[p]++;
				}
				else {
					Sleep(3000);
					cout << "�㷭�˰��죬����û�ҵ���Ҫ���Ķ���" << endl;
					cout << "��Ҫ��Ҫ���������������ɱ�ˣ�" << endl;
					cout << "1Ҫ�� 2������" << endl;
					int q;
					cin >> q;
					if (q == 1) street();
				}
			}
		}
	}
	else {
		cout << "����ɹ�" << endl;
		bag[p]++;
		money -= m;
		if (ane == 1) D_Of_C++;
		if (ane1 == 1) D_Of_C1 += m;
	}
	Sleep(1000);
	return 0;
}
int buywand(int p, int m)
{
	if (money < m) cout << "ûǮ�����ȥ��" << endl;
	else {
		cout << "����ɹ�" << endl;
		wand[p - 6]++;
		money -= m;
		if (ane == 1) D_Of_C++;
		if (ane1 == 1) D_Of_C1 += m;
	}
	Sleep(1000);
	return 0;
}
int make(int w1, int w2, int c1, int c2)
{
	if (w1 < 24 || w2 < 33) {
		cout << "������û�����ֲ��ϣ�����Ϲ����" << endl;
		Sleep(1000);
		return 0;
	}
	if (c1 == 0||c2 == 0) {
		cout << "������0����������ħ�ȣ�û��!" << endl;
		Sleep(1000);
		return 0;
	}
	if (bag[w1] < c1) {
		if (bag[w2] < c2) cout << "��ľ�ĺ���о������";
		else cout << "��о����";
	}
	else if (bag[w2] < c2) cout << "ľ�Ĳ���";
	else {
		cout << "�����ɹ�" << endl;
		string wn;
		wn = Material1name[w1 - 24] + Material2name[w2 - 33] + "ħ��";
		bag[w1] -= c1;
		bag[w2] -= c2;
		wand[wandi++]++;
		wandpower[wandpoweri++] = c1 * 20 * (w1 - 4) + c1 * 10 * (w2 - 13);
		wandname[wandnamei++] = wn;
	}
	Sleep(1000);
	return 0;
}
int levelup()
{
	if (experience >= level * 100) {
		experience -= level * 100;
		level++;
		maxhealth += 100; health += 100; attack += 10; defense += 5; speed += 10;
		if (rand() % 2 && level > 4) bag[0] += 1;
		cout << "������1��" << endl;
		levelup();
		if (ane1 == 4) D_Of_C1++;
	}
	return 0;
}
int Hos()
{
	int a;
	if (health < maxhealth) {
		cout << "ʣ��������(" << health << "/" << maxhealth << ")" << endl;
		cout << "��Ҫ" << ((maxhealth) - health) / 16 << "Ԫ �Ƿ�ָ�. �ȼ�С�ڵ���10��ѻָ�" << endl;
		cout << "1,�� 2,��" << endl;
		cin >> a;
		if (a == 1) {
			if (level > 10) {
				if (money >= ((maxhealth) - health) / 16) {
					money -= ((maxhealth) - health) / 16;
					cout << "�ָ��ɹ�\nʣ�ࣺ" << money << "Ԫ";
					if (ane == 2) D_Of_C++;
					if (ane1 == 1) D_Of_C1 += ((maxhealth) - health) / 16;
					health = maxhealth;
				}
				else cout << "Ǯ����" << endl;
			}
			else {
				health = maxhealth;
				cout << "�ָ��ɹ�" << endl;
				if (ane == 2) D_Of_C++;
			}
		}
		else if (a == 2) return 0;
		else {
			cout << "�������";
			Hos();
		}
	}
	else {
		cout << "��������";
		Sleep(1000);
	}
	return 0;
}
int w()
{
	int aaaa = 1;
	while (aaaa) {
		for (int i = 0; i < wandi; i++) {
			if (wandname[i] == Nwand) cout << "o";
			else cout << " ";
			cout << i + 1 << "," << wandname[i] << " " << wand[i] << "��" << "  ������" << wandpower[i] << endl;
		}
		cout << "1��װ��ħ�� 2��ж������ħ�� 0���˳�" << endl;
		cin >> aaaa;
		if (aaaa == 1) {
			cout << "������ħ�ȱ��" << endl;
			int bbbb;
			cin >> bbbb;
			if (wand[bbbb - 1]) {
				if (Nwand != "����") {
					cout << "��װ��ħ��";
					Sleep(1000);
				}
				else {
					cout << "װ���ɹ�";
					Nwand = wandname[bbbb - 1];
					attack += wandpower[bbbb - 1];
				}
			}
			else {
				cout << "����δӵ�д�ħ��";
			}
			Sleep(1000);
		}
		else if (aaaa == 2) {
			for (int ia = 0; ia < wandi - 1; ia++) {
				if (Nwand == wandname[ia]) {
					cout << "�ɹ�ж��";
					attack -= wandpower[ia];
					break;
				}
			}
			Nwand = "����";
			Sleep(1000);
		}
		else if (aaaa == 0) break;
		else cout << "�������";
		levelup();
		system("cls");
		cout << "ħ����ʿ��" << name << endl;
		cout << "������";
		if (camp) cout << "����ħ" << endl;
		else cout << "��������" << endl;
		cout << "����:" << health << "/" << maxhealth << endl;
		cout << "����:" << attack << endl;
		cout << "����:" << defense << endl;
		cout << "�ٶ�:" << speed << endl;
		cout << "�ȼ�:" << level << endl;
		cout << "����:" << experience << "/" << level * 100 << endl;
		cout << "���:" << money << endl;
		cout << "1,ħ����(��������ռ��) 2,���(ɱ��/��ֹʳ��ͽ) 3,";
		if (camp) cout << "�����ִ�(�������ز���) ";
		else cout << "����ħ�ܲ�(����ħ����) ";
		cout << "4,�����ִ�(���ս��) 5,��������ħ���̵� 6,�齱 7,����ʯ�� 8,���� 9,���� 10,���ϵ� 11,���� 12,�ռ����� 13,���� 14,���� ";
		if (camp) cout << "15, ҽ�Ʊ�������ħ�ģ�";
		else cout << "15, �Ӹ���Ůʿ ";
		cout << "16,�ı����������ר�� ��Ҫ���룩 17,���� 18,�ǳ�" << endl;
		cout << "8" << endl;
		cout << "1,�鿴ħ�� 2,�鿴ҩˮ 3,�鿴����ʯ 4,ѧϰ����" << endl;
		cout << "1" << endl;
	}
	return 0;
}
int e()
{
	int bbbb = 1;
	while (bbbb) {
		cout << "1,����ʯR " << bag[1] << "��" << endl;
		cout << "2,����ʯSR " << bag[2] << "��" << endl;
		cout << "3,����ʯSSR " << bag[3] << "��" << endl;
		cout << "4,����ʯSSS " << bag[4] << "��" << endl;
		cout << "5,����ʯX " << bag[5] << "��" << endl;
		cout << "0,�˳� 6,һ��ʹ��";
		int aaaa;
		cin >> bbbb;
		switch (bbbb)
		{
		case 1:
			cout << "������";
			cin >> aaaa;
			if (bag[1] >= aaaa) {
				cout << "���óɹ�";
				experience += aaaa * 100;
				bag[1] -= aaaa;
				Sleep(1000);
				break;
			}
			break;
		case 2:
			cout << "������";
			cin >> aaaa;
			if (bag[2] >= aaaa) {
				cout << "���óɹ�";
				experience += aaaa * 250;
				bag[2] -= aaaa;
				Sleep(1000);
				break;
			}
			break;
		case 3:
			cout << "������";
			cin >> aaaa;
			if (bag[3] >= aaaa) {
				cout << "���óɹ�";
				experience += aaaa * 500;
				bag[3] -= aaaa;
				Sleep(1000);
				break;
			}
			break;
		case 4:
			cout << "������";
			cin >> aaaa;
			if (bag[4] >= aaaa) {
				cout << "���óɹ�";
				experience += aaaa * 1200;
				bag[4] -= aaaa;
				Sleep(1000);
				break;
			}
			break;
		case 5:
			cout << "������";
			cin >> aaaa;
			if (bag[5] >= aaaa) {
				cout << "���óɹ�";
				experience += aaaa * 2500;
				bag[5] -= aaaa;
				Sleep(1000);
				break;
			}
			break;
		case 0:
			break;
		case 6:
			cout << "���óɹ�";
			experience += bag[1] * 100;
			experience += bag[2] * 250;
			experience += bag[3] * 500;
			experience += bag[4] * 1200;
			experience += bag[5] * 2500;
			bag[1] = bag[2] = bag[3] = bag[4] = bag[5] = 0;
			break;
		default:
			cout << "�������";
			Sleep(1000);
			break;
		}
		levelup();
		system("cls");
		cout << "ħ����ʿ��" << name << endl;
		cout << "������";
		if (camp) cout << "����ħ" << endl;
		else cout << "��������" << endl;
		cout << "����:" << health << "/" << maxhealth << endl;
		cout << "����:" << attack << endl;
		cout << "����:" << defense << endl;
		cout << "�ٶ�:" << speed << endl;
		cout << "�ȼ�:" << level << endl;
		cout << "����:" << experience << "/" << level * 100 << endl;
		cout << "���:" << money << endl;
		cout << "1,ħ����(��������ռ��) 2,���(ɱ��/��ֹʳ��ͽ) 3,";
		if (camp) cout << "�����ִ�(�������ز���) ";
		else cout << "����ħ�ܲ�(����ħ����) ";
		cout << "4,�����ִ�(���ս��) 5,��������ħ���̵� 6,�齱 7,����ʯ�� 8,���� 9,���� 10,���ϵ� 11,���� 12,�ռ����� 13,���� 14,���� ";
		if (camp) cout << "15, ҽ�Ʊ�������ħ�ģ�";
		else cout << "15, �Ӹ���Ůʿ ";
		cout << "16,�ı����������ר�� ��Ҫ���룩 17,���� 18,�ǳ�" << endl;
		cout << "8" << endl;
		cout << "1,�鿴ħ�� 2,�鿴ҩˮ 3,�鿴����ʯ 4,ѧϰ����" << endl;
		cout << "3" << endl;
	}
	return 0;
}
int p()
{
	int bbbb = 1;
	while (bbbb) {
		cout << "1,����ҩˮ " << bag[19] << "��" << endl;
		cout << "2,����ҩˮ " << bag[20] << "��" << endl;
		cout << "3,����ҩˮ " << bag[21] << "��" << endl;
		cout << "4,����ҩˮ " << bag[22] << "��" << endl;
		cout << "5,�ٶ�ҩˮ " << bag[23] << "��" << endl;
		cout << "6,ȫ��ҩˮ " << bag[23] << "��" << endl;
		cout << "0,�˳� 7,һ��ʹ��";
		cin >> bbbb;
		int aaaa;
		switch (bbbb)
		{
		case 1:
			cout << "������";
			cin >> aaaa;
			if (bag[19] >= aaaa) {
				cout << "���óɹ�";
				health += aaaa * 50;
				maxhealth += aaaa * 50;
				bag[19] -= aaaa;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 2:
			cout << "������";
			cin >> aaaa;
			if (bag[20] >= aaaa) {
				cout << "���óɹ�";
				defense += aaaa * 10;
				bag[20] -= aaaa;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 3:
			cout << "������";
			cin >> aaaa;
			if (bag[21] >= aaaa) {
				cout << "���óɹ�";
				attack += aaaa * 25;
				bag[21] -= aaaa;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 4:
			cout << "������";
			cin >> aaaa;
			if (bag[22] >= aaaa) {
				cout << "���óɹ�";
				experience += aaaa * 200;
				bag[22] -= aaaa;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 5:
			cout << "������";
			cin >> aaaa;
			if (bag[43] >= aaaa) {
				cout << "���óɹ�";
				speed += aaaa;
				bag[43] -= aaaa;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 6:
			cout << "������";
			cin >> aaaa;
			if (bag[23] >= aaaa) {
				cout << "���óɹ�";
				health += aaaa * 50;
				maxhealth += aaaa * 50;
				defense += aaaa * 10;
				attack += aaaa * 25;
				experience += aaaa * 200;
				speed += aaaa;
				bag[23] -= aaaa;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 7:
			cout << "���óɹ�";
			health += bag[19] * 50;
			maxhealth += bag[19] * 50;
			defense += bag[20] * 10;
			attack += bag[21] * 25;
			experience += bag[22] * 200;
			speed += bag[43];
			health += bag[23] * 50;
			maxhealth += bag[23] * 50;
			defense += bag[23] * 10;
			attack += bag[23] * 25;
			experience += bag[23] * 200;
			speed += bag[23];
			bag[19] = 0;
			bag[20] = 0;
			bag[21] = 0;
			bag[22] = 0;
			bag[23] = 0;
			bag[43] = 0;
			break;
		case 0:
			break;
		default:
			cout << "�������";
			Sleep(1000);
			break;
		}
		levelup();
		system("cls");
		cout << "ħ����ʿ��" << name << endl;
		cout << "������";
		if (camp) cout << "����ħ" << endl;
		else cout << "��������" << endl;
		cout << "����:" << health << "/" << maxhealth << endl;
		cout << "����:" << attack << endl;
		cout << "����:" << defense << endl;
		cout << "�ٶ�:" << speed << endl;
		cout << "�ȼ�:" << level << endl;
		cout << "����:" << experience << "/" << level * 100 << endl;
		cout << "���:" << money << endl;
		cout << "1,ħ����(��������ռ��) 2,���(ɱ��/��ֹʳ��ͽ) 3,";
		if (camp) cout << "�����ִ�(�������ز���) ";
		else cout << "����ħ�ܲ�(����ħ����) ";
		cout << "4,�����ִ�(���ս��) 5,��������ħ���̵� 6,�齱 7,����ʯ�� 8,���� 9,���� 10,���ϵ� 11,���� 12,�ռ����� 13,���� 14,���� ";
		if (camp) cout << "15, ҽ�Ʊ�������ħ�ģ�";
		else cout << "15, �Ӹ���Ůʿ ";
		cout << "16,�ı����������ר�� ��Ҫ���룩 17,���� 18,�ǳ�" << endl;
		cout << "8" << endl;
		cout << "1,�鿴ħ�� 2,�鿴ҩˮ 3,�鿴����ʯ 4,ѧϰ����" << endl;
		cout << "2" << endl;
	}
	return 0;
}
int sfunc()
{
	int bbbb = 1;
	while (bbbb) {
		cout << "1,��츴�� " << bag[6] << "��" << endl;
		cout << "2,���׻��� " << bag[7] << "��" << endl;
		cout << "3,��赹�� " << bag[8] << "��" << endl;
		cout << "4,�����Ӱ " << bag[9] << "��" << endl;
		cout << "5,����ͣ " << bag[10] << "��" << endl;
		cout << "6,ͳͳʯ�� " << bag[11] << "��" << endl;
		cout << "7,�ָ���� " << bag[12] << "��" << endl;
		cout << "8,�ٻ��� " << bag[13] << "��" << endl;
		cout << "9,һ���Կ� " << bag[14] << "��" << endl;
		cout << "10,����뷢 " << bag[15] << "��" << endl;
		cout << "11,������� " << bag[16] << "��" << endl;
		cout << "12,���ǳ��� " << bag[17] << "��" << endl;
		cout << "13,���ߴ����� " << bag[18] << "��" << endl;
		cout << "0���˳�";
		cin >> bbbb;
		switch (bbbb)
		{
		case 1:
			if (bag[6] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "�ܹ��ָ�200��Ѫ" << endl;
				bag[6] -= 1;
				Sl[0] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 2:
			if (bag[7] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "�ָܻ�100��Ѫ����50����" << endl;
				bag[7] -= 1;
				Sl[1] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 3:
			if (bag[8] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "��ʹ�Է���ͣһ�غ�" << endl;
				bag[8] -= 1;
				Sl[2] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 4:
			if (bag[9] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "������250���۶Է�500��Ѫ" << endl;
				bag[9] -= 1;
				Sl[3] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 5:
			if (bag[10] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "��ʹ�Է�����ʩ�ӵ�״̬û��" << endl;
				bag[10] -= 1;
				Sl[4] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 6:
			if (bag[11] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "%10�������¶Է�����10�غ�" << endl;
				cout << "%90�������¶Է�����2�غ�" << endl;
				bag[11] -= 1;
				Sl[5] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 7:
			if (bag[12] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "%50��������������" << endl;
				bag[12] -= 1;
				Sl[6] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 8:
			if (bag[13] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "���ٻ��������" << endl;
				bag[13] -= 1;
				Sl[7] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 9:
			if (bag[14] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "%90��ʹ�Է��޼���" << endl;
				cout << "%10��ʹ�Է�������Ϊ0" << endl;
				bag[14] -= 1;
				Sl[8] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 10:
			if (bag[15] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "�Է�һֱ��10��Ѫֱ���Է������%10�����" << endl;
				bag[15] -= 1;
				Sl[9] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 11:
			if (bag[16] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "�Է���Ѫ5�غϣ�ÿ�غϿ�200��" << endl;
				bag[16] -= 1;
				Sl[10] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 12:
			if (bag[17] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "�öԷ��Լ������Լ�����Ȼ�������㣩" << endl;
				bag[17] -= 1;
				Sl[11] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 13:
			if (bag[18] >= 1) {
				cout << "ѧϰ�ɹ�" << endl;
				cout << "�öԷ�ֱ�ӿ�3/4��Ѫ" << endl;
				bag[18] -= 1;
				Sl[12] = 1;
				Sleep(1000);
				break;
			}
			else cout << "��Ʒ����" << endl;
			break;
		case 0:
			break;
		default:
			cout << "�������";
			Sleep(1000);
			break;
		}
		system("cls");
		cout << "ħ����ʿ��" << name << endl;
		cout << "������";
		if (camp) cout << "����ħ" << endl;
		else cout << "��������" << endl;
		cout << "����:" << health << "/" << maxhealth << endl;
		cout << "����:" << attack << endl;
		cout << "����:" << defense << endl;
		cout << "�ٶ�:" << speed << endl;
		cout << "�ȼ�:" << level << endl;
		cout << "����:" << experience << "/" << level * 100 << endl;
		cout << "���:" << money << endl;
		cout << "1,ħ����(��������ռ��) 2,���(ɱ��/��ֹʳ��ͽ) 3,";
		if (camp) cout << "�����ִ�(�������ز���) ";
		else cout << "����ħ�ܲ�(����ħ����) ";
		cout << "4,�����ִ�(���ս��) 5,��������ħ���̵� 6,�齱 7,����ʯ�� 8,���� 9,���� 10,���ϵ� 11,���� 12,�ռ����� 13,���� 14,���� ";
		if (camp) cout << "15, ҽ�Ʊ�������ħ�ģ�";
		else cout << "15, �Ӹ���Ůʿ ";
		cout << "16,�ı����������ר�� ��Ҫ���룩 17,���� 18,�ǳ�" << endl;
		cout << "8" << endl;
		cout << "1,�鿴ħ�� 2,�鿴ҩˮ 3,�鿴����ʯ 4,ѧϰ����" << endl;
		cout << "4" << endl;
	}
	return 0;
}
int LD()
{
	cout << "ʣ��齱ȯ:" << bag[0] << "��" << endl;
	cout << "1,�齱 2,�˳�" << endl;
	int a;
	cin >> a;
	if (a == 1) {
		cout << "�鼸�Σ�";
		int num;
		cin >> num;
		if (bag[0] >= num) {
			bag[0] -= num;
			int num1 = 0, num2 = 0, num3 = 0, num4 = 0, num5 = 0;
			int num6 = 0, num7 = 0, num8 = 0, num9 = 0, num10 = 0;
			int num11 = 0;
			for (int i = 0; i < num; i++)
			{
				switch (rand() % 20)
				{
				case 0:
				case 1:
					num1++;
					bag[1]++;
					break;
				case 2:
				case 3:
					num2++;
					bag[2]++;
					break;
				case 4:
				case 5:
					num3++;
					bag[3]++;
					break;
				case 6:
				case 7:
					num4++;
					bag[4]++;
					break;
				case 8:
					num5++;
					bag[5]++;
					break;
				case 9:
				case 10:
					num6++;
					bag[19]++;
					break;
				case 11:
				case 12:
					num7++;
					bag[20]++;
					break;
				case 13:
				case 14:
					num8++;
					bag[21]++;
					break;
				case 15:
				case 16:
					num9++;
					bag[22]++;
					break;
				case 17:
					num10++;
					bag[23]++;
					break;
				case 18:
					num11 += 50;
					money += 50;
					break;
				case 19:
					num11 += 100;
					money += 100;
					break;
				}
			}
			cout << "�����˾���ʯR   " << num1 << "��" << endl;
			cout << "����ʯSR         " << num2 << "��" << endl;
			cout << "����ʯSSR        " << num3 << "��" << endl;
			cout << "����ʯSSS        " << num4 << "��" << endl;
			cout << "����ʯX          " << num5+10000000 << "��" << endl;
			cout << "����ҩˮ         " << num6+10000 << "��" << endl;
			cout << "����ҩˮ         " << num7 << "��" << endl;
			cout << "����ҩˮ         " << num8 << "��" << endl;
			cout << "����ҩˮ         " << num9 << "��" << endl;
			cout << "ȫ��ҩˮ         " << num10+100000 << "��" << endl;
			cout << "���             " << num11+10000 << "��" << endl;
		}
		else cout << "���ĳ齱ȯ����" << endl;
	}
	else if (a == 2) return 0;
	else {
		cout << "������䡣";
		system("cls");
		LD();
	}
	_getch();
	return 0;
}
int dig()
{
	cout << "�����ڿ�״̬";
	Sleep(1000);
	system("cls");
	int x = 0;
	while (1) {
		system("cls");
		cout << "��";Sleep(20);
		cout << "��";Sleep(20);
		cout << "��";Sleep(20);
		cout << ".";Sleep(20);
		cout << ".";Sleep(20);
		cout << "." << endl;
		x++;Sleep(50);
		int ad = rand() % 3;
		if (ad == 2) {
			ad = rand() % 100;
			if (ad < 6) {
				switch (rand() % 3)
				{
				case 0:
					cout << "���ڵ��˼����������䣡����" << endl;
					bag[7]++;
					break;
				case 1:
					cout << "���ڵ��˼���������ͣ������" << endl;
					bag[10]++;
					break;
				case 2:
					cout << "���ڵ��˼�����ʯ���䣡����" << endl;
					bag[11]++;
					break;
				}
				Sleep(500);
			}
			else if (ad >= 6 && ad < 20) {
				switch (rand() % 20)
				{
				case 0:
					cout << "���ڵ���ҹ����β�𣡣���" << endl;
					bag[32]+=1000000000;
					break;
				case 1:
				case 2:
					cout << "���ڵ��˶�����βë��" << endl;
					bag[30]+=100;
					break;
				case 3:
				case 4:
					cout << "���ڵ������񾭣�" << endl;
					bag[31]+=100;
					break;
				case 5:
				case 6:
					cout << "���ڵ��˷����ë��" << endl;
					bag[29]+=100;
					break;
				case 7:
				case 8:
					cout << "���ڵ���������" << endl;
					bag[27]+=100;
					break;
				case 9:
				case 10:
					cout << "���ڵ�������β��" << endl;
					bag[28]++;
					break;
				case 11:
				case 12:
				case 13:
					cout << "���ڵ�������ˮ�ֵ���ë" << endl;
					bag[26]++;
					break;
				case 14:
				case 15:
				case 16:
					cout << "���ڵ���è���Ӻ���" << endl;
					bag[24]++;
					break;
				case 17:
				case 18:
				case 19:
					cout << "���ڵ�������ͷ��" << endl;
					bag[25]++;
					break;
				}
				Sleep(500);
			}
			else if (ad >= 20 && ad < 50) {
				switch (rand() % 10)
				{
				case 0:
					cout << "���ڵ�����ľ" << endl;
					bag[33]++;
					break;
				case 1:
					cout << "���ڵ�������ľ" << endl;
					bag[34]+=1000000000;
					break;
				case 2:
					cout << "���ڵ��˶���ľ" << endl;
					bag[35]++;
					break;
				case 3:
					cout << "���ڵ���ɽ�ľ����" << endl;
					bag[36]++;
					break;
				case 4:
					cout << "���ڵ�����ľ" << endl;
					bag[37]++;
					break;
				case 5:
					cout << "���ڵ���еľ" << endl;
					bag[38]++;
					break;
				case 6:
					cout << "���ڵ���ɽë�ľ" << endl;
					bag[39]++;
					break;
				case 7:
					cout << "���ڵ�����ľ" << endl;
					bag[40]++;
					break;
				case 8:
					cout << "���ڵ���ӣ��ľ" << endl;
					bag[41]++;
					break;
				case 9:
					cout << "���ڵ����һ���ľ" << endl;
					bag[42]++;
					break;
				}
				Sleep(500);
			}
			else if (ad >= 50 && ad <= 100) {
				int as = rand() % 20 + 30;
				cout << "���ڵ���" << as << "���" << endl;
				money += as;
				Sleep(500);
			}
		}
		else if (ad == 1) {
			ad = rand() % 3;
			if (ad == 0) {
				cout << "�������˴�����" << endl;
				fight("������", 5000, 500, 50, 20, 1000);
				if (dead)
				{
					cout << "������" << endl;
					return 0;
				}
			}
			if (ad == 1) {
				cout<<"��������ʳ��ͽ" << endl;
				fight("ʳ��ͽ", 10000, 1000, 100, 17, 1000);
				if (dead)
				{
					cout << "������" << endl;
					return 0;
				}
			}
			if (ad == 2) {
				cout << "�������˻���" << endl;
				fight("��", 5000, 2000, 200, 17, 1000);
				if (dead)
				{
					cout << "������" << endl;
					return 0;
				}
			}
			cout << "�Ƿ�����ڿ�" << endl;
			cout << "1,�� 2,��" << endl;
			int ans;
			cin >> ans;
			if (ans == 2) return 0;
		}
	}
	return 0;
}
int clearance()
{
	system("cls");
	cout << "���ڳ��ڴ�������һ��ֽ��������д�ţ�";
	if (camp) {
		cout << "����ħ����֪����������...�Ҿ͸�����ɣ����ڻ����ִĵ��㣡" << endl;
		cout << "                                           ������������������" << endl;
	}
	else {
		cout << "����������, �㿴������ֽ����ʱ��, ���ǵ�У�Ѿ�������������, Ҫô��ǰ��������Ҫô�Ҿͻ�����ͬ����ͳͳɱ��������"<<endl;
		cout << "                                                                                               ��������ħ" << endl;
	}
	_getch();
	f = 1;
	return 0;
}
int maze()
{
	bool is[101][101];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			is[i][j] = false;
	int x = 8, y = 1;
	string a[100] = {
		"##################################################",
		"# 1   #   2  2 3#  #  1 #89#1#1# 1 1  #12  #3  #1#",
		"#2#1#5  # #1# #   ## # ##91  6   #9#7#11## # # 11#",
		"#   ## ## # # # #### # #####  # ####5##  # # #####",
		"#2########### # 4 #      ##  #####4    5##1# #189o",
		"# 1  1#     #2# ##  # ##   5#    ######### # #7#8#",
		"#1# #1 2# #     #  #9 # ### # ##2## #   ##  5#167#",
		"#  1## ## # # ### #4##  ##  6 #  3  ###   #####5##",
		"I 2 #### #### #  1 6   #1# ##  5###6##  # #11134##",
		"I  1  #      7 # # # #   227# #  #   # #2 #2#21#5#",
		"##1 #1  #1# ## 5 #   # #3####  #  1#5# # 1 111#6 #",
		"#  2##3##1# ### ## ### #    ## ####  # #1####### #",
		"# ##3  ##1###7#    ##### ##  #   ###3  4## 9   # #",
		"#23   #    3   # ##9 ##6 6##   ### 9## ##1 # #3  #",
		"# # #   # # ## # ##    ##7 ## # 9  ###9#11##2## ##",
		"### # #######  # 2 # #3 # # #  1## 1 1## ##1 #3  #",
		"#5  #2   ## # #### # #5#  # ### #8###1   #1# #1# #",
		"# # # #   # # 4 5  # #  # 7   # # #   ####  8  #9#",
		"#   2 # #42   # ##    # 11#2#3   9  # ##9  # #999#",
		"##################################################",
		};
	while (1) {
		is[x - 1][y - 1] = true;
		is[x - 1][y] = true;
		is[x - 1][y + 1] = true;
		is[x][y - 1] = true;
		is[x][y] = true;
		is[x][y + 1] = true;
		is[x + 1][y - 1] = true;
		is[x + 1][y] = true;
		is[x + 1][y + 1] = true;
		system("cls");
		cout << "����:" << health << "/" << maxhealth << endl;
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 50; j++) {
				if (is[i][j]) cout << a[i][j];
				else cout << "0";
			}
			cout << endl;
		}
		int ch;
		ch = _getch();
		if (ch == 'a') {
			if (a[x][y - 1] == ' ')
			{
				a[x][y - 1] = '@';
				a[x][y] = ' ';
				y -= 1;
			}
			else if ('0' <= a[x][y - 1] && a[x][y - 1] <= '9')
			{
				cout << "��������" << (int)(a[x][y - 1] - '0') << "�����ӭս�ɣ�";
				fight("����", 10000 * (a[x][y - 1] - '0'), 2500 * (a[x][y - 1] - '0'), 100 * (a[x][y - 1] - '0'), 20, 500 * (a[x][y - 1] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x][y - 1] = '@';
				a[x][y] = ' ';
				y -= 1;
				a[x][y] = ' ';
			}
			else if (a[x][y - 1] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳������ֵ����磬����˳��������ڴ��µĽ�����������" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x][y - 1] == 'o')
			{
				cout << "��ͨ����" << endl;
				_getch();
				clearance();
			}
		}
		if (ch == 'd') {
			if (a[x][y + 1] == ' ')
			{
				a[x][y + 1] = '@';
				a[x][y] = ' ';
				y += 1;
			}
			else if ('0' <= a[x][y + 1] && a[x][y + 1] <= '9')
			{
				cout << "��������" << (int)(a[x][y + 1] - '0') << "�����ӭս�ɣ�";
				fight("����", 10000 * (a[x][y + 1] - '0'), 2500 * (a[x][y + 1] - '0'), 100 * (a[x][y + 1] - '0'), 20, 500 * (a[x][y + 1] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x][y + 1] = '@';
				a[x][y] = ' ';
				y += 1;
				a[x][y] = ' ';
			}
			else if (a[x][y + 1] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳������ֵ����磬����˳��������ڴ��µĽ�����������" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x][y + 1] == 'o')
			{
				cout << "��ͨ����" << endl;
				_getch();
				clearance();
			}
		}
		if (ch == 'w') {
			if (a[x - 1][y] == ' ')
			{
				a[x - 1][y] = '@';
				a[x][y] = ' ';
				x -= 1;
			}
			else if ('0' <= a[x - 1][y] && a[x - 1][y] <= '9')
			{
				cout << "��������" << (int)(a[x - 1][y] - '0') << "�����ӭս�ɣ�";
				fight("����", 10000 * (a[x - 1][y] - '0'), 2500 * (a[x - 1][y] - '0'), 100 * (a[x - 1][y] - '0'), 20, 500 * (a[x - 1][y] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x - 1][y] = '@';
				a[x][y] = ' ';
				x -= 1;
				a[x][y] = ' ';
			}
			else if (a[x - 1][y] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳������ֵ����磬����˳��������ڴ��µĽ�����������" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x - 1][y] == 'o')
			{
				cout << "��ͨ����" << endl;
				_getch();
				clearance();
			}
		}
		if (ch == 's') {
			if (a[x + 1][y] == ' ')
			{
				a[x + 1][y] = '@';
				a[x][y] = ' ';
				x += 1;
			}
			else if ('0' <= a[x + 1][y] && a[x + 1][y] <= '9')
			{
				cout << "��������" << (int)(a[x + 1][y] - '0') << "�����ӭս�ɣ�";
				fight("����", 10000 * (a[x + 1][y] - '0'), 2500 * (a[x + 1][y] - '0'), 100 * (a[x + 1][y] - '0'), 20, 500 * (a[x + 1][y] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x + 1][y] = '@';
				a[x][y] = ' ';
				x += 1;
				a[x][y] = ' ';
			}
			else if (a[x + 1][y] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳������ֵ����磬����˳��������ڴ��µĽ�����������" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x + 1][y] == 'o')
			{
				cout << "��ͨ����" << endl;
				_getch();
				clearance();
			}
		}
	}
	return 0;
}
int DriveOut()
{
	switch (rand() % 3)
	{
	case 1:
		cout << "������ûǮ���������������ȥ������" << endl;
		break;
	case 2:
		cout << "������ʲô��ûǮ������" << endl;
		break;
	case 3:
		cout << "�㣺�ɲ����Խ�һ���ۣ�" << endl;
		cout << "���������У�������ô�򵥣�" << endl;
		break;
	}
	Sleep(1000);
	return 0;
}
int poisonshop()
{
	system("cls");
	cout << "��������λ���ˣ���Ҫ��ʲô��" << endl;
	cout << "1,����      |С����ҩˮ+200|     100Ԫ" << endl;
	cout << "2,����     ||������ҩˮ+500||    200Ԫ" << endl;
	cout << "3,����      |С����ҩˮ +20|     100Ԫ" << endl;
	cout << "4,����     ||�����ҩˮ +50||    200Ԫ" << endl;
	cout << "5,����      |С����ҩˮ+100|     100Ԫ" << endl;
	cout << "6,����     ||�󹥻�ҩˮ+250||    200Ԫ" << endl;
	cout << "7,����        |Сȫ��ҩˮ|       500Ԫ" << endl;
	cout << "8,����       ||��ȫ��ҩˮ||      1000Ԫ" << endl;
	cout << "9,����      |||��ȫ��ҩˮ|||     2000Ԫ" << endl;
	cout << "10,���� *|||||����ȫ��ҩˮ|||||*  10000Ԫ" << endl;
	cout << "���������Լ���Ǯ����������" << money << "Ԫ" << endl;
	int which;
	cin >> which;
	switch (which)
	{
	case 1:
		if (money < 100) DriveOut();
		else {
			money -= 100;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			health += 200;
			maxhealth += 200;
		}
		break;
	case 2:
		if (money < 200) DriveOut();
		else {
			money -= 200;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			health += 500;
			maxhealth += 500;
		}
		break;
	case 3:
		if (money < 100) DriveOut();
		else {
			money -= 100;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			defense += 20;
		}
		break;
	case 4:
		if (money < 200) DriveOut();
		else {
			money -= 200;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			defense += 50;
		}
		break;
	case 5:
		if (money < 100) DriveOut();
		else {
			money -= 100;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			attack += 100;
		}
		break;
	case 6:
		if (money < 200) DriveOut();
		else {
			money -= 200;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			attack += 250;
		}
		break;
	case 7:
		if (money < 500) DriveOut();
		else {
			money -= 500;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			health += 50;
			defense += 5;
			attack += 25;
			experience += 1000;
		}
		break;
	case 8:
		if (money < 1000) DriveOut();
		else {
			money -= 1000;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			health += 150;
			defense += 15;
			attack += 75;
			experience += 3000;
		}
		break;
	case 9:
		if (money < 2000) DriveOut();
		else {
			money -= 2000;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			health += 450;
			defense += 45;
			attack += 225;
			experience += 9000;
		}
		break;
	case 10:
		if (money < 10000) DriveOut();
		else {
			money -= 10000;
			cout << "������һ·�ߺã�" << endl;
			cout << "������ҩˮ�ͺ�����ȥ��" << endl;
			health += 2500;
			defense += 250;
			attack += 1250;
			experience += 50000;
		}
		break;
	default:
		break;
	}
	Sleep(1000);
	return 0;
}
int bookshop()
{
	system("cls");
	cout << "��������������ʦ������ĵط�����Ҫ��ʲô��" << endl;
	cout << "1,����  ||||�ָ����������||||   40000Ԫ  �ֻ�������Ӧ" << endl;
	cout << "2,����     ||�����似����||      10000Ԫ  �Ѿ�����" << endl;
	cout << "3,����    |||�����似����|||     15000Ԫ  �ֻ�������Ӧ" << endl;
	cout << "4,����    |||�ٻ��似����|||     20000Ԫ  �ֻ�������Ӧ" << endl;
	cout << "5,���� *|||||����ͣ������|||||*  25000Ԫ  �ֻ�������Ӧ" << endl;
	cout << "6,����   ||||����似����||||    20000Ԫ  �ֻ�������Ӧ" << endl;
	cout << "7,����    ||���뷢������||     15000Ԫ  �ֻ�������Ӧ" << endl;
	cout << "���������Լ���Ǯ����������" << money << "Ԫ" << endl;
	int which;
	cin >> which;
	switch (which)
	{
	case 1:
		if (money < 40000) DriveOut();
		else {
			money -= 40000;
			cout << "������һ·�ߺã�" << endl;
			bag[12]++;
		}
		break;
	case 2:
		cout << "�������Բ��𣬱����Ѿ�����" << endl;
		break;
	case 3:
		if (money < 20000) DriveOut();
		else {
			money -= 20000;
			cout << "������һ·�ߺã�" << endl;
			bag[16]++;
		}
		break;
	case 4:
		if (money < 20000) DriveOut();
		else {
			money -= 20000;
			cout << "������һ·�ߺã�" << endl;
			bag[13]++;
		}
		break;
	case 5:
		if (money < 25000) DriveOut();
		else {
			money -= 25000;
			cout << "������һ·�ߺã�" << endl;
			bag[10]++;
		}
		break;
	case 6:
		if (money < 20000) DriveOut();
		else {
			money -= 20000;
			cout << "������һ·�ߺã�" << endl;
			bag[17]++;
		}
		break;
	case 7:
		if (money < 15000) DriveOut();
		else {
			money -= 15000;
			cout << "������һ·�ߺã�" << endl;
			bag[15]++;
		}
		break;
	default:
		break;
	}
	return 0;
}
int NoticeBoard(int l, int x, int y)
{
	if (l == 10 && x == 6 && y == 1) {
		system("cls");
		cout << "����'*'��" << endl;
		cout << "     ��������" << endl;
		_getch();
	}
	if (l == 10 && x == 8 && y == 12) {
		system("cls");
		cout << "�߰ɣ�˭���㲻��������..." << endl;
		cout << "                  ��������" << endl;
		_getch();
	}
	if (l == 12 && x == 3 && y == 1) {
		system("cls");
		cout << "ɱ����Χ��" << endl;
		cout << "      ��������" << endl;
		_getch();
	}
	if (l == 12 && x < 4 && y == 20) {
		system("cls");
		cout << "��ϲͨ��һ�룡�����߼���..." << endl;
		cout << "       ��������" << endl;
		_getch();
	}
	if (l == 12 && x > 4 && y == 20) {
		system("cls");
		cout << "��ϲͨ��һ�룡�����߼���..." << endl;
		cout << "       ��������" << endl;
		_getch();
	}
	if (l == 12 && x == 10) {
		system("cls");
		cout << "����ȫ�������ɣ�" << endl;
		cout << "       ��������" << endl;
		_getch();
	}
	else {
		system("cls");
		cout << "��ȥ�ɣ�������ط���..." << endl;
		_getch();
	}
	return 0;
}
int checkpoint(int l)
{
	bool is[101][101];
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			is[i][j] = false;
	int x = 1, y = 1;
	string a[100];
	if (l == 1) {
		a[0] = "######";
		a[1] = "I    o";
		a[2] = "######";
	}
	else if (l == 2) {
		a[0] = "#######";
		a[1] = "I    1#";
		a[2] = "#### ##";
		a[3] = "##1  ##";
		a[4] = "#### ##";
		a[5] = "#P    o";
		a[6] = "#######";
	}
	else if (l == 3) {
		a[0] = "#########";
		a[1] = "I #  1#S#";
		a[2] = "# ## ##1#";
		a[3] = "# 2     #";
		a[4] = "#### ## #";
		a[5] = "#P1  #o #";
		a[6] = "#########";
	}
	else if (l == 4) {
		a[0] = "#######o#######";
		a[1] = "I       #P3   #";
		a[2] = "#       ##### #";
		a[3] = "#         1P  #";
		a[4] = "#       ##### #";
		a[5] = "#S      #    2#";
		a[6] = "######### #####";
		a[7] = "#P121 2 1  11P#";
		a[8] = "###############";
	}
	else if (l == 5) {
		a[0] = "###############";
		a[1] = "I 3     #P3   #";
		a[2] = "# 3 #   ##### #";
		a[3] = "# 2 #     1   #";
		a[4] = "# 2 # # ##### #";
		a[5] = "# 1 # #P#    2#";
		a[6] = "#####2S## ###o#";
		a[7] = "#P1 1 # 1   1P#";
		a[8] = "###############";
	}
	else if (l == 6) {
		a[0] = "###############";
		a[1] = "#   11  2  6PP#";
		a[2] = "#2# #P#########";
		a[3] = "#2##### #S#   o";
		a[4] = "I       #2# ###";
		a[5] = "# #####  11 ###";
		a[6] = "# #P##### #####";
		a[7] = "#1112       4P#";
		a[8] = "###############";
		x = 4;
	}
	else if (l == 7) {
		a[0] = "###############";
		a[1] = "#3 4#  P#  # B#";
		a[2] = "#1# #9## 1#  3#";
		a[3] = "#1#6# 9#  # ###";
		a[4] = "I #7   94 # # o";
		a[5] = "# #1 3 ##  P# #";
		a[6] = "# ########### #";
		a[7] = "#       1  P  #";
		a[8] = "###############";
		x = 4;
	}
	else if (l == 8) {
		a[0]  = "#################";
		a[1]  = "#PPPPPPPPPPPPPPP#";
		a[2]  = "#P#############P#";
		a[3]  = "#PPPP 9999999 PP#";
		if (rand() % 100 < 7) a[4] = "#################";
		else a[4] = "######### #######";
		a[5]  = "#2 2#2 2#9##2  P#";
		a[6]  = "# # # # # #22#  #";
		a[7]  = "# # # # # # #22##";
		a[8]  = "I # # # # # # # o";
		a[9]  = "##22# # # # # # #";
		a[10] = "#  #22# #3# # # #";
		a[11] = "#P  2##2 5 2#2 2#";
		a[12] = "#################";
		x = 8;
	}
	else if (l == 9) {
		a[0] = "#################";
		a[1] = "I     9###9     I";
		a[2] = "#      # #      #";
		a[3] = "#    ##P9P##    #";
		a[4] = "#   9# 9o9 #9   #";
		a[5] = "#    ##P9P##    #";
		a[6] = "#      # #      #";
		a[7] = "I     9###9     I";
		a[8] = "#################";
		if (rand() % 2) x = 7;
		if (rand() % 2) y = 15;
	}
	else if (l == 10) {
		a[0] = "#############################";
		a[1] = "#00*****009***P0000000000000#";
		a[2] = "#0*9000*00*000*0**P000000000#";
		a[3] = "#0*000**00*0#0*0900*****00**o";
		a[4] = "#0*00**00*90#0******000****0#";
		a[5] = "#0*00*00**00#0000000***00000#";
		a[6] = "#T*00*90*00##################";
		a[7] = "I**000***00#================I";
		a[8] = "############T################";
		x = 7;
		y = 1;
	}
	else if (l == 11) {
		a[0] = "#############################";
		a[1] = "#        33344555#P         #";
		a[2] = "#22222P  33344566#P         ##";
		a[3] = "#11   2  33344567#7 8 8 8 8 9######################";
		a[4] = "I 1   2  33344567           999999999999999  PPPPo#";
		a[5] = "#11   2  33344567#7 8 8 8 8 9######################";
		a[6] = "#22222P  33344566#P         ##";
		a[7] = "#        33344555#P         #";
		a[8] = "#############################";
		x = 4;
		y = 1;
	}
	else if (l == 12) {
		a[0] = "###################################################";
		a[1] = "#999999999999999999.T.999999999P999999999999999999#";
		a[2] = "#9999999999.99.99.99T.999999999P999999999999999999#";
		a[3] = "#T9...99.99999999999T.999999999P9999999999999999..#";
		a[4] = "I...9.9.9999.999.99...999999999P9999999999999999.X#";
		a[5] = "#T9...99999999.99999T.999999999P9999999999999999..#";
		a[6] = "#9999999.99.999.99.9T.999999999P999999999999999999#";
		a[7] = "#99999.9999999999999T.999999999P999999999999999999#";
		a[8] = "###################################################";
		a[9] = "#oPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP #";
		a[10] = "#################################################T#";
		x = 4;
		y = 1;
	}
	else {
		a[0] = "#############################";
		a[1] = "#T                         T#";
		a[2] = "#                           #";
		a[3] = "#                           #";
		a[4] = "#                           #";
		a[5] = "#                           #";
		a[6] = "#                           #";
		a[7] = "I                          T#";
		a[8] = "#############################";
		x = 7;
		y = 1;
		for (int i = 0; i < 100; i++)
			for (int j = 0; j < 100; j++) is[i][j] = true;
	}
	a[x][y] = '@';
	while (1) {
		is[x - 1][y - 1] = true;
		is[x - 1][y] = true;
		is[x - 1][y + 1] = true;
		is[x][y - 1] = true;
		is[x][y] = true;
		is[x][y + 1] = true;
		is[x + 1][y - 1] = true;
		is[x + 1][y] = true;
		is[x + 1][y + 1] = true;
		system("cls");
		cout << "����:" << health << "/" << maxhealth << endl;
		cout << "����:" << attack << endl;
		cout << "����:" << defense << endl;
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 50; j++) {
				if (is[i][j]) cout << a[i][j];
				else cout << "0";
			}
			cout << endl;
		}
		int ch;
		ch = _getch();
		if (ch == 'a') {
			if ('0' < a[x][y - 1] && a[x][y - 1] <= '9')
			{
				cout << "��������" << (int)(a[x][y - 1] - '0') << "�����ӭս�ɣ�";
				fight("����", 1000 * (a[x][y - 1] - '0'), 250 * (a[x][y - 1] - '0'), 10 * (a[x][y - 1] - '0'), 12, 50 * (a[x][y - 1] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x][y - 1] = '@';
				a[x][y] = ' ';
				y--;
				a[x][y] = ' ';
			}
			else if (a[x][y - 1] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳���" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x][y - 1] == 'o')
			{
				cout << "��ͨ����" << endl;
				if (nowlevel + 1 == l)
				{
					nowlevel++;
				}
				_getch();
				return 0;
			}
			else if (a[x][y - 1] == 'P')
			{
				int m1 = rand() % 50;
				int m2 = rand() % 2;
				int m3 = rand() % 2;
				int m4 = rand() % 2;
				int m5 = rand() % 2;
				int m6 = rand() % 2;
				cout << "������:" << endl;
				cout << m1 << "Ԫ" << endl;
				cout << m2 << "ƿ����ҩˮ" << endl;
				cout << m3 << "ƿ����ҩˮ" << endl;
				cout << m4 << "ƿ����ҩˮ" << endl;
				cout << m5 << "ƿ����ҩˮ" << endl;
				cout << m6 << "ƿȫ��ҩˮ" << endl;
				money += m1;
				bag[19] += m2;
				bag[20] += m3;
				bag[21] += m4;
				bag[22] += m5;
				bag[23] += m6;
				_getch();
				a[x][y - 1] = '@';
				a[x][y] = ' ';
				y--;
			}
			else if (a[x][y - 1] == 'S')
			{
				poisonshop();
			}
			else if (a[x][y - 1] == 'B')
			{
				bookshop();
			}
			else if (a[x][y - 1] == 'T')
			{
				NoticeBoard(l, x, y - 1);
			}
			else if (a[x][y - 1] == '0' && l == 10)
			{
				a[x][y] = '0';
				x = 7;
				y = 12;
				a[x][y] = '@';
			}
			else if (a[x][y - 1] == 'X' && l == 12)
			{
				a[x][y] = ' ';
				x = 9;
				y = 49;
				a[x][y] = '@';
			}
			else if (a[x][y - 1] != '#')
			{
				a[x][y - 1] = '@';
				a[x][y] = ' ';
				y -= 1;
			}
			if (l == 9 && x == 4 && y == 12)
			{
				a[x][y - 2] = '@';
				a[x][y] = ' ';
				y -= 2;
			}
		}
		if (ch == 'd') {
			if ('0' < a[x][y + 1] && a[x][y + 1] <= '9')
			{
				cout << "��������" << (int)(a[x][y + 1] - '0') << "�����ӭս�ɣ�";
				fight("����", 1000 * (a[x][y + 1] - '0'), 250 * (a[x][y + 1] - '0'), 10 * (a[x][y + 1] - '0'), 12, 50 * (a[x][y + 1] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x][y + 1] = '@';
				a[x][y] = ' ';
				y++;
				a[x][y] = ' ';
			}
			else if (a[x][y + 1] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳���" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x][y + 1] == 'o')
			{
				cout << "��ͨ����" << endl;
				if (nowlevel + 1 == l)
				{
					nowlevel++;
				}
				_getch();
				return 0;
			}
			else if (a[x][y + 1] == 'P')
			{
				int m1 = rand() % 50;
				int m2 = rand() % 2;
				int m3 = rand() % 2;
				int m4 = rand() % 2;
				int m5 = rand() % 2;
				int m6 = rand() % 2;
				cout << "������:" << endl;
				cout << m1 << "Ԫ" << endl;
				cout << m2 << "ƿ����ҩˮ" << endl;
				cout << m3 << "ƿ����ҩˮ" << endl;
				cout << m4 << "ƿ����ҩˮ" << endl;
				cout << m5 << "ƿ����ҩˮ" << endl;
				cout << m6 << "ƿȫ��ҩˮ" << endl;
				money += m1;
				bag[19] += m2;
				bag[20] += m3;
				bag[21] += m4;
				bag[22] += m5;
				bag[23] += m6;
				_getch();
				a[x][y + 1] = '@';
				a[x][y] = ' ';
				y++;
			}
			else if (a[x][y + 1] == 'S')
			{
				poisonshop();
			}
			else if (a[x][y + 1] == 'B')
			{
				bookshop();
			}
			else if (a[x][y + 1] == 'T')
			{
				NoticeBoard(l, x, y + 1);
			}
			else if (a[x][y + 1] == '0' && l == 10)
			{
				a[x][y] = '0';
				x = 7;
				y = 12;
				a[x][y] = '@';
			}
			else if (a[x][y + 1] == 'X' && l == 12)
			{
				a[x][y] = ' ';
				x = 9;
				y = 49;
				a[x][y] = '@';
			}
			else if (a[x][y + 1] != '#')
			{
				a[x][y + 1] = '@';
				a[x][y] = ' ';
				y++;
			}
			if (l == 9 && x == 4 && y == 4)
			{
				a[x][y + 2] = '@';
				a[x][y] = ' ';
				y += 2;
			}
		}
		if (ch == 'w') {
			if ('0' < a[x - 1][y] && a[x - 1][y] <= '9')
			{
				cout << "��������" << (int)(a[x - 1][y] - '0') << "�����ӭս�ɣ�";
				fight("����", 1000 * (a[x - 1][y] - '0'), 250 * (a[x - 1][y] - '0'), 10 * (a[x - 1][y] - '0'), 12, 50 * (a[x - 1][y] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x - 1][y] = '@';
				a[x][y] = ' ';
				x--;
				a[x][y] = ' ';
			}
			else if (a[x - 1][y] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳���" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x - 1][y] == 'o')
			{
				cout << "��ͨ����" << endl;
				if (nowlevel + 1 == l)
				{
					nowlevel++;
				}
				_getch();
				return 0;
			}
			else if (a[x - 1][y] == 'P')
			{
				int m1 = rand() % 50;
				int m2 = rand() % 2;
				int m3 = rand() % 2;
				int m4 = rand() % 2;
				int m5 = rand() % 2;
				int m6 = rand() % 2;
				cout << "������:" << endl;
				cout << m1 << "Ԫ" << endl;
				cout << m2 << "ƿ����ҩˮ" << endl;
				cout << m3 << "ƿ����ҩˮ" << endl;
				cout << m4 << "ƿ����ҩˮ" << endl;
				cout << m5 << "ƿ����ҩˮ" << endl;
				cout << m6 << "ƿȫ��ҩˮ" << endl;
				money += m1;
				bag[19] += m2;
				bag[20] += m3;
				bag[21] += m4;
				bag[22] += m5;
				bag[23] += m6;
				_getch();
				a[x - 1][y] = '@';
				a[x][y] = ' ';
				x--;
			}
			else if (a[x - 1][y] == 'S')
			{
				poisonshop();
			}
			else if (a[x - 1][y] == 'B')
			{
				bookshop();
			}
			else if (a[x - 1][y] == 'T')
			{
				NoticeBoard(l, x - 1, y);
			}
			else if (a[x - 1][y] == '0' && l == 10)
			{
				a[x][y] = '0';
				x = 7;
				y = 12;
				a[x][y] = '@';
			}
			else if (a[x - 1][y] == 'X' && l == 12)
			{
				a[x][y] = ' ';
				x = 9;
				y = 49;
				a[x][y] = '@';
			}
			else if (a[x - 1][y] != '#')
			{
				a[x - 1][y] = '@';
				a[x][y] = ' ';
				x -= 1;
			}
		}
		if (ch == 's') {
			if (a[x + 1][y] == ' ')
			{
				a[x + 1][y] = '@';
				a[x][y] = ' ';
				x += 1;
			}
			else if ('0' < a[x + 1][y] && a[x + 1][y] <= '9')
			{
				cout << "��������" << (int)(a[x + 1][y] - '0') << "�����ӭս�ɣ�";
				fight("����", 1000 * (a[x + 1][y] - '0'), 250 * (a[x + 1][y] - '0'), 10 * (a[x + 1][y] - '0'), 12, 50 * (a[x + 1][y] - '0'));
				if (dead)
				{
					Sleep(1000);
					return 0;
				}
				a[x + 1][y] = '@';
				a[x][y] = ' ';
				x++;
				a[x][y] = ' ';
			}
			else if (a[x + 1][y] == 'I')
			{
				cout << "���Ƿ�Ҫ�˳���" << endl;
				cout << "1ȷ�� 2ȡ��" << endl;
				int num;
				cin >> num;
				if (num == 1)
				{
					break;
				}
			}
			else if (a[x + 1][y] == 'o')
			{
				cout << "��ͨ����" << endl;
				if (nowlevel + 1 == l)
				{
					nowlevel++;
				}
				_getch();
				return 0;
			}
			else if (a[x + 1][y] == 'P')
			{
				int m1 = rand() % 50;
				int m2 = rand() % 2;
				int m3 = rand() % 2;
				int m4 = rand() % 2;
				int m5 = rand() % 2;
				int m6 = rand() % 2;
				cout << "������:" << endl;
				cout << m1 << "Ԫ" << endl;
				cout << m2 << "ƿ����ҩˮ" << endl;
				cout << m3 << "ƿ����ҩˮ" << endl;
				cout << m4 << "ƿ����ҩˮ" << endl;
				cout << m5 << "ƿ����ҩˮ" << endl;
				cout << m6 << "ƿȫ��ҩˮ" << endl;
				money += m1;
				bag[19] += m2;
				bag[20] += m3;
				bag[21] += m4;
				bag[22] += m5;
				bag[23] += m6;
				_getch();
				a[x + 1][y] = '@';
				a[x][y] = ' ';
				x++;
			}
			else if (a[x + 1][y] == 'S')
			{
				poisonshop();
			}
			else if (a[x + 1][y] == 'B')
			{
				bookshop();
			}
			else if (a[x + 1][y] == 'T')
			{
				NoticeBoard(l, x + 1, y);
			}
			else if (a[x + 1][y] == '0' && l == 10)
			{
				a[x][y] = '0';
				x = 7;
				y = 12;
				a[x][y] = '@';
			}
			else if (a[x + 1][y] == 'X' && l == 12)
			{
				a[x][y] = ' ';
				x = 9;
				y = 49;
				a[x][y] = '@';
			}
			else if (a[x + 1][y] != '#')
			{
				a[x + 1][y] = '@';
				a[x][y] = ' ';
				x++;
			}
		}
	}
	return 0;
}
int MM()
{
	if (amm == 0) {
		int lie = 0;
		cout << "....����45����,Ʈ��80��...." << endl;
		cout << "�������ɻ��:" << endl;
		cout << "�齱ȯ*100 �������赹�ػ����������� ȫ��ҩˮ*50";
		cout << " ���*2000 ����ʯX*50" << endl;
		cout << " 1���� 2��ǿ������" << endl;
		int a;
		cin >> a;
		if (a == 1) {
			cout << "��������ħ��������" << endl;
			Sleep(1000);
			cout << "ħ�������ſ���:��������" << endl;
			Sleep(1000);
			cout << "1���٣� 2���µġ�" << endl;
			cin >> a;
			if (a == 1) cout << "ħ�������ſ���:��������" << endl;
			else {
				if (camp) cout << "ħ�������ſ���:�����ܣ����Ƿ���ħ���ˣ�" << endl;
				else {
					cout << "ħ�������ſ�����ϸһ����" << endl;
					Sleep(1000);
					cout << "ħ�������ſ���:���ǹ������ص��ˣ�ץ�����ʹ����������䣡" << endl;
				}
			}
			Sleep(1000);
			fight("���ſ���", 2000, 200, 20, 0, 1000);
			if (dead) return 0;
			fight("���ſ���", 2000, 200, 20, 0, 1000);
			if (dead) return 0;
			cout << "����100��Ѫ" << endl;
			health += 100;
			Sleep(1000);
			cout << "���߿��˴���" << endl;
			Sleep(1000);
			cout << "����ļ����������" << endl;
			Sleep(1000);
			fight("����", 10000, 200, 20, 0, 500);
			if (dead) return 0;
			fight("����", 10000, 200, 20, 0, 500);
			if (dead) return 0;
			fight("����", 10000, 200, 20, 0, 500);
			if (dead) return 0;
			cout << "����500��Ѫ" << endl;
			health += 500;
			cout << "��ɱ���˵����, ��׼����¥����" << endl;
			Sleep(1000);
			cout << "ͻȻһȺԱ�����˹���" << endl;
			Sleep(1000);
			cout << "Ա����������������" << endl;
			Sleep(1000);
			cout << "1,����  ����,�ǣ�" << endl;
			cin >> a;
			if (a == 1) {
				cout << "Ա������˭�ɵģ�" << endl;
				Sleep(1000);
				cout << "�����ָ��һ��Ա��" << endl;
				Sleep(1000);
				cout << "����" << endl;
				Sleep(1000);
				cout << "��ȺԱ���Ҵ����˹�ȥ" << endl;
				Sleep(1000);
				cout << "��Ͽ�����¥��" << endl;
				Sleep(1000);
				lie = 1;
			}
			else {
				cout << "Ա�����ɵ�����" << endl;
				Sleep(1000);
				fight("Ա��", 3000, 200, 100, 14, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 14, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 14, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 15, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 17, 1000);
				if (dead) return 0;
				if (rand() % 3 == 0) {
					cout << "�����˼�����������" << endl;
					bag[7]++;
					Sleep(1000);
				}
				cout << "��Ͽ�����¥��" << endl;
				health += 500;
			}
			Sleep(1000);
			cout << "�������˸�����������˹����ķ����" << endl;
			Sleep(1000);
			fight("��ķ����", 10000, 1000, 100, 20, 3000);
			health += 5000;
			if (dead) return 0;
			if (lie) {
				cout << "�ϴε�Ա�����˹���" << endl;
				Sleep(1000);
				cout << "Ա��:�㣬��ƭ�����ǣ�" << endl;
				Sleep(1000);
				fight("Ա��", 3000, 200, 100, 14, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 14, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 14, 1000);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 15, 1500);
				if (dead) return 0;
				fight("Ա��", 3000, 200, 100, 17, 2000);
				if (dead) return 0;
				if (rand() % 3 == 0){
					cout << "�����˼�����������" << endl;
					bag[7]++;
					Sleep(1000);
				}
				health += 500;
			}
			cout << "�������˲���";
			fight("����", 15000, 1500, 150, 20, 4000);
			if (dead) return 0;
			cout << "����:" << endl;
			cout << "�齱ȯ*100 �������赹�ػ����������� ȫ��ҩˮ*50";
			cout << " ���*2000 ����ʯX*50" << endl;
			bag[0] += 100; bag[8]++; bag[23] += 50; money += 2000; bag[5] += 50; amm = 1;
			Sleep(3000);
		}
		else if (a == 2) return 0;
		else {
			cout << "��������";
			Sleep(1000);
		}
	}
	else {
		cout << "����ռ��ħ���� ���Խ������µط�" << endl;
		cout << "0,�˳� 1,����Ȫ 2,��" << endl;
		int b;
		cin >> b;
		switch (b)
		{
		case 0:
			break;
		case 1:
			time_t c_start, t_start, c_end, t_end;
			c_start = clock();
			t_start = time(NULL);
			cout << "��������Ȫ ���������ֹͣ" << endl;
			_getch();
			c_end = clock();
			t_end = time(NULL);
			cout << "����" << (int)difftime(c_end, c_start) / 100 << "Ԫ" << endl;
			cout << "����" << (int)difftime(c_end, c_start) / 10 << "����" << endl;
			experience += (int)difftime(c_end, c_start) / 10;
			money += (int)difftime(c_end, c_start) / 100;
			_getch();
			break;
		case 2:
			cout << "���߽���" << endl;
			Sleep(1000);
			ict++;
			if (ict == 5) cout << "�㲻С�Ŀ���ǽ��,�����˻���" << endl;
			else if (ict > 5) cout << "���ҵ�ԭ���������صĵط��������ǿ���ʯ���ܵ��ֳ�����" << endl;
			cout << "0,�˳� 1,�ڿ�";
			if (ict > 4) cout << " 2,����";
			cout << endl;
			int c;
			cin >> c;
			if (c == 1) dig();
			else if (c == 2 && ict > 4) {
				cout << "���߽�����" << endl;
				_getch();
				cout << "�㷢����һ����ȫ��ͬ�����磬��������˹���" << endl;
				_getch();
				cout << "ÿȥһ���ط����п�����������" << endl;
				_getch();
				cout << "������һ��ֱ�����������ɭ�֣������ҵ�ĳЩ����" << endl;
				_getch();
				MessageBox(0, TEXT("���� ����>60000 ����>20000 ����>2000 �ٶ�>1000 ʱ����"), TEXT("��Ҫ��ʾ"), MB_OK);
				if (MessageBox(0, TEXT("�� wasd �ƶ���o���ڣ�I��ڣ�@��"), TEXT("��Ҫ��ʾ"), MB_OKCANCEL | MB_ICONINFORMATION) != IDOK){
					MessageBox(0, TEXT("�´������ɣ�"), TEXT("��Ҫ��ʾ"), MB_OK);
					return 0;
				};
				cout << "��ʼ�ɣ�" << endl;
				maze();
			}
			else cout << "��������" << endl;
			Sleep(1000);
			break;
		}
	}
	return 0;
}
int finalfight(string Hname)
{
	int hisH = 1000000000, hisA = 1000000, hisD = 500000, hisSP = 5000;
	int hfaint = 0, hhurt = 0, hbeat = 0;
	int mfaint = 0, mhurt = 0;
	dead = false;
	int ha = hisA;
	int his = hisA + hisD + hisH;
	while (1)
	{
		if (hfaint > 0) {
			if (rand() % 3 == 0) {
				cout << "�Է�ʹ�ü��ܣ�����ͣ��ֹͣ��ħ��" << endl;
				hfaint = 1;
			}
			hfaint -= 1;
		}
		if (hbeat == 1) {
			if (rand() % 10 == 0) {
				cout << "�Է�һ�㣬��������ʯͷ" << endl;
				hbeat = 0;
			}
			else {
				cout << "�Է�����������ʯͷ����ײ�����ı����� ��Ѫ50��" << endl;
				hisH -= 50;
			}
		}
		if (mfaint > 0) {
			if (Sl[6]) mfaint = 0;
			else mfaint -= 1;
		}
		if (mhurt > 0) {
			if (Sl[6]) mhurt = 0;
			else {
				mhurt -= 1;
				cout << "�������һ�ѵ��̴���һ�� ��Ѫ200��" << endl;
				health -= 200;
			}
		}
		if (mfaint <= 0) {
			if (rand() % 3 && Sl[0]) {
				cout << "��ʹ�ü��ܿ�츴�� ��������200" << endl;
				health += 200;
			}
			if (rand() % 3 && Sl[1]) {
				cout << "��ʹ�ü������׻��� ��������100 ��������50" << endl;
				health += 100;
				defense += 50;
			}
			if (rand() % 3 && Sl[2]) {
				cout << "��ʹ�ü��ܻ�赹�� " << Hname << "һ�غ�֮�ڲ��ܹ���" << endl;
				hfaint += 1;
			}
			if (rand() % 3 && Sl[3]) {
				cout << "��ʹ�ü��������Ӱ ��������200 �Է���Ѫ200��" << endl;
				hisH -= 200;
				attack += 200;
			}
			if (rand() % 3 && Sl[5]) {
				if (rand() % 10) {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "���غ�֮�ڲ��ܹ���" << endl;
					hfaint += 2;
				}
				else {
					cout << "��ʹ�ü���ͳͳʯ�� " << Hname << "ʮ�غ�֮�ڲ��ܹ���" << endl;
					hfaint += 10;
				}
			}
			if (rand() % 4 == 0 && Sl[7]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
				hisH = monsterfight(Hname, hisH, hisA, hisD, 23, hisSP);
				if (hisH < 1)
				{
					cout << "�Է�����" << endl; Sleep(1000);
					cout << "ȫ���˶�����ף��" << endl; Sleep(1000);
					cout << "ͻȻ��" << Hname << "��ħ��һת��ָ�����㡣" << endl; Sleep(1000);
					cout << "���淢��һ����ɫ�Ĺ���" << endl; Sleep(1000);
					cout << "����æ��ħ��һ��" << endl; Sleep(1000);
					cout << "�ǹ����������ħ�ȣ���ը��" << endl; Sleep(1000);
					cout << "���ħ�ȶ���" << endl; Sleep(1000);
					cout << "�㱻ը��20����" << endl; Sleep(1000);
					cout << "δ�����..." << endl; Sleep(10000);
					return 0;
				}
				if (Sl[0]) {
					cout << "�ڶԷ���ʯ�ֵ�ս���У����Ѿ��ָ���2000����" << endl;
					if (maxhealth < health + 2000) health = maxhealth;
					else  health += 2000;
				}
			}
			if (rand() % 4 == 0 && Sl[8]) {
				cout << "��ʹ�ü����ٻ��䣡�ٻ���ʯ�ָ�" << Hname << "ս��" << endl;
			}
			if (rand() % 3 && Sl[9]) {
				cout << "��ʹ�ü������뷢�������ʮ��ʯͷ" << endl;
				hbeat = 1;
			}
			if (rand() % 3 && Sl[10]) {
				cout << "��ʹ�ü��������䣡�Է�����ʹ5�غ�" << endl;
				hhurt += 5;
			}
			if (rand() % 3 && Sl[11]) {
				cout << "���ǳ��ϣ���ʹ�ö���䣬��ͼ��" << Hname << "�Լ������Լ���" << endl;
				Sleep((rand() % 2000) + 1000);
				cout << Hname << "��������ˣ���ʼ�����Լ�" << endl;
				Sleep(700);
				int ran = rand() % 40 - 20;
				if (hisA + ran > hisD) {
					cout << "�Է�������� �Լ���Ѫ" << hisH - hisD + ran << "�� ʣ��" << hisH - (hisA - hisD + ran) << "��" << endl;
					hisH -= hisA - hisD + ran;
				}
				else cout << "�Է�������� �Լ���Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			if (rand() % 2 && Sl[12]) {
				cout << "��ʹ�ü��ܰ��ߴ����� " << Hname << "��Ѫ" << hisH - hisH / 4 << "��" << endl;
				hisH /= 4;
			}
			Sleep(1000);
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > hisSP) {
				if (attack + ran > hisD) {
					cout << "�㷢����� " << Hname << "��Ѫ" << attack - hisD + ran << "�� ʣ��" << hisH - (attack - hisD + ran) << "��" << endl;
					hisH -= attack - hisD + ran;
				}
				else cout << "�㷢����� " << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
			}
			else
			{
				if (rand() % 2) cout << "��һ�����˹�ȥ����û������" << endl;
				else {
					cout << "��һ�����˹�ȥ����ֻ��������" << endl;
					if ((attack / 3) + ran > hisD) {
						cout << Hname << "��Ѫ" << (attack / 3) + ran - hisD << "�� ʣ��" << hisH - ((attack / 3) + ran - hisD) << "��" << endl;
						hisH -= (attack / 3) + ran - hisD;
					}
					else  cout << Hname << "��Ѫ0�� ʣ��" << hisH << "��" << endl;
				}
			}
		}
		Sleep(700);
		if (hhurt > 0) {
			hhurt -= 1;
			cout << "�Է���������������䣬�������Ĵ���� ��Ѫ200��" << endl;
			hisH -= 200;
		}
		if (hisH <= 0) {
			if (rand() % 3 == 0) {
				cout << "�Է��������ܣ��ָ���� ��Ѫ����" << endl;
				hisH = ha;
				Sleep(1000);
			}
			else {
				cout << "�Է�����"<< endl; Sleep(1000);
				cout << "ȫ���˶�����ף��" << endl; Sleep(1000);
				cout << "ͻȻ��" << Hname << "��ħ��һת��ָ�����㡣" << endl; Sleep(1000);
				cout << "���淢��һ����ɫ�Ĺ���" << endl; Sleep(1000);
				cout << "����æ��ħ��һ��" << endl; Sleep(1000);
				cout << "�ǹ����������ħ�ȣ���ը��" << endl; Sleep(1000);
				cout << "���ħ�ȶ���" << endl; Sleep(1000);
				cout << "�㱻ը��20����" << endl; Sleep(1000);
				cout << "δ�����..." << endl; Sleep(10000);
				return 0;
			}
		}
		if (rand() % 3 == 0) {
			cout << "�Է��������ܣ���츴��  ������200" << endl;
			hisH += 200;
		}
		if (rand() % 3 == 0) {
			cout << "�Է��������ܣ����׻���  ������50 ��������50" << endl;
			hisH += 50;
			hisD += 50;
		}
		if (rand() % 3 == 0) {
			cout << "�Է�ʹ�ü��������Ӱ ��������200 ��Ѫ200��" << endl;
			health -= 200;
			hisA += 200;
		}
		if (rand() % 3 == 0) {
			cout << "�Է�ʹ�ü��ܻ�赹�� " << name << "һ�غ�֮�ڲ��ܹ���" << endl;
			mfaint += 1;
		}
		if (rand() % 3 == 0)
		{
			if (rand() % 10) {
				cout << "�Է�ʹ�ü���ͳͳʯ�� " << name << "���غ�֮�ڲ��ܹ���" << endl;
				mfaint += 2;
			}
			else {
				cout << "�Է�ʹ�ü���ͳͳʯ�� " << name << "ʮ�غ�֮�ڲ��ܹ���" << endl;
				mfaint += 10;
			}
		}
		if (rand() % 3 == 0) {
			cout << "�Է�ʹ�ü��ܰ��ߴ����� " << name << "��Ѫ" << health - health / 4 << "��" << endl;
			health /= 4;
		}
		Sleep(1000);
		if (hfaint <= 0) {
			int ran = rand() % 40 - 20;
			if (rand() % 10000 > speed) {
				if (hisA + ran > defense) {
					cout << Hname << "������� " << "���Ѫ" << hisA - defense + ran << "�� ʣ��" << health - (hisA - defense + ran) << "��" << endl;
					health -= hisA - defense + ran;
				}
				else cout << Hname << "������� " << "���Ѫ0�� ʣ��" << health << "��" << endl;
			}
			else {
				if (rand() % 2) cout << Hname << "һ�����˹�������û������" << endl;
				else {
					if ((hisA / 3) + ran > hisD) {
						cout << Hname << "������� ���Ѫ" << (hisA / 3) + ran - defense << "�� ʣ��" << health - ((hisA / 3) + ran - defense) << "��" << endl;
						health -= ((hisA / 3) + ran - defense);
					}
					else cout << Hname << "������� " << "���Ѫ0�� ʣ��" << health << "��" << endl;
				}
			}
			Sleep(1000);
			if (health <= 0) {
				if (Sl[6] && rand() % 2) {
					cout << "�㷢�����ܣ��ָ���� ��Ѫ����" << endl;
					health = maxhealth;
					Sleep(1000);
				}
				else {
					cout << "������";
					health = 20;
					dead = true;
					return 0;
				}
			}
		}
	}
	return 0;
}
int harrypotter_main()
{
	int isbreak;
	isbreak = false;
	if (MessageBox(0, TEXT("�����������⣬�벻Ҫ�����κ��ַ������򽫵�����Ϸ������"), TEXT("��Ҫ��ʾ"), MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
	{
		MessageBox(0, TEXT("��Ȼ�㲻ͬ�⣬�Ǿͱ�����"), TEXT("��Ҫ��ʾ"), MB_OK);
		return 0;
	};
	srand((unsigned)time(NULL));
	cout << "                              1.2.9 \n";
	cout << "      MagicWorld--HarryPotter       \n";
	cout << "                                    \n";
	cout << "         / >                        \n";
	cout << "        /    >          /           \n";
	cout << "       < _____ >       /            \n";
	cout << "        |-O--O-|      /             \n";
	cout << "       /   == - .    /              \n";
	cout << "     /           . [  ]             \n";
	cout << "       /      /` ___/               \n";
	cout << "                                    \n";
	cout << "                             by ��\n";
	cout << "���롮start����ʼ��Ϸ                  \n";
	string start;
	cin >> start;
	for (int i = 8; i < 100; i++) wandname[i] = "1";
	if (start == "start") {
		int i;
		system("cls");
		for (i = 0; i < 20; i++) {
			cout << "loading..." << endl << "--------------------------" << endl << "   ";
			for (int j = 0; j <= i % 5; j++) cout << "+==+";
			cout << "   " << endl << "--------------------------" << endl;
			switch (rand() % 4)
			{
			case 0:
				cout << "���������������ս���ĺ÷�����" << endl;
				break;
			case 1:
				cout << "��ʼ��Ϸʱ�ǵ�ѡ����Ӫ��" << endl;
				break;
			case 2:
				cout << "�˳�ʱҪ���档" << endl;
				break;
			case 3:
				cout << "���ֿ�ʼ��Ϸʱ����3ƿ����ҩˮ1�ų齱ȯ��" << endl;
				break;
			}
			Sleep(250);
			system("cls");
		}
		while (1)
		{
			isbreak = false;
			cout << "1,��¼ 2,ע��";
			int a;
			cin >> a;
			if (a == 1) login();
			else Reg();
			while (1) {
				if (isbreak)
				{
					break;
				}
				system("cls");
				cout << "ħ����ʿ��" << name << endl;
				cout << "������";
				if (camp) cout << "����ħ" << endl;
				else cout << "��������" << endl;
				cout << "����:" << health << "/" << maxhealth << endl;
				cout << "����:" << attack << endl;
				cout << "����:" << defense << endl;
				cout << "�ٶ�:" << speed << endl;
				cout << "�ȼ�:" << level << endl;
				cout << "����:" << experience << "/" << level * 100 << endl;
				cout << "���:" << money << endl;
				cout << "1,ħ����(��������ռ��) 2,���(ɱ��/��ֹʳ��ͽ) 3,";
				if (camp) cout << "�����ִ�(�������ز���) ";
				else cout << "����ħ�ܲ�(����ħ����) ";
				cout << "4,�����ִ�(���ս��) 5,��������ħ���̵� 6,�齱 7,����ʯ�� 8,���� 9,���� 10,���ϵ� 11,���� 12,�ռ����� 13,���� 14,���� ";
				if (camp) cout << "15, ҽ�Ʊ�������ħ�ģ�";
				else cout << "15, �Ӹ���Ůʿ ";
				cout << "16,�ı����������ר�� ��Ҫ���룩 17,���� 18,�ǳ�" << endl;
				cin >> a;
				switch (a)
				{
				case 1:
					MM();
					break;
				case 2:
					street();
					break;
				case 3:
					for (int i = 1; i < 100; i++) {
						cout << "|";
						for (int j = 0; j < 10 && i < 100; j++, i++) {
							if (nowlevel + 1 < i) cout << " " << i << " |";
							else cout << ":" << i << ":|";
						}
						cout << endl;
					}
					int num;
					cin >> num;
					if (nowlevel + 1 < num) cout << "��δ�������" << endl;
					else checkpoint(num);
					Sleep(1000);
					break;
				case 4:
					if (camp) {
						if (f) finalfight("����������");
						else cout << "����Ҫ��Ѱ�ҹ������ص�����" << endl;
					}
					else {
						if (f) finalfight("����ħ");
						else cout << "����Ҫ��Ѱ�ҷ���ħ������" << endl;
					}
					Sleep(1000);
					break;
				case 5:
					cout << "1 ����������βëħ��   100Ԫ" << endl;
					cout << "2 ����ľ����ħ��     200Ԫ" << endl;
					cout << "3 �����ľħ��        550Ԫ" << endl;
					cout << "4 ����ħ��            1200Ԫ" << endl;
					cout << "5 ����ľħ��          3650Ԫ" << endl;
					cout << "6 ����ľ�����ëħ��   5780Ԫ" << endl;
					cout << "7 ��ɼľ�����ëħ��   7120Ԫ" << endl;
					cout << "8 ��ħ��              5Ԫ" << endl;
					cout << "0 �˳�              0Ԫ" << endl;
					int b;
					cin >> b;
					switch (b)
					{
					case 1:
						buywand(6, 100);
						system("cls");
						break;
					case 2:
						buywand(7, 200);
						system("cls");
						break;
					case 3:
						buywand(8, 550);
						system("cls");
						break;
					case 4:
						buywand(9, 1200);
						system("cls");
						break;
					case 5:
						buywand(10, 3650);
						system("cls");
						break;
					case 6:
						buywand(11, 5780);
						system("cls");
						break;
					case 7:
						buywand(12, 7120);
						system("cls");
						break;
					case 8:
						buywand(13, 5);
						system("cls");
						break;
					default:
						break;
					}
					break;
				case 6:
					LD();
					break;
				case 7:
					cout << "1 ����ʯR      100Ԫ    100����" << endl;
					cout << "2 ����ʯSR     200Ԫ    250����" << endl;
					cout << "3 ����ʯSSR    400Ԫ    500����" << endl;
					cout << "4 ����ʯSSS    1000Ԫ   1200����" << endl;
					cout << "5 ����ʯX      2000Ԫ   2500����" << endl;
					cout << "0 �˳�         0Ԫ      0����" << endl;
					int c;
					cin >> c;
					switch (c)
					{
					case 1:
						buy(1, 100);
						system("cls");
						break;
					case 2:
						buy(2, 200);
						system("cls");
						break;
					case 3:
						buy(3, 550);
						system("cls");
						break;
					case 4:
						buy(4, 1200);
						system("cls");
						break;
					case 5:
						buy(5, 3650);
						system("cls");
						break;
					default:
						break;
					}
					break;
				case 8:
					cout << "1,�鿴ħ�� 2,�鿴ҩˮ 3,�鿴����ʯ 4,ѧϰ����" << endl;
					cin >> b;
					if (b == 1) w();
					else if (b == 2) p();
					else if (b == 3) e();
					else if (b == 4) sfunc();
					else {
						cout << "��������" << endl;
						Sleep(1000);
					}
					break;
				case 9:
					int material1, material2, mn1, mn2;
					cout << "1,���� 2,�鿴����";
					cin >> material1;
					if (material1 == 1) {
						cout << "��Ҫ��ʲô��о��" << endl;
						for (int ij = 0; ij < 9; ij++) cout << ij + 1 << "," << Material1name[ij] << " " << bag[ij + 24] << "��" << endl;
						cin >> material1;
						cout << "������" << endl;
						cin >> mn1;
						cout << "��Ҫ��ʲôľ�ģ�" << endl;
						for (int ij = 0; ij < 10; ij++) cout << ij + 1 << "," << Material2name[ij] << " " << bag[ij + 33] << "��" << endl;
						cin >> material2;
						cout << "������" << endl;
						cin >> mn2;
						make(material1 + 23, material2 + 32, mn1, mn2);
						break;
					}
					else if (material1 == 2) {
						cout << "��о��" << endl;
						for (int ij = 0; ij < 9; ij++) cout << ij + 1 << "," << Material1name[ij] << " " << bag[ij + 24] << "��" << endl;
						cout << "ľ�ģ�" << endl;
						for (int ij = 0; ij < 10; ij++) cout << ij + 1 << "," << Material2name[ij] << " " << bag[ij + 33] << "��" << endl;
						_getch();
					}
					else cout << "��������";
					break;
				case 10:
					break;
				case 11:
					if (xy == 1) {
						if (ane == 0) cout << "�ٴ� 1 �ظ���";
						else if (ane == 1) cout << "��������Ʒ";
						else if (ane == 2) cout << "��Ѫһ��";
						else if (ane == 3) cout << "ɱ��10����";
						cout << "(" << D_Of_C << "/" << OK << ")" << endl;
						if (D_Of_C >= OK) {
							cout << "������ɣ���"; maxhealth += 200; health += 200; defense += 20; xy = 0; bag[43]++;
						}
						Sleep(1000);
					}
					else {
						ane = rand() % 4;
						D_Of_C = 0;
						xy = 1;
						if (ane == 0) {
							cout << "�ٴ� 1 �ظ���"; OK = 1;
						}
						else if (ane == 1) {
							cout << "��������Ʒ"; OK = 2;
						}
						else if (ane == 2) {
							cout << "��Ѫһ��"; OK = 1;
						}
						else if (ane == 3) {
							cout << "ɱ��10����"; OK = 10;
						}
						Sleep(1000);
					}
					break;
				case 12:
					if (xy1 == 1) {
						if (ane1 == 0) {
							if (camp)  cout << "ɱ��1���˲�����";
							else cout << "ɱ��1���ɼ���";
						}
						else if (ane1 == 1) cout << "����5000Ԫ";
						else if (ane1 == 2) {
							if (camp) cout << "ɱ��5���µ�";
							else cout << "ɱ��5��¬��˹�������";
						}
						else if (ane1 == 3) cout << "ɱ��100������";
						else if (ane1 == 4) cout << "����10��";
						cout << "(" << D_Of_C1 << "/" << OK1 << ")" << endl;
						if (D_Of_C1 >= OK1) {
							cout << "������ɣ���" << endl;
							xy1 = 0;
							cout << "����500Ԫ ������+10 ������+10 ����+500" << endl;
							money += 500; attack += 200; health += 1000; maxhealth += 1000; defense += 150; bag[43] += 5;
						}
						Sleep(1000);
					}
					else {
						ane1 = rand() % 5;
						D_Of_C1 = 0;
						xy1 = 1;
						if (ane1 == 0) {
							if (camp) cout << "ɱ��1���˲�����";
							else cout << "ɱ��1���ɼ���";
							OK1 = 1;
						}
						else if (ane1 == 1) {
							cout << "����5000Ԫ"; OK1 = 5000;
						}
						else if (ane1 == 2) {
							if (camp) cout << "ɱ��5���µ�";
							else cout << "ɱ��5��¬��˹�������";
							OK1 = 5;
						}
						else if (ane1 == 3) {
							cout << "ɱ��100������"; OK1 = 100;
						}
						else if (ane1 == 4) {
							cout << "����10��"; OK1 = 10;
						}
						Sleep(1000);
					}
					break;
				case 13:
					cout << "1 ��Ǯ����" << LE1 << "��  2 ���鸱��" << LE2 << "��" << endl;
					int y;
					cin >> y;
					if (y == 1) {
						for (int i = 0; i < LE1 % 5; i++) {
							if (rand() % 3 == 0) fight2("ľ��׮", 1500, 100, 10, 0, 1000);
							else if (rand() % 3 == 1) fight2("ɳ��", 3000, 50, 20, 0, 1000);
							else fight2("ľ��", 1000, 100, 10, 0, 1000);
							if (dead) break;
						}
						for (int i = 0; i < (LE1 / 5) % 25; i++) {
							if (dead) break;
							if (rand() % 3 == 0) fight2("ʯ��׮(������)", 3000, 200, 20, 0, 2000);
							else if (rand() % 3 == 1) fight2("ʯ��(������)", 6000, 100, 60, 0, 2000);
							else fight2("ʯ��", 3000, 300, 30, 0, 2000);
						}
						for (int i = 0; i < (LE1 / 25) % 125; i++) {
							if (dead) break;
							if (rand() % 3 == 0) fight2("����׮(������)", 6000, 400, 40, 0, 4000);
							else if (rand() % 3 == 1) fight2("����(������)", 12000, 200, 120, 0, 4000);
							else fight2("����", 6000, 400, 40, 0, 4000);
						}
						for (int i = 0; i < (LE1 / 125) % 625; i++) {
							if (dead) break;
							if (rand() % 3 == 0) fight2("����׮(������)", 12000, 800, 80, 0, 6500);
							else if (rand() % 3 == 1) fight2("���(������)", 24000, 400, 240, 0, 6500);
							else fight2("���", 12000, 800, 80, 0, 6500);
						}
						if (!dead) {
							LE1++;
							if (ane == 0) D_Of_C++;
						}
					}
					if (y == 2) {
						for (int i = 0; i < LE2 % 5; i++) {
							if (rand() % 3 == 0) fight1("ľ��׮", 1500, 100, 10, 0, 1000);
							else if (rand() % 3 == 1) fight1("ɳ��", 3000, 50, 20, 0, 1000);
							else fight1("ľ��", 1000, 100, 10, 0, 1000);
							if (dead) break;
						}
						for (int i = 0; i < (LE2 / 5) % 25; i++) {
							if (dead) break;
							if (rand() % 3 == 0) fight1("ʯ��׮(������)", 3000, 200, 20, 0, 1000);
							else if (rand() % 3 == 1) fight1("ʯ��(������)", 6000, 100, 60, 0, 1000);
							else fight1("ʯ��", 3000, 300, 30, 0, 1000);
						}
						for (int i = 0; i < (LE2 / 25) % 125; i++) {
							if (dead) break;
							if (rand() % 3 == 0) fight1("����׮(������)", 6000, 400, 40, 0, 4000);
							else if (rand() % 3 == 1) fight1("����(������)", 12000, 200, 120, 0, 4000);
							else fight1("����", 6000, 400, 40, 0, 4000);
						}
						for (int i = 0; i < (LE2 / 125) % 625; i++) {
							if (dead) break;
							if (rand() % 3 == 0) fight1("����׮(������)", 12000, 800, 80, 0, 6500);
							else if (rand() % 3 == 1) fight1("���(������)", 24000, 400, 240, 0, 6500);
							else fight1("���", 12000, 800, 80, 0, 6500);
						}
						if (!dead) {
							LE2++;
							if (ane == 0) D_Of_C++;
						}
					}
					break;
				case 14:
					save();
					cout << "����ɹ���";
					Sleep(1000);
					break;
				case 15:
					Hos();
					Sleep(1000);
					break;
				case 16:
					int pw;
					cout << "���룺";
					cin >> pw;
					if (pw == 1212) {
						cout << "0~42,�ı䱳�� 43,��� 44,�ȼ� 45,���� 46,���� 47,���� 48,���� 49,������� 50,����ħ����Ȩ��(0û�� 0<��) 51,�ٶ�" << endl;
						unsigned long long num1, num2;
						cout << "���ţ�";
						cin >> num1;
						cout << "�ı�ɣ�";
						cin >> num2;
						if (num1 <= 42) bag[num1] = num2;
						else {
							switch (num1)
							{
							case 43:
								money = num2;
								break;
							case 44:
								level = num2;
								break;
							case 45:
								experience = num2;
								break;
							case 46:
								health = num2;
								break;
							case 47:
								defense = num2;
								break;
							case 48:
								attack = num2;
								break;
							case 49:
								maxhealth = num2;
								break;
							case 50:
								amm = num2;
								break;
							case 51:
								speed = num2;
								break;
							default:
								break;
							}
						}
						levelup();
						cout << "�ı�ɹ�";
					}
					else cout << "�������" << endl;
					Sleep(1000);
					break;
				case 17:
					cout << "1,�ؿ����� 2,�ؿ�����" << endl;
					int xd;
					cin >> xd;
					if (xd == 1) system("start https://paste.ubuntu.com/p/2YQBCmYvSb/");
					if (xd == 2) {
						cout << "�����Ƚ���һ��ͼ��" << endl;
						cout << "�X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[" << endl;
						cout << "�U @ �U  �U I �U  �U o �U  �U # �U" << endl;
						cout << "�^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a" << endl;
						cout << "���Լ�   ����    ���    ǽ" << endl;
						cout << "�X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[" << endl;
						cout << "�U 1 �U  �U 2 �U  �U 3 �U  �U 4 �U" << endl;
						cout << "�^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a" << endl;
						cout << "1����   2����   3����  4����" << endl;
						cout << "��1000 ��2000  ��3000 ��4000" << endl;
						cout << "��250  ��500   ��750  ��1000" << endl;
						cout << "��10   ��20    ��30   ��40" << endl;
						cout << "��50   ��100   ��150  ��200" << endl;
						cout << "�X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[" << endl;
						cout << "�U 5 �U  �U 6 �U  �U 7 �U  �U 8 �U" << endl;
						cout << "�^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a" << endl;
						cout << "5����   6����   7����  8����" << endl;
						cout << "��5000 ��6000  ��7000 ��8000" << endl;
						cout << "��1250 ��1500  ��1750 ��2000" << endl;
						cout << "��50   ��60    ��70   ��80" << endl;
						cout << "��250  ��300   ��350  ��400" << endl;
						cout << "�X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[  �X�T�T�T�[" << endl;
						cout << "�U 9 �U  �U S �U  �U B �U  �U T �U" << endl;
						cout << "�^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a  �^�T�T�T�a" << endl;
						cout << "9����  ҩˮ�̵�  ���   ��ʾ��" << endl;
						cout << "��9000" << endl;
						cout << "��2250" << endl;
						cout << "��90" << endl;
						cout << "��450" << endl;
						cout << "�X�T�T�T�[" << endl;
						cout << "�U X �U" << endl;
						cout << "�^�T�T�T�a" << endl;
						cout << "���ͻ�" << endl;
						cout << "����ͼ���˽���ϸ��0�˳�" << endl;
						string st;
						cin >> st;
						if (st == "@") system("start https://paste.ubuntu.com/p/cdJPnhXddT/");
						else if (st == "I" || st == "i") system("start https://paste.ubuntu.com/p/h5npMzvDBX/");
						else if (st == "o" || st == "O") system("start https://paste.ubuntu.com/p/By6Fdyq9wq/");
						else if (st == "#") system("start https://paste.ubuntu.com/p/DswXYhVGFn/");
						else if (st <= "9" && st >= "1") system("start https://paste.ubuntu.com/p/4vZDjY7fX4/");
						else if (st == "S" || st == "s") system("start https://paste.ubuntu.com/p/SvSTDGrcD3/");
						else if (st == "B" || st == "b") system("start https://paste.ubuntu.com/p/MMqwYn63N9/");
						else if (st == "T" || st == "t") system("start https://paste.ubuntu.com/p/mXgfbyhGGJ/");
						else if (st == "X" || st == "x") system("start https://paste.ubuntu.com/p/M6svDYryGt/");
						else if (st == "0");
						else cout << "��������" << endl;
						Sleep(1000);
					}
					break;
				case 18:
					isbreak = true;
				}
				levelup();
			}
		}
	}
}

