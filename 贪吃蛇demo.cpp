#include<iostream>
#include<vector>
#include<windows.h>
#include <stdlib.h>
#include<time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include<stdio.h>
#include <conio.h>
using namespace std;
#define chang 100
#define kuan 50
#define width 100
#define height 30
//FOREGROUND_BLUE //��ɫ
//FOREGROUND_GREEN //��ɫ
//FOREGROUND_RED //��ɫ
//FOREGROUND_INTENSITY //��ǿ
//BACKGROUND_BLUE //��ɫ����
//BACKGROUND_GREEN //��ɫ����
//BACKGROUND_RED //��ɫ����
//BACKGROUND_INTENSITY //����ɫ��ǿ
//COMMON_LVB_REVERSE_VIDEO //��ɫ
void Interface();//��������

const WORD FORE_BLUE = FOREGROUND_BLUE;           //��ɫ�ı�����  
const WORD FORE_GREEN = FOREGROUND_GREEN;          //��ɫ�ı�����  
const WORD FORE_RED = FOREGROUND_RED;            //��ɫ�ı�����  
const WORD FORE_PURPLE = FORE_BLUE | FORE_RED;      //��ɫ�ı�����  
const WORD FORE_CYAN = FORE_BLUE | FORE_GREEN;    //��ɫ�ı�����  
const WORD FORE_YELLOW = FORE_RED | FORE_GREEN;     //��ɫ�ı�����  
const WORD FORE_GRAY = FOREGROUND_INTENSITY;      //��ɫ�ı�����  
const WORD BACK_BLUE = BACKGROUND_BLUE;           //��ɫ��������  
const WORD BACK_GREEN = BACKGROUND_GREEN;          //��ɫ��������  
const WORD BACK_RED = BACKGROUND_RED;            //��ɫ��������  
const WORD BACK_PURPLE = BACK_BLUE | BACK_RED;      //��ɫ��������  
const WORD BACK_CYAN = BACK_BLUE | BACK_GREEN;    //��ɫ��������  
const WORD BACK_YELLOW = BACK_RED | BACK_GREEN;     //��ɫ��������  
const WORD BACK_GRAY = BACKGROUND_INTENSITY;      //��ɫ��������  

int Ctime = 150;
char map[kuan][chang] = { ' ' };
char map2[kuan][chang] = { ' ' };
char go[30][100] = { ' ' };
char Border[30][85] = { ' ' };
int res[kuan][chang];
char now_dir = 'p';
char pre_dir = '0';
int flag_d = 0;//�����Ƿ������ߵ�����
int flag_s = 0;//�����Ƿ������ߵ�����
int flag_a = 0;//�����Ƿ������ߵ�����
int flag_w = 0;//�����Ƿ������ߵ�����
int fx, fy;
int degree;//�Ѷ�ϵ��
int flag = 0;//�����Ƿ�ʼ��Ϸ
int score = 0;//����
			  //��������̨���������ɫ����
void Makeitmove(char ch);
//��ʼ���ߵ�����
//�ù���ƶ���ͷ��λ�ã��Ա��������ӡ
void color(const unsigned short color1)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ  
	CursorInfo.bVisible = false; //���ؿ���̨���  
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬ 
	if (color1 >= 0 && color1 <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color1);
	else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void gotoxy(int x, int y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*COORD��Windows AP
typedef struct _COORD {

SHORT X; // horizontal coordinate

SHORT Y; // vertical coordinate
} COORD;*/
void move(int d_x, int d_y)
{
	gotoxy(d_y, d_x);
}
struct snake {
	int x;
	int y;
	struct snake *next;
};
struct snake *tail, *p, *q, *head;
class xsnake {
public:
	void set_map();
	void prin_map();
	void set_map2();
	void Buildsnake(int def_len);
	/*void randFood();*/
	/*void judgeIffood(int ffx, int ffy);
	void judgeBrage(int ffx, int ffy);*/
	void input_direction();
	void prin_body();
	friend void Calcue();
private:
	struct body {
		vector<char> Body_line;
	}Body;
};

//tail = NULL;
void xsnake::Buildsnake(int def_len)//��ʼ������ĳ���
{
	for (int i = 1; i <= def_len; i++)
	{
		Body.Body_line.push_back('o');
		p = new struct snake;
		p->x = 1;
		p->y = i;
		p->next = NULL;
		res[p->x][p->y] = 1;
		if (tail == NULL)
			tail = p;
		else
			q->next = p;
		q = p;
	}
	head = p;
}

void xsnake::prin_body()
{
	color(10);
	for (int i = 0; i < Body.Body_line.size(); i++)
	{
		cout << Body.Body_line[i];
	}
}
//�������
void Calcue()
{
	move(kuan / 2, chang + 12);
	cout << score;
}
/*------------------------------------------------------------------------------------------------*/
//�������ʳ��
void randFood()
{
	srand(time(0));
	fx = fy = 0;
	while (fx < 1||fy<1||res[fx][fy]==1||map[fx+1][fy+1]==6)
	{
		fx = rand() % (kuan - 2);
		fy = rand() % (chang - 2);
	}
	map[fx][fy] = 3;
	gotoxy(fy, fx);
	color(12);
	cout << map[fx][fy];
}
//���Ž�����Ϸ�󱳾�����
void Play_BackMusic()
{
	
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\������Ϸ����.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
}
//����ѡ������
//DWORD WINAPI Play_ChooseMusic(LPVOID lpParamter)
//{
//	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\�����л�.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
//	return 0;
//}
void Play_ChooseMusic()
{
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\�����л�.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
}
//����ѡ�е�����
void Play_GetMusic()
{
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\�ո��.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
}
//���Ų˵���������
DWORD WINAPI Play_Menu(LPVOID lpParamter)
{
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\��˵.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
	return 0;
}
//��Ϸʧ������
void Play_GameOverMusic()
{
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\GameOver.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
}
//��ӡ������
void Play_PrintMusic()
{
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\��ӡ.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
}
//���ذ�ť����
void Play_ReturnMusic()
{
	PlaySound(TEXT("D:\\My fireheart\\VS workspace\\reposrepos\\̰����Game\\̰����Game\\����.wav"), NULL, SND_ASYNC | SND_NODEFAULT);
}
//�򵥵�ͼ����
void set_map()
{
	for (int i = 1; i <= chang; i++)
	{
		map[1][i] = 6;
		map[kuan][i] = 6;
	}
	for (int i = 1; i <= kuan; i++)
	{
		map[i][1] = 6;
		map[i][chang] = 6;
	}
}
//�е��Ѷȵ�ͼ����
void set_map2()
{
	for (int i = 1; i <= chang; i++)
	{
		map[1][i] = 6;
		map[kuan][i] = 6;
	}
	for (int i = 1; i <= kuan; i++)
	{
		map[i][1] = 6;
		map[i][chang] = 6;
	}
	for (int i = 15; i<17; i++)
	{
		for (int j = 16; j<31; j++)
		{
			map[i][j] = 6;
			map[i][j + 54] = 6;
			map[i + 20][j] = 6;
			map[i + 20][j + 54] = 6;
		}
	}
	for (int i = 6; i<15; i++)
	{
		for (int j = 29; j<31; j++)
		{
			map[i][j] = 6;
			map[i + 31][j] = 6;
			map[i][j + 41] = 6;
			map[i + 31][j + 41] = 6;
		}
	}
	for (int i = 25; i<27; i++)
	{
		for (int j = 41; j<61; j++)
		{
			map[i][j] = 6;
		}
	}
	for (int i = 19; i<33; i++)
	{
		for (int j = 50; j<52; j++)
		{
			map[i][j] = 6;
		}
	}
}
//���ѵ�ͼ
void set_map3()
{

	for (int i = 1; i <= chang; i++)
	{
		map[1][i] = 6;
		map[kuan][i] = 6;
	}
	for (int i = 1; i <= kuan; i++)
	{
		map[i][1] = 6;
		map[i][chang] = 6;
	}


	for (int i = 5; i<47; i++)
	{
		map[i][5] = 6;
	}
	for (int i = 5; i<97; i++)
	{
		map[5][i] = 6;
	}
	for (int i = 9; i<97; i++)
	{
		map[46][i] = 6;
	}
	for (int i = 9; i<47; i++)
	{
		map[i][96] = 6;
	}                       //1

	for (int i = 9; i<93; i++)
	{
		map[9][i] = 6;
	}
	for (int i = 9; i<89; i++)
	{
		map[42][i] = 6;
	}
	for (int i = 13; i<43; i++)
	{
		map[i][9] = 6;
	}
	for (int i = 10; i<43; i++)
	{
		map[i][92] = 6;
	}                       //2

	for (int i = 13; i<89; i++)
	{
		map[13][i] = 6;
	}
	for (int i = 17; i<89; i++)
	{
		map[38][i] = 6;
	}
	for (int i = 14; i<39; i++)
	{
		map[i][13] = 6;
	}
	for (int i = 17; i<39; i++)
	{
		map[i][88] = 6;
	}                       //3

	for (int i = 21; i<85; i++)
	{
		map[17][i] = 6;
	}
	for (int i = 17; i<85; i++)
	{
		map[34][i] = 6;
	}
	for (int i = 17; i<35; i++)
	{
		map[i][17] = 6;
	}
	for (int i = 17; i<31; i++)
	{
		map[i][84] = 6;
	}                       //4
	for (int i = 21; i<77; i++)
	{
		map[21][i] = 6;
	}
	for (int i = 21; i<81; i++)
	{
		map[30][i] = 6;
	}
	for (int i = 21; i<27; i++)
	{
		map[i][21] = 6;
	}
	for (int i = 21; i<31; i++)
	{
		map[i][80] = 6;
	}                       //5
	for (int i = 25; i<77; i++)
	{
		map[25][i] = 6;
	}
	for (int i = 25; i<77; i++)
	{
		map[26][i] = 6;
	}                       //6
}
//��ʼ�Ķ�������
void Brown()
{
	char a = 22;
	color(9);
	move(11, 51);
	for (int i = 0; i<10; i++)
		cout << a;          //1

	move(12, 49);
	cout << a << a;
	move(12, 61);
	cout << a << a;           //2

	move(13, 47);
	cout << a << a;
	move(13, 51);
	cout << a;
	move(13, 60);
	cout << a;
	move(13, 63);
	cout << a << a;           //3

	move(14, 46);
	cout << a;
	move(14, 49);
	cout << a << a;
	move(14, 52);
	for (int i = 0; i<8; i++)
		cout << a;
	move(14, 61);
	cout << a << a;
	move(14, 65);
	cout << a;              //4

	move(15, 43);
	cout << a << a << a;
	move(15, 48);
	cout << a;
	move(15, 51);
	cout << a;
	move(15, 60);
	cout << a;
	move(15, 63);
	cout << a;
	move(15, 66);
	cout << a;               //5

	move(16, 42);
	cout << a;
	move(16, 46);
	cout << a;
	move(16, 48);
	cout << a;
	move(16, 51);
	cout << a;
	move(16, 60);
	cout << a;
	move(16, 63);
	cout << a;
	move(16, 66);
	cout << a;               //6

	move(17, 42);
	cout << a << a;
	move(17, 45);
	cout << a;
	move(17, 48);
	cout << a;
	move(17, 50);
	cout << a << a;
	move(17, 60);
	cout << a << a;
	move(17, 63);
	cout << a;
	move(17, 66);
	cout << a;               //7

	move(18, 42);
	cout << a << a << a << a;
	move(18, 48);
	cout << a;
	move(18, 50);
	for (int i = 0; i<12; i++)
		cout << a;
	move(18, 63);
	cout << a;
	move(18, 66);
	cout << a;

	move(19, 41);
	cout << a;
	move(19, 45);
	cout << a;
	move(19, 49);
	cout << a << a << a;
	move(19, 61);
	cout << a << a;
	move(19, 66);
	cout << a;

	move(20, 40);
	cout << a;
	move(20, 46);
	cout << a << a << a << a;
	move(20, 63);
	cout << a << a << a << a;

	move(21, 41);
	cout << a;
	move(21, 45);
	cout << a;
	move(21, 67);
	cout << a;

	move(22, 42);
	cout << a;
	move(22, 45);
	cout << a;
	move(22, 50);
	cout << a;
	move(22, 67);
	cout << a;

	move(23, 43);
	cout << a << a << a;
	move(23, 51);
	cout << a;
	move(23, 67);
	cout << a;

	move(24, 45);
	cout << a;
	move(24, 52);
	for (int i = 0; i<10; i++)
		cout << a;
	move(24, 67);
	cout << a;

	move(25, 46);
	cout << a;
	move(25, 66);
	cout << a;

	move(26, 47);
	cout << a << a;
	move(26, 64);
	cout << a << a;

	move(27, 49);
	cout << a;
	move(27, 63);
	cout << a;

	move(28, 50);
	for (int i = 0; i<13; i++)
		cout << a;
}
void Green()
{
	char a = 22;
	color(10);
	move(12, 51);
	for (int i = 0; i<10; i++)
		cout << a;

	move(13, 52);
	for (int i = 0; i<8; i++)
		cout << a;

	move(19, 52);
	for (int i = 0; i<9; i++)
		cout << a;

	move(20, 50);
	for (int i = 0; i<13; i++)
		cout << a;

	move(21, 46);
	for (int i = 0; i<21; i++)
		cout << a;

	move(22, 46);
	cout << a << a << a << a;
	move(22, 51);
	for (int i = 0; i<16; i++)
		cout << a;

	move(23, 46);
	cout << a << a << a << a << a;
	move(23, 52);
	for (int i = 0; i<15; i++)
		cout << a;

	move(24, 46);
	for (int i = 0; i<6; i++)
		cout << a;
	move(24, 62);
	for (int i = 0; i<5; i++)
		cout << a;

	move(25, 47);
	for (int i = 0; i<19; i++)
		cout << a;

	move(26, 49);
	for (int i = 0; i<15; i++)
		cout << a;

	move(27, 50);
	for (int i = 0; i<13; i++)
		cout << a;
}
void Red()
{
	char a = 22;
	color(12);
	move(13, 49);
	cout << a << a;
	move(13, 61);
	cout << a << a;
	move(14, 47);
	cout << a << a;
	move(14, 51);
	cout << a;
	move(14, 60);
	cout << a;
	move(14, 63);
	cout << a << a;
	move(15, 46);
	cout << a << a;
	move(15, 64);
	cout << a << a;
	move(15, 52);
	for (int i = 0; i<8; i++)
		cout << a;
	move(16, 43);
	cout << a << a << a;
	move(16, 47);
	cout << a;
	move(16, 52);
	for (int i = 0; i<8; i++)
		cout << a;
	move(16, 64);
	cout << a << a;
	move(17, 44);
	cout << a;
	move(17, 46);
	cout << a << a;
	move(17, 52);
	for (int i = 0; i<8; i++)
		cout << a;
	move(17, 64);
	cout << a << a;
	move(18, 46);
	cout << a << a;
	move(18, 64);
	cout << a << a;
	move(19, 42);
	cout << a << a << a;
	move(19, 46);
	cout << a << a << a;
	move(19, 63);
	cout << a << a << a;
	move(20, 41);
	cout << a << a << a << a << a;
	move(21, 42);
	cout << a << a << a;
	move(22, 43);
	cout << a << a;
}
void White()
{
	char a = 22;
	color(15);
	move(15, 49);
	cout << a << a;
	move(15, 61);
	cout << a << a;
	move(16, 49);
	cout << a << a;
	move(16, 61);
	cout << a << a;
	move(17, 49);
	cout << a;
	move(17, 62);
	cout << a;
	move(18, 49);
	cout << a;
	move(18, 62);
	cout << a;
}
void Bro()
{
	char a = 22;
	color(11);
	move(32, 40);
	cout << a << a << a << a;
	move(32, 47);
	cout << a << a << a << a;
	move(32, 55);
	cout << a << a << a;
	move(32, 63);
	cout << a;
	move(32, 70);
	cout << a << a << a;

	move(33, 40);
	cout << a;
	move(33, 44);
	cout << a;
	move(33, 47);
	cout << a;
	move(33, 51);
	cout << a;
	move(33, 54);
	cout << a;
	move(33, 58);
	cout << a;
	move(33, 61);
	cout << a;
	move(33, 63);
	cout << a;
	move(33, 65);
	cout << a;
	move(33, 70);
	cout << a;
	move(33, 72);
	cout << a;

	move(34, 40);
	cout << a;
	move(34, 44);
	cout << a;
	move(34, 47);
	cout << a;
	move(34, 51);
	cout << a;
	move(34, 54);
	cout << a;
	move(34, 58);
	cout << a;
	move(34, 61);
	cout << a << a << a << a << a;
	move(34, 70);
	cout << a << a << a;

	move(35, 40);
	cout << a << a << a << a;
	move(35, 47);
	cout << a << a << a << a;
	move(35, 54);
	cout << a;
	move(35, 58);
	cout << a;
	move(35, 63);
	cout << a;
	move(35, 65);
	cout << a;

	move(36, 40);
	cout << a << a << a << a;
	move(36, 47);
	cout << a;
	move(36, 49);
	cout << a;
	move(36, 54);
	cout << a;
	move(36, 58);
	cout << a;
	move(36, 63);
	cout << a;

	move(37, 40);
	cout << a;
	move(37, 44);
	cout << a;
	move(37, 47);
	cout << a;
	move(37, 50);
	cout << a;
	move(37, 54);
	cout << a;
	move(37, 58);
	cout << a;
	move(37, 61);
	cout << a;
	move(37, 63);
	cout << a;
	move(37, 65);
	cout << a;
	move(37, 68);
	cout << a << a << a;
	move(37, 72);
	cout << a << a << a;

	move(38, 40);
	cout << a;
	move(38, 44);
	cout << a;
	move(38, 47);
	cout << a;
	move(38, 51);
	cout << a;
	move(38, 54);
	cout << a;
	move(38, 58);
	cout << a;
	move(38, 61);
	cout << a;
	move(38, 63);
	cout << a;
	move(38, 65);
	cout << a;
	move(38, 68);
	cout << a;
	move(38, 70);
	cout << a;
	move(38, 72);
	cout << a;
	move(38, 74);
	cout << a;

	move(39, 40);
	cout << a << a << a << a;
	move(39, 47);
	cout << a;
	move(39, 51);
	cout << a;
	move(39, 55);
	cout << a << a << a;
	move(39, 61);
	cout << a << a << a << a << a;
	move(39, 68);
	cout << a << a << a;
	move(39, 72);
	cout << a << a << a;
}
void prin_Begin()
{
	Brown();
	Green();
	Red();
	White();
	Bro();
	move(45, 27);
	cout << "�� �� �� �� �� �� ��";
	char ch = 'a';
	while (ch != ' ')
	{
		ch = _getch();
	}
}
//��ӡ��ͼ
void prin_map()
{
	system("cls");
	Play_BackMusic();
	color(13);
	for (int i = 1; i <= kuan; i++)
	{
		for (int j = 1; j <= chang; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
	move(kuan / 2, chang + 5);
	color(10);
	cout << "Score��" << "0";
}
//ʧ��
void GameOver()
{
	Play_GameOverMusic();
	for (int i = 6; i<11; i++)
		go[i][41] = 22;
	for (int i = 15; i<20; i++)
		go[i][41] = 22;    //1

	for (int i = 5; i<12; i++)
		go[i][42] = 22;
	for (int i = 14; i<21; i++)
		go[i][42] = 22;    //2

	for (int i = 43; i<46; i++)
	{
		go[5][i] = 22;
		go[11][i] = 22;
		go[14][i] = 22;
		go[20][i] = 22;
	}
	go[8][45] = 22;          //345

	go[5][46] = 22;
	go[6][46] = 22;
	go[8][46] = 22;
	go[9][46] = 22;
	go[10][46] = 22;
	go[11][46] = 22;
	for (int i = 14; i<21; i++)
		go[i][46] = 22;     //6

	go[6][47] = 22;
	go[8][47] = 22;
	go[9][47] = 22;
	go[10][47] = 22;
	for (int i = 15; i<20; i++)
		go[i][47] = 22;        //7

	for (int i = 7; i<12; i++)
		go[i][50] = 22;
	for (int i = 14; i<19; i++)
		go[i][50] = 22;        //10

	for (int i = 6; i<12; i++)
		go[i][51] = 22;
	for (int i = 14; i<20; i++)
		go[i][51] = 22;        //11

	go[5][52] = 22;
	go[6][52] = 22;
	go[9][52] = 22;
	go[20][52] = 22;
	go[19][52] = 22;           //12

	go[5][53] = 22;
	go[9][53] = 22;
	go[20][53] = 22;           //13

	go[5][54] = 22;
	go[6][54] = 22;
	go[9][54] = 22;
	go[20][54] = 22;
	go[19][54] = 22;           //14

	for (int i = 6; i<12; i++)
		go[i][55] = 22;
	for (int i = 14; i<20; i++)
		go[i][55] = 22;        //15

	for (int i = 7; i<12; i++)
		go[i][56] = 22;
	for (int i = 14; i<19; i++)
		go[i][56] = 22;        //16

	for (int i = 5; i<12; i++)
		go[i][59] = 22;
	for (int i = 14; i<21; i++)
		go[i][59] = 22;        //19

	for (int i = 6; i<12; i++)
		go[i][60] = 22;
	for (int i = 14; i<21; i++)
		go[i][60] = 22;        //20

	go[7][61] = 22;
	go[8][61] = 22;
	go[14][61] = 22;
	go[17][61] = 22;
	go[20][61] = 22;           //21

	go[8][62] = 22;
	go[9][62] = 22;
	go[14][62] = 22;
	go[17][62] = 22;
	go[20][62] = 22;           //22

	go[7][63] = 22;
	go[8][63] = 22;
	go[14][63] = 22;
	go[17][63] = 22;
	go[20][63] = 22;           //23

	for (int i = 6; i<12; i++)
		go[i][64] = 22;
	go[14][64] = 22;
	go[17][64] = 22;
	go[20][64] = 22;           //24

	for (int i = 5; i<12; i++)
		go[i][65] = 22;
	go[14][65] = 22;
	go[20][65] = 22;           //25

	for (int i = 5; i<12; i++)
		go[i][68] = 22;
	for (int i = 14; i<21; i++)
		go[i][68] = 22;        //28

	for (int i = 5; i<12; i++)
		go[i][69] = 22;
	for (int i = 14; i<21; i++)
		go[i][69] = 22;        //29

	go[5][70] = 22;
	go[8][70] = 22;
	go[11][70] = 22;
	go[14][70] = 22;
	go[17][70] = 22;           //30

	go[5][71] = 22;
	go[8][71] = 22;
	go[11][71] = 22;
	go[14][71] = 22;
	go[18][71] = 22;
	go[17][71] = 22;           //31

	go[5][72] = 22;
	go[8][72] = 22;
	go[11][72] = 22;
	go[14][72] = 22;
	go[19][72] = 22;
	go[17][72] = 22;
	go[18][72] = 22;           //32

	go[5][73] = 22;
	go[8][73] = 22;
	go[11][73] = 22;
	go[14][73] = 22;
	go[17][73] = 22;
	go[15][73] = 22;
	go[16][73] = 22;
	go[20][73] = 22;
	go[19][73] = 22;           //33

	go[5][74] = 22;
	go[16][74] = 22;
	go[11][74] = 22;
	go[15][74] = 22;
	go[20][74] = 22;           //34
}

void Prin_Go()
{
	system("cls");
	flag_a = 1;
	flag_d = 1;
	flag_s = 1;
	flag_w = 1;
	color(11);
	for (int i = 1; i < height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			cout << go[i][j];
		}
		Sleep(250);
		cout << endl;
	}
	move(27, 32);
	color(12);
	cout << "�� �� �� �� �ǣ�";
	color(8);
	cout << score;
	cout << "                                               ";
}
//�ж��Ƿ�Ե���ʳ��
void judgeIffood(int ffx, int ffy)
{
	if (fx == ffx && fy == ffy)
	{
		Ctime -= 10;
		randFood();
		score++;
		Calcue();
	}
	else
	{
		cout << " ";
		res[tail->x][tail->y] = 0;
		tail = tail->next;
	}
}
//�ж��Ƿ�ײ����ǽ
void judgeBrage(int ffx, int ffy)
{
	if (ffx == kuan - 2 || ffy == chang - 2 || ffx == 0 || ffy == 1)
	{
		flag_a = 1;
		flag_d = 1;
		flag_s = 1;
		flag_w = 1;
		system("cls");
		color(12);
		GameOver();
		Prin_Go();
	}
	if (map[ffx+1][ffy+1] == 6||ffy==1)
	{
		flag_a = 1;
		flag_d = 1;
		flag_s = 1;
		flag_w = 1;
		system("cls");
		color(12);
		GameOver();
		Prin_Go();
	}
}
//�ж��Ƿ�ײ�����Լ�
void judgeIfItself(int ffx, int ffy)
{
	if (res[ffx][ffy] == 1)
	{
		flag_a = 1;
		flag_d = 1;
		flag_s = 1;
		flag_w = 1;
		GameOver();
		Prin_Go();
	}
}
//��������
void About_us()
{
	system("cls");
	color(15);
	move(4, 23);
	cout << "       ������ϷΪ��������������Ϸ���ɡ�Bro��Ϸ�����ҡ���Ʒ��" << endl;
	Play_PrintMusic();
	Sleep(800);
	move(6, 25);
	cout << "��ʱ������ݣ�������������̨̰���ߡ���Bro��Ϸ�����ҡ��Ǽ�" << endl;
	Play_PrintMusic();
	Sleep(800);
	move(8, 25);
	cout << "����У��ѧ����ɵ�С�Ŷӣ���Ҫ�Ŷ���Ա�����쿡�����ԣ�����" << endl;
	Play_PrintMusic();
	move(10, 25);
	Sleep(800);
	cout << "�ҳ�����2018��6��24�գ����긣�����š�������һ���������飬��" << endl;
	Play_PrintMusic();
	move(12, 25);
	Sleep(800);
	cout << "������Ĵ��ͥ����Ȼ���ǲŴ�һ����������������ȷ��Ŀ�꣬����" << endl;
	Play_PrintMusic();
	move(14, 25);
	Sleep(800);
	cout << "����������Ӧ���еĸ�ƴ�ľ����������ǻ���δ������Ҵ�������" << endl;
	Play_PrintMusic();
	Sleep(800);
	move(16, 25);
	cout << "���õ���Ʒ����Ҿ����ڴ�!" << endl;
	Play_PrintMusic();
	Sleep(800);
	color(8);
	cout << "��P������";
	char str = _getch();
	if (str == 'p')
	{
		Play_ReturnMusic();
		Interface();
	}
}
//����˵��
void Opera_Desc()
{
	system("cls");
	color(15);
	move(4, 29);
	cout << "��  ��  ˵  ��" << endl;
	move(6, 32);
	cout << "�� ��S";
	move(8, 32);
	cout << "�� �ң�D";
	move(10, 32);
	cout << "�� �£�S";
	move(12, 32);
	cout << "�� �ϣ�W";
	move(14, 32);
	cout << "�� ͣ��U";
	move(16, 32);
	cout << "�� ����Y";
	move(18, 32);
	color(8);
	cout << "�� P �� ��";
	char str = '.';
	while (str != 'p')
	{
		str = _getch();
	}
	if (str == 'p')
	{
		Play_ReturnMusic();
		Interface();
	}
}
//����ָ��
//����
DWORD WINAPI orderTomoveR(LPVOID lpParamter)
{
	pre_dir = 'd';
	flag_d = 0;
	while (1)
	{
		if (flag_d == 1)
			return 0;
		move(head->x, head->y + 1);
		judgeBrage(head->x, head->y);
		color(14);
		cout << 'o';
		p = new struct snake;
		p->x = head->x;
		p->y = head->y + 1;
		head->next = p;
		head = p;
		judgeIfItself(head->x, head->y);
		res[head->x][head->y] = 1;
		move(tail->x, tail->y);
		judgeIffood(head->x, head->y);
		//cout << ' ';
		Sleep(Ctime);
	}
	return 0;
}
//����
DWORD WINAPI orderTomoveX(LPVOID lpParamter)
{
	flag_s = 0;
	pre_dir = 's';
	while (1)
	{
		if (flag_s == 1)
		{
			return 0;
		}
		move(head->x + 1, head->y);
		judgeBrage(head->x, head->y);
		color(14);
		cout << 'o';
		p = new struct snake;
		p->x = head->x + 1;
		p->y = head->y;
		head->next = p;
		head = p;
		head->next = NULL;
		judgeIfItself(head->x, head->y);
		res[head->x][head->y] = 1;
		move(tail->x, tail->y);
		judgeIffood(head->x, head->y);
		//cout << ' ';
		//tail = tail->next;
		Sleep(Ctime);
	}
	return 0;
}
//����
DWORD WINAPI orderTomoveU(LPVOID lpParamter)
{
	int mark_x = head->x;
	int mark_y = head->y;
	flag_w = 0;
	pre_dir = 'w';
	while (1)
	{
		if (flag_w == 1)
			return 0;
		move(head->x - 1, head->y);
		judgeBrage(head->x, head->y);
		color(14);
		cout << 'o';
		p = new struct snake;
		p->x = head->x - 1;
		p->y = head->y;
		head->next = p;
		head = p;
		head->next = NULL;
		judgeIfItself(head->x, head->y);
		res[head->x][head->y] = 1;
		move(tail->x, tail->y);
		judgeIffood(head->x, head->y);
		//cout << ' ';
		//tail = tail->next;
		Sleep(Ctime);
	}
	return 0;
}
//����
DWORD WINAPI orderTomoveL(LPVOID lpParamter)
{
	flag_a = 0;
	pre_dir = 'a';
	while (1)
	{
		if (flag_a == 1)
			return 0;
		move(head->x, head->y - 1);
		judgeBrage(head->x, head->y);
		color(14);
		cout << 'o';
		p = new struct snake;
		p->x = head->x;
		p->y = head->y - 1;
		head->next = p;
		head = p;
		head->next = NULL;
		judgeIfItself(head->x, head->y);
		res[head->x][head->y] = 1;
		move(tail->x, tail->y);
		judgeIffood(head->x, head->y);
		//cout << ' ';
		//tail = tail->next;
		Sleep(Ctime);
	}
	return 0;
}
void xsnake::input_direction()
{
	pre_dir = 'p';
	char Save_dir;
	while ((now_dir = _getch()) != ' ')
	{
		if (now_dir == 'u')
		{
			flag_a = 1;
			flag_d = 1;
			flag_s = 1;
			flag_w = 1;
			Save_dir = pre_dir;
			pre_dir = 'u';
		}
		if (pre_dir == 'u'&&now_dir == 'y')
		{
			flag_a = 0;
			flag_d = 0;
			flag_s = 0;
			flag_w = 0;
			if (Save_dir == 'd')
			{
				HANDLE handle01 = CreateThread(NULL, 0, orderTomoveR, NULL, 0, NULL);
			}
			else if (Save_dir == 's')
			{
				HANDLE handle02 = CreateThread(NULL, 0, orderTomoveX, NULL, 0, NULL);
			}
			else if (Save_dir == 'a')
			{
				HANDLE handle06 = CreateThread(NULL, 0, orderTomoveL, NULL, 0, NULL);
			}
			else if (Save_dir == 'w')
			{
				HANDLE handle04 = CreateThread(NULL, 0, orderTomoveU, NULL, 0, NULL);
			}
		}
		if (now_dir == 'd'&&pre_dir == 'p')
		{
			HANDLE handle01 = CreateThread(NULL, 0, orderTomoveR, NULL, 0, NULL);
			//WaitForSingleObject(handle01, INFINITE);
		}
		if (now_dir == 's'&&pre_dir == 'p')
		{
			HANDLE handle02 = CreateThread(NULL, 0, orderTomoveX, NULL, 0, NULL);
		}
		//�����ߵ�ʱ��׼��������
		if (now_dir == 's'&&pre_dir == 'd')
		{
			flag_d = 1;
			HANDLE handle03 = CreateThread(NULL, 0, orderTomoveX, NULL, 0, NULL);
		}
		//�����ߵ�ʱ��׼��������
		if (now_dir == 'w'&&pre_dir == 'd')
		{
			flag_d = 1;
			HANDLE handle04 = CreateThread(NULL, 0, orderTomoveU, NULL, 0, NULL);
		}
		//�����ߵ�ʱ��׼��������
		if (now_dir == 'd'&&pre_dir == 's')
		{
			flag_s = 1;
			HANDLE handle05 = CreateThread(NULL, 0, orderTomoveR, NULL, 0, NULL);
		}
		//���µ�ʱ��׼������
		if (now_dir == 'a'&&pre_dir == 's')
		{
			flag_s = 1;
			HANDLE handle06 = CreateThread(NULL, 0, orderTomoveL, NULL, 0, NULL);
		}
		//�����ʱ��׼������
		if (now_dir == 'w'&&pre_dir == 'a')
		{
			flag_a = 1;
			HANDLE handle06 = CreateThread(NULL, 0, orderTomoveU, NULL, 0, NULL);
		}
		//�����ߵ�ʱ��������
		if (now_dir == 's'&&pre_dir == 'a')
		{
			flag_a = 1;
			HANDLE handle07 = CreateThread(NULL, 0, orderTomoveX, NULL, 0, NULL);
		}

		//�����ߵ�ʱ��׼������
		if (now_dir == 'a'&&pre_dir == 'w')
		{
			flag_w = 1;
			HANDLE handle07 = CreateThread(NULL, 0, orderTomoveL, NULL, 0, NULL);
		}
		//�����ߵ�ʱ��׼������
		if (now_dir == 'd'&&pre_dir == 'w')
		{
			flag_w = 1;
			HANDLE handle07 = CreateThread(NULL, 0, orderTomoveR, NULL, 0, NULL);
		}
	}
}
void set_Border()
{
	for (int j = 0; j <= 60; j++)
	{
		Border[0][j] = 3;
		Border[15][j] = 3;
	}
	for (int i = 1; i <= 15; i++)
	{
		Border[i][10] = 3;
		Border[i][50] = 3;
	}
}
void prin_Border()
{
	color(12);
	for (int i = 0; i <= 15; i++)
	{
		for (int j = 0; j <= 60; j++)
		{
			cout << Border[i][j];
		}
		cout << endl;
	}
}
//�Ѷ�ϵ������
void DegreeOfDifficult()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ  
	CursorInfo.bVisible = false; //���ؿ���̨���  
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬  
	system("cls");
	prin_Border();
	move(4, 23);
	color(14);
	cout << "��ѡ���Ѷ�";
	move(6, 24);
	cout << ">";
	move(6, 25);
	color(10);
	cout << "�� ��";
	move(8, 25);
	cout << "�� ��";
	move(10, 25);
	cout << "�� ��";
	move(14, 25);
	color(8);
	cout << "�� P �� ��";
	int sr_x = 6;
	char ssg;
	while ((ssg = _getch()) != '\0')
	{
		if (ssg == 'p')
		{
			Play_ReturnMusic();
			Interface();
		}
		if (ssg == 's')
		{
			Play_ChooseMusic();
			if (sr_x < 10)
			{
				move(sr_x, 24);
				cout << " ";
				sr_x += 2;
				move(sr_x, 24);
				color(14);
				cout << ">";
			}
		}
		if (ssg == 'w')
		{
			Play_ChooseMusic();
			if (sr_x > 6)
			{
				move(sr_x, 24);
				cout << " ";
				sr_x -= 2;
				move(sr_x, 24);
				color(14);
				cout << ">";
			}
		}
		if (ssg == ' ')
		{
			Play_GetMusic();
			Sleep(300);
			if (sr_x == 6)
			{
				degree = 6;
				set_map();
			}
			if (sr_x == 8)
			{
				degree = 8;
				set_map2();
			}
			if (sr_x == 10)
			{
				set_map3();
				degree = 10;
			}
			return;
		}
	}
}
//����
void Interface()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ  
	CursorInfo.bVisible = false; //���ؿ���̨���  
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬  
	system("cls");
	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);    //��ñ�׼����豸���
	CONSOLE_SCREEN_BUFFER_INFO csbi;                        //���崰�ڻ�������Ϣ�ṹ��  
	GetConsoleScreenBufferInfo(handle_out, &csbi);          //��ô��ڻ�������Ϣ 
	set_Border();
	prin_Border();
	//Play_MenuMusic();
	//HANDLE handle10 = CreateThread(NULL, 0, Play_Menu, NULL, 0, NULL);
	move(6, 24);
	color(14);
	cout << ">";
	move(6, 25);
	SetConsoleTextAttribute(handle_out, BACK_CYAN);
	cout << "�� ʼ �� Ϸ" << endl;
	move(8, 25);
	cout << "�� Ϸ ˵ ��" << endl;
	move(10, 25);
	cout << "�� �� �� ��" << endl;
	SetConsoleTextAttribute(handle_out, FOREGROUND_INTENSITY | FORE_RED);
	char select;
	int st_x = 6;
	while ((select=_getch())!='\0')
	{
		//select = _getch();
		if (select == 's')
		{
			//HANDLE handle11 = CreateThread(NULL, 0, Play_ChooseMusic, NULL, 0, NULL);
			Play_ChooseMusic();
			if (st_x < 10)
			{
				move(st_x, 24);
				cout << " ";
				st_x += 2;
				move(st_x, 24);
				color(14);
				cout << ">";
			}
		}
		if (select == 'w')
		{
			Play_ChooseMusic();
			if (st_x > 6)
			{
				move(st_x, 24);
				cout << " ";
				st_x -= 2;
				move(st_x, 24);
				color(14);
				cout << ">";
			}
		}
		if (select == ' ')
		{
			Play_GetMusic();
			//������Ϸ
			if (st_x == 6)
			{
				DegreeOfDifficult();
				break;
			}
			//����ѡ����Ϸ˵������
			if (st_x == 8)
			{
				Opera_Desc();
				break;
			}
			//����������ǽ���
			if (st_x == 10)
			{
				About_us();
				break;
			}
		}
	}
}
int main()
{
	//HANDLE handle08 = CreateThread(NULL, 0, randFood, NULL, 0, NULL);  
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ  
	CursorInfo.bVisible = false; //���ؿ���̨���  
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬  
	prin_Begin();
	Interface();
	xsnake s1;
	//s1.set_map();//��
	//s1.set_map2();//�е�
	prin_map();
	s1.Buildsnake(10);
	randFood();
	move(tail->x, tail->y);//��ʼ�����ѹ���ƶ������
	s1.prin_body();//��ӡ�տ�ʼ�������������
	s1.input_direction();
	Sleep(3000);
	system("pause");
	return 0;
}

