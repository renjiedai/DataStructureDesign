#include <iostream>
#include <string>
#include <limits>

using namespace std;

//自定义一个Vector类
template <typename T>
class Vector {
public:
	~Vector();
	Vector();
	//运算符重载[]
	T& operator[](const int x);
	const T& operator[](const int x)const;
	Vector<T>(const Vector<T>& rhs);
	Vector<T>& operator=(const Vector<T>& rhs);
	//判断是否已经满了
	bool isFull();
	//判断是否为空
	bool isEmpty();
	//插入一个元素
	void pushBack(const T& temp);
	//删除末尾元素
	void popBack();
	//清空Vector
	void clear();
	//get函数
	int getSize();
	//重新设置容量
	void reSize(int newSize);
private:
	void extendSize();
	int size;
	int maxSize;
	T* myVector;
};

template<typename T>
Vector<T>::Vector()
{
	size = 0;
	maxSize = 0;
	myVector = nullptr;
}

template<typename T>
Vector<T>::~Vector()
{
	clear();
}

template<typename T>
T& Vector<T>::operator[](const int index)
{
	return *(myVector + index);
}


template<typename T>
const T& Vector<T>::operator[](const int index)const
{
	return *(myVector + index);
}

template<typename T>
Vector<T>::Vector(const Vector<T>& rhs)
{
	operator=(rhs);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
{
	size = rhs.size;
	maxSize = rhs.maxSize;
	myVector = new T[maxSize];
	for (int i = 0; i < size; i++)
	{
		myVector[i] = rhs[i];
	}
	return *this;
}

template<typename T>
void Vector<T>::extendSize()
{
	//扩大容量到原来2倍+1
	T* temp = new T[maxSize * 2 + 1];
	maxSize = maxSize * 2 + 1;
	for (int i = 0; i < size; i++)
	{
		temp[i] = myVector[i];
	}
	delete[]myVector;
	myVector = temp;
}

template<typename T>
bool Vector<T>::isFull()
{
	if (size == maxSize)
	{
		return true;
	}
	return false;
}

template<typename T>
bool Vector<T>::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	return false;
}


template<typename T>
void Vector<T>::pushBack(const T& temp)
{
	if (isFull())
	{
		extendSize();
	}
	myVector[size++] = temp;
}

template<typename T>
void Vector<T>::popBack()
{
	if (!isEmpty())
	{
		size--;
	}
}

template<typename T>
void Vector<T>::clear()
{
	delete[] myVector;
	myVector = nullptr;
	size = 0;
	maxSize = 0;
}

template<typename T>
int Vector<T>::getSize()
{
	return size;
}

template<typename T>
void Vector<T>::reSize(int newSize)
{
	T* temp = new T[newSize + 1];
	if (newSize >= size)
	{
		for (int i = 0; i < size; i++)
		{
			temp[i] = myVector[i];
		}
	}
	else
	{
		for (int i = 0; i < newSize; i++)
		{
			temp[i] = myVector[i];
		}
	}
	clear();
	myVector = temp;
	maxSize = newSize + 1;
	size = newSize;
}




//堆类，用于获取权值最小的边
template<typename T>
class Heap {
public:
	//构造函数与析构函数
	Heap() = default;
	~Heap();
	//获得堆的大小
	int getSize();
	//建立堆
	void build(Vector<T>& everyLength);
	//向堆中插入元素
	void insert(const T& inputData);
	//弹出堆中的元素
	bool pop();
	//获得堆顶元素
	T getTop();
	//清空堆中所有元素，释放内存
	void makeEmpty();
private:
	//用于存储数据
	Vector<T> data;
	//从start下滑调整堆中数据
	void siftDown(int start, int max);
	//从堆中最后一个位置上滑调整数据
	void siftUp(int start);
};

template<typename T>
void Heap<T>::siftUp(int start)
{
	//存储当前位置
	int current = start;
	int parent = (current - 1) / 2;
	//存储当前位置的数据
	T temp = data[current];
	//循环找要交换的位置
	while (current > 0)
	{
		//父节点不大于自己，说明位置已经不用调整，跳出
		if (data[parent]->getCost() <= temp->getCost())
		{
			break;
		}
		else
		{
			//否则将自己的数值赋值为父节点的值
			data[current] = data[parent];
			//并继续循环寻找自己数值应在的位置
			current = parent;
			parent = (parent - 1) / 2;
		}
	}
	//找到了位置，完成调整
	data[current] = temp;
}

template<typename T>
void Heap<T>::siftDown(int start, int max)
{
	//从当前位置开始
	int current = start;
	//找小孩子
	int lessChild = 2 * current + 1;
	//当前节点的值存入temp
	T temp = data[current];
	while (lessChild <= max)
	{
		if (lessChild < max)
		{
			//先找到较小孩子的下标
			if (data[lessChild]->getCost() > data[lessChild + 1]->getCost())
			{
				lessChild++;
			}
		}
		//根节点比较小的孩子节点小，跳出循环
		if (temp->getCost() <= data[lessChild]->getCost())
		{
			break;
		}
		//否则当前节点的值赋值为较小孩子的值，并且继续往下判断是否符合堆的条件
		else
		{
			data[current] = data[lessChild];
			current = lessChild;
			lessChild = 2 * lessChild + 1;
		}
	}
	//将原来的值给找到的正确位置，完成交换调整
	data[current] = temp;
}

template<typename T>
Heap<T>::~Heap()
{
	makeEmpty();
}

template<typename T>
int Heap<T>::getSize()
{
	return data.getSize();
}

template<typename T>
void Heap<T>::build(Vector<T>& everyLength)
{
	//先插入所有数据
	for (int i = 0; i < everyLength.getSize(); i++)
	{
		data.pushBack(everyLength[i]);
	}
	//然后依次调整每一个数据
	int currentPos = (getSize() - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, getSize() - 1);
		currentPos--;
	}
}

template<typename T>
void Heap<T>::insert(const T& inputData)
{
	//插入元素
	data.pushBack(inputData);
	//插入新元素后向上调整
	siftUp(getSize() - 1);
}

template<typename T>
bool Heap<T>::pop()
{
	//没有元素，直接返回false
	if (getSize() == 0)
	{
		return false;
	}
	//将最后一个赋值到0号位置
	data[0] = data[getSize() - 1];
	data.popBack();
	//下滑调整
	siftDown(0, getSize() - 1);
	return true;
}

template<typename T>
T Heap<T>::getTop()
{
	return data[0];
}

template<typename T>
void Heap<T>::makeEmpty()
{
	data.clear();
}



template<typename NameT, typename DataT>
class Vertex;
//边类，表示图的边
template<typename NameT, typename DataT>
class Edge {
public:
	Edge() = default;
	Edge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight);
	//get函数和set函数
	Vertex<NameT, DataT>* getCurrentVertex();
	Vertex<NameT, DataT>* getDestVertex();
	DataT getCost();
	Edge<NameT, DataT>* getNext();
	void setCurrentVertex(Vertex<NameT, DataT>* inputCurrentVertex);
	void setDestVertex(Vertex<NameT, DataT>* inputDestVertex);
	void setNext(Edge<NameT, DataT>* inputNext);
	void setCost(DataT& inputCost);
private:
	//边的两个顶点
	Vertex<NameT, DataT>* currentVertex = nullptr;
	Vertex<NameT, DataT>* destVertex = nullptr;
	//边的权重(造价)
	DataT cost;
	//边的下一条边
	Edge<NameT, DataT>* next = nullptr;
};

template<typename NameT, typename DataT>
Edge<NameT, DataT>::Edge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight)
{
	this->currentVertex = currentVertex;
	this->destVertex = destVertex;
	this->cost = weight;
}

template<typename NameT, typename DataT>
Vertex<NameT, DataT>* Edge<NameT, DataT>::getCurrentVertex()
{
	return this->currentVertex;
}

template<typename NameT, typename DataT>
Vertex<NameT, DataT>* Edge<NameT, DataT>::getDestVertex()
{
	return this->destVertex;
}

template<typename NameT, typename DataT>
DataT Edge<NameT, DataT>::getCost()
{
	return this->cost;
}

template<typename NameT, typename DataT>
Edge<NameT, DataT>* Edge<NameT, DataT>::getNext()
{
	return this->next;
}

template<typename NameT, typename DataT>
void Edge<NameT, DataT>::setCurrentVertex(Vertex<NameT, DataT>* inputCurrentVertex)
{
	this->currentVertex = inputCurrentVertex;
}

template<typename NameT, typename DataT>
void Edge<NameT, DataT>::setDestVertex(Vertex<NameT, DataT>* inputDestVertex)
{
	this->destVertex = inputDestVertex;
}

template<typename NameT, typename DataT>
void Edge<NameT, DataT>::setNext(Edge<NameT, DataT>* inputNext)
{
	this->next = inputNext;
}

template<typename NameT, typename DataT>
void Edge<NameT, DataT>::setCost(DataT& inputCost)
{
	this->cost = inputCost;
}




template<typename NameT, typename DataT>
class Vertex {
public:
	Vertex() = default;
	Vertex(NameT inputName);
	//get和set函数
	NameT getName();
	Edge<NameT, DataT>* getHead();
	bool getSelected();
	void setName(NameT inputName);
	void setHead(Edge<NameT, DataT>* inputHead);
	void setSelected(bool inputSlected);
private:
	//顶点名字
	NameT name;
	//顶点的第一个边指针
	Edge<NameT, DataT>* head = nullptr;
	//记录该节点是否已经被选中
	bool selected = false;
};

template<typename NameT, typename DataT>
Vertex<NameT, DataT>::Vertex(NameT inputName)
{
	this->name = inputName;
}

template<typename NameT, typename DataT>
NameT Vertex<NameT, DataT>::getName()
{
	return this->name;
}

template<typename NameT, typename DataT>
Edge<NameT, DataT>* Vertex<NameT, DataT>::getHead()
{
	return this->head;
}

template<typename NameT, typename DataT>
bool Vertex<NameT, DataT>::getSelected()
{
	return this->selected;
}

template<typename NameT, typename DataT>
void Vertex<NameT, DataT>::setName(NameT inputName)
{
	this->name = inputName;
}

template<typename NameT, typename DataT>
void Vertex<NameT, DataT>::setHead(Edge<NameT, DataT>* inputHead)
{
	this->head = inputHead;
}

template<typename NameT, typename DataT>
void Vertex<NameT, DataT>::setSelected(bool inputSlected)
{
	this->selected = inputSlected;
}

template<typename NameT, typename DataT>
class Graph {
public:
	Graph() = default;
	//析构函数，释放内存
	~Graph();
	//清空图中的边
	void clearGraph();
	//清空图中的顶点
	void clearVertex();
	//通过名字寻找顶点
	Vertex<NameT, DataT>* findVertexByName(NameT vertexName);
	//插入顶点
	void insertVertex(NameT inputVertexName);
	//插入边
	void insertEdge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight);
	//get函数，获得顶点表
	Vector<Vertex<NameT, DataT>*> getVertexTable();
private:
	//顶点表
	Vector<Vertex<NameT, DataT>*> vertexTable;
};

template<typename NameT, typename DataT>
Graph<NameT, DataT>::~Graph()
{
	//清除图，释放内存
	clearGraph();
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::clearGraph()
{
	//指向节点和边的指针
	Vertex<NameT, DataT>* tempVertex = nullptr;
	Edge<NameT, DataT>* tempCurrentEdge = nullptr;
	Edge<NameT, DataT>* tempNextEdge = nullptr;
	//对每个节点，删除其所有的边
	for (int i = 0; i < vertexTable.getSize(); i++)
	{
		tempVertex = vertexTable[i];
		tempCurrentEdge = tempVertex->getHead();
		while (tempCurrentEdge != nullptr)
		{
			tempNextEdge = tempCurrentEdge->getNext();
			delete tempCurrentEdge;
			tempCurrentEdge = tempNextEdge;
		}
	}
	return;
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::clearVertex()
{
	this->vertexTable.clear();
}

template<typename NameT, typename DataT>
Vertex<NameT, DataT>* Graph<NameT, DataT>::findVertexByName(NameT vertexName)
{
	//从顶点表中遍历，如果找到则返回顶点
	for (int i = 0; i < vertexTable.getSize(); i++)
	{
		if (vertexTable[i]->getName() == vertexName)
		{
			return vertexTable[i];
		}
	}
	//没有找到则返回空指针
	return nullptr;
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::insertVertex(NameT inputVertexName)
{
	//新建顶点
	Vertex<NameT, DataT>* newVertex = new Vertex<NameT, DataT>(inputVertexName);
	//插入顶点
	vertexTable.pushBack(newVertex);
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::insertEdge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight)
{
	//暂存要插入边的两个端点
	Vertex<NameT, DataT>* tempCurrentVertex = currentVertex;
	Vertex<NameT, DataT>* tempDestVertex = destVertex;
	Edge<NameT, DataT>* tempEdge = tempCurrentVertex->getHead();
	//第一个点没有边，则要插入的边为其首边
	if (tempEdge == nullptr)
	{
		Edge<NameT, DataT>* newEdge = new Edge<NameT, DataT>(currentVertex, destVertex, weight);
		tempCurrentVertex->setHead(newEdge);
	}
	//否者一直向后找，直到找到没有边为止
	else
	{
		while (tempEdge->getNext() != nullptr)
		{
			tempEdge = tempEdge->getNext();
		}
		//插入新的边
		Edge<NameT, DataT>* newEdge = new Edge<NameT, DataT>(currentVertex, destVertex, weight);
		tempEdge->setNext(newEdge);
	}
	//对边的另一个端点也进行同样处理
	tempEdge = tempDestVertex->getHead();
	if (tempEdge == nullptr)
	{
		Edge<NameT, DataT>* newEdge = new Edge<NameT, DataT>(destVertex, currentVertex, weight);
		tempDestVertex->setHead(newEdge);
	}
	else
	{
		while (tempEdge->getNext() != nullptr)
		{
			tempEdge = tempEdge->getNext();
		}
		//插入新的边
		Edge<NameT, DataT>* newEdge = new Edge<NameT, DataT>(destVertex, currentVertex, weight);
		tempEdge->setNext(newEdge);
	}
	return;
}

template<typename NameT, typename DataT>
Vector<Vertex<NameT, DataT>*> Graph<NameT, DataT>::getVertexTable()
{
	return this->vertexTable;
}


//电网造价系统类，实现各项功能
class PowerGridCostSystem
{
public:
	//显示菜单
	void showMenu();
	//建立电网
	void buildPowerGrid();
	//添加电网的边
	void addPowerGridEdge();
	//Prim算法求最小生成树
	void costMinByPrim();
	//展示结果
	void showResult();
	//启动电网造价系统
	void runPowerGridCostSystem();
private:
	//检查输入的顶点名字是否已经存在
	bool isVertexExist(Vector<string>& vertexName);
	//检查指定两顶点间输入的边是否已经存在
	bool isEdgeExist(Vertex<string, int>* currentVertex, Vertex<string, int>* destVertex);
	//返回最大能有的边的数目
	int getMaxAddEdge();

	int currentEdgeNumber = 0;
	Graph<string, int> powerGrid;
	Vector<Edge<string, int>*> result;
};

void PowerGridCostSystem::showMenu()
{
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA---创建电网顶点\t\t**" << endl;
	cout << "**\t\tB---添加电网的边\t\t**" << endl;
	cout << "**\t\tC---构造最小生成树\t\t**" << endl;
	cout << "**\t\tD---显示最小生成树\t\t**" << endl;
	cout << "**\t\tE---退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void PowerGridCostSystem::buildPowerGrid()
{
	//初始化
	powerGrid.clearGraph();
	powerGrid.clearVertex();
	currentEdgeNumber = 0;
	result.clear();
	//顶点个数
	int vertexNumber = 0;
	//存储定点名字的Vector数组
	Vector<string> vertexName;
	cout << "请输入电网顶点的个数:";
	cin >> vertexNumber;
	//检验输入的合法性，增强程序的健壮性
	while (vertexNumber <= 0 || cin.fail())
	{
		cout << "电网顶点的个数只能是正整数!" << endl;
		cout << "请重新输入电网顶点个数:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> vertexNumber;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vertexName.reSize(vertexNumber);
	//输入顶点名字，存入Vector
	cout << "请依次输入电网各顶点的名称:" << endl;
	for (int i = 0; i < vertexNumber; i++)
	{
		cin >> vertexName[i];
	}
	//检查输入的名字是否有重名现象
	while (isVertexExist(vertexName))
	{
		cout << "创建的新顶点中含有重复的名称!" << endl;
		cout << "请重新依次输入各顶点的名称:" << endl;
		for (int i = 0; i < vertexNumber; i++)
		{
			cin >> vertexName[i];
		}
	}
	//向电网图中加入元素
	for (int i = 0; i < vertexNumber; i++)
	{
		powerGrid.insertVertex(vertexName[i]);
	}
}

void PowerGridCostSystem::addPowerGridEdge()
{
	//边对应的两个顶点的名字
	string name1;
	string name2;
	//两个顶点指针
	Vertex<string, int>* vertex1 = nullptr;
	Vertex<string, int>* vertex2 = nullptr;
	//边的权重
	int weight = 0;
	//本次要加入的边数
	int edgeNumber = 0;
	//条件判断，防止要添加的边数目过多，增强程序健壮性
	if (currentEdgeNumber >= getMaxAddEdge())
	{
		cout << "目前边的个数已至最大值，无法再添加！" << endl;
		return;
	}
	cout << "请输入添加边的个数:";
	cin >> edgeNumber;
	//错误处理，对输入错误或者输入的边数过多进行处理
	while (edgeNumber <= 0 || cin.fail() || edgeNumber > (getMaxAddEdge() - currentEdgeNumber))
	{
		//边输入错误
		if (edgeNumber <= 0 || cin.fail())
		{
			cout << "边的个数只能是正整数!" << endl;
		}
		//数量输入错误
		else
		{
			cout << "输入后边的数量会超过最大值!" << endl;
		}
		cout << "请重新输入边个数:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> edgeNumber;
	}
	//电网系统的边数增加
	currentEdgeNumber += edgeNumber;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < edgeNumber; i++)
	{
		//输入两个顶点与边的权重
		cout << "请输入两个顶点及边:";
		while (true)
		{
			cin >> name1 >> name2 >> weight;
			vertex1 = powerGrid.findVertexByName(name1);
			vertex2 = powerGrid.findVertexByName(name2);
			//对输入的顶点进行检查，进行错误处理
			if (name1 == name2)
			{
				cout << "输入的两个顶点相同!";
			}
			else if (vertex1 == nullptr)
			{
				cout << "第一个顶点不存在!";
			}
			else if (vertex2 == nullptr)
			{
				cout << "第二个顶点不存在!";
			}
			else if (weight <= 0 || cin.fail())
			{
				cout << "每一条边的花费必须是正整数!";
			}
			//边合法的情况
			else
			{
				//如果点未存在，就插入点，跳出循环
				if (!isEdgeExist(vertex1, vertex2))
				{
					powerGrid.insertEdge(vertex1, vertex2, weight);
					break;
				}
				//否则提升两顶点以及存在边，重新输入
				else
				{
					cout << "此两个顶点之间已经存在边!";
				}
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl;
			cout << "请重新输入两个顶点及边:";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return;
}

void PowerGridCostSystem::costMinByPrim()
{
	//系统顶点为0，直接返回
	if (powerGrid.getVertexTable().getSize() == 0)
	{
		cout << "系统中没有顶点!" << endl;
		return;
	}
	//系统只有一个顶点，意味着没有边，也不需要边
	else if (powerGrid.getVertexTable().getSize() == 1)
	{
		cout << "系统中没有边!" << endl;
		return;
	}
	//存储顶点个数
	int vertexNumber = powerGrid.getVertexTable().getSize();
	//记录已经插入的顶点个数
	int count = 1;
	//定义两个边类指针暂存下一个边以及最小边
	Edge<string, int>* nextEdge = nullptr;
	Edge<string, int>* minEdge = nullptr;
	//起始顶点(根节点)的名字
	string init;
	//查找最小边用的堆
	Heap<Edge<string, int>*> heap;
	//起始顶点(根节点)
	Vertex<string, int>* initVertex = nullptr;
	//清空节点
	result.clear();
	//将图中的顶点selected全部设置为false，为调用做准备
	for (int i = 0; i < vertexNumber; i++)
	{
		powerGrid.getVertexTable()[i]->setSelected(false);
	}
	//输入起始顶点
	cout << "请输入起始顶点:";
	cin >> init;
	//查找起始顶点
	initVertex = powerGrid.findVertexByName(init);
	//错误处理语句，增强程序的健壮性
	while (initVertex == nullptr)
	{
		cout << "此顶点不在系统之中!" << endl;
		cout << "请重新输入：";
		cin >> init;
		initVertex = powerGrid.findVertexByName(init);
	}
	//初始顶点设置为被选中
	initVertex->setSelected(true);
	//顶点尚未选择完成的时候，执行循环
	while (count < vertexNumber)
	{
		//寻找与起始顶点相连且未被选中的所有顶点，并将其放入堆
		nextEdge = initVertex->getHead();
		while (nextEdge != nullptr)
		{
			if (nextEdge->getDestVertex()->getSelected() == false)
			{
				heap.insert(nextEdge);
			}
			nextEdge = nextEdge->getNext();
		}
		//错误处理，如果没有找到相连且未被选中的顶点，说明电力系统尚未联通
		if (heap.getSize() == 0)
		{
			cout << "目前的电力系统并未连通!" << endl;
			return;
		}
		while (heap.getSize() != 0)
		{
			//选出最小边，放入result储存
			minEdge = heap.getTop();
			if (minEdge->getDestVertex()->getSelected() == false)
			{
				//最小边对应的另一半顶点selected设为true
				minEdge->getDestVertex()->setSelected(true);
				//另一个顶点当做初始点继续搜寻
				initVertex = minEdge->getDestVertex();
				//放入result结果
				result.pushBack(minEdge);
				//弹出堆
				heap.pop();
				count++;
				break;
			}
			else
			{
				heap.pop();
			}
		}
	}
	cout << "生成Prim最小生成树!" << endl;
	return;
}

void PowerGridCostSystem::showResult()
{
	//结果中边的数目小于顶点-1或者顶点数目仅为1，最小生成树未成功生成
	if ((result.getSize() != (powerGrid.getVertexTable().getSize() - 1)) || (powerGrid.getVertexTable().getSize() == 1))
	{
		cout << "最小生成树未成功生成!" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为:" << endl;
	//依次输出结果
	for (int i = 0; i < result.getSize(); i++)
	{
		if (i % 4 == 0)
		{
			cout << endl;
		}
		cout << result[i]->getCurrentVertex()->getName() << "-<" << result[i]->getCost() << ">-" << result[i]->getDestVertex()->getName() << "    ";
	}
	return;
}

void PowerGridCostSystem::runPowerGridCostSystem()
{
	//显示菜单
	showMenu();
	//存储输入的命令，使用string提升cin的健壮性
	string cmmand;
	while (true)
	{
		cout << endl;
		cout << "请选择操作：";
		cin >> cmmand;
		switch (cmmand[0])
		{
		case 'A':
			//建立电网系统
			buildPowerGrid();
			break;
		case 'B':
			//给电网系统增加边
			addPowerGridEdge();
			break;
		case 'C':
			//建立最小生成树
			costMinByPrim();
			break;
		case 'D':
			//展示结果
			showResult();
			break;
		case 'E':
			cout << "成功退出系统！" << endl;
			return;
		default:
			cout << "操作数输入不正确，请重新输入!";
			break;
		}
	}
}

bool PowerGridCostSystem::isVertexExist(Vector<string>& vertexName)
{
	//检查Vector内部是否有重名的
	for (int i = 0; i < vertexName.getSize() - 1; i++)
	{
		for (int j = i + 1; j < vertexName.getSize(); j++)
		{
			if (vertexName[i] == vertexName[j])
			{
				return true;
			}
		}
	}
	//检查Vector内顶点与电网已存在顶点点是否有重名
	for (int i = 0; i < vertexName.getSize(); i++)
	{
		if (powerGrid.findVertexByName(vertexName[i]) != nullptr)
		{
			cout << "存在新顶点名称与系统中已存在的顶点名称重复!" << endl;
			return true;
		}
	}
	return false;
}

bool PowerGridCostSystem::isEdgeExist(Vertex<string, int>* currentVertex, Vertex<string, int>* destVertex)
{
	Vertex<string, int>* tempCurrentVertex = currentVertex;
	Edge<string, int>* tempCurrentEdge = tempCurrentVertex->getHead();
	while (tempCurrentEdge != nullptr)
	{
		//已经有了边，返回true
		if (tempCurrentEdge->getDestVertex()->getName() == destVertex->getName())
		{
			return true;
		}
		//否则继续寻找直到当前顶点的所有相连顶点都被寻找
		tempCurrentEdge = tempCurrentEdge->getNext();
	}
	//没有找到，返回false
	return false;
}

int PowerGridCostSystem::getMaxAddEdge()
{
	//先获得最大的顶点数
	int vertexNumber = powerGrid.getVertexTable().getSize();
	//最大边数即完全图边数为maxEdge
	int maxEdge = (vertexNumber - 1) * vertexNumber / 2;
	return maxEdge;
}


int main()
{
	//电网造价系统
	PowerGridCostSystem powerGridCostSystem;
	//运行电网造价系统
	powerGridCostSystem.runPowerGridCostSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}


