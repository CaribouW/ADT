#include<stdio.h>
#include <malloc.h>
#include <stdlib.h>

//总体思路，先选择方向，再进行运动调用
int IsEnd(x, y);
void generateOfNoLimit(int x, int y);
void generateOfOneLimit(int x, int y, int limit);
void generareOfTwoLimit(int x, int y, int limit1, int limit2);
void generareOfThreeLimit(int x, int y, int limit1, int limit2, int limit3);  //方向选择器
void back(int x, int y);                //返回器
void print(int x);
void RightWord(int x, int y);
void LeftWord(int x, int y);
void UpWord(int x, int y);
void DownWord(int x, int y);
void GoAhead(int x, int y, int dire);   //头文件的主函数
void MoveOut(int x, int y, int dire);   //运动调用器
int x1, y1;         
int** maze;             /*用于储存迷宫地形的二维数组*/

void generateOfNoLimit(int x, int y)
{
	int dire;/*控制方向*/
	dire = rand() % 4 + 1;//随机生成数1,2,3,4 代表四个方向
	MoveOut(x, y, dire);
}
void generateOfOneLimit(int x, int y, int limit){
	int dire=limit;
	while (dire==limit)
		dire = rand() % 4 + 1;
	MoveOut(x, y, dire);
}
void generareOfTwoLimit(int x, int y, int limit1, int limit2){
	int dire=limit1;
	while (dire==limit1||dire==limit2)
		dire = dire = rand() % 4 + 1;
	MoveOut(x, y, dire);
}
void generareOfThreeLimit(int x, int y, int limit1, int limit2, int limit3){
	int dire=limit1;
	while (dire == limit1 || dire == limit2||dire==limit3)
		dire = dire = rand() % 4 + 1;
	MoveOut(x, y, dire);
}

/*往回走找到找过的路*/
void back(int x, int y){
	
}
void print(int x){
	if (x == 0)
	{
		printf("█");
	}
	else if (x == 1)
	{
		printf("○");
	}
	else
	{
		printf("  ");
	}
}
void RightWord(int x, int y){
	if (maze[x + 2][y]!=2)
		maze[x + 1][y] = 2;
	return;
		
}
void LeftWord(int x, int y){
	if (maze[x - 2][y]!=2)
		maze[x - 1][y] = 2;
	return;
}
void UpWord(int x, int y){
	if (maze[x][y+2]!=2)
		maze[x][y + 1] = 2;
	return;
}
void DownWord(int x, int y){
	if (maze[x][y-2]!=2)
		maze[x][y - 1] = 2;
	return;
}
void GoAhead(int x, int y, int dire){
	if (x<1 || y<1 || x>x1 - 1 || y>y1 - 1)
	{
		if (x < 1) {
			x += 2;
			//back(x, y, 2);
		}
		if (y < 1) {
			y += 2;
			//back(x, y, 4);
		}
		if (x > x1 - 1) {
			x -= 2;
			//back(x, y, 1);
		}
		if (y > y1 - 1) {
			y -= 2;
			//back(x, y, 3);
		}
	}
	maze[x][y] = 2;
	do
	{
		if (x<1 || y<1 || x>x1 - 1 || y>y1 - 1)
		{
			if (x < 1) {
				x += 2;
				//back(x, y, 2);
			}
			if (y < 1) {
				y += 2;
				//back(x, y, 4);
			}
			if (x > x1 - 1) {
				x -= 2;
				//back(x, y, 1);
			}
			if (y > y1 - 1) {
				y -= 2;
				//back(x, y, 3);
			}
		}
		MoveOut(x, y, dire);//走出去了第一步
		if (dire == 1){  maze[x][y] = 2; x = x + 2;}
		if (dire == 2){  maze[x][y] = 2;x = x - 2; }
		if (dire == 3){  maze[x][y] = 2; y = y + 2;}
		if (dire == 4){ maze[x][y] = 2;y = y - 2;}
		dire = rand() % 4 + 1;
		int k = 0;
		for (int i = 0; i < x1; i++){
			for (int j = 0; j < y1; j++)
				if (maze[i][j] == 1)
					k = 1;
		}
		if (!k)
			break;
		if (IsEnd(x, y))
		{
			if (x < 1) {
				x += 2;
				//back(x, y, 2);
			}
			if (y < 1) {
				y += 2;
				//back(x, y, 4);
			}
			if (x > x1 - 1) {
				x -= 2;
				//back(x, y, 1);
			}
			if (y > y1 - 1) {
				y -= 2;
				//back(x, y, 3);
			}
			back(x, y);
		}
	} while (1);
	return;
}
void MoveOut(int x, int y, int dire){
	if (dire == 1){//rightWord
		//右下角
		if (x == x1 - 2 && y == 1)generareOfTwoLimit(x,y,1, 4);
		//右侧
		else if (x == x1 - 2 && y != 1 && y != y1 - 1)generateOfOneLimit(x, y, 1);
		//右上角
		else if (x == x1 - 2 && y == y1 - 1)generareOfTwoLimit(x, y, 1, 3);
		else 
			RightWord(x, y);
	}
	if (dire == 2){//向左走
		//左上角
		if (x == 1 && y == y1 - 2)generareOfTwoLimit(x, y, 2, 4);
		//左侧
		else if (x == 1 && y != y1 - 2 && y != 1)generateOfOneLimit(x, y, 2);
		//左下角
		else if (x == 1 && y == 1)generareOfTwoLimit(x, y, 2, 4);
		else
			LeftWord(x, y);
	}
	if (dire == 3){//向上走
		//左上角
		if (y == y1 - 2 && x == 1)generareOfTwoLimit(x, y, 3, 2);
		//上侧
		else if (y == y1 - 2 && x != 1 && x != x1 - 2)generateOfOneLimit(x, y, 3);
		//右上角
		else if (y == y1 - 2 && x == x1 - 2)generareOfTwoLimit(x, y, 1, 3);
		else
			UpWord(x, y);
	}
	if (dire == 4){//向下走
		//左下角
		if (y == 1 && x == 1)generareOfTwoLimit(x, y, 2, 4);
		//下侧
		else if (y == 1 && x != 1 && x != x1 - 2)generateOfOneLimit(x, y, 4);
		//右下角
		else if (y == 1 && x== x1 - 2)generareOfTwoLimit(x, y, 4, 1);
		else
			DownWord(x, y);
	}

}
int IsEnd(x, y){
	if (x<1 || y<1 || x>x1 - 1 || y>y1 - 1){
		if (x < 1) {
			x += 2;
			//back(x, y, 2);
		}
		if (y < 1) {
			y += 2;
			//back(x, y, 4);
		}
		if (x > x1 - 1) {
			x -= 2;
			//back(x, y, 1);
		}
		if (y > y1 - 1) {
			y -= 2;
			//back(x, y, 3);
		}
	}
	if ((maze[x - 1][y] + maze[x + 1][y] + maze[x][y + 1] + maze[x][y - 1]) == 2)
		return 1;
	return 0;
}