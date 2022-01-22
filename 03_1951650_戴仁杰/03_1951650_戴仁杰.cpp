#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAZESIZE = 7;

//�������࣬���ڴ����������
class Point
{
public:
	Point() = default;
	Point(int row, int col);
	//һЩget������set����
	int getRow();
	int getCol();
	void setRow(int row);
	void setCol(int col);
	//���������롢����������
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
	//����Ҫ���ʽ�������ֵ
	out << "<" << po.row << "," << po.col << ">";
	return out;
}

template <typename T>
class Node
{
public:
	//Ĭ�Ϲ��캯���Լ����ι��캯��
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
	//��õ�ǰ����Ԫ�ظ���
	int getLinkSize();
	//��ĩβ����Ԫ��
	bool appendElemAtLast(T& data);
	//ɾ��ĩβԪ��
	bool popElemAtLast();
private:
	//˽�б������洢ͷ���͵�ǰԪ�ظ���
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
	//�ռ�����ʧ�ܣ�����false
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
	//������Ԫ�ظ���С��1����û��Ԫ�أ�ɾ��ʧ��
	if (size < 1)
	{
		return false;
	}
	//Ѱ�ҵ����ڶ����ڵ��λ�ã�����Ϊhead�ڵ�
	while (current->getNext()->getNext() != nullptr)
	{
		current = current->getNext();
	}
	//ɾ��β��㲢����һ���ڵ��next��Ϊnullptr
	delete current->getNext();
	current->setNext(nullptr);
	size--;
	return true;
}


template <typename T>
class Maze
{
public:
	//��ʾ�Թ�����ò
	void showMaze();
	//����������������Թ��ĺ�����������ʼλ�ã���ֹλ�����Թ��е��ض��ַ����洢
	bool MazeDFS(T& startPosition);
	//��ʾ�洢��·��
	void showPath();
	//Ѱ��S������λ��
	Point findStartPosition();

private:
	//�ö�ά����洢��ͼ��#������ͨ�У�0�������ͨ��
	char map[MAZESIZE][MAZESIZE] = {
		{'#','#','#','#','#','#','#'},
		{'#','S','#','0','0','0','#'},
		{'#','0','#','0','#','#','#'},
		{'#','0','#','0','#','0','#'},
		{'#','0','0','0','0','0','#'},
		{'#','0','#','0','#','E','#'},
		{'#','#','#','#','#','#','#'},
	};
	//���ڱ�ǵ�ǰ��Point���ǲ��Ǳ��߹��ˣ���ʼʱĬ�϶�û���߹�
	char isPassed[MAZESIZE][MAZESIZE] = { '\0' };
	//��ʾ���������ĸ���λ���ƶ������ں���DFS����ʹ��
	int move[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };
	//����������¼Ѱ�ҵ�·��
	Linklist<T> path;
};

template<typename T>
void Maze<T>::showMaze()
{
	//�����ͷ
	cout << " \t";
	for (int i = 0; i < MAZESIZE; i++)
	{
		cout << i << "��\t";
	}
	cout << endl;
	//���ʣ�ಿ��
	for (int j = 0; j < MAZESIZE; j++)
	{
		cout << j << "��\t";
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
	//���赱ǰ�ǿ����ߵ��յ�ģ��Ȳ���
	path.appendElemAtLast(currentPosition);
	//��ǰ�ڵ㼴Ϊ�յ㣬����true
	if (map[startPosition.getRow()][startPosition.getCol()] == 'E')
	{
		map[startPosition.getRow()][startPosition.getCol()] = 'X';
		return true;
	}
	//���ڴ洢��һ���ڵ�λ��
	T nextPosition = T(0, 0);
	for (int i = 0; i < 4; i++)
	{
		nextPosition.setRow(startPosition.getRow() + move[i][0]);
		nextPosition.setCol(startPosition.getCol() + move[i][1]);
		//��ǰ����㲻��ǽ����û�б��߹�
		if (map[nextPosition.getRow()][nextPosition.getCol()] != '#' && isPassed[nextPosition.getRow()][nextPosition.getCol()] != 'H')
		{
			isPassed[nextPosition.getRow()][nextPosition.getCol()] = 'H';
			//��ǰ�����յ㣬������һ���ڵ�����ߵ��յ�
			if (MazeDFS(nextPosition))
			{
				//��ͼ�ϸõ㱻��ΪX����ʾ���������
				map[startPosition.getRow()][startPosition.getCol()] = 'X';
				return true;
			}
		}
	}
	//ͨ������������Ȼû�ҵ����е�·������ʾ��ǰ�ڵ㲻����
	path.popElemAtLast();
	return false;
}

template <typename T>
void Maze<T>::showPath()
{
	//·����û��Ԫ�أ�֤��û��ͨ·������
	if (path.getLinkSize() == 0)
	{
		cout << "�ӵ�ǰλ���޷��ߵ��Թ����ڣ�" << endl;
		return;
	}
	Node<T>* current = path.getHead();
	while (current->getNext()->getNext() != nullptr)
	{
		current = current->getNext();
		cout << current->gatData() << " ---> ";
	}
	//���һ�������������Ӻ��ͷ������
	cout << current->getNext()->gatData() << endl;
	return;
}

template<typename T>
Point Maze<T>::findStartPosition()
{
	Point position = Point(0, 0);
	//����map���飬����λ��
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
	//���ԭʼ�Թ���ͼ
	cout << "�Թ���ͼ(#������ͨ�У�0�������ͨ�У�SΪ��㣬EΪ�յ�)��" << endl << endl;
	maze.showMaze();
	//���ó�ʼ����ĵ�
	Point startPoint = maze.findStartPosition();
	//Ѱ��·��������
	maze.MazeDFS(startPoint);
	cout << "����������ɽ��:";
	string input;
	getline(cin, input);
	cout << endl << endl;
	//չʾ���ߺ���Թ��Լ�·��
	cout << "���ߵ�ͼ����(X�����ߵ�·��)��" << endl << endl;
	maze.showMaze();
	cout << "�Թ�·��" << endl;
	maze.showPath();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}