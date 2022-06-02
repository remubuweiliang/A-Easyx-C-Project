#include<stdio.h>
#include<graphics.h>
#include<Windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<time.h>
#include <easyx.h>
#include<ctype.h>
#include <math.h>
#pragma comment(lib,"winmm.lib")
#define initheight 640
#define initwidth 480
#define High 480 
#define Width 640
#define movieheight 480
#define moviewidth 640
#pragma warning(disable:4996)
int board[20][20] = { 0 };
int flag = 0; 
int MouseX, MouseY;
MOUSEMSG m;
struct
{
	int num;//格子当前状态，1表示有雷，0表示无雷或已经显示数字
	int roundnum;//统计格子周围的雷数
	int flag;//右键按下显示红旗标志，0表示没有，1表示有
}Mine[10][10];
typedef struct tagBall
{
	int x;
	int y;
	int moveX;
	int moveY;
	int color;
}Ball;
int mineNUM;//统计处理过的格子数
TCHAR randmineNUM[100];

int tree(void);
void chapter1(void);
void chapter2(void);
void chapter3(void);
void chapter4(void);
void chapter5(void);
void chapter6(void);
int times(int i);
void thank(void);
void fault(void);
#define chapterwidth 200
#define chapterheight 355
static char str[3] = "0";

void initall1(void);
int initall2(void);
int message(void);
int situation(void);

int musicinit(void);
int music(void);
int playmusic(void);
void closemusic(void);
int look(void);

int timedata(void);

int game(void);
int game3(void);
void game3f(void);
int playgame3(void);
int judge(int a, int b);
int game2(void);
void game2f(void);
int playgame2(void);
int minestatistics(int i, int j);
void showwhite(int i, int j);
void drawsmile(void);
void drawredflag(int i, int j);
void drawempty(int i, int j, int mode, int color);
void mousegetXY(void);
int game2play(void);
void game2begin(void);
void game2over(void);
void game2win(void);
int game1(void);
int playgame1(void);
void game1f(void);

void move(void);
void gotoxy(int x, int y);
void eye();
void one();
void two();
void three();
int checkbutton(int x, int y);
int PLAY = 0;//是否第一次
int FLAG = 1;//失败后重新开始
int AGAIN = 0;//中途重新开始
//主模块
int main(void)
{
	mciSendString("open ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
	mciSendString("play music1 repeat", 0, 0, 0);
	move();
A://initall1();
	int function;
	function = initall2();
B:switch (function)
{
case 0:
	break;
case 1://@1.节粮打卡
{
	tree();
	closegraph();
	goto A;
	break;
}
case 2://@2.粮食现状
{
	situation();
	closegraph();
	closemusic();
	mciSendString("open ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
	mciSendString("play music1 repeat", 0, 0, 0);
	goto A;
	break;
}
case 3://@3.音乐休闲
{

G:int musicf;
	musicf = 0;
	musicf = music();
	musicinit();
	switch (musicf)
	{
	case 1:
	{
		playmusic();
		closegraph();
		goto G;
	}
	case 2:
	{
		goto A;
		closegraph();
		break;
	}
	}
}
case 4://@4.休闲益智
{
C:int g = game();
	switch (g)
	{
	case 1://连连看
	{
	F:int g1 = game1();
		switch (g1)
		{
		case 1://开始游戏
		{
			playgame1();
			goto E;
		}
		case 2://游戏规则
		{
			game1f();
			goto F;
		}
		case 3://返回菜单
		{
			closemusic();
			mciSendString("open ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
			mciSendString("play music1 repeat", 0, 0, 0);
			goto B;
		}
		}
	}
	case 2://扫雷
	{
	E:int g2 = game2();
		switch (g2)
		{
		case 1://开始游戏
		{
			playgame2();
			goto E;
		}
		case 2://游戏规则
		{
			game2f();
			goto E;
		}
		case 3://返回菜单
		{
			closemusic();
			mciSendString("open ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
			mciSendString("play music1 repeat", 0, 0, 0);
			goto B;
		}
		}
	}
	case 3://五子棋
	{
	D:int g3 = game3();
		switch (g3)
		{
		case 1://开始游戏
		{
			playgame3();
			goto D;
		}
		case 2://游戏规则
		{
			game3f();
			goto C;
		}
		case 3://返回菜单
		{
			closemusic();
			mciSendString("open ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
			mciSendString("play music1 repeat", 0, 0, 0);
			goto B;
		}
		}
	}
	case 4:
	{
		goto A;
	}
	}
	break;
	}
case 5://@5.日期时间
{
	timedata();
	goto A;
	break;
}
case 6://@6.版权信息
{
	message();
	goto A;
	break;
}
}
return 0;
}
//菜单初始化模块
void move(void)
{
	initgraph(800, 600);
	eye();
	two();
	Sleep(300);
	three();
	Sleep(1500);
	return;
}
void initall1(void)//初始化界面
{
	initgraph(initwidth, initheight);
	IMAGE img1;
	loadimage(&img1, "..\\data\\picture\\img1.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img1);
	while (!kbhit())//按任意键继续,设置字体闪烁效果
	{
		for (int i = 0; i <= 255; i += 25)
		{
			settextcolor(RGB(i, 0, 0));
			settextstyle(33, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(initwidth / 4 + 20, initheight * 2 / 3, "按任意键继续");
			Sleep(100);
		}
		for (int i = 0; i <= 255; i += 25)
		{
			settextcolor(RGB(0, i, 0));
			settextstyle(33, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(initwidth / 4 + 20, initheight * 2 / 3, "按任意键继续");
			Sleep(100);
		}
		for (int i = 0; i <= 255; i += 25)
		{
			settextcolor(RGB(0, 0, i));
			settextstyle(33, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(initwidth / 4 + 20, initheight * 2 / 3, "按任意键继续");
			Sleep(100);
		}
	}
	return;
}
int initall2(void)//初始化界面,选择菜单
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "菜单");
	IMAGE img2;
	loadimage(&img2, "..\\data\\picture\\img2.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img2);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 20, initheight * 4 / 7, "菜单");
	outtextxy(initwidth / 4, initheight * 4 / 7+40, "@1.节粮打卡");
	outtextxy(initwidth / 4, initheight * 4 / 7+40*2, "@2.粮食现状");
	outtextxy(initwidth / 4, initheight * 4 / 7 + 40 * 3, "@3.音乐休闲");
	outtextxy(initwidth / 4, initheight * 4 / 7 + 40 * 4, "@4.休闲益智");
	outtextxy(initwidth / 4, initheight * 4 / 7 + 40 * 5, "@5.日期时间");
	outtextxy(initwidth / 4, initheight * 4 / 7 + 40 * 6, "@6.版权信息");
	Sleep(1000);
	fflush(stdin);
	while (1)//选择
	{
		while (kbhit())
		{
			static int fox = 1;
			for (int i = 1; i <= 6; i++)
			{
				setfillcolor(RGB(255, 255, 255));
				fillcircle(initwidth / 5, initheight * 4 / 7 + 15 + 40 *i, 10);
			}
			char ch = getch();
			if (ch == 72 && fox > 1 || ch == 'w' && fox > 1 || ch == 'W' && fox > 1)
				fox--;
			else if (ch == 80 && fox < 6 || ch == 's' && fox < 6 || ch == 'S' && fox < 6)
				fox++;
			else if (ch == ' ' || ch == 13)//按空格或回车键确定
				return fox;
			else if (ch == 27)
			{
				if (MessageBox(hwnd, "是否退出程序？", "退出", MB_YESNO) == IDYES)
					return 0;
			}
			setfillcolor(RGB(0, 0, 0));
			fillcircle(initwidth / 5, initheight * 4 / 7 + 15 + 40 * fox, 10);
		}
	}
}
int message(void)//出厂信息
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "出厂信息");
	IMAGE img3;
	loadimage(&img3, "..\\data\\picture\\img3.jpg");
	putimage(0, 0, &img3);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 20, initheight * 1/ 20, "开发商：");
	settextcolor(RGB(0, 0, 200));
	outtextxy(initwidth / 20+textwidth("开发商："), initheight * 1 / 20, "华师大学软工一班");
	settextcolor(RGB(0, 0, 0));
	outtextxy(initwidth / 20, initheight * 1 / 20+40, "负责人：");
	settextcolor(RGB(0, 0, 200));
	outtextxy(initwidth / 20+textwidth("负责人："), initheight * 1 / 20 + 40, "詹润源");
	settextcolor(RGB(0, 0, 0));
	outtextxy(initwidth / 20, initheight * 1 / 20+40*2, "开发日期：");
	settextcolor(RGB(0, 0, 200));
	outtextxy(initwidth / 20 + textwidth("开发日期："), initheight * 1 / 20 + 40 * 2, "2020年11月20日");
	settextcolor(RGB(0, 0, 0));
	outtextxy(initwidth / 20, initheight * 1 / 20+40*3, "调试环境：");
	settextcolor(RGB(0, 0, 200));
	outtextxy(initwidth / 20 + textwidth("调试环境："), initheight * 1 / 20 + 40 * 3, "VS2019社区版");
	outtextxy(initwidth / 20, initheight * 1 / 20+40*4, "         (附easyx图形库)");
	settextcolor(RGB(0, 100, 100));
	outtextxy(initwidth / 20, initheight * 1 / 20 + 40 * 5, "图片来源于网络");
	outtextxy(initwidth / 20, initheight * 1 / 20 + 40 * 6, "如侵权，请联系，见谅！");
	while (1)
	{
		for (int i = 0; i <=300; i++)
		{
			if(i%2==0)
				settextcolor(RGB(0,0,0));
			else
				settextcolor(RGB(176,193 ,200));
			outtextxy(initwidth / 20, initheight * 1/20 + 40 * 7+25, "按回车键返回");
			Sleep(820);
			if (kbhit())
			{
				if(char ch=getch()==13)
				return 0;
			}
		}
		
	}
}
//节粮树模块
int tree(void)//种树
{
	initgraph(480, 640);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "节粮打卡");
	IMAGE img23;
	loadimage(&img23, "..\\data\\picture\\img23.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img23);
	settextcolor(BLACK);
	int n = 0, m;
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	if (MessageBox(hwnd, "今日是否成功节粮~", "打卡", MB_YESNO) == IDYES)
	{
		n = 1;
	}
	m = times(n);
	if (m < 10)
	{
		chapter1();
		return 0;
	}
	else if (m < 20 && m >= 10)
	{
		chapter2();
		return 0;
	}
	else if (m < 30 && m >= 20)
	{
		chapter3();
		return 0;
	}
	else if (m < 40 && m >= 30)
	{
		chapter4();
		return 0;
	}
	else if (m < 50 && m >= 40)
	{
		chapter5();
		return 0;
	}
	else if (m >= 50)
	{
		chapter6();

		thank();
		return 0;
	}
	else
	{
		fault();
		return 0;
	}
	return 0;
}
int times(int i)
{
	if (i == 1)
	{
		FILE* fp;
		if ((fp = fopen("..\\data\\data.txt", "a+")) == NULL)
		{
			HWND hwnd = GetHWnd();
			SetWindowText(hwnd, "创建失败！！！");
		}
		fclose(fp);
		fp = NULL;
		if ((fp = fopen("..\\data\\data.txt", "r+")) == NULL)
		{
			HWND hwnd = GetHWnd();
			SetWindowText(hwnd, "打开失败！！！");
		}
		fgets(str, 3, fp);
		fclose(fp);
		int i = atoi(str) + 1;
		_stprintf_s(str, _T("%d"), i);
		if ((fp = fopen("..\\data\\data.txt", "w+")) == NULL)
		{
			HWND hwnd = GetHWnd();
			SetWindowText(hwnd, "存储失败！！！");
		}
		fputs(str, fp);
		fclose(fp);
		return atoi(str);
	}
	else
	{
		FILE* fp;
		if ((fp = fopen("C:\\Users\\若木不微凉。\\Desktop\\节@粮\\data\\data.txt", "r+")) == NULL)
		{
			HWND hwnd = GetHWnd();
			SetWindowText(hwnd, "打开失败！！！");
		}
		fgets(str, 3, fp);
		return atoi(str);
	}
}
void chapter1(void)
{
	initgraph(chapterwidth, chapterheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "一级");
	IMAGE img22;
	loadimage(&img22, "..\\data\\picture\\img22.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, 200, 355, &img22, 813.6, 355);
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 30, chapterheight * 1 / 7, "您已打卡");
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵"), chapterheight * 1 / 7, str);
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵呵"), chapterheight * 1 / 7, "次");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void chapter2(void)
{
	initgraph(chapterwidth, chapterheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "二级");
	IMAGE img22;
	loadimage(&img22, "..\\data\\picture\\img22.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, 200, 355, &img22, 675, 355);
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 30, chapterheight * 1 / 7, "您已打卡");
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵"), chapterheight * 1 / 7, str);
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵呵"), chapterheight * 1 / 7, "次");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void chapter3(void)
{
	initgraph(chapterwidth, chapterheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "三级");
	IMAGE img22;
	loadimage(&img22, "..\\data\\picture\\img22.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, 200, 355, &img22, 490, 355);
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 30, chapterheight * 1 / 7, "您已打卡");
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵"), chapterheight * 1 / 7, str);
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵呵"), chapterheight * 1 / 7, "次");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void chapter4(void)
{
	initgraph(chapterwidth, chapterheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "四级");
	IMAGE img22;
	loadimage(&img22, "..\\data\\picture\\img22.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, 200, 355, &img22, 280, 355);
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 30, chapterheight * 1 / 7, "您已打卡");
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵"), chapterheight * 1 / 7, str);
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵呵"), chapterheight * 1 / 7, "次");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void chapter5(void)
{
	initgraph(chapterwidth, chapterheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五级");
	IMAGE img22;
	loadimage(&img22, "..\\data\\picture\\img22.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, 200, 355, &img22, 25, 355);
	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 30, chapterheight * 1 / 7, "您已打卡");
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵"), chapterheight * 1 / 7, str);
	outtextxy(chapterwidth / 20 + 30 + textwidth("呵呵呵呵呵"), chapterheight * 1 / 7, "次");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void chapter6(void)
{
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "VICTORY");
	initgraph(480, 640);
	IMAGE img23;
	loadimage(&img23, "..\\data\\picture\\img23.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img23);
	settextcolor(BLACK);
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 130, chapterheight * 1 / 7 - 30, "您已打卡");
	outtextxy(chapterwidth / 20 + 130 + textwidth("呵呵呵呵"), chapterheight * 1 / 7 - 30, str);
	outtextxy(chapterwidth / 20 + 130 + textwidth("呵呵呵呵呵"), chapterheight * 1 / 7 - 30, "次");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void thank()
{
	initgraph(480, 640);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "感谢！！！");
	IMAGE img23;
	loadimage(&img23, "..\\data\\picture\\img23.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img23);
	settextcolor(BLACK);
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20, chapterheight * 1 / 7 - 30, "感谢您为地球所做出的一切");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
void fault(void)
{
	initgraph(480, 640);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "数据错误！！！");
	IMAGE img23;
	loadimage(&img23, "..\\data\\picture\\img23.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img23);
	settextcolor(BLACK);
	settextstyle(50, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(chapterwidth / 20 + 200, chapterheight * 1 / 7 - 30, "Fault！！！");
	while (1)
	{
		if (kbhit())
		{
			if (char ch = getch() == 13)
				return;
		}
	}
}
//现状介绍模块
int situation(void)
{
	initgraph(moviewidth, movieheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "粮食现状");
	closemusic();
	mciSendString("open ..\\data\\music\\music14.wma alias music14", 0, 0, 0);
	mciSendString("play music14 repeat", 0, 0, 0);
	IMAGE img10, img11, img12, img13, img14, img15, img16, img17, img18, img19, img20, img21, img24;
	loadimage(&img10, "..\\data\\picture\\img10.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	loadimage(&img11, "..\\data\\picture\\img11.jpg");
	loadimage(&img12, "..\\data\\picture\\img12.jpg");
	loadimage(&img13, "..\\data\\picture\\img13.jpg");
	loadimage(&img14, "..\\data\\picture\\img14.jpg");
	loadimage(&img15, "..\\data\\picture\\img15.jpg");
	loadimage(&img16, "..\\data\\picture\\img16.jpg");
	loadimage(&img17, "..\\data\\picture\\img17.jpg");
	loadimage(&img18, "..\\data\\picture\\img18.jpg");
	loadimage(&img19, "..\\data\\picture\\img19.jpg");
	loadimage(&img20, "..\\data\\picture\\img20.jpg");
	loadimage(&img21, "..\\data\\picture\\img21.jpg");
	loadimage(&img24, "..\\data\\picture\\img24.jpg");
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	putimage(0, 0, &img10);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "因");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "为");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "灾");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 2 / 3, "害");
	Sleep(500);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 1, movieheight * 2 / 3 + 50, "大");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 2, movieheight * 2 / 3 + 50, "地");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 3, movieheight * 2 / 3 + 50, "生");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 4, movieheight * 2 / 3 + 50, "灵");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 5, movieheight * 2 / 3 + 50, "涂");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 6, movieheight * 2 / 3 + 50, "碳");
	Sleep(250);
	getchar();
	putimage(0, 0, &img11);
	settextcolor(RGB(255, 255, 255));
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "气");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "候");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "的");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 2 / 3, "恶");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 4, movieheight * 2 / 3, "化");
	Sleep(500);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 1, movieheight * 2 / 3 + 50, "粮");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 2, movieheight * 2 / 3 + 50, "食");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 3, movieheight * 2 / 3 + 50, "产");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 4, movieheight * 2 / 3 + 50, "量");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 5, movieheight * 2 / 3 + 50, "急");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 6, movieheight * 2 / 3 + 50, "剧");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 7, movieheight * 2 / 3 + 50, "下");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 8, movieheight * 2 / 3 + 50, "降");
	Sleep(250);
	getchar();
	putimage(0, 0, &img12);
	settextcolor(RGB(0, 0, 0));
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "有");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "如");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "末日般");
	Sleep(500);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 5, movieheight * 2 / 3, "的");
	Sleep(500);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 3, movieheight * 2 / 3 + 50, "全球灾害");
	Sleep(500);
	getchar();
	putimage(0, 0, &img13);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "让");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "一");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "个");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 2 / 3, "个");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 4, movieheight * 2 / 3, "无");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 5, movieheight * 2 / 3, "辜");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 6, movieheight * 2 / 3, "的");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 7, movieheight * 2 / 3, "人");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 8, movieheight * 2 / 3, "儿");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 5, movieheight * 2 / 3 + 50, "饱");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 6, movieheight * 2 / 3 + 50, "受");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 7, movieheight * 2 / 3 + 50, "苦");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 8, movieheight * 2 / 3 + 50, "难");
	Sleep(250);
	getchar();
	putimage(0, 0, &img14);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "因");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "为");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "贫穷");
	Sleep(500);
	getchar();
	putimage(0, 0, &img15);
	settextcolor(RGB(255, 255, 255));
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "人");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "们");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "整");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 2 / 3, "日");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 4, movieheight * 2 / 3, "为");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 5, movieheight * 2 / 3, "生");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 6, movieheight * 2 / 3, "计");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 7, movieheight * 2 / 3, "奔");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 8, movieheight * 2 / 3, "波");
	Sleep(250);
	getchar();
	putimage(0, 0, &img16);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "为");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "了");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "几");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 2 / 3, "斗");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 4, movieheight * 2 / 3, "米");
	Sleep(500);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 1, movieheight * 2 / 3 + 50, "苦");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 2, movieheight * 2 / 3 + 50, "苦");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 3, movieheight * 2 / 3 + 50, "哀");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 4, movieheight * 2 / 3 + 50, "求");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 5, movieheight * 2 / 3 + 50, "着");
	Sleep(250);
	getchar();
	putimage(0, 0, &img17);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "心酸");
	Sleep(500);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "？");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 1, movieheight * 2 / 3 + 50, "亦");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 2, movieheight * 2 / 3 + 50, "或");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 3, movieheight * 2 / 3 + 50, "是");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 4, movieheight * 2 / 3 + 50, "怜悯");
	Sleep(500);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 6, movieheight * 2 / 3 + 50, "？");
	Sleep(250);
	getchar();
	putimage(0, 0, &img18);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "好");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "在");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 2, movieheight * 2 / 3, "有");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 2 / 3, "一");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 4, movieheight * 2 / 3, "群");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 5, movieheight * 2 / 3, "友爱");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 7, movieheight * 2 / 3, "的");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 8, movieheight * 2 / 3, "人儿");
	Sleep(250);
	getchar();
	putimage(0, 0, &img19);
	settextcolor(RGB(0, 0, 255));
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 2 / 3, "以");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 2 / 3, "凡人之力");
	Sleep(900);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 1, movieheight * 2 / 3 + 50, "驱散死神");
	Sleep(900);
	getchar();
	putimage(0, 0, &img20);
	settextcolor(RGB(255, 255, 0));
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 0, movieheight * 1 / 5, "所以");
	Sleep(500);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 1, movieheight * 1 / 5 + 50, "你");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 2, movieheight * 1 / 5 + 50, "是");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 3, movieheight * 1 / 5 + 50, "愿");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 4, movieheight * 1 / 5 + 50, "做");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 5, movieheight * 1 / 5 + 50, "一个");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 7, movieheight * 1 / 5 + 50, "恶魔");
	Sleep(500);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 2, movieheight * 1 / 5 + 50 * 2, "浪费粮食，");
	Sleep(900);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 7, movieheight * 1 / 5 + 50 * 2, "肆意挥霍？");
	Sleep(900);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 0, movieheight * 1 / 5 + 50 * 3, "还是");
	Sleep(500);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 1, movieheight * 1 / 5 + 50 * 4, "成");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 2, movieheight * 1 / 5 + 50 * 4, "为");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 3, movieheight * 1 / 5 + 50 * 4, "一位");
	Sleep(250);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 5, movieheight * 1 / 5 + 50 * 4, "天使");
	Sleep(500);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 2, movieheight * 1 / 5 + 50 * 5, "济世扶贫，");
	Sleep(900);
	outtextxy(moviewidth / 20 + 70 + textwidth("呵") * 7, movieheight * 1 / 5 + 50 * 5, "散播温暖？");
	Sleep(900);
	getchar();
	cleardevice();
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷书");
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5, "据统计");//报告指出,冲突,气候变化与经济波动是导致粮食不安全的主要原因.
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50, "2018年");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 3, movieheight * 1 / 5 + 50, "全球有");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 6, movieheight * 1 / 5 + 50, "53个国家");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 10, movieheight * 1 / 5 + 50, "或");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 11, movieheight * 1 / 5 + 50, "地区");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 13, movieheight * 1 / 5 + 50, "约");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 14, movieheight * 1 / 5 + 50, "1.13亿人");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 18, movieheight * 1 / 5 + 50, "遭受");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 20, movieheight * 1 / 5 + 50, "重度饥饿");
	Sleep(900);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5 + 50 * 2, "其中");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50 * 3, "气候变化");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 4, movieheight * 1 / 5 + 50 * 3, "与");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 5, movieheight * 1 / 5 + 50 * 3, "经济波动");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5 + 50 * 4, "是导致");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50 * 5, "粮食危机");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 4, movieheight * 1 / 5 + 50 * 5, "的");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 5, movieheight * 1 / 5 + 50 * 5, "主要原因");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 9, movieheight * 1 / 5 + 50 * 5, "!");
	Sleep(250);
	getchar();
	cleardevice();
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5, "所以");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50, "你应该");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 3, movieheight * 1 / 5 + 50, "知道");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5 + 50 * 2, "世界上");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 2, movieheight * 1 / 5 + 50 * 3, "有多少人");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 6, movieheight * 1 / 5 + 50 * 3, "在忍受着");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 10, movieheight * 1 / 5 + 50 * 3, "饥饿的压迫");
	Sleep(900);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5 + 50 * 4, "每一粒米");
	Sleep(900);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 3, movieheight * 1 / 5 + 50 * 4, "每一粒粮");
	Sleep(900);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50 * 5, "都是");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 2, movieheight * 1 / 5 + 50 * 5, "他们");
	Sleep(250);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 4, movieheight * 1 / 5 + 50 * 5, "对生命");
	Sleep(500);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 7, movieheight * 1 / 5 + 50 * 5, "的渴望");
	Sleep(900);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 10, movieheight * 1 / 5 + 50 * 5, "！");
	Sleep(500);
	getchar();
	cleardevice();
	putimage(0, 0, &img24);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "楷书");
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * -1, movieheight * 1 / 5, "所以");
	Sleep(700);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50, "让我们");
	Sleep(700);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 3, movieheight * 1 / 5 + 50, "从现在");
	Sleep(700);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 6, movieheight * 1 / 5 + 50, "做起");
	Sleep(700);
	settextstyle(50, 0, "隶书");
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 0, movieheight * 1 / 5 + 50 * 3, "节约粮食！");
	Sleep(900);
	outtextxy(moviewidth / 20 + 50 + textwidth("呵") * 5, movieheight * 1 / 5 + 50 * 3, "珍爱生命！");
	Sleep(900);
	getchar();
	cleardevice();
	settextcolor(RGB(255, 255, 0));
	putimage(0, 0,&img21);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 0, movieheight * 1 / 5, "献");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 1, movieheight * 1 / 5, "点滴");
	Sleep(250);
	outtextxy(moviewidth / 20 + 130 + textwidth("呵") * 3, movieheight * 1 / 5, "之力");
	Sleep(900);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 1, movieheight * 1 / 5 + 50, "得");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 2, movieheight * 1 / 5 + 50, "天下");
	Sleep(250);
	outtextxy(moviewidth / 20 + 150 + textwidth("呵") * 4, movieheight * 1 / 5 + 50, "大同");
	Sleep(250);
	getchar();
	return 0;
}
//音乐模块
int musicinit(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "音乐休闲");
	IMAGE img4;
	loadimage(&img4, "..\\data\\picture\\img4.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img4);
	settextcolor(WHITE);
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);//设置字体渐出效果
	outtextxy(initwidth / 20, initheight * 1 / 20,"生");
	Sleep(200);
	outtextxy(initwidth / 20+textwidth("呵"), initheight * 1 / 20, "活");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*2, initheight * 1 / 20, "在");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*3, initheight * 1 / 20, "忙");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*4, initheight * 1 / 20, "碌");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*5, initheight * 1 / 20, "的");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*6, initheight * 1 / 20, "大");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵") * 7, initheight * 1 / 20, "都");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵") * 8, initheight * 1 / 20, "市");
	Sleep(200);
	outtextxy(initwidth / 20 + 50, initheight * 1 / 20 + 80, "在");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*1, initheight * 1 / 20 + 80, "饱");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*2, initheight * 1 / 20 + 80, "腹");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*3, initheight * 1 / 20 + 80, "的");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*4, initheight * 1 / 20 + 80, "满");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*5, initheight * 1 / 20 + 80, "足");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*6, initheight * 1 / 20 + 80, "感");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*7, initheight * 1 / 20 + 80, "中");
	Sleep(200);
	outtextxy(initwidth / 20, initheight * 1 / 20+80*2, "不");
	Sleep(200);
	outtextxy(initwidth / 20+textwidth("呵")*1, initheight * 1 / 20 + 80 * 2, "妨");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*2, initheight * 1 / 20 + 80 * 2, "暂");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*3, initheight * 1 / 20 + 80 * 2, "缓");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*4, initheight * 1 / 20 + 80 * 2, "脚");
	Sleep(200);
	outtextxy(initwidth / 20 + textwidth("呵")*5, initheight * 1 / 20 + 80 * 2, "步");
	Sleep(200);
	outtextxy(initwidth / 20+50, initheight * 1 / 20+80*3, "去");
	Sleep(200);
	outtextxy(initwidth / 20 + 50+textwidth("呵")*1, initheight * 1 / 20 + 80 * 3, "聆");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*2, initheight * 1 / 20 + 80 * 3, "听");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*3, initheight * 1 / 20 + 80 * 3, "一");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*4, initheight * 1 / 20 + 80 * 3, "首");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*5, initheight * 1 / 20 + 80 * 3, "时");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*6, initheight * 1 / 20 + 80 * 3, "光");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*7, initheight * 1 / 20 + 80 * 3, "心");
	Sleep(200);
	outtextxy(initwidth / 20 + 50 + textwidth("呵")*8, initheight * 1 / 20 + 80 * 3, "曲");
	Sleep(200);
	while (!kbhit())//按任意键继续,设置字体闪烁效果
	{
		for (int i = 0; i <= 255; i += 25)
		{
			settextcolor(RGB(i, 0, 0));
			settextstyle(33, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(initwidth / 4 + 20, initheight * 2 / 3, "按任意键继续");
			Sleep(100);
		}
		for (int i = 0; i <= 255; i += 25)
		{
			settextcolor(RGB(0, i, 0));
			settextstyle(33, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(initwidth / 4 + 20, initheight * 2 / 3, "按任意键继续");
			Sleep(100);
		}
		for (int i = 0; i <= 255; i += 25)
		{
			settextcolor(RGB(0, 0, i));
			settextstyle(33, 0, "楷体");
			setbkmode(TRANSPARENT);
			outtextxy(initwidth / 4 + 20, initheight * 2 / 3, "按任意键继续");
			Sleep(100);
		}
	}
	return 0;
}
int music(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "音乐休闲");
	IMAGE img4;
	loadimage(&img4, "..\\data\\picture\\img4.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img4);
	settextcolor(RGB(255, 255, 255));
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 4, initheight * 1 / 7, "点歌");
	outtextxy(initwidth / 4, initheight * 1 / 7 + 40, "返回菜单");
	fflush(stdin);
	while (1)
	{
		while (kbhit())
		{
		    int musicfox = 1;
			for (int i = 0; i <= 1; i++)
			{
				setfillcolor(RGB(255, 255, 255));
				fillcircle(initwidth / 5, initheight * 1 / 7 + 15 + 40 * i, 10);
			}
			char ch = getch();
			if (ch == 72  || ch == 'w'  || ch == 'W' )
				musicfox = 1;
			else if (ch == 80 || ch == 's' || ch == 'S')
				musicfox = 2;
			else if (ch == ' ' || ch == 13)//按空格或回车键确定
				return musicfox;
			setfillcolor(RGB(0, 0, 0));
			fillcircle(initwidth / 5, initheight * 1 / 7 + 15 + 40 * (musicfox-1), 10);
		}
	}
}
int playmusic(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "音乐选择");
	IMAGE img4;
	loadimage(&img4, "..\\data\\picture\\img4.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img4);
	settextcolor(RGB(255, 255, 255));
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 4, initheight * 1 / 7, "点歌");
	char str[3];
	P:InputBox(str, 3, "请输入你喜欢的数字（1---100）", "心曲匹配", "love~", 41, 22, HideCaret);                                  //她的生日。
	if ((int)atoi(str) == 1)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
		mciSendString("play music1 repeat", 0, 0, 0);
		look();
		return 1;
	}
	else if ((int)atoi(str) == 2)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music2.wma alias music2", 0, 0, 0);
		mciSendString("play music2 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 3)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music3.wma alias music3", 0, 0, 0);
		mciSendString("play music3 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 4)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music4.wma alias music4", 0, 0, 0);
		mciSendString("play music4 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 5)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music5.wma alias music5", 0, 0, 0);
		mciSendString("play music5 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 6)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music6.wma alias music6", 0, 0, 0);
		mciSendString("play music6 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 7)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music7.wma alias music7", 0, 0, 0);
		mciSendString("play music7 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 8)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music8.wma alias music8", 0, 0, 0);
		mciSendString("play music8 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 9)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music9.wma alias music9", 0, 0, 0);
		mciSendString("play music9 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 10)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music10.wma alias music10", 0, 0, 0);
		mciSendString("play music10 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 11)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music11.wma alias music11", 0, 0, 0);
		mciSendString("play music11 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 12)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music12.wma alias music12", 0, 0, 0);
		mciSendString("play music12 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 13)
	{
		closemusic();
		mciSendString("open ..\\data\\music\\music13.wma alias music13", 0, 0, 0);
		mciSendString("play music13 repeat", 0, 0, 0);
		look();
		return 0;
	}
	else if ((int)atoi(str) == 14)
	{
	closemusic();
	mciSendString("open ..\\data\\music\\music14.wma alias music14", 0, 0, 0);
	mciSendString("play music14 repeat", 0, 0, 0);
	look();
	return 0;
	}
	else if ((int)atoi(str) == 15)
	{
	closemusic();
	mciSendString("open ..\\data\\music\\music15.wma alias music15", 0, 0, 0);
	mciSendString("play music15 repeat", 0, 0, 0);
	look();
	return 0;
	}
	else
	{
	HWND hwnd = GetHWnd();
	MessageBox(hwnd, "输入错误，请重新输入", "警告~",MB_OK);
	goto P;
	}
}
void closemusic(void)
{
	mciSendString("close ..\\data\\music\\music1.wma alias music1", 0, 0, 0);
	mciSendString("stop music1", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music2.wma alias music2", 0, 0, 0);
	mciSendString("stop music2", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music3.wma alias music3", 0, 0, 0);
	mciSendString("stop music3", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music4.wma alias music4", 0, 0, 0);
	mciSendString("stop music4", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music5.wma alias music5", 0, 0, 0);
	mciSendString("stop music5", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music6.wma alias music6", 0, 0, 0);
	mciSendString("stop music6", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music7.wma alias music7", 0, 0, 0);
	mciSendString("stop music7", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music8.wma alias music8", 0, 0, 0);
	mciSendString("stop music8", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music9.wma alias music9", 0, 0, 0);
	mciSendString("stop music9", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music10.wma alias music10", 0, 0, 0);
	mciSendString("stop music10", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music11.wma alias music11", 0, 0, 0);
	mciSendString("stop music11", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music12.wma alias music12", 0, 0, 0);
	mciSendString("stop music12", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music13.wma alias music13", 0, 0, 0);
	mciSendString("stop music13", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music14.wma alias music14", 0, 0, 0);
	mciSendString("stop music14", 0, 0, 0);
	mciSendString("close ..\\data\\music\\music15.wma alias music15", 0, 0, 0);
	mciSendString("stop music15", 0, 0, 0);
}
int look(void)//音乐养眼图
{
	initgraph(800, 600);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "养眼图");
	setbkcolor(WHITE);
	//cleardevice();
	int arrColor[] = {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		BROWN,
		LIGHTGRAY,
		DARKGRAY,
		LIGHTBLUE,
		LIGHTGREEN,
		LIGHTCYAN,
		LIGHTRED,
		LIGHTMAGENTA,
		YELLOW,
		WHITE
	};
	Ball arrBall[20];
	for (int i = 0; i < 20; i++)
	{
		arrBall[i].x = rand() % 800;
		arrBall[i].y = rand() % 600;
		arrBall[i].moveX = 5;
		arrBall[i].moveY = 5;
		arrBall[i].color = arrColor[rand() % 16];
	}
	// 让球不要越过整个窗体
	fflush(stdin);
	while (1)
	{
		BeginBatchDraw();
		for (int i = 0; i < 20; i++)
		{
			if (arrBall[i].y > 600)
			{
				arrBall[i].moveY = -arrBall[i].moveY;
				arrBall[i].color = arrColor[rand() % 16];
			}

			if (arrBall[i].x > 800)
			{
				arrBall[i].moveX = -arrBall[i].moveX;
				arrBall[i].color = arrColor[rand() % 16];
			}

			if (arrBall[i].y < 0)
			{
				arrBall[i].moveY = -arrBall[i].moveY;
				arrBall[i].color = arrColor[rand() % 16];
			}

			if (arrBall[i].x < 0)
			{
				arrBall[i].moveX = -arrBall[i].moveX;
				arrBall[i].color = arrColor[rand() % 16];
			}

			setfillcolor(arrBall[i].color);
			fillcircle(arrBall[i].x, arrBall[i].y, 10);

			arrBall[i].x = arrBall[i].x + arrBall[i].moveX;
			arrBall[i].y = arrBall[i].y + arrBall[i].moveY;
		}
		FlushBatchDraw();
		cleardevice();
		Sleep(40);
		if (kbhit())
		{
			char ch = getchar();
			if (ch==13||ch == 27)
				return 0;
		}
	}

}
//时钟模块
int timedata(void)//查看日期时间
{
	initgraph(Width, High);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "时间");
	int center_x, center_y;      // 中心点的坐标，也是表的中心
	center_x = Width / 2;
	center_y = High / 2;
	int secondLength = Width / 5;
	int minuteLength = Width / 6;
	int hourLength = Width / 7;
	int secondEnd_x, secondEnd_y;    // 终点
	int minuteEnd_x, minuteEnd_y;
	int hourEnd_x, hourEnd_y;
	float secondAngle;       // 对应的角度
	float minuteAngle;
	float hourAngle;
	SYSTEMTIME ti;
	BeginBatchDraw();
	//画时钟
	while (1)
	{
		// 绘制表盘
		setlinestyle(PS_SOLID, 1);
		setcolor(WHITE);
		circle(center_x, center_y, Width / 4);
		const double PI = acos(-1.0);
		char stryear[10], strmonth[10], strday[10];//转化word型为字符型
		// 画刻度
		int x, y, i;
		for (i = 0; i < 60; i++)
		{
			x = center_x + int(Width / 4.3 * sin(PI * 2 * i / 60));
			y = center_y + int(Width / 4.3 * cos(PI * 2 * i / 60));

			if (i % 15 == 0)
				bar(x - 5, y - 5, x + 5, y + 5);
			else if (i % 5 == 0)
				circle(x, y, 3);
			else
				putpixel(x, y, WHITE);
		}
		settextstyle(33, 0, "楷书");
		outtextxy(center_x - 25, center_y + Width / 4 + 20, "时钟");
		GetLocalTime(&ti);        // 获取当前时间
		_stprintf_s(stryear, _T("%d"), ti.wYear);
		_stprintf_s(strmonth, _T("%d"), ti.wMonth);
		_stprintf_s(strday, _T("%d"), ti.wDay);
		outtextxy(160, 40, stryear);
		outtextxy(230, 40, "年");
		outtextxy(260, 40, strmonth);
		outtextxy(290, 40, "月");
		outtextxy(320, 40, strday);
		outtextxy(360, 40, "日");
		if (ti.wDayOfWeek == 0)
			outtextxy(400, 40, "星期日");
		if (ti.wDayOfWeek == 1)
			outtextxy(400, 40, "星期一");
		if (ti.wDayOfWeek == 2)
			outtextxy(400, 40, "星期二");
		if (ti.wDayOfWeek == 3)
			outtextxy(400, 40, "星期三");
		if (ti.wDayOfWeek == 4)
			outtextxy(400, 40, "星期四");
		if (ti.wDayOfWeek == 5)
			outtextxy(400, 40, "星期五");
		if (ti.wDayOfWeek == 6)
			outtextxy(400, 40, "星期六");
		// 角度变化
		secondAngle = ti.wSecond * 2 * PI / 60;
		minuteAngle = ti.wMinute * 2 * PI / 60 + secondAngle / 60;
		hourAngle = ti.wHour * 2 * PI / 12 + minuteAngle / 12;
		secondEnd_x = center_x + secondLength * sin(secondAngle);
		secondEnd_y = center_y - secondLength * cos(secondAngle);
		minuteEnd_x = center_x + minuteLength * sin(minuteAngle);
		minuteEnd_y = center_y - minuteLength * cos(minuteAngle);
		hourEnd_x = center_x + hourLength * sin(hourAngle);
		hourEnd_y = center_y - hourLength * cos(hourAngle);
		setlinestyle(PS_SOLID, 2);
		setcolor(YELLOW);
		line(center_x, center_y, secondEnd_x, secondEnd_y);
		setlinestyle(PS_SOLID, 5);
		setcolor(BLUE);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		setlinestyle(PS_SOLID, 10);
		setcolor(RED);
		line(center_x, center_y, hourEnd_x, hourEnd_y);
		FlushBatchDraw();
		Sleep(10);
		setcolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		line(center_x, center_y, secondEnd_x, secondEnd_y);  // 隐藏
		setlinestyle(PS_SOLID, 5);
		line(center_x, center_y, minuteEnd_x, minuteEnd_y);
		setlinestyle(PS_SOLID, 10);
		line(center_x, center_y, hourEnd_x, hourEnd_y);
		if (kbhit())
		{
			if (char ch = getch() == 13)
				break;
		}
	}
	EndBatchDraw();
	return 0;
}
//游戏模块
int game(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "休闲益智");
	IMAGE img1;
	loadimage(&img1, "..\\data\\picture\\img1.jpg");//C:\Users\若木不微凉。\Desktop\节@粮\data\picture
	putimage(0, 0, &img1);
	//游戏菜单
	while (1)
	{
		settextcolor(RGB(0, 0, 0));
		settextstyle(33, 0, "楷体");
		setbkmode(TRANSPARENT);
		outtextxy(initwidth / 20, initheight * 1 / 20, "游戏类别");
		outtextxy(initwidth / 20 + 80, initheight * 1 / 20 + 50, "一.食物连连看");
		outtextxy(initwidth / 20 + 80, initheight * 1 / 20 + 50 * 2, "二.光盘行动");
		outtextxy(initwidth / 20 + 80, initheight * 1 / 20 + 50 * 3, "三.五子棋");
		outtextxy(initwidth / 20 + 80, initheight * 1 / 20 + 50 * 4, "返回菜单");
		while (kbhit())
		{
			static int gamebox = 1;
			for (int i = 1; i <= 4; i++)
			{
				setfillcolor(RGB(255, 255, 255));
				fillcircle(initwidth / 5 - 10, initheight * 1 / 20 + 15 + 50 * i, 10);
			}
			char ch = getch();
			if (ch == 72 && gamebox > 1 || ch == 'w' && gamebox > 1 || ch == 'W' && gamebox > 1)
				gamebox--;
			else if (ch == 80 && gamebox < 4 || ch == 's' && gamebox < 4 || ch == 'S' && gamebox < 4)
				gamebox++;
			else if (ch == 13)//按回车确定
				return gamebox;
			setfillcolor(RGB(0, 0, 0));
			fillcircle(initwidth / 5 - 10, initheight * 1 / 20 + 15 + 50 * gamebox, 10);
		}
	}
}
int game3(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五子棋");
	closemusic();
	mciSendString("open ..\\data\\music\\music4.wma alias music4", 0, 0, 0);
	mciSendString("play music4 repeat", 0, 0, 0);
	IMAGE img9;
	loadimage(&img9, "..\\data\\picture\\img9.jpg");
	putimage(0, 0, &img9);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth /10, initheight * 1 / 5, "开始游戏");//返回1
	outtextxy(initwidth / 10, initheight * 1 / 5+40, "游戏规则");//返回2
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40*2, "返回菜单");//返回3
	//选择模块
	while (1)
	{
		while (kbhit())
		{
			static int game3box = 1;
			for (int i = 1; i <= 3; i++)
			{
				setfillcolor(RGB(255, 255, 255));
				fillcircle(initwidth / 10-20, initheight * 1/ 5 -25 + 40 * game3box, 10);
			}
			char ch = getch();
			if (ch == 72 && game3box > 1 || ch == 'w' && game3box > 1 || ch == 'W' && game3box > 1)
				game3box--;
			else if (ch == 80 && game3box < 3 || ch == 's' && game3box < 3 || ch == 'S' && game3box < 3)
				game3box++;
			else if (ch == ' ' || ch == 13)//按空格或回车键确定
				return game3box;
			setfillcolor(RGB(0, 0, 0));
			fillcircle(initwidth / 10 - 20, initheight * 1 / 5 - 25 + 40 * game3box, 10);
		}
	}
	return 0;
}
void game3f(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五子棋规则说明");
	IMAGE img5;
	loadimage(&img5, "..\\data\\picture\\img5.jpg");
	putimage(0, 0, &img5);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 10, initheight * 1 / 5, "用键盘操控落点位置");
	outtextxy(initwidth / 10, initheight * 1 / 5+40, "按回车键确定");
	outtextxy(initwidth / 10, initheight * 1 / 5+40*2, "率先连成五子者获胜！");
	while (kbhit)
	{
		if (char ch = getch() ==  13)
			break;
	}
}
int playgame3(void)
{
	IMAGE img5;
	initgraph(600, 500);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五子棋");
	loadimage(&img5, "..\\data\\picture\\img5.jpg", 600, 500);
	putimage(0, 0, &img5);
	setlinecolor(WHITE);
	for (int i = 0; i < 20; i++)
	{
		line(0, i * 25, 500, i * 25);   //25 50 75 100
		line(i * 25, 0, i * 25, 500);
	}
	setlinestyle(PS_SOLID, 2);  //画实线 宽度2
	line(500, 0, 500, 500);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "楷体");
	setbkmode(TRANSPARENT);
	outtextxy(512, 60, "1黑棋");
	outtextxy(512, 120, "2白棋");
	int x = 0, y = 0;
	int a = 0, b = 0;
	MOUSEMSG m; 
	hwnd = GetHWnd();
	while (1)
	{
		m = GetMouseMsg();//求距离的绝对值
		for (int i = 1; i < 20; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)
				{
					a = i;
					b = j;
					x = i * 25;
					y = j * 25;
				}
			}
		}
		if (m.uMsg == WM_LBUTTONDOWN)  //检查鼠标左键是否按下
		{
			if (board[a][b] != 0)
			{
				MessageBox(hwnd, "这里已经有棋子了，请重新下棋", "五子棋", MB_OK);
				continue;
			}
			if (flag % 2 == 0)
			{
				setfillcolor(BLACK);
				solidcircle(x, y, 10);
				board[a][b] = 1;
			}
			else
			{
				setfillcolor(WHITE);
				solidcircle(x, y, 10);
				board[a][b] = 2;
			}
			flag++;
		}
		if (judge(a, b))
		{
			if (1 == flag % 2)
			{
				MessageBox(hwnd, "玩家一取得胜利", "游戏结束", MB_OK);
				return 0;
			}
			else
			{
				MessageBox(hwnd, "玩家二取得胜利", "游戏结束", MB_OK);
				return 0;
			}
		}
	}
}
int judge(int a, int b)
	{
		int i, j;
		int t = 2 - flag % 2;
		for (i = a - 4, j = b; i <= a; i++)  //横向
		{
			if (i >= 1 && i < 16 && t == board[i][j] && t == board[i + 1][j] && t == board[i + 2][j] && t == board[i + 3][j] && t == board[i + 4][j])
				return 1;
		}
		for (i = a, j = b - 4; j <= a; j++)   //竖向
		{
			if (j >= 1 && j < 16 && t == board[i][j] && t == board[i][j + 1] && t == board[i][j + 2] && t == board[i][j + 3] && t == board[i][j + 4])
				return 1;
		}
		for (i = a - 4, j = b - 4; i <= a, j <= b; i++, j++)   //斜下
		{
			if (i >= 1 && i < 16 && j >= 1 && j < 16 && t == board[i][j] && t == board[i + 1][j + 1] && t == board[i + 2][j + 2] && t == board[i + 3][j + 3] && t == board[i + 4][j + 4])
				return 1;
		}
		for (i = a - 4, j = b + 4; i <= a, j >= b; i++, j--)   //斜上
		{
			if (i >= 1 && i < 16 && j >= 1 && j < 16 && t == board[i][j] && t == board[i + 1][j - 1] && t == board[i + 2][j - 2] && t == board[i + 3][j - 3] && t == board[i + 4][j - 4])
				return 1;
		}
		return 0;
	}
int game2(void)
{
	closemusic();
	mciSendString("open ..\\data\\music\\music5.wma alias music5", 0, 0, 0);
	mciSendString("play music5 repeat", 0, 0, 0);
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "绝不剩饭！");
	IMAGE img7;
	loadimage(&img7, "..\\data\\picture\\img7.jpg");
	putimage(0, 0, &img7);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 10, initheight * 1 / 5, "开始游戏");//返回1
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40, "游戏规则");//返回2
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 2, "返回菜单");//返回3
	while (1)
	{
		while (kbhit())
		{
			static int game2box = 1;
			for (int i = 1; i <= 3; i++)
			{
				setfillcolor(RGB(255, 255, 255));
				fillcircle(initwidth / 10 - 20, initheight * 1 / 5 - 25 + 40 * game2box, 10);
			}
			char ch = getch();
			if (ch == 72 && game2box > 1 || ch == 'w' && game2box > 1 || ch == 'W' && game2box > 1)
				game2box--;
			else if (ch == 80 && game2box < 3 || ch == 's' && game2box < 3 || ch == 'S' && game2box < 3)
				game2box++;
			else if (ch == ' ' || ch == 13)//按空格或回车键确定
				return game2box;
			setfillcolor(RGB(0, 0, 0));
			fillcircle(initwidth / 10 - 20, initheight * 1 / 5 - 25 + 40 * game2box, 10);
		}
	}
	return 0;
}
void game2f(void)//文本说明
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "光盘行动规则背景");
	IMAGE img5;
	loadimage(&img5, "..\\data\\picture\\img5.jpg");
	putimage(0, 0, &img5);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 10, initheight * 1 / 5, "一大块盘子全部是粮食");
	settextcolor(RGB(50, 50, 50));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40, "但是有些粮食被换成了毒药");
	settextcolor(RGB(100, 100, 100));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 2, "小方格内的数字表示:");
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 3, " 九宫格内毒药的数量");
	settextcolor(RGB(150, 150, 0));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 4, "请你点击方格吃掉无毒的食物");
	settextcolor(RGB(255, 255, 0));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 5, "以身作则光盘精神");
	settextcolor(RGB(0, 0, 255));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 6, "排除所有毒药即获胜");
	while (kbhit)
	{
		if (char ch = getch() == 13)
			break;
	}
}
int playgame2(void)
{
	initgraph(200, 230);
	static int g2o = 0;
	while (1)
	{
		if (FLAG == 1)
		{
			game2begin();//绘制出游戏界面并判断是否玩过和重新开始
			g2o=game2play();//游戏过程的函数
			if (AGAIN == 1)
			{
				AGAIN = 0;
				continue;
			}
		}
		if (g2o == 1)
		{
			g2o = 0;
			return 0;
		}
		FLAG = 0;
		if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键按下事件
		{
			mousegetXY();
			if (MouseX > 90 && MouseX < 110 && MouseY>5 && MouseY < 25)
			{
				FLAG = 1;
				continue;
			}
		}
		if (m.uMsg == WM_LBUTTONDOWN)//鼠标左键按下事件
		{
			mousegetXY();
			if (MouseX > 170 && MouseX < 200 && MouseY>5 && MouseY < 25)
			{
				return 0;
			}
		}
	}
	return 0;
}
int minestatistics(int i, int j)
{
	int nNUM = 0;
	if (i == 0 && j == 0)//左上角格子的统计
	{
		if (Mine[0][1].num == 1)
			nNUM++;
		if (Mine[1][0].num == 1)
			nNUM++;
		if (Mine[1][1].num == 1)
			nNUM++;
	}
	else
		if (i == 0 && j == 9)//右上角格子的统计
		{
			if (Mine[0][8].num == 1)
				nNUM++;
			if (Mine[1][9].num == 1)
				nNUM++;
			if (Mine[1][8].num == 1)
				nNUM++;
		}
		else
			if (i == 9 && j == 0)//左下角格子的统计
			{
				if (Mine[8][0].num == 1)
					nNUM++;
				if (Mine[9][1].num == 1)
					nNUM++;
				if (Mine[8][1].num == 1)
					nNUM++;
			}
			else
				if (i == 9 && j == 9)//右下角格子的统计
				{
					if (Mine[9][8].num == 1)
						nNUM++;
					if (Mine[8][9].num == 1)
						nNUM++;
					if (Mine[8][8].num == 1)
						nNUM++;
				}
				else if (j == 0)//左边第一列格子的统计
				{
					if (Mine[i][j + 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j].num == 1)
						nNUM++;
					if (Mine[i - 1][j].num == 1)
						nNUM++;
					if (Mine[i - 1][j + 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j + 1].num == 1)
						nNUM++;
				}
				else if (j == 9)//右边第一列格子的统计
				{
					if (Mine[i][j - 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j].num == 1)
						nNUM++;
					if (Mine[i - 1][j].num == 1)
						nNUM++;
					if (Mine[i - 1][j - 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j - 1].num == 1)
						nNUM++;
				}
				else if (i == 0)//第一行格子的统计
				{
					if (Mine[i + 1][j].num == 1)
						nNUM++;
					if (Mine[i][j - 1].num == 1)
						nNUM++;
					if (Mine[i][j + 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j - 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j + 1].num == 1)
						nNUM++;
				}
				else if (i == 9)//最后一行格子的统计
				{
					if (Mine[i - 1][j].num == 1)
						nNUM++;
					if (Mine[i][j - 1].num == 1)
						nNUM++;
					if (Mine[i][j + 1].num == 1)
						nNUM++;
					if (Mine[i - 1][j - 1].num == 1)
						nNUM++;
					if (Mine[i - 1][j + 1].num == 1)
						nNUM++;
				}
				else//普通格子的统计
				{
					if (Mine[i - 1][j].num == 1)
						nNUM++;
					if (Mine[i - 1][j + 1].num == 1)
						nNUM++;
					if (Mine[i][j + 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j + 1].num == 1)
						nNUM++;
					if (Mine[i + 1][j].num == 1)
						nNUM++;
					if (Mine[i + 1][j - 1].num == 1)
						nNUM++;
					if (Mine[i][j - 1].num == 1)
						nNUM++;
					if (Mine[i - 1][j - 1].num == 1)
						nNUM++;
				}
	return nNUM;//把格子周围一共有多少雷数的统计结果返回
}
void showwhite(int i, int j)//显示无雷区的空白部分
{
	if (Mine[i][j].flag == 1 || Mine[i][j].num == 0)//如果有红旗或该格处理过就不对该格进行任何判断
		return;
	mineNUM--;//显示过数字或者空格的格子就表示多处理了一个格子,当所有格子都处理过了表示胜利
	if (Mine[i][j].roundnum == 0 && Mine[i][j].num != 1)//显示空格
	{
		drawempty(i, j, 1, WHITE);
		Mine[i][j].num = 0;
	}
	else
		if (Mine[i][j].roundnum != 0)//输出雷数
		{
			drawempty(i, j, 1, WHITE);
			_stprintf_s(randmineNUM, _T("%d"), Mine[i][j].roundnum);
			setcolor(RED);
			outtextxy(6 + j * 20, 32 + i * 20, randmineNUM);
			Mine[i][j].num = 0;//已经输出雷数的格子用0表示已经用过这个格子
			return;
		}

	//8个方向递归显示所有的空白格子
	if (i != 0 && Mine[i - 1][j].num != 1)
		showwhite(i - 1, j);
	if (i != 0 && j != 9 && Mine[i - 1][j + 1].num != 1)
		showwhite(i - 1, j + 1);
	if (j != 9 && Mine[i][j + 1].num != 1)
		showwhite(i, j + 1);
	if (j != 9 && i != 9 && Mine[i + 1][j + 1].num != 1)
		showwhite(i + 1, j + 1);
	if (i != 9 && Mine[i + 1][j].num != 1)
		showwhite(i + 1, j);
	if (i != 9 && j != 0 && Mine[i + 1][j - 1].num != 1)
		showwhite(i + 1, j - 1);
	if (j != 0 && Mine[i][j - 1].num != 1)
		showwhite(i, j - 1);
	if (i != 0 && j != 0 && Mine[i - 1][j - 1].num != 1)
		showwhite(i - 1, j - 1);
}
void drawsmile(void)
{
	setfillstyle(BS_SOLID);
	setfillcolor(YELLOW);
	fillellipse(90, 5, 110, 25);//绘制椭圆（笑脸）函数，参数为椭圆外切矩形的左上右下角坐标
	setfillstyle(BS_SOLID);
	setfillcolor(BLACK);//画眼睛
	fillellipse(93, 13, 97, 17);
	fillellipse(103, 13, 107, 17);
	bar(97, 20, 103, 21);//画嘴巴
}
void drawredflag(int i, int j)
{
	setfillstyle(BS_SOLID);
	setfillcolor(RED);
	bar(8 + j * 20, 35 + i * 20, 8 + j * 20 + 5, 35 + i * 20 + 5);
	setcolor(BLACK);
	line(8 + j * 20, 35 + i * 20, 8 + j * 20, 35 + i * 20 + 10);
}
void drawempty(int i, int j, int mode, int color) //画出16*16的小格
{
	setfillstyle(BS_SOLID);
	setfillcolor(color);
	if (mode == 0)
	{
		bar(10 + j * 20 - 8, 40 + i * 20 - 8, 10 + j * 20 + 8, 40 + i * 20 + 8);
	}
	else if (mode == 1)
	{
		bar(10 + j * 20 - 7, 40 + i * 20 - 7, 10 + j * 20 + 7, 40 + i * 20 + 7);
	}
}
void mousegetXY(void)//获得鼠标的位置
{
	m = GetMouseMsg();
	MouseX = m.x;
	MouseY = m.y;
}
void game2begin(void)
{
	int i, j;
	cleardevice();
	PLAY = 1;
	mineNUM = 0;
	setfillstyle(BS_SOLID);//此处用法和TC不同
	setfillcolor(WHITE);
	bar(0, 0, 200, 230); //设置背景区域
	for (i = 0; i < 10; i++) //绘制每个雷区（小格）
	{
		for (j = 0; j < 10; j++)
		{
			drawempty(i, j, 0, LIGHTGRAY);
		}
	}
	drawsmile();//画出中间的笑脸
	settextcolor(RGB(0, 0, 0));
	settextstyle(10, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(170, 10, "返回");
	srand((unsigned)time(NULL));//根据时间给随机数不同的种子数
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{

			Mine[i][j].num = rand() % 8;//随机数产生范围0-7

			if (Mine[i][j].num == 1)
			{
				mineNUM++;
			}
			else
			{
				Mine[i][j].num = 2;
			}
			printf("%3d", Mine[i][j].num);
			Mine[i][j].flag = 0;
		}
		

	}  
	_stprintf_s(randmineNUM, "%d", mineNUM);//将minrNUM转换成字符串类型
	setbkcolor(WHITE);
	setcolor(RED);
	settextstyle(20, 0, "楷体");
	outtextxy(5, 10, randmineNUM);
	mineNUM = 100 - mineNUM;
}
int game2play(void)//游戏过程
{
	int i, j, Num = 0;//Num用来接收统计函数返回一个格子周围有多少地雷
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
			Mine[i][j].roundnum = minestatistics(i, j);//统计每个格子周围有多少地雷
	while (!kbhit())
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			mousegetXY();
			if (MouseX > 90 && MouseX < 110 && MouseY>5 && MouseY < 25)//重新来
			{
				MessageBox(NULL, TEXT("重新开始成功"), TEXT("YES"), MB_OK);
				AGAIN = 1;
				return 0;
			}
			if (MouseX > 170 && MouseX < 200 && MouseY>5 && MouseY < 25)//返回
			{
				MessageBox(NULL, TEXT("返回菜单！"), TEXT("YES"), MB_OK);
				return 1;
			}
			if (MouseX > 0 && MouseX < 200 && MouseY>30 && MouseY < 230)//当前鼠标位置在格子范围内
			{
				j = (MouseX) / 20;
				i = (MouseY - 30) / 20;
				if (Mine[i][j].flag == 1)//如果格子有红旗则左键无效
					continue;
				if (Mine[i][j].num != 0)//如果格子没有处理过
				{
					if (Mine[i][j].num == 1)//鼠标按下的格子是地雷
					{
						game2over();//游戏失败
						break;
					}
					else//鼠标按下的格子不是地雷
					{
						Num = minestatistics(i, j);
						if (Num == 0)//周围没地雷就用递归算法来显示空白格子
							showwhite(i, j);
						else//按下格子周围有地雷
						{
							_stprintf_s(randmineNUM, _T("%d"), Num);//输出当前格子周围的雷数
							drawempty(i, j, 1, WHITE);
							setcolor(RED);
							outtextxy(6 + j * 20, 32 + i * 20, randmineNUM);
							mineNUM--;
						}
						Mine[i][j].num = 0;//点过的格子周围雷数的数字变为0表示这个格子已经用过
						if (mineNUM < 1)//胜利
						{
							game2win();
							break;
						}
					}
				}
			}
		}
		case WM_RBUTTONDOWN:
		{
			mousegetXY();
			if (MouseX > 0 && MouseX < 200 && MouseY>30 && MouseY < 230)//当前鼠标位置在格子范围内
			{
				j = (MouseX) / 20;
				i = (MouseY - 30) / 20;
				if (Mine[i][j].flag == 0 && Mine[i][j].num != 0)//本来没红旗现在显示红旗
				{
					drawredflag(i, j);
					Mine[i][j].flag = 1;
				}
				else
					if (Mine[i][j].flag == 1)//有红旗标志再按右键就红旗消失
					{
						drawempty(i, j, 0, LIGHTGRAY);
						Mine[i][j].flag = 0;
					}
			}
		}
		}
	}
}
void game2over(void)
{
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (Mine[i][j].num == 1)//显示所有地雷
			{
				drawempty(i, j, 0, WHITE);
				setfillstyle(BS_SOLID);
				setfillcolor(RED);
				fillellipse(3 + j * 20, 33 + i * 20, 17 + j * 20, 47 + i * 20);
				setbkcolor(WHITE);
				setcolor(RED);
				settextstyle(16, 0, _T("宋体"));
				outtextxy(2, 2, _T("你输了"));
			}
		}
	}
}
void game2win(void)
{
	setbkcolor(WHITE);
	setcolor(RED);
	settextstyle(16, 0, _T("宋体"));
	outtextxy(2, 2, _T("你赢了"));
}
int game1(void)
{
	closemusic();
	mciSendString("open ..\\data\\music\\music3.wma alias music3", 0, 0, 0);
	mciSendString("play music3 repeat", 0, 0, 0);
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "五子棋");
	IMAGE img5;
	loadimage(&img5, "..\\data\\picture\\img5.jpg");
	putimage(0, 0, &img5);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 10, initheight * 1 / 5, "开始游戏");//返回1
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40, "游戏规则");//返回2
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 2, "返回菜单");//返回3
	while (1)
	{
		while (kbhit())
		{
			static int game1box = 1;
			for (int i = 1; i <= 3; i++)
			{
				setfillcolor(RGB(255, 255, 255));
				fillcircle(initwidth / 10 - 20, initheight * 1 / 5 - 25 + 40 * game1box, 10);
			}
			char ch = getch();
			if (ch == 72 && game1box > 1 || ch == 'w' && game1box > 1 || ch == 'W' && game1box > 1)
				game1box--;
			else if (ch == 80 && game1box < 3 || ch == 's' && game1box < 3 || ch == 'S' && game1box < 3)
				game1box++;
			else if (ch == ' ' || ch == 13)//按空格或回车键确定
				return game1box;
			setfillcolor(RGB(0, 0, 0));
			fillcircle(initwidth / 10 - 20, initheight * 1 / 5 - 25 + 40 * game1box, 10);
		}
	}
	return 0;
}
int playgame1(void)
{
	closemusic();
	mciSendString("open ..\\data\\music\\music3.wma alias music3", 0, 0, 0);
	mciSendString("play music3 repeat", 0, 0, 0);
	return 0;
}
void game1f(void)
{
	initgraph(initwidth, initheight);
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "食物连连看规则");
	IMAGE img5;
	loadimage(&img5, "..\\data\\picture\\img5.jpg");
	putimage(0, 0, &img5);
	settextcolor(RGB(0, 0, 0));
	settextstyle(33, 0, "宋体");
	setbkmode(TRANSPARENT);
	outtextxy(initwidth / 10, initheight * 1 / 5, "为了光盘行动");
	settextcolor(RGB(50, 50, 50));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40, "需要把所有的食物吃完");
	settextcolor(RGB(100, 100, 100));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 2, "但是每次必须吃掉");
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 3, " 两个相同的食物！！");
	settextcolor(RGB(150, 150, 0));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 4, "请你点击食物吃掉它们");
	settextcolor(RGB(255, 255, 0));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 5, "若成功吃掉所有食物");
	settextcolor(RGB(0, 0, 255));
	outtextxy(initwidth / 10, initheight * 1 / 5 + 40 * 6, "则获胜");
	while (kbhit)
	{
		if (char ch = getch() == 13)
			break;
	}
}
void gotoxy(int x, int y)
{
	COORD Pos;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(hCon, Pos);
}
//动画函数
void eye()
{
	int flag = 1;
	MOUSEMSG m;
	FlushMouseMsgBuffer();
	void one();
	int check_button(int x, int y);
	initgraph(800, 600);
	system("color f5");
	setbkcolor(15);

	setbkcolor(RGB(173, 189, 202));
	cleardevice();

	setfillcolor(RGB(173, 189, 202));
	solidroundrect(250, 160, 550, 410, 150, 150);

	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	solidroundrect(226, 214, 362, 316, 50, 50);
	solidroundrect(462, 214, 600, 316, 50, 50);

	setfillcolor(RGB(0, 0, 0));
	fillcircle(269, 267, 25);
	fillcircle(505, 267, 25);

	setlinecolor(RGB(125, 0, 0));
	setfillcolor(RGB(125, 0, 0));
	solidroundrect(350, 367, 481, 481, 80, 80);

	settextcolor(WHITE);
	setbkcolor(RGB(125, 0, 0));
	settextstyle(32, 16, _T("宋体"));
	outtextxy(390, 410, "进入");

	while (flag)
	{

		Sleep(600);

		setlinecolor(WHITE);
		setfillcolor(RGB(255, 255, 255));
		fillcircle(269, 267, 25);
		fillcircle(505, 267, 25);
		setfillcolor(RGB(0, 0, 0));
		fillcircle(319, 267, 25);
		fillcircle(555, 267, 25);

		Sleep(600);

		setlinecolor(WHITE);
		setfillcolor(RGB(255, 255, 255));
		fillcircle(319, 267, 25);
		fillcircle(555, 267, 25);
		setfillcolor(RGB(0, 0, 0));
		fillcircle(269, 267, 25);
		fillcircle(505, 267, 25);

		while (MouseHit())
		{
			m = GetMouseMsg();	// 获取鼠标消息
			if (checkbutton(m.x, m.y))
			{
				switch (m.uMsg)		// 根据不同的鼠标消息，执行不同的代码
				{
				case WM_LBUTTONDOWN:
					one();
					flag = 0;
					break;
				default:
					break;
				}
			}
		}
	}
}
void one()
{
	cleardevice();
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(RGB(239, 90, 89));
	fillcircle(400, 200, 50);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(400, 200, 15);
	setfillcolor(RGB(0, 0, 0));
	fillcircle(400, 200, 5);

	setfillcolor(RGB(173, 188, 201));
	fillrectangle(250, 250, 550, 300);

	setfillcolor(RGB(80, 92, 133));
	setlinecolor(RGB(80, 92, 133));
	arc(300, 300, 500, 500, 0, 3.14159);
	line(300, 399, 500, 399);
	floodfill(350, 350, RGB(80, 92, 133));

	setfillcolor(RGB(243, 169, 183));
	POINT pts1[] = { {400, 400},{346,400},{314, 470}, {358, 489},{400, 400} };
	solidpolygon(pts1, 4);
	POINT pts2[] = { {400, 400},{457,400},{488, 470}, {443, 490},{400, 400} };
	solidpolygon(pts2, 4);

	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillcircle(400, 275, 4);  //little-cicrle-up


	Sleep(200);

	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillrectangle(250, 250, 550, 300);
	setfillcolor(RGB(173, 188, 201));
	POINT pts3[] = { {250,265},{546,234},{550, 283},{253, 314},{250,265} };  //left-arm
	solidpolygon(pts3, 4);

	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillcircle(400, 275, 4);  //little-cicrle-up

	Sleep(300);

	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillcircle(400, 350, 4);  //little-cicrle-bottom

	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	solidpolygon(pts3, 4);
	setfillcolor(RGB(173, 188, 201));
	fillrectangle(250, 250, 550, 300);


	Sleep(200);

	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillrectangle(250, 250, 550, 300);
	setfillcolor(RGB(173, 188, 201));
	POINT pts4[] = { {255,230},{550,271},{544, 319},{248, 279},{255,230} };  //right-arm
	solidpolygon(pts4, 4);

	Sleep(200);

	//小人往下蹲
	cleardevice();

	//头部三个circle
	setfillcolor(RGB(239, 90, 89));
	fillcircle(390, 210, 50);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(390, 210, 15);
	setfillcolor(RGB(0, 0, 0));
	fillcircle(390, 210, 5);

	//手臂
	setfillcolor(RGB(173, 188, 201));
	POINT right_arm_2[] = { {245,240},{540,281},{534, 329},{238, 289},{245,240} };  //right-arm
	solidpolygon(right_arm_2, 4);

	//两条腿
	setfillcolor(RGB(243, 169, 183));
	//POINT pts1[] = { {400, 400},{346,400},{314, 470}, {358, 489},{400, 400}};
	solidpolygon(pts1, 4);
	//POINT pts2[] = { {400, 400},{457,400},{488, 470}, {443, 490},{400, 400}};
	solidpolygon(pts2, 4);

	//半圆身子
	setfillcolor(RGB(80, 92, 133));
	setlinecolor(RGB(80, 92, 133));
	arc(290, 310, 490, 510, 0, 3.14159);
	line(290, 409, 490, 409);
	floodfill(340, 360, RGB(80, 92, 133));

	//衣服扣子
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillcircle(390, 360, 4);  //little-cicrle-bottom

	Sleep(200);

	//小人往下蹲2
	cleardevice();

	//头部三个circle
	setfillcolor(RGB(239, 90, 89));
	fillcircle(380, 220, 50);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(380, 220, 15);
	setfillcolor(RGB(0, 0, 0));
	fillcircle(380, 220, 5);

	//手臂
	setfillcolor(RGB(173, 188, 201));
	POINT right_arm_3[] = { {235,250},{530,291},{524, 339},{228, 299},{235,250} };  //right-arm
	solidpolygon(right_arm_3, 4);

	//两条腿
	setfillcolor(RGB(243, 169, 183));
	//POINT pts1[] = { {400, 400},{346,400},{314, 470}, {358, 489},{400, 400}};
	solidpolygon(pts1, 4);
	//POINT pts2[] = { {400, 400},{457,400},{488, 470}, {443, 490},{400, 400}};
	POINT pts_right_leg[] = { {400, 419},{461,416},{495, 460}, {460, 490},{400, 419} };
	solidpolygon(pts_right_leg, 4);

	//半圆身子
	setfillcolor(RGB(80, 92, 133));
	setlinecolor(RGB(80, 92, 133));
	arc(280, 320, 480, 520, 0, 3.14159);
	line(280, 419, 480, 419);
	floodfill(330, 350, RGB(80, 92, 133));

	//衣服扣子
	setfillcolor(RGB(255, 255, 255));
	setlinecolor(RGB(255, 255, 255));
	fillcircle(380, 370, 4);  //little-cicrle-bottom

	Sleep(300);
}
int checkbutton(int x, int y)
{
	if (x > 350 && x < 481 && y>367 && y < 481)
		return 1;
	else
		return 0;
}
void two()
{
	setbkcolor(RGB(248, 106, 89));
	cleardevice();

	/*little one circle*/
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 283, 15);

	Sleep(300);

	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 179, 339, 262);

	Sleep(300);
	cleardevice();
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 293, 15);
	fillcircle(424, 283, 15);
	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 179, 339, 262);

	Sleep(300);
	cleardevice();
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 303, 15);
	fillcircle(424, 293, 15);
	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 179, 339, 272);

	POINT pts1[] = { {400, 179},{432,173},{450, 264}, {415, 272},{400, 179} };
	solidpolygon(pts1, 4);

	Sleep(300);
	cleardevice();
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 323, 15);
	fillcircle(424, 300, 15);
	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 189, 339, 282);

	POINT pts2[] = { {400, 189},{432,183},{450, 274}, {415, 282},{400, 189} };
	solidpolygon(pts2, 4);

	Sleep(200);

	cleardevice();
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 343, 15);
	fillcircle(424, 320, 15);
	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 209, 339, 322);

	POINT pts3[] = { {400, 209},{432,203},{450, 294}, {415, 302},{400, 209} };
	solidpolygon(pts3, 4);

	setfillcolor(RGB(90, 59, 70));
	setlinecolor(RGB(90, 59, 70));
	arc(296, 87, 479, 278, -0.19, 2.949);
	line(299, 163, 479, 200);
	floodfill(386, 127, RGB(90, 59, 70));

	Sleep(200);

	cleardevice();
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 363, 15);
	fillcircle(418, 360, 15);
	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 229, 339, 342);
	fillrectangle(400, 229, 435, 342);


	setfillcolor(RGB(90, 59, 70));
	setlinecolor(RGB(90, 59, 70));
	arc(281, 97, 464, 288, 0, 3.1415);
	line(281, 191, 466, 191);
	floodfill(395, 150, RGB(90, 59, 70));

	Sleep(200);

	setfillcolor(RGB(253, 177, 169));
	setlinecolor(RGB(253, 177, 169));
	POINT pts4[] = { {325,0},{375,50},{425,0},{325,0} };
	solidpolygon(pts4, 3);

	Sleep(100);

	setlinecolor(RGB(248, 106, 89));
	setfillcolor(RGB(248, 106, 89));
	fillcircle(321, 363, 15);
	fillcircle(418, 360, 15);

	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 493, 15);
	fillcircle(418, 493, 15);

	Sleep(100);
	setlinecolor(RGB(248, 106, 89));
	setfillcolor(RGB(248, 106, 89));
	fillrectangle(304, 229, 339, 342);
	fillrectangle(400, 229, 435, 342);

	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 339, 339, 452);
	fillrectangle(400, 339, 435, 452);

	Sleep(100);

	setfillcolor(RGB(248, 106, 89));
	setlinecolor(RGB(248, 106, 89));
	floodfill(395, 150, RGB(248, 106, 89));

	setlinecolor(RGB(109, 147, 163));
	setfillcolor(RGB(109, 147, 163));
	fillrectangle(169, 271, 350, 295);
	fillrectangle(402, 271, 582, 294);

	setfillcolor(RGB(90, 59, 70));
	setlinecolor(RGB(90, 59, 70));
	arc(281, 245, 464, 436, 0, 3.1415);
	line(281, 339, 466, 339);
	floodfill(395, 290, RGB(90, 59, 70));

	Sleep(100);
	setfillcolor(RGB(248, 106, 89));
	setlinecolor(RGB(248, 106, 89));
	solidpolygon(pts4, 3);

	setfillcolor(RGB(253, 177, 169));
	setlinecolor(RGB(253, 177, 169));
	POINT pts5[] = { {378,50},{432,107},{377,161},{323,107},{378,50} };
	solidpolygon(pts5, 4);

	Sleep(100);
	setfillcolor(RGB(248, 106, 89));
	setlinecolor(RGB(248, 106, 89));
	solidpolygon(pts5, 4);

	setfillcolor(RGB(253, 177, 169));
	setlinecolor(RGB(253, 177, 169));
	POINT pts6[] = { {378,134},{432,191},{378,245},{323,191},{378,134} };
	solidpolygon(pts6, 4);

	Sleep(100);

	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(378, 190, 30);

	Sleep(100);

	setlinecolor(BLACK);
	setfillcolor(RGB(0, 0, 0));
	fillcircle(378, 190, 10);

	Sleep(100);
	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(141, 284, 13);
	fillcircle(616, 284, 13);

	setlinecolor(RGB(125, 123, 123));
	setfillcolor(RGB(125, 123, 123));
	fillroundrect(125, 500, 308, 508, 5, 5);
}
void three()
{

	setbkcolor(RGB(248, 106, 89));
	cleardevice();

	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(141, 284, 13);
	fillcircle(557, 175, 13);

	settextcolor(WHITE);
	setbkcolor(RGB(248, 106, 89));
	settextstyle(32, 16, _T("宋体"));
	outtextxy(575, 139, "Hi~");

	setfillcolor(RGB(253, 177, 169));
	setlinecolor(RGB(253, 177, 169));
	POINT pts6[] = { {378,134},{432,191},{378,245},{323,191},{378,134} };
	solidpolygon(pts6, 4);

	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(378, 190, 30);

	setlinecolor(BLACK);
	setfillcolor(RGB(0, 0, 0));
	fillcircle(378, 190, 10);

	setlinecolor(RGB(125, 123, 123));
	setfillcolor(RGB(125, 123, 123));
	fillroundrect(125, 500, 308, 508, 5, 5);

	setlinecolor(RGB(109, 147, 163));
	setfillcolor(RGB(109, 147, 163));

	POINT pts7[] = { {416,281},{531,179},{550,200},{433,300},{416,281} };
	solidpolygon(pts7, 4);

	fillrectangle(169, 271, 350, 295);

	setfillcolor(RGB(90, 59, 70));
	setlinecolor(RGB(90, 59, 70));
	arc(281, 245, 464, 436, 0, 3.1415);
	line(281, 339, 466, 339);
	floodfill(395, 290, RGB(90, 59, 70));

	setlinecolor(WHITE);
	setfillcolor(RGB(255, 255, 255));
	fillcircle(321, 493, 15);
	fillcircle(418, 493, 15);

	setlinecolor(RGB(246, 178, 175));
	setfillcolor(RGB(246, 178, 175));
	fillrectangle(304, 339, 339, 452);
	fillrectangle(400, 339, 435, 452);
}