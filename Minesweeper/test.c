#include "game.h"

menu()
{
	printf("*******************************\n");
	printf("****   ��ӭ����ɨ����Ϸ��  ****\n");
	printf("****      1.������Ϸ       ****\n");
	printf("****      0.�˳���Ϸ       ****\n");
	printf("*******************************\n");
}

void game()
{
	char mine[ROWS][COLS] = { 0 }; //�÷��׵�����
	char show[ROWS][COLS] = { 0 }; //չʾ����ҵ�����
	InitBoard(mine, ROWS, COLS, '0');
	InitBoard(show, ROWS, COLS, '*');
	ScMinc(mine, ROW, COL);        //����
	//DisplayBoard(mine, ROW, COL);  
	DisplayBoard(show, ROW, COL);
	FindMind(mine, show, ROW, COL);//����
}

void test()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do
	{
		menu();
		printf("��ѡ��:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("�˳���Ϸ\n");
			break;
		default:
			printf("�������\n");
		}
	} while (input);
}

int main()
{
	test();
	return 0;
}