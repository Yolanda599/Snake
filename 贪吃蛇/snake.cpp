#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define WIN_WIDTH  640//���ڿ��
#define WIN_HEIGHT 480//���ڸ߶�
#define MAX_SNAKE 100//�ߵ�������
enum OPTION{     //ö���ߵķ���
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ESC,
};
struct Snake  //�ߵĽṹ��
{
	int num;//�ߵĽ���
	int dir;//�ߵķ���
	int score;//����
	int size;//�ߵĴ�С
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
	sprintf(text, "��̰���ߡ�");
	outtextxy(430, 100, text);
	sprintf(text, "����ʼ��Ϸ��");
	outtextxy(430, 120, text);
	sprintf(text, "������˵����ͨ�����������");
	outtextxy(430, 140, text);
	sprintf(text, "���˳���Ϸ��ESC�� ");
	outtextxy(430, 160, text);
}
void GameInit(){
	srand(GetTickCount());

	//��ʼ������
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

	//��ʼ��ʳ��
	food.food0.x = rand() % (WIN_WIDTH/10)*10;
	food.food0.y = rand() % (WIN_HEIGHT/10)*10;
	food.flag = 1; 
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);

	//��Ϸ����
	PlaySound("G:\\VisualStudio2013\\VisualStudioProjects\\̰����\\̰����\\Avril_Lavigne_-_Innocence_Live_.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
void Draw(){
	//����ɫ
	setbkcolor(RGB(214, 219, 233));
	cleardevice();
	//����
	for (int i = 0; i < snake.num; i++)
	{
		setlinecolor(WHITE);
		setfillcolor(YELLOW);
		fillrectangle(snake.coor[i].x, snake.coor[i].y, snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
	}
	//��ʳ��
	if (food.flag==1)
	{
		setfillcolor(food.color);
		fillellipse(food.food0.x, food.food0.y, food.food0.x + 10, food.food0.y + 10);
	}
	//����
	char temp[20] = "";
	setcolor(BLACK);
	sprintf(temp, "score:%d", snake.score);
	setbkmode(TRANSPARENT);
	outtextxy(20, 20, temp);
	//�˵�
	menu();
}
void SnakeMove(){
	//ÿһ��Ϊ��һ������
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
      //ʹ��win32API��ȡ������Ϣ
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
//��Ϸ�����ж�
void Judge(){
	//�ж������Ƿ�ײ���Լ�
	for (int i = 4; i < snake.num; i++)
	{
		if (snake.coor[0].x == snake.coor[i].x && snake.coor[0].y == snake.coor[i].y)
		{
			GameOver();
		}
	}
	//�ж����Ƿ�ײǽ
	if (snake.coor[0].y< 0 || snake.coor[0].y> WIN_HEIGHT || snake.coor[0].x  < 0 || snake.coor[0].x  > WIN_WIDTH)
	{   
		printf("Game Over��");
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
	//settextstyle(100, 0, "����");
	outtextxy(200, 200, "GAME OVER!");
	Sleep(3000);
	exit(0);
}
void PtScore(){
	//����
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
