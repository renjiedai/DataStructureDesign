#include <iostream>
#include <limits>

using namespace std;

class NQueens
{
public:
	//构造函数中传入皇后的个数
	NQueens(int queenNum);
	//析构函数释放内存
	~NQueens();
	//打印数组元素
	void outputBoard();
	//判断当前位置能否落下皇后
	bool check(int row, int col);
	//递归寻找皇后排法，参数为第row行
	void queensSolve(int row);
private:
	//皇后的个数
	int queenNum = 0;
	//存储棋盘的指针
	char** board = nullptr;
	//存储当前行、列是否有皇后
	bool* rowQueen;
	bool* colQueen;
	//存储左上到右下、右上到左下斜线是否有皇后
	bool* LRQueen;
	bool* RLQueen;
	//存储摆放方法的数目
	int solutionNum = 0;
};

NQueens::NQueens(int queenNum)
{
	this->queenNum = queenNum;
	//动态内存申请一个queenNum*queenNum大小的棋盘
	board = new char* [queenNum];
	for (int i = 0; i < queenNum; i++)
	{
		board[i] = new char[queenNum]();
		//给新申请的空间赋值为字符'0'
		for (int j = 0; j < queenNum; j++)
		{
			board[i][j] = '0';
		}
	}
	//动态申请判断行列斜线的数组
	rowQueen = new bool[queenNum]();
	colQueen = new bool[queenNum]();
	LRQueen = new bool[2 * queenNum - 1]();
	RLQueen = new bool[2 * queenNum - 1]();
}

NQueens::~NQueens()
{
	//释放棋盘
	for (int i = 0; i < queenNum; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	//释放判断行列斜线的数组
	delete[] rowQueen;
	delete[] colQueen;
	delete[] LRQueen;
	delete[] RLQueen;
}

void NQueens::outputBoard()
{
	//对于棋盘上每个元素，输出其值
	for (int i = 0; i < queenNum; i++)
	{
		for (int j = 0; j < queenNum; j++)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

bool NQueens::check(int row, int col)
{
	//同行同列左斜线右斜线均无棋子，返回true
	if (!rowQueen[row] && !colQueen[col] && !LRQueen[queenNum + col - row - 1] && !RLQueen[row + col])
	{
		return true;
	}
	return false;
}

void NQueens::queensSolve(int row)
{
	//对于每一列，从左到右遍历每一列
	for (int col = 0; col < queenNum; col++)
	{		
		if (check(row, col))
		{
			board[row][col] = 'X';
			rowQueen[row] = true;
			colQueen[col] = true;
			LRQueen[queenNum + col - row - 1] = true;
			RLQueen[row + col] = true;

			//当前已经是最后一个了，找到了一种合理的方案
			if (row + 1 == queenNum)
			{
				solutionNum++;
				outputBoard();
			}
			//否则继续安排下一行
			else
			{
				queensSolve(row + 1);
			}
			board[row][col] = '0';
			rowQueen[row] = false;
			colQueen[col] = false;
			LRQueen[queenNum + col - row - 1] = false;
			RLQueen[row + col] = false;
		}
		//此时所有方法均已执行完毕，输出解法数目
		if (row == 0 && col == queenNum - 1)
		{
			cout << "共有" << solutionNum << "种解法！" << endl;
		}
	}
	return;
}

int main()
{
	//皇后的个数
	int queensNum;
	cout << "现有NxN的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！" << endl << endl;
	cout << "请输入皇后的个数：";
	cin >> queensNum;
	while (cin.fail() || queensNum <= 0)
	{
		cout << "皇后数应为正整数！" << endl;
		cout << "请输入皇后的个数：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> queensNum;
	}
	cout << endl;
	NQueens nQueens = NQueens(queensNum);
	cout << "皇后摆法：" << endl << endl;
	nQueens.queensSolve(0);
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}