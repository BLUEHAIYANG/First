#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include<time.h>


const int w=22;
const int h=50;

char ch;
char map[w][h];	//
int snake[500][3];
int head;//�ж��Ƿ�����ͷ
int score=head;//��ŵ÷�
int direct=2;//�жϷ���
int food[2];
int poison[2];

void initmap();
void initsnake();
void showmap();
void move();
void getdirect();
void reinitmap();//���õ�ͼ
int ifbump();//�ж��Ƿ����Լ���ײ��ײǽ��
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
		identifyHead();//�¼���һ�������ж�head�Ĵ�С���ɹ������headֵһֱ���Ե������
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
			printf("��ײǽ���ˣ�\n");
			break;
		}
		if(ifeatself())
		{	gotoxy(1,24);
			printf("��ҧ�����Լ���");
			break;
		
		}*/
		gotoxy(1,23);
		printf("��ĵ÷���=%d",head);
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
			if(i==0||j==0||i==w-1||j==h-1)//�����ȺŲ�����Ⱥò��ã�==��ȣ�=��ֵ����������
				map[i][j]='*';//map[i][j]=1��ʾǽ
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
		printf("\n");//�޸��˵�ͼ�����bug
	}
}

void getdirect()
{
	if(_kbhit())//���������������⣬ִ�е�moveʱֱ�Ӿ�������
		ch=getch();
	switch(ch)
	{//��ǰ�汾ֻ�������д��WSAD
		case'W':
		case'w'://��Ұ����ϡ�
			if(direct!=2)
				direct=1;
				break;
		case'S':
		case's'://��Ұ����¡�
			if(direct!=1)
				direct=2;
				break;
		case'A'://��Ұ�����
		case'a':if(direct!=4)
				direct=3;
				break;
		case'D':
		case'd'://��Ұ����ҡ�
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
					break;//������break�����ܹ��ٿغ��������С����Ϊʲô�أ�����������ԭ�������ִ���Ȼ�����ͨ����������Ҫ�ĸı䣡����
		}
	
	//���ߵ����岹��������������a��b������������ֵ�ľ��䰸����
	int tempX,tempY;//(����ʱ���������ǰһ����ͷ�������������ֵ)
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
	//���³�ʼ����ͼ
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
	if((snake[head][1]==0||snake[head][1]==w-1||snake[head][2]==0||snake[head][2]==h-1))//�����ȺŰ��ևN��??????
		return 1;
	else return 0;

}

void identifyHead()
{
	for(int i=0;i<500;i++)
		{
			if(snake[i][0]==1)//==�����ȺŲ�����ȣ�����������������������
			{	
				head=i;
				break;//����һ��break�ͽ���ˣ�
			}
		}//���������飬�ҵ���ͷ��
}

void makefood()
{
	srand((unsigned)time(NULL)); 
	int x = rand() % 49 + 1;int y = rand() % 19 + 1;//��÷���forѭ�����档
	//����һ��1-50������Ϊ������  1-20������Ϊ������
	for(int i=0;i<500;i++)//������ظ�����������һ��  ֱ�����ظ�Ϊֹ
	{
		if(snake[i][1]==x && snake[i][2]==y)
		{x = rand() % 49 + 2;y = rand() % 19 + 2;}
		else break;
	}
		
	food[0] = y;
	food[1] = x;
	//Ӧ�ò��ܽ���ͼ���ŵĴ�ӡ�������������
}

int ifeat()
{
	if(snake[head][1]==food[0]&&snake[head][2]==food[1])
		{
		snake[head + 1][0] = 1, snake[head + 1][1] = food[0], snake[head + 1][2] = food[1];//���¶�����ͷ
		snake[head][0] = 0;//ȡ��֮ǰ����ͷ
		food[0] = 0, food[1] = 0;//����ǰ��food�ÿ�
		return 1;
		}
	return 0;
}

void fastshow()
{
	int j;j=head-1;
	for(j=head-1;j>=0;j--)
	{	
		gotoxy(snake[head][2],snake[head][1]);//ɾ����ԭ������Ľ���ֵ���֣�
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
	for(int i=0;i<head-1;i++)//����ط�����i<head-1!!!!!!�ش����
	{
		if((snake[head][1]==snake[i][1]&&snake[head][2]==snake[i][2]))
			return 1;
		
	}
	return 0;
}

	
