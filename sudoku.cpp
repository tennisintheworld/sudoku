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
char permutation[15] = { '1','2','4','5','6','7','8','9' };//3是我的学号后两位经过变换后得到的数
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
void outputsolvesudoku();
void setvis(int a, int b, int num);
void resetvis(int a, int b, int num);
bool checkvis(int a, int b, int num);


//build sudoku
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
	char rule1[10][5] = { "036","063" };//123列的平移规则，0代表第一个不平移
	char rule2[10][5] = { "258","285","528","582","825","852" };//456列的平移规则
	char rule3[10][5] = { "147","174","417","471","714","741" };//789列的平移规则
	do
	{
		permutation[8] = '3';//(6+5)%9+1=3，插入由学号获得的固定数字到排列尾部
		for (int i = 0; i < 2; i++)//组合获得72种排列方式
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					buildsudoku(rule1[i], rule2[j], rule3[k]);//由排列经过变换获得完整数独
					if (++buildcnt == needcnt)
						return;
				}
			}
		}
	} while (next_permutation(permutation, permutation + 8));
	//STL库函数,next_permutation(char* first,char* last)
	//可以高效率生成一个容器里面的全排列
}

void outputbuildsudoku()
{
	outputfile << outputdata;//sudoku.txt
}


//solve sudoku
void inputsudokuquestion(int row, char* save)
{
	for (int j = 0; j < 17; j++)
	{
		if (j % 2 == 0)
		{
			map[row][j / 2] = save[j];
			setvis(row, j / 2, save[j] - '0');
		}

	}
}

void solvesudoku(int a, int b)
{
	while (map[a][b] != '0')
	{
		if (b < 8)
			b++;
		else
			b = 0, a++;
		if (a == 9)//成功走到了最后一个，证明找到了解
		{
			is_findans = true;
			return;
		}
	}
	bool is_search = false;
	for (int i = 1; i <= 9; i++)
	{
		if (checkvis(a, b, i))//检查是否可以在某个点放下某个数字
		{
			setvis(a, b, i);
			map[a][b] = i + '0';
			is_search = true;
			solvesudoku(a, b);
		}
		if (is_search)//搜索过了
		{
			is_search = false;
			if (is_findans)//找到了
				return;
			else//没找到
			{
				map[a][b] = '0';
				resetvis(a, b, i);
			}
		}
	}
}

void setvis(int a, int b, int num)
{
	vis[0][a][num] = 1;
	vis[1][b][num] = 1;
	vis[2][a / 3 * 3 + b / 3][num] = 1;
}

void resetvis(int a, int b, int num)
{
	vis[0][a][num] = 0;
	vis[1][b][num] = 0;
	vis[2][a / 3 * 3 + b / 3][num] = 0;
}

bool checkvis(int a, int b, int num)
{
	if (vis[0][a][num] == 0 && vis[1][b][num] == 0 && vis[2][a / 3 * 3 + b / 3][num] == 0)
		return true;
	else
		return false;
}

void outputsolvesudoku()
{
	char outputsave[1000];
	memset(outputsave, 0, sizeof(outputsave));
	int m = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			outputsave[m++] = map[i][j];
			if ((m + 1) % 18 == 0)
				outputsave[m++] = '\n';//一行结束的换行
			else
				outputsave[m++] = ' ';//数字之间的空格
		}
	}

	outputfileSolvesudoku << outputsave;//sudoku.txt
}

int main(int argc,char* argv[])
{
	FILE *fp;
		fp = fopen(argv[2], "r");
	if (argc == 3 && strcmp(argv[1], "-c") == 0)//sudoku.exe -c 1000 表示生成1000个终局，参数为-c
	{
		int len = strlen(argv[2]);
		for (int i = 0; i < len; i++)
		{
			if (argv[2][i] >= '0' && argv[2][i] <= '9')
				needcnt += (argv[2][i] - '0') * pow(10, len - i - 1);
			else
			{
				cout << "error" << endl;
				return 0;
			}
		}
		while (buildcnt < needcnt)
			buildans();
		outputdata[datas++] = '\0';
		outputbuildsudoku();
	}
	else if (argc == 3 && strcmp(argv[1], "-s") == 0)//sudoku.exe -s 文件绝对路径：表示求解文件里的数独问题，参数为-s
	{

		char save[100];
		int cnt = 0;
		while (fgets(save, 20, fp))
		{
			if (strcmp(save, "\n") == 0)
				continue;
			inputsudokuquestion(cnt, save);
			cnt++;
			if (cnt == 9)
			{
				if (!is_firstquestion)
					outputfileSolvesudoku << endl;
				else
					is_firstquestion = false;

				is_findans = false;
				solvesudoku(0, 0);
				cnt = 0;
				outputsolvesudoku();
				memset(vis, 0, sizeof(vis));
			}
		}
	}
	else//参数不是-c也不是-s
		cout << "error" << endl;
	
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
