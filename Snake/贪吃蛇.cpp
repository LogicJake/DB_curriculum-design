#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <malloc.h>
int addscore = 10;						//每次得分 
int speed = 100;
int speedMax[5] = {100,130,160,190,220}; 	//每一等级速度的速度 
int scoreMax[5] = {100,200,300,450,600}; //每一等级最低分数 
int colour[6] = {1,2,3,4,5,6};				//每一等级蛇的颜色
int scoreWin = 1400;							//胜利条件 
int level = 0;					//等级 
int score = 0;					//分数 
int food[2] = {20,15};			//食物初始位置 
struct snakenode{				 
	int x;						//横坐标
	int y;						//纵坐标
	int life;					//是否存活 
	struct snakenode *next;		 
}snakenode;
typedef struct snakenode *snakehead; 
void gotoxy(int x, int y)		//自己实现的gotoxy 
{	
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);		//获得输出句柄 
	SetConsoleCursorPosition(hOut, pos);
} 
void Drawpoint(int x,int y)	//画蛇的结点 
{
	gotoxy(x,y);
	printf("○");			
 } 
void Drawline(int x1,int y1,int x2,int y2)	//画墙 
{
	do{
	gotoxy(x1,y1); 
	printf("█"); 
	if(x1 < x2)
		x1 += 2;
	if(y1 < y2)
		y1++;
	}while(x1 != x2 || y1 != y2);
}
void Drawfood(int x,int y)	//显示食物 
{
	gotoxy(x,y);
	printf("●");
}
void Setcolor(const unsigned short color)
{     
    if(color > 0 && color <= 6)
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    else
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void Drawsnake(snakehead p) 
{
	Setcolor(colour[level]);
	gotoxy(p->x,p->y);
	printf("●");		//画蛇头 
	p = p->next;				
	while(p != NULL){
		Drawpoint(p->x,p->y);
		p = p->next;
	}
}
void DrawMap(snakehead p)					//生成地图 
{
	system("cls");
	Drawline(0,0,60,0);			//上边线 
	Drawline(0,1,0,30);			//左边线
	Drawline(0,29,60,29);		//下边线
	Drawline(60,0,60,30);		//右边线
	Drawfood(food[0],food[1]);	//生成食物 
	Drawsnake(p);
	Setcolor(7);
	Drawline(62,0,90,0);
	Drawline(90,0,90,30);
	gotoxy(73,1);
	printf("按键"); 
	gotoxy(64,2);
	printf("W:上 S:下");
	gotoxy(64,3);
	printf("A:左 D:右");
	gotoxy(64,4);
	printf("E:暂停  Esc:结束游戏退出");
	Drawline(62,6,90,6);
	gotoxy(73,7);
	printf("Status");
	gotoxy(73,8);
	printf("游戏中");
	Drawline(62,10,90,10);
	gotoxy(73,11);												
	printf("score:%d",score);
	gotoxy(73,12);
	printf("Level:%d",level);
	Drawline(62,14,90,14);
	gotoxy(64,16);
	printf("Level\t\tscore");
	for(int i = 0; i < 5; i++)
	{
		gotoxy(64,17+i);
		printf("%d\t\t%d",i+1,scoreMax[i]); 
	} 
	gotoxy(64,22);
	printf("...\t\t...");
	Drawline(62,29,90,29); 
} 
/*
	a:1 向左 
	d:2 向右 
	w:3 向上 
	s:4 向下 
	e:5 暂停 
*/
int keydown(int z)				
{
	char ch;
	if(kbhit())
	{
		ch=getch();
		switch(ch){
			case 'A':
			case 'a':if(z != 2) z = 1;break;
			case 'D':
			case 'd':if(z != 1) z = 2;break;
			case 'W':
			case 'w':if(z != 4) z = 3;break;
			case 'S':
			case 's':if(z != 3) z = 4;break;
			case 'E':
			case 'e':z=5;break;
			default :break;
		}
		if(ch == 27)				//ESC¼ü
			z = 27;			
		}
	return z;
}
void mkfood(snakehead p)
{
	snakehead q = p;
	food[0] = (rand()%28)*2+2;
	food[1] = (rand()%28)+1; 
	while(q != NULL)	
	{
		if(food[0] == q->x && food[1] == q->y)
			mkfood(p);
		q = q->next;
	} 
}
snakehead Renewsnake(snakehead p, int z)			//更新蛇 
{
	snakehead q,r;
	int x = p->x;
	int y = p->y;
	switch(z)
	{
		case 1:x -= 2;break;
		case 2:x += 2;break;
		case 3:y--;break;
		case 4:y++;break;
	}
	//生成新的蛇头 
	q = (snakehead)malloc(sizeof(snakenode));
	q->x = x;
	q->y = y;
	q->life = 1;
	q->next = p;
	r = p;
	while(r != NULL)
	{
		if(q->x == r->x && q->y == r->y)		//判断是否吃到自己 
			q->life = 0;
		r = r->next;
	}
	if(q->x > 58 || q->x < 1 || q->y > 28 || q->y < 1)	//是否撞墙 
		q->life = 0;
	if(q->x == food[0] && q->y == food[1])				//是否吃到食物 
	{
		score = score+addscore;
		if(level >= 4 && speed < 296)
			speed = speed+2;
		if(level < 5 && score >= scoreMax[level])		//升级
		{
			level++;
			if(level != 5){
				speed = speedMax[level];
			}
		}
		mkfood(q);
	}
	else		//没吃到食物删除最后一个结点 
	{
		while(p->next->next != NULL)
			p = p->next;
		r = p->next;
		p->next = NULL;
		free(r);
	}	
	return q;	
}
snakehead Initsnake()
{
	snakehead snake = (snakehead)malloc(sizeof(snakenode));
	snake->x = 10;
	snake->y = 10;
	snake->life = 1;
	snake->next = (snakehead)malloc(sizeof(snakenode));
	snake->next->x = 10;
	snake->next->y = 9;
	snake->next->next = (snakehead)malloc(sizeof(snakenode));
	snake->next->next->x = 10;
	snake->next->next->y = 8;
	snake->next->next->next = NULL;
	return snake;
}
int main()
{
	int i = 0;
	int flag = 0;
	system("title 贪吃蛇");
	system("mode con cols=94 lines=40");
	srand(time(NULL));
	int z = 4;					//初始向下运动 
	snakehead snake = Initsnake();
	DrawMap(snake);
	gotoxy(62,8);													
	printf("熟知按键后按任意键开始游戏");
	getch();
	while(1)
	{
		int temp_z = z;
		z = keydown(z);
		if(z == 27)
			break;
		if(z == 5)
		{
			gotoxy(73,8);
			printf("暂停中");
			getch(); 
			z = temp_z; 
		}
		snake = Renewsnake(snake,z);
		if(score >= scoreWin)
		{
			flag = 1;
			break;
		 } 
		if (snake->life == 0)
		{
			flag = 2;
			break;
		}
		DrawMap(snake);
		Sleep(300-speed);
	}
	if(flag == 1)
	{
		gotoxy(70,8);													
		printf("Congratulation!!!");
		gotoxy(0,30);
	}
	if(flag == 2)
	{
		gotoxy(70,8);													
		printf("Game Over!!!");
		gotoxy(0,30);
 	}
 } 
