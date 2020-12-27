#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define WIN_WIDTH  640//窗口宽度
#define WIN_HEIGHT 480//窗口高度
#define MAX_SNAKE 100//蛇的最大节数
enum OPTION{     //枚举蛇的方向
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ESC,
};
struct Snake  //蛇的结构体
{
	int num;//蛇的节数
	int dir;//蛇的方向
	int score;//分数
	int size;//蛇的大小
	POINT coor[MAX_SNAKE];
}snake;
struct Food
{
	POINT food0;
	int flag;
	DWORD color;
}food;

void menu();
void GameInit();
void Draw();
void SnakeMove();
void Control();
void EatFood();
void Judge();
void GameOver();
void PtScore();
char text[80];

void menu(){
	setcolor(RGB(41, 57, 85));
	sprintf(text, "☆贪吃蛇☆");
	outtextxy(430, 100, text);
	sprintf(text, "【开始游戏】");
	outtextxy(430, 120, text);
	sprintf(text, "【控制说明】通过方向键控制");
	outtextxy(430, 140, text);
	sprintf(text, "【退出游戏】ESC键 ");
	outtextxy(430, 160, text);
}
void GameInit(){
	srand(GetTickCount());

	//初始化蛇体
	snake.num = 3;
	snake.dir = RIGHT;
	snake.score = 0;
	snake.size = 10;
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[1].x = snake.size;
	snake.coor[1].y = 0;
	snake.coor[0].x = 2 * snake.size;
	snake.coor[0].y = 0;

	//初始化食物
	food.food0.x = rand() % (WIN_WIDTH/10)*10;
	food.food0.y = rand() % (WIN_HEIGHT/10)*10;
	food.flag = 1; 
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);

	//游戏音乐
	PlaySound("G:\\VisualStudio2013\\VisualStudioProjects\\贪吃蛇\\贪吃蛇\\Avril_Lavigne_-_Innocence_Live_.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void Draw(){
	//背景色
	setbkcolor(RGB(214, 219, 233));
	cleardevice();
	//画蛇
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(YELLOW);
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
	}
	//画食物
	if (food.flag==1)
	{
		setfillcolor(food.color);
		fillellipse(food.food0.x, food.food0.y, food.food0.x + 10, food.food0.y + 10);
	}
	//分数
	char temp[20] = "";
	setcolor(BLACK);
	sprintf(temp, "score:%d", snake.score);
	setbkmode(TRANSPARENT);
	outtextxy(20, 20, temp);
	//菜单
	menu();
}
void SnakeMove(){
	//每一节为上一节坐标
	for (int i = snake.num-1; i >0; i--)
	{
		snake.coor[i].x = snake.coor[i - 1].x;
		snake.coor[i].y = snake.coor[i - 1].y;
	}

	switch (snake.dir)
	{
	case UP:
			snake.coor[0].y -= 10;
			break;
	case DOWN:
			snake.coor[0].y += 10;
			break;
	case LEFT:
			snake.coor[0].x -= 10;
			break;
	case RIGHT:
			snake.coor[0].x += 10;
			break;
	case ESC:
		    GameOver();
		    return;
	default:
		break;
	}
}
void Control(){
      //使用win32API获取键盘信息
	if (GetAsyncKeyState(VK_UP)&&snake.dir!= DOWN)
	{
		snake.dir = UP;
	}
	if (GetAsyncKeyState(VK_DOWN) && snake.dir != UP)
	{
		snake.dir = DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT) && snake.dir != RIGHT)
	{
		snake.dir = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) && snake.dir != LEFT)
	{
		snake.dir = RIGHT;
	}
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		snake.dir = ESC;
	}
}
void EatFood(){
	if (snake.coor[0].x == food.food0.x && snake.coor[0].y == food.food0.y && food.flag == 1)
	{
		snake.num++;
		snake.score += 10;
		food.flag = 0;
		PtScore();
	}
	if (food.flag==0)
	{
		food.food0.x = rand() % (WIN_WIDTH / 10) * 10;
		food.food0.y = rand() % (WIN_HEIGHT / 10) * 10;
		food.flag = 1;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	}
}
//游戏结束判断
void Judge(){
	//判断蛇身是否撞到自己
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			GameOver();
		}
	}
	//判断蛇是否撞墙
	if (snake.coor[0].y< 0 || snake.coor[0].y> WIN_HEIGHT || snake.coor[0].x  < 0 || snake.coor[0].x  > WIN_WIDTH)
	{   
		printf("Game Over！");
		GameOver();
	}
}
void GameOver(){
	cleardevice();
    PtScore();
	char a[20] = "";
	settextcolor(RED);
	sprintf(text, "Game Over!");
	//outtextxy(200, 200, text);
	//settextstyle(100, 0, "宋体");
	outtextxy(200, 200, "GAME OVER!");
	Sleep(3000);
	exit(0);
}
void PtScore(){
	//分数
	char str[20] = "";
	//setfillstyle(SOLID_FILL, BLACK);
	settextcolor(RED);
	sprintf(str, "Your score is:%d", snake.score);
	//setbkmode(TRANSPARENT);
	outtextxy(20, 20, str);
}
int main(){
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	BeginBatchDraw();
	while (1)
	{
		if (t2-t1>100)
		{
			SnakeMove();
			t1 = t2;
		}
		t2 = GetTickCount();
        Draw();
		Control();
		EatFood();
		FlushBatchDraw();
		Judge();
	}
	getchar();
	closegraph();
	return 0;
}
