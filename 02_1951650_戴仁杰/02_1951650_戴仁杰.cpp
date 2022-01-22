#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

//节点类，存储人员的编号，并提供操作的方法
template<typename T>
class Node
{
public:
	Node() = default;
	//带参构造函数
	Node(T numberID, Node<T>* next);
	//获得当前人员编号
	T getNumberID();
	//获取后继节点
	Node<T>* getNext();
	//设置当前人员编号
	void setNumberID(T numberID);
	//设置后继节点
	void setNext(Node<T>* next);
private:
	T numberID = 0;
	Node<T>* next = nullptr;

};

template<typename T>
Node<T>::Node(T numberID, Node* next)
{
	this->numberID = numberID;
	this->next = next;
}

template<typename T>
T Node<T>::getNumberID()
{
	return this->numberID;
}

template<typename T>
Node<T>* Node<T>::getNext()
{
	return this->next;
}

template<typename T>
void Node<T>::setNumberID(T numberID)
{
	this->numberID = numberID;
}

template<typename T>
void Node<T>::setNext(Node* next)
{
	this->next = next;
}

//用于存储人员信息的循环链表结构
template<typename T>
class Linklist
{
public:
	Linklist();
	~Linklist();
	//返回numberID节点的前一个节点的指针，方便后续操作
	Node<T>* findElemByNumberID(T numberID);
	//在链表的position位置增加编号为numberID的元素
	bool appendElem(T numberID, int position);
	//删除链表中指定numberID的元素
	bool popElem(T numberID);
	//显示出当前剩余的元素numberID
	Node<T>* getHead();
	int getSize();

private:
	Node<T>* head = nullptr;
	int size = 0;

};

template<typename T>
Linklist<T>::Linklist()
{
	head = new Node<T>;
	head->setNext(head);
	size = 0;
}

template<typename T>
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

template<typename T>
Node<T>* Linklist<T>::findElemByNumberID(T numberID)
{
	Node<T>* current = head;
	for (int i = 0; i < size; i++)
	{
		
		if (current->getNext()->getNumberID() == numberID)
		{
			return current;
		}
		current = current->getNext();
	}
	return nullptr;
}

template<typename T>
bool Linklist<T>::appendElem(T numberID, int position)
{
	//当插入位置不合理时，直接返回
	if (position<1 || position>size + 1)
	{
		return false;
	}
	//否则循环找要插入的节点
	Node<T>* current = head;
	for (int i = 1; i < position; i++)
	{
		current = current->getNext();
	}
	//设置插入的节点以及对上一个节点进行修改next指针完成插入操作
	Node<T>* newNode = new Node<T>(numberID, current->getNext());
	current->setNext(newNode);
	size++;
	return true;
}

template<typename T>
bool Linklist<T>::popElem(T numberID)
{
	Node<T>* prior = findElemByNumberID(numberID);
	//未找到，返回删除失败
	if (prior == nullptr)
	{
		return false;
	}
	//查询成功，目标节点删除
	Node<T>* next = prior->getNext()->getNext();
	delete prior->getNext();
	prior->setNext(next);
	//删除完成，链表大小减一
	size--;
	return true;
}

template<typename T>
Node<T>* Linklist<T>::getHead()
{
	return this->head;
}

template<typename T>
int Linklist<T>::getSize()
{
	return this->size;
}

//约瑟夫游戏类，负责对链表进行更好的管理
class JosephusGame
{
public:
	//类的构造函数中完成初始化
	JosephusGame();
	//插入玩家信息
	void insertPerson();
	//根据报号删除玩家
	void killPerson();
	//展示剩余玩家信息
	void showLivers();

private:
	Linklist<int> linklist;
	int numbers;
	int start;
	int death;
	int live;

};

JosephusGame::JosephusGame()
{
	//初始化定义游戏要求中的N S M K等变量
	int N, S, M, K;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K人为止" << endl;
	cout << endl;
	//格式化控制符控制输出信息，保持对齐
	cout << left << setw(25) << "请输入生死游戏的总人数N：";
	cin >> N;
	//进行输入检测，增强程序的健壮性，下同
	while (cin.fail() || N <= 0)
	{
		cout << left << setw(25) << "总人数N应为正整数！" << endl;
		cout << left << setw(25) << "请重新输入总人数N：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> N;
	}
	cout << left << setw(25) << "请输入游戏开始的位置S：";
	cin >> S;
	while (cin.fail() || S <= 0)
	{
		cout << left << setw(25) << "开始的位置S应为正整数！" << endl;
		cout << left << setw(25) << "请重新输入开始的位置S：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> S;
	}
	cout << left << setw(25) << "请输入死亡数字M：";
	cin >> M;
	while (cin.fail() || M <= 0)
	{
		cout << left << setw(25) << "死亡数字M应为正整数！" << endl;
		cout << left << setw(25) << "请重新输入死亡数字M：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> M;
	}
	cout << left << setw(25) << "请输入剩余的生者人数K：";
	cin >> K;
	while (cin.fail() || K <= 0 || K > N)
	{
		cout << left << setw(25) << "剩余生者人数K应为正整数且不大于总人数N！" << endl;
		cout << left << setw(25) << "请重新输入剩余生者人数K：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> K;
	}
	cout << endl;
	this->numbers = N;
	this->start = S;
	this->death = M;
	this->live = K;
}

void JosephusGame::insertPerson()
{
	//依次给numbers个玩家编号，从1到numbers插入链表
	for (int i = 1; i <= numbers; i++)
	{
		linklist.appendElem(i, i);
	}
}

void JosephusGame::killPerson()
{
	Node<int>* startNode = linklist.getHead()->getNext();
	Node<int>* tempStartNode = nullptr;
	int popNodeNumberID = 0;
	int deathNumber = 0;
	//先找到开始的节点
	for (int i = 1; i < start; i++)
	{
		startNode = startNode->getNext();
		//如果是头结点，那么不计数
		if (startNode == linklist.getHead())
		{
			i--;
		}
	}
	//未达到最终剩余人数时，执行删除操作
	while (linklist.getSize() > live)
	{	
		for (int i = 1; i < death; i++)
		{
			//如果是头结点，那么不计数
			if (startNode == linklist.getHead())
			{
				i--;
			}
			startNode = startNode->getNext();			
		}
		if (startNode == linklist.getHead())
		{
			startNode = startNode->getNext();
		}
		deathNumber += 1;
		popNodeNumberID = startNode->getNumberID();
		cout << "第" << deathNumber <<  "个死者的位置是：\t" << popNodeNumberID << endl;
		//用于暂存当前的下一个指针
		tempStartNode = startNode->getNext();
		linklist.popElem(popNodeNumberID);
		startNode = tempStartNode;
	}
	cout << endl;
}

void JosephusGame::showLivers()
{
	Node<int>* current = linklist.getHead();
	cout << "最后剩下：\t" << linklist.getSize() << "人" << endl;
	cout << "剩余的生者位置为：";
	for (int i = 0; i < linklist.getSize(); i++)
	{
		current = current->getNext();
		cout << setw(7) << current->getNumberID();
	}
	cout << endl;
}

int main()
{
	//建立约瑟夫游戏类并对其进行插入、删除、展示生者
	JosephusGame game = JosephusGame();
	game.insertPerson();
	game.killPerson();
	game.showLivers();

# ifdef _WIN32
	system("pause");
# endif
	return 0;
}