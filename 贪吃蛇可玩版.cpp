#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include<time.h>


const int w=22;
const int h=50;

char ch;
char map[w][h];	//
int snake[500][3];
int head;//判断是否是蛇头
int score=head;//存放得分
int direct=2;//判断方向
int food[2];
int poison[2];

void initmap();
void initsnake();
void showmap();
void move();
void getdirect();
void reinitmap();//重置地图
int ifbump();//判断是否与自己相撞或撞墙。
int ifeat();
int ifeatself();
void identifyHead();
void makefood();
void makepoison();
void gotoxy(int, int);
void fastshow();



void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}




int main()
{
	snake[3][1]=6;
	snake[3][2]=4;

	initmap();
	initsnake();
	food[0]=0;
	food[1]=0;
	 showmap();
	while(1)
	{
		identifyHead();//新加入一个函数判定head的大小，成功解决了head值一直不对的情况。
		getdirect();
		Sleep(30);
		reinitmap();
	    move();
		fastshow();
		if(ifeat()) ;
		if(food[0]==0&&food[1]==0)
			makefood();
		/*if(ifbump())
		{	gotoxy(1,24);
			printf("你撞墙输了！\n");
			break;
		}
		if(ifeatself())
		{	gotoxy(1,24);
			printf("你咬伤了自己！");
			break;
		
		}*/
		gotoxy(1,23);
		printf("你的得分是=%d",head);
	}
		return 0;
}

void initmap()
{
	int i,j;
	for (i=0;i<w;i++)
	{
		for(j=0;j<h;j++)
		{
			if(i==0||j==0||i==w-1||j==h-1)//两个等号才是相等好不好！==相等，=赋值别老是忘！
				map[i][j]='*';//map[i][j]=1表示墙
			else map[i][j]=' ';
		}
		
	}
}


void initsnake()
{
	snake[0][0]=0;snake[0][1]=2;snake[0][2]=4;
	snake[1][0]=0;snake[1][1]=3;snake[1][2]=4;
	snake[2][0]=0;snake[2][1]=4;snake[2][2]=4;
	snake[3][0]=0;snake[3][1]=5;snake[3][2]=4;
	snake[4][0]=1;snake[4][1]=8;snake[4][2]=4;
	
}

void showmap()
{
	map[food[0]][food[1]]='o';
	int i,j;
	for (i=0;i<w;i++)
	{
		for(j=0;j<h;j++)
		{
			printf("%c",map[i][j]);
			
		}
		printf("\n");//修复了地图乱码的bug
	}
}

void getdirect()
{
	if(_kbhit())//恐怕是这里有问题，执行到move时直接就跳过了
		ch=getch();
	switch(ch)
	{//当前版本只能输入大写的WSAD
		case'W':
		case'w'://玩家按“上”
			if(direct!=2)
				direct=1;
				break;
		case'S':
		case's'://玩家按“下”
			if(direct!=1)
				direct=2;
				break;
		case'A'://玩家按“左”
		case'a':if(direct!=4)
				direct=3;
				break;
		case'D':
		case'd'://玩家按“右”
			if(direct!=3)
				direct=4;
				break;
	}
	
	
	/*for(int i=0;i<500;i++)
	{
		if(direct=1)
			snake[i][2]++;
		else if(direct=2)
			snake[i][2]--;
		else if(direct=3)
			snake[i][1]--;
		else
			snake[i][1]++;
	}*/
	

}

void move()
{
	
	switch(direct)
		{
			case 1:snake[head][1]--;
					break;
			case 2:snake[head][1]++;
					break;
			case 3:snake[head][2]--;
					break;
			case 4:snake[head][2]++;
					break;//加入了break语句就能够操控横纵坐标减小啦？为什么呢？！！！！！原来的这种错误竟然会编译通过！！！重要的改变！！！
		}
	
	//让蛇的身体补上来，这里用了a，b两个变量互换值的经典案例。
	int tempX,tempY;//(用临时变量来存放前一个蛇头或者蛇身的坐标值)
	tempX=snake[head][1];
	tempY=snake[head][2];
	int j;j=head-1;
	for(j=head-1;j>=0;j--)
	{	
		int temp;
		temp=tempX;tempX=snake[j][1];snake[j][1]=temp;
		temp=tempY;tempY=snake[j][2];snake[j][2]=temp;
	}


	
	
}

void reinitmap()
{
	//重新初始化地图
	for (int i = 0;i<w;i++) {
		for (int j = 0;j<h;j++) {
			if (i == 0 || j == 0 || i == w - 1 || j == h- 1) 
				map[i][j] = '*';
			else 
				map[i][j] = ' ';
			
		}
	}

	
	
		
}

int ifbump()
{
	if((snake[head][1]==0||snake[head][1]==w-1||snake[head][2]==0||snake[head][2]==h-1))//两个等号啊兄嘚！??????
		return 1;
	else return 0;

}

void identifyHead()
{
	for(int i=0;i<500;i++)
		{
			if(snake[i][0]==1)//==两个等号才是相等！！！！！！！！！！！！
			{	
				head=i;
				break;//加了一个break就解决了！
			}
		}//遍历蛇数组，找到蛇头。
}

void makefood()
{
	srand((unsigned)time(NULL)); 
	int x = rand() % 49 + 1;int y = rand() % 19 + 1;//这得放在for循环外面。
	//生成一个1-50的数作为横坐标  1-20的数作为纵坐标
	for(int i=0;i<500;i++)//如果有重复就重新生成一个  直到不重复为止
	{
		if(snake[i][1]==x && snake[i][2]==y)
		{x = rand() % 49 + 2;y = rand() % 19 + 2;}
		else break;
	}
		
	food[0] = y;
	food[1] = x;
	//应该不能将地图符号的打印放着这个函数中
}

int ifeat()
{
	if(snake[head][1]==food[0]&&snake[head][2]==food[1])
		{
		snake[head + 1][0] = 1, snake[head + 1][1] = food[0], snake[head + 1][2] = food[1];//重新定义蛇头
		snake[head][0] = 0;//取消之前的蛇头
		food[0] = 0, food[1] = 0;//将当前的food置空
		return 1;
		}
	return 0;
}

void fastshow()
{
	int j;j=head-1;
	for(j=head-1;j>=0;j--)
	{	
		gotoxy(snake[head][2],snake[head][1]);//删除了原本在这的交换值部分！
		putchar('A');
		gotoxy(snake[j][2],snake[j][1]);
		putchar('a');
		gotoxy(snake[0][2],snake[0][1]);
		putchar(' ');
		
	}
	gotoxy(food[1],food[0]);
	putchar('o');
	
}

int ifeatself()
{
	for(int i=0;i<head-1;i++)//这个地方不是i<head-1!!!!!!重大错误！
	{
		if((snake[head][1]==snake[i][1]&&snake[head][2]==snake[i][2]))
			return 1;
		
	}
	return 0;
}

	
