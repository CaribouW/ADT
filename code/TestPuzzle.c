#include"Func.h"

int main()
{
	int  i, j;
	//int** maze;             /*用于储存迷宫地形的二维数组*/
	int s;
	int repeat = 1;

	while (repeat == 1)
	{
		printf("请输入两个奇数以确定迷宫的长与宽：\n");
		scanf("%d%d", &x1, &y1);
		if (x1<3 || y1<3 || x1 % 2 == 0 || y1 % 2 == 0)                     /*长宽过小或有偶数就无法生成迷宫*/
		{
			printf("输入有误！\n");                       /*提示输入错误*/
			system("pause");
			return 0;
		}
		/*
		*若尺寸不匹配则退出
		*/
		maze = (int**)malloc(sizeof(int*)*y1);              /*为二维数组动态分配储存空间*/
		for (i = 0; i<y1; i++)
		{
			maze[i] = (int*)malloc(sizeof(int)*x1);
		}
		for (i = 0; i<x1; i++)
		{
			for (j = 0; j<y1; j++)
				maze[i][j] = 0;                          /*先把所有元素都变成零*/
		}
		//建议用calloc 直接一步到位

		for (i = 0; i<x1; i++)
		{
			for (j = 0; j<y1; j++)
			{
				if (i % 2 == 1 && j % 2 == 1)
					maze[i][j] = 1;                   /*把所有两个坐标为奇数的元素变为1*/
			}
		}

		GoAhead(1, 1, rand() % 4 + 1);

		for (i = 0; i<x1; i++)
		{
			for (j = 0; j<y1; j++)
			{
				print(maze[i][j]);
			}
			printf("\n");
		}

		printf("请输入数字：\n 1--继续游戏    2--退出游戏\n");    /*选择是否继续*/
		scanf("%d", &repeat);
	}
}

