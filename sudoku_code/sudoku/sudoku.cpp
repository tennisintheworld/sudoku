// sudoku.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <algorithm>
using namespace std;

//build sudoku
char permutation[15] = { '1','2','4','5','6','7','8','9' };
char outputdata[200000000];
int datas;
int buildcnt, needcnt;
ofstream outputfile("sudoku.txt");
ofstream outputfileSolvesudoku("sudoku.txt");
void buildans();
void outputbuildsudoku();
void buildsudoku(char* row1rule, char* row2rule, char* row3rule);
//solve sudoku
char vis[3][10][10];
char flag[9][9];
char map[9][9];
bool is_findans = false;
bool is_firstquestion = true;
void inputsudokuquestion(int row, char* save);
void solvesudoku(int a, int b);
void setvis(int a, int b, int num);
void resetvis(int a, int b, int num);


void buildsudoku(char* row1rule, char* row2rule, char* row3rule)
{
	for (int i = 0; i < 3; i++)
	{
		outputdata[datas++] = permutation[(8 + row1rule[i] - '0') % 9];
		for (int j = 1; j < 17; j++)
		{
			outputdata[datas++] = ' ';//存入空格
			j++;
			//存入数据
			outputdata[datas++] = permutation[((16 - j) / 2 + row1rule[i] - '0') % 9];
			
		}
		outputdata[datas++] = '\n';//换行
	}

	for (int i = 0; i < 3; i++)
	{
		outputdata[datas++] = permutation[(8 + row2rule[i] - '0') % 9];
		for (int j = 1; j < 17; j++)
		{
			outputdata[datas++] = ' ';//存入空格
			j++;
			//存入数据
			outputdata[datas++] = permutation[((16 - j) / 2 + row2rule[i] - '0') % 9];

		}
		outputdata[datas++] = '\n';//换行
	}

	for (int i = 0; i < 3; i++)
	{
		outputdata[datas++] = permutation[(8 + row3rule[i] - '0') % 9];
		for (int j = 1; j < 17; j++)
		{
			outputdata[datas++] = ' ';//存入空格
			j++;
			//存入数据
			outputdata[datas++] = permutation[((16 - j) / 2 + row3rule[i] - '0') % 9];

		}
		outputdata[datas++] = '\n';//换行
	}

	outputdata[datas++] = '\n';
}

void buildans()
{
	char rule1[10][5] = { "036","063" };
	char rule2[10][5] = { "258","285","528","582","825","852" };
	char rule3[10][5] = { "147","174","417","471","714","741" };
	do
	{
		permutation[8] = '3';//(6+5)%9+1=3
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					buildsudoku(rule1[i], rule2[j], rule3[k]);
					if (++buildcnt == needcnt)
						return;
				}
			}
		}
	} while (next_permutation(permutation, permutation + 8));
	//STL库函数,next_permutation(char* first,char* last)
	//可以高效率生成一个容器里面的全排列
}

int main()
{
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
