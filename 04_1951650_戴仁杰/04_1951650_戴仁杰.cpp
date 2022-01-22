#include <iostream>
#include <limits>

using namespace std;

class NQueens
{
public:
	//���캯���д���ʺ�ĸ���
	NQueens(int queenNum);
	//���������ͷ��ڴ�
	~NQueens();
	//��ӡ����Ԫ��
	void outputBoard();
	//�жϵ�ǰλ���ܷ����»ʺ�
	bool check(int row, int col);
	//�ݹ�Ѱ�һʺ��ŷ�������Ϊ��row��
	void queensSolve(int row);
private:
	//�ʺ�ĸ���
	int queenNum = 0;
	//�洢���̵�ָ��
	char** board = nullptr;
	//�洢��ǰ�С����Ƿ��лʺ�
	bool* rowQueen;
	bool* colQueen;
	//�洢���ϵ����¡����ϵ�����б���Ƿ��лʺ�
	bool* LRQueen;
	bool* RLQueen;
	//�洢�ڷŷ�������Ŀ
	int solutionNum = 0;
};

NQueens::NQueens(int queenNum)
{
	this->queenNum = queenNum;
	//��̬�ڴ�����һ��queenNum*queenNum��С������
	board = new char* [queenNum];
	for (int i = 0; i < queenNum; i++)
	{
		board[i] = new char[queenNum]();
		//��������Ŀռ丳ֵΪ�ַ�'0'
		for (int j = 0; j < queenNum; j++)
		{
			board[i][j] = '0';
		}
	}
	//��̬�����ж�����б�ߵ�����
	rowQueen = new bool[queenNum]();
	colQueen = new bool[queenNum]();
	LRQueen = new bool[2 * queenNum - 1]();
	RLQueen = new bool[2 * queenNum - 1]();
}

NQueens::~NQueens()
{
	//�ͷ�����
	for (int i = 0; i < queenNum; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	//�ͷ��ж�����б�ߵ�����
	delete[] rowQueen;
	delete[] colQueen;
	delete[] LRQueen;
	delete[] RLQueen;
}

void NQueens::outputBoard()
{
	//����������ÿ��Ԫ�أ������ֵ
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
	//ͬ��ͬ����б����б�߾������ӣ�����true
	if (!rowQueen[row] && !colQueen[col] && !LRQueen[queenNum + col - row - 1] && !RLQueen[row + col])
	{
		return true;
	}
	return false;
}

void NQueens::queensSolve(int row)
{
	//����ÿһ�У������ұ���ÿһ��
	for (int col = 0; col < queenNum; col++)
	{		
		if (check(row, col))
		{
			board[row][col] = 'X';
			rowQueen[row] = true;
			colQueen[col] = true;
			LRQueen[queenNum + col - row - 1] = true;
			RLQueen[row + col] = true;

			//��ǰ�Ѿ������һ���ˣ��ҵ���һ�ֺ���ķ���
			if (row + 1 == queenNum)
			{
				solutionNum++;
				outputBoard();
			}
			//�������������һ��
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
		//��ʱ���з�������ִ����ϣ�����ⷨ��Ŀ
		if (row == 0 && col == queenNum - 1)
		{
			cout << "����" << solutionNum << "�ֽⷨ��" << endl;
		}
	}
	return;
}

int main()
{
	//�ʺ�ĸ���
	int queensNum;
	cout << "����NxN�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһб���ϣ�" << endl << endl;
	cout << "������ʺ�ĸ�����";
	cin >> queensNum;
	while (cin.fail() || queensNum <= 0)
	{
		cout << "�ʺ���ӦΪ��������" << endl;
		cout << "������ʺ�ĸ�����";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> queensNum;
	}
	cout << endl;
	NQueens nQueens = NQueens(queensNum);
	cout << "�ʺ�ڷ���" << endl << endl;
	nQueens.queensSolve(0);
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}