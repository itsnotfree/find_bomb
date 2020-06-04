#include "game.h"

//��ʼ������
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	memset(board, set, rows*cols*sizeof(board[0][0]));
}

//��ӡ����
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("   ");
	for (i = 0; i < row; i++)
	{
		printf("  %d ", i + 1);
	}
	printf("\n");
	for (j = 0; j < col + 1; j++)
	{
		printf("---|");
	}
	printf("\n");
	for (i = 0; i < row; i++)
	{
		printf(" %d |", i + 1);
		for (j = 0; j < col; j++)
		{
			printf(" %c |", board[i][j]);
		}
		printf("\n");
		printf("   |", i + 1);
		for (j = 0; j < col; j++)
		{
			printf("---|");
		}
		printf("\n");
	}
	printf("\n");
}

//������
void ScMinc(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = EASY_COUNT;
	while (count)
	{
		x = rand() % 9 + 1;
		y = rand() % 9 + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			count--;
		}
	}
}

//ͳ����Χ�׵ĸ���
static int GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	return mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] +
		mine[x][y + 1] +
		mine[x - 1][y + 1] - 8 * '0';
}

//�õݹ��ų���Χû���׵�����
static void NoMine(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	int ret = GetMineCount(mine, x, y);
	if (ret == 0)
	{
		show[x][y] = ' ';
		if ((x - 1)>0 && (y - 1)>0 && (show[x - 1][y - 1] == '*'))
			NoMine(mine, show, x - 1, y - 1);
		if ((x - 1)>0 && (y)>0 && (show[x - 1][y] == '*'))
			NoMine(mine, show, x - 1, y);
		if ((x - 1)>0 && (y + 1)>0 && (show[x - 1][y + 1] == '*'))
			NoMine(mine, show, x - 1, y + 1);
		if ((x)>0 && (y - 1)>0 && (show[x][y - 1] == '*'))
			NoMine(mine, show, x, y - 1);
		if ((x)>0 && (y + 1)>0 && (show[x][y + 1] == '*'))
			NoMine(mine, show, x, y + 1);
		if ((x + 1)>0 && (y - 1)>0 && (show[x + 1][y - 1] == '*'))
			NoMine(mine, show, x + 1, y - 1);
		if ((x + 1)>0 && (y)>0 && (show[x + 1][y] == '*'))
			NoMine(mine, show, x + 1, y);
		if ((x + 1)>0 && (y + 1)>0 && (show[x + 1][y + 1] == '*'))
			NoMine(mine, show, x + 1, y + 1);
	}
	else
		show[x][y] = ret + '0';
}


//����
void FindMind(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int win = 0;  //ͳ�Ʋ����׵�������
	int ret = 0;  //ͳ����Χ�׵ĸ���
	while (win < ROW*COL - EASY_COUNT)
	{
		int select = 0;
		system("CLS"); //�������Ż�����
		DisplayBoard(show, ROW, COL);
		printf("----- 1.ɨ�� --- 2.����� -----\n");
		printf("��ѡ��:>");
		scanf("%d", &select);
		if (select == 1)
		{
			printf("������Ҫ�Ų�����꣺>");
			scanf("%d %d", &x, &y);
			if (x >= 1 && x <= row && y >= 1 && y <= col)
			{
				if (mine[x - 1][y - 1] == '1' && show[x - 1][y - 1] == '*'&& win == 0)
				{
					InitBoard(mine, ROWS, COLS, '0');
					ScMinc(mine, ROW, COL);
					win++;
				}
				if (mine[x - 1][y - 1] == '0' && show[x - 1][y - 1] == '*')
				{
					NoMine(mine, show, x - 1, y - 1);
					DisplayBoard(show, ROW, COL);
					win = win + 8;
				}
				if (mine[x - 1][y - 1] == '1' && show[x - 1][y - 1] == '*' && win != 0)
				{
					show[x - 1][y - 1] = 'S';
					DisplayBoard(show, ROW, COL);
					printf("���ź����㱻ը����\n\n");
					DisplayBoard(mine, row, col);
					break;
				}
			}
			else
			{
				printf("����Ƿ�\n");
			}
		}

		if (select == 2)
		{
			printf("������Ҫ����׵����꣺>");
			scanf("%d %d", &x, &y);
			if (show[x - 1][y - 1] == '*')
			{
				show[x - 1][y - 1] = '@'; //������ұ���Ѿ�ȷ������
				DisplayBoard(show, ROW, COL);
			}
			else
			{
				printf("����Ƿ�\n");
			}
		}
	}
	if (win > ROW*COL - EASY_COUNT)
	{
		printf("��ϲ�㣬���׳ɹ���\n");
		DisplayBoard(mine, row, col);
	}
}
