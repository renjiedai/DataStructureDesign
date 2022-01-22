#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAZESIZE = 7;

//点坐标类，用于存放行列坐标
class Point
{
public:
	Point() = default;
	Point(int row, int col);
	//一些get函数和set函数
	int getRow();
	int getCol();
	void setRow(int row);
	void setCol(int col);
	//重载流输入、流输出运算符
	friend istream& operator>>(istream& in, Point& po);
	friend ostream& operator<<(ostream& out, const Point& po);	
private:
	int row = 0;
	int col = 0;
};

Point::Point(int row, int col)
{
	this->row = row;
	this->col = col;
}

int Point::getRow()
{
	return this->row;
}

int Point::getCol()
{
	return this->col;
}

void Point::setRow(int row)
{
	this->row = row;
	return;
}

void Point::setCol(int col)
{
	this->col = col;
	return;
}

istream& operator>>(istream& is, Point& po)
{
	is >> po.row >> po.col;
	return is;
}

ostream& operator<<(ostream& out, const Point& po)
{
	//按照要求格式输出坐标值
	out << "<" << po.row << "," << po.col << ">";
	return out;
}

template <typename T>
class Node
{
public:
	//默认构造函数以及带参构造函数
	Node() = default;
	Node(T& data, Node<T>* next);
	T gatData();
	Node<T>* getNext();
	void setData(T& data);
	void setNext(Node<T>* next);
private:
	T data;
	Node<T>* next = nullptr;
};

template <typename T>
Node<T>::Node(T& data, Node<T>* next)
{
	this->data = data;
	this->next = next;
}

template <typename T>
T Node<T>::gatData()
{
	return this->data;
}

template <typename T>
Node<T>* Node<T>::getNext()
{
	return this->next;
}

template <typename T>
void Node<T>::setData(T& data)
{
	this->data = data;
	return;
}

template <typename T>
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
	return;
}



template <typename T>
class Linklist
{
public:
	Linklist();
	~Linklist();
	Node<T>* getHead();
	//获得当前链表元素个数
	int getLinkSize();
	//在末尾插入元素
	bool appendElemAtLast(T& data);
	//删除末尾元素
	bool popElemAtLast();
private:
	//私有变量，存储头结点和当前元素个数
	Node<T>* head;
	int size;
};

template <typename T>
Linklist<T>::Linklist()
{
	head = new Node<T>;
	head->setNext(nullptr);
	size = 0;
}

template <typename T>
Linklist<T>::~Linklist()
{
	Node<T>* nextNode = head;
	for (int i = 0; i < size; i++)
	{
		nextNode = head->getNext();
		delete head;
		head = nextNode;
	}
	delete nextNode;
}

template <typename T>
Node<T>* Linklist<T>::getHead()
{
	return this->head;
}

template <typename T>
int Linklist<T>::getLinkSize()
{
	return this->size;
}

template <typename T>
bool Linklist<T>::appendElemAtLast(T& data)
{
	Node<T>* newNode = new Node<T>(data, nullptr);
	//空间申请失败，返回false
	if (newNode == nullptr)
	{
		return false;
	}
	Node<T>* current = head;
	while (current->getNext() != nullptr)
	{
		current = current->getNext();
	}
	current->setNext(newNode);
	size++;
	return true;
}

template <typename T>
bool Linklist<T>::popElemAtLast()
{
	Node<T>* current = head;
	//链表中元素个数小于1，即没有元素，删除失败
	if (size < 1)
	{
		return false;
	}
	//寻找倒数第二个节点的位置，可能为head节点
	while (current->getNext()->getNext() != nullptr)
	{
		current = current->getNext();
	}
	//删除尾结点并将上一个节点的next置为nullptr
	delete current->getNext();
	current->setNext(nullptr);
	size--;
	return true;
}


template <typename T>
class Maze
{
public:
	//显示迷宫的样貌
	void showMaze();
	//用于深度优先搜索迷宫的函数，传入起始位置，终止位置用迷宫中的特定字符来存储
	bool MazeDFS(T& startPosition);
	//显示存储的路径
	void showPath();
	//寻找S的坐标位置
	Point findStartPosition();

private:
	//用二维数组存储地图，#代表不可通行，0代表可以通行
	char map[MAZESIZE][MAZESIZE] = {
		{'#','#','#','#','#','#','#'},
		{'#','S','#','0','0','0','#'},
		{'#','0','#','0','#','#','#'},
		{'#','0','#','0','#','0','#'},
		{'#','0','0','0','0','0','#'},
		{'#','0','#','0','#','E','#'},
		{'#','#','#','#','#','#','#'},
	};
	//用于标记当前的Point点是不是被走过了，初始时默认都没有走过
	char isPassed[MAZESIZE][MAZESIZE] = { '\0' };
	//表示下右上左四个方位的移动，便于后续DFS搜索使用
	int move[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	//用链表来记录寻找的路径
	Linklist<T> path;
};

template<typename T>
void Maze<T>::showMaze()
{
	//输出表头
	cout << " \t";
	for (int i = 0; i < MAZESIZE; i++)
	{
		cout << i << "列\t";
	}
	cout << endl;
	//输出剩余部分
	for (int j = 0; j < MAZESIZE; j++)
	{
		cout << j << "行\t";
		for (int k = 0; k < MAZESIZE; k++)
		{
			cout << map[j][k] << '\t';
		}
		cout << endl << endl;
	}
	return;
}

template <typename T>
bool Maze<T>::MazeDFS(T& startPosition)
{
	T currentPosition = startPosition;
	//假设当前是可以走到终点的，先插入
	path.appendElemAtLast(currentPosition);
	//当前节点即为终点，返回true
	if (map[startPosition.getRow()][startPosition.getCol()] == 'E')
	{
		map[startPosition.getRow()][startPosition.getCol()] = 'X';
		return true;
	}
	//用于存储下一个节点位置
	T nextPosition = T(0, 0);
	for (int i = 0; i < 4; i++)
	{
		nextPosition.setRow(startPosition.getRow() + move[i][0]);
		nextPosition.setCol(startPosition.getCol() + move[i][1]);
		//当前这个点不是墙壁且没有被走过
		if (map[nextPosition.getRow()][nextPosition.getCol()] != '#' && isPassed[nextPosition.getRow()][nextPosition.getCol()] != 'H')
		{
			isPassed[nextPosition.getRow()][nextPosition.getCol()] = 'H';
			//当前不是终点，但是下一个节点可以走到终点
			if (MazeDFS(nextPosition))
			{
				//地图上该点被置为X，表示走了这个点
				map[startPosition.getRow()][startPosition.getCol()] = 'X';
				return true;
			}
		}
	}
	//通过上述两步仍然没找到可行的路径，表示当前节点不合适
	path.popElemAtLast();
	return false;
}

template <typename T>
void Maze<T>::showPath()
{
	//路径中没有元素，证明没有通路，返回
	if (path.getLinkSize() == 0)
	{
		cout << "从当前位置无法走到迷宫出口！" << endl;
		return;
	}
	Node<T>* current = path.getHead();
	while (current->getNext()->getNext() != nullptr)
	{
		current = current->getNext();
		cout << current->gatData() << " ---> ";
	}
	//最后一个单独处理，不加后箭头并换行
	cout << current->getNext()->gatData() << endl;
	return;
}

template<typename T>
Point Maze<T>::findStartPosition()
{
	Point position = Point(0, 0);
	//遍历map数组，查找位置
	for (int i = 0; i < MAZESIZE; i++)
	{
		for (int j = 0; j < MAZESIZE; j++)
		{
			if (map[i][j] == 'S')
			{
				position.setRow(i);
				position.setCol(j);
			}
		}
	}
	return position;
}



int main()
{
	Maze<Point> maze;
	//输出原始迷宫地图
	cout << "迷宫地图(#代表不可通行，0代表可以通行，S为起点，E为终点)：" << endl << endl;
	maze.showMaze();
	//设置初始输入的点
	Point startPoint = maze.findStartPosition();
	//寻找路径并保存
	maze.MazeDFS(startPoint);
	cout << "按任意键生成结果:";
	string input;
	getline(cin, input);
	cout << endl << endl;
	//展示行走后的迷宫以及路径
	cout << "行走地图如下(X代表走的路径)：" << endl << endl;
	maze.showMaze();
	cout << "迷宫路径" << endl;
	maze.showPath();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}