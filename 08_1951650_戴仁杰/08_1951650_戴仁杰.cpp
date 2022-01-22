#include <iostream>
#include <string>
#include <limits>

using namespace std;

//�Զ���һ��Vector��
template <typename T>
class Vector {
public:
	~Vector();
	Vector();
	//���������[]
	T& operator[](const int x);
	const T& operator[](const int x)const;
	Vector<T>(const Vector<T>& rhs);
	Vector<T>& operator=(const Vector<T>& rhs);
	//�ж��Ƿ��Ѿ�����
	bool isFull();
	//�ж��Ƿ�Ϊ��
	bool isEmpty();
	//����һ��Ԫ��
	void pushBack(const T& temp);
	//ɾ��ĩβԪ��
	void popBack();
	//���Vector
	void clear();
	//get����
	int getSize();
	//������������
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
	//����������ԭ��2��+1
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




//���࣬���ڻ�ȡȨֵ��С�ı�
template<typename T>
class Heap {
public:
	//���캯������������
	Heap() = default;
	~Heap();
	//��öѵĴ�С
	int getSize();
	//������
	void build(Vector<T>& everyLength);
	//����в���Ԫ��
	void insert(const T& inputData);
	//�������е�Ԫ��
	bool pop();
	//��öѶ�Ԫ��
	T getTop();
	//��ն�������Ԫ�أ��ͷ��ڴ�
	void makeEmpty();
private:
	//���ڴ洢����
	Vector<T> data;
	//��start�»�������������
	void siftDown(int start, int max);
	//�Ӷ������һ��λ���ϻ���������
	void siftUp(int start);
};

template<typename T>
void Heap<T>::siftUp(int start)
{
	//�洢��ǰλ��
	int current = start;
	int parent = (current - 1) / 2;
	//�洢��ǰλ�õ�����
	T temp = data[current];
	//ѭ����Ҫ������λ��
	while (current > 0)
	{
		//���ڵ㲻�����Լ���˵��λ���Ѿ����õ���������
		if (data[parent]->getCost() <= temp->getCost())
		{
			break;
		}
		else
		{
			//�����Լ�����ֵ��ֵΪ���ڵ��ֵ
			data[current] = data[parent];
			//������ѭ��Ѱ���Լ���ֵӦ�ڵ�λ��
			current = parent;
			parent = (parent - 1) / 2;
		}
	}
	//�ҵ���λ�ã���ɵ���
	data[current] = temp;
}

template<typename T>
void Heap<T>::siftDown(int start, int max)
{
	//�ӵ�ǰλ�ÿ�ʼ
	int current = start;
	//��С����
	int lessChild = 2 * current + 1;
	//��ǰ�ڵ��ֵ����temp
	T temp = data[current];
	while (lessChild <= max)
	{
		if (lessChild < max)
		{
			//���ҵ���С���ӵ��±�
			if (data[lessChild]->getCost() > data[lessChild + 1]->getCost())
			{
				lessChild++;
			}
		}
		//���ڵ�Ƚ�С�ĺ��ӽڵ�С������ѭ��
		if (temp->getCost() <= data[lessChild]->getCost())
		{
			break;
		}
		//����ǰ�ڵ��ֵ��ֵΪ��С���ӵ�ֵ�����Ҽ��������ж��Ƿ���϶ѵ�����
		else
		{
			data[current] = data[lessChild];
			current = lessChild;
			lessChild = 2 * lessChild + 1;
		}
	}
	//��ԭ����ֵ���ҵ�����ȷλ�ã���ɽ�������
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
	//�Ȳ�����������
	for (int i = 0; i < everyLength.getSize(); i++)
	{
		data.pushBack(everyLength[i]);
	}
	//Ȼ�����ε���ÿһ������
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
	//����Ԫ��
	data.pushBack(inputData);
	//������Ԫ�غ����ϵ���
	siftUp(getSize() - 1);
}

template<typename T>
bool Heap<T>::pop()
{
	//û��Ԫ�أ�ֱ�ӷ���false
	if (getSize() == 0)
	{
		return false;
	}
	//�����һ����ֵ��0��λ��
	data[0] = data[getSize() - 1];
	data.popBack();
	//�»�����
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
//���࣬��ʾͼ�ı�
template<typename NameT, typename DataT>
class Edge {
public:
	Edge() = default;
	Edge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight);
	//get������set����
	Vertex<NameT, DataT>* getCurrentVertex();
	Vertex<NameT, DataT>* getDestVertex();
	DataT getCost();
	Edge<NameT, DataT>* getNext();
	void setCurrentVertex(Vertex<NameT, DataT>* inputCurrentVertex);
	void setDestVertex(Vertex<NameT, DataT>* inputDestVertex);
	void setNext(Edge<NameT, DataT>* inputNext);
	void setCost(DataT& inputCost);
private:
	//�ߵ���������
	Vertex<NameT, DataT>* currentVertex = nullptr;
	Vertex<NameT, DataT>* destVertex = nullptr;
	//�ߵ�Ȩ��(���)
	DataT cost;
	//�ߵ���һ����
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
	//get��set����
	NameT getName();
	Edge<NameT, DataT>* getHead();
	bool getSelected();
	void setName(NameT inputName);
	void setHead(Edge<NameT, DataT>* inputHead);
	void setSelected(bool inputSlected);
private:
	//��������
	NameT name;
	//����ĵ�һ����ָ��
	Edge<NameT, DataT>* head = nullptr;
	//��¼�ýڵ��Ƿ��Ѿ���ѡ��
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
	//�����������ͷ��ڴ�
	~Graph();
	//���ͼ�еı�
	void clearGraph();
	//���ͼ�еĶ���
	void clearVertex();
	//ͨ������Ѱ�Ҷ���
	Vertex<NameT, DataT>* findVertexByName(NameT vertexName);
	//���붥��
	void insertVertex(NameT inputVertexName);
	//�����
	void insertEdge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight);
	//get��������ö����
	Vector<Vertex<NameT, DataT>*> getVertexTable();
private:
	//�����
	Vector<Vertex<NameT, DataT>*> vertexTable;
};

template<typename NameT, typename DataT>
Graph<NameT, DataT>::~Graph()
{
	//���ͼ���ͷ��ڴ�
	clearGraph();
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::clearGraph()
{
	//ָ��ڵ�ͱߵ�ָ��
	Vertex<NameT, DataT>* tempVertex = nullptr;
	Edge<NameT, DataT>* tempCurrentEdge = nullptr;
	Edge<NameT, DataT>* tempNextEdge = nullptr;
	//��ÿ���ڵ㣬ɾ�������еı�
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
	//�Ӷ�����б���������ҵ��򷵻ض���
	for (int i = 0; i < vertexTable.getSize(); i++)
	{
		if (vertexTable[i]->getName() == vertexName)
		{
			return vertexTable[i];
		}
	}
	//û���ҵ��򷵻ؿ�ָ��
	return nullptr;
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::insertVertex(NameT inputVertexName)
{
	//�½�����
	Vertex<NameT, DataT>* newVertex = new Vertex<NameT, DataT>(inputVertexName);
	//���붥��
	vertexTable.pushBack(newVertex);
}

template<typename NameT, typename DataT>
void Graph<NameT, DataT>::insertEdge(Vertex<NameT, DataT>* currentVertex, Vertex<NameT, DataT>* destVertex, DataT weight)
{
	//�ݴ�Ҫ����ߵ������˵�
	Vertex<NameT, DataT>* tempCurrentVertex = currentVertex;
	Vertex<NameT, DataT>* tempDestVertex = destVertex;
	Edge<NameT, DataT>* tempEdge = tempCurrentVertex->getHead();
	//��һ����û�бߣ���Ҫ����ı�Ϊ���ױ�
	if (tempEdge == nullptr)
	{
		Edge<NameT, DataT>* newEdge = new Edge<NameT, DataT>(currentVertex, destVertex, weight);
		tempCurrentVertex->setHead(newEdge);
	}
	//����һֱ����ң�ֱ���ҵ�û�б�Ϊֹ
	else
	{
		while (tempEdge->getNext() != nullptr)
		{
			tempEdge = tempEdge->getNext();
		}
		//�����µı�
		Edge<NameT, DataT>* newEdge = new Edge<NameT, DataT>(currentVertex, destVertex, weight);
		tempEdge->setNext(newEdge);
	}
	//�Աߵ���һ���˵�Ҳ����ͬ������
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
		//�����µı�
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


//�������ϵͳ�࣬ʵ�ָ����
class PowerGridCostSystem
{
public:
	//��ʾ�˵�
	void showMenu();
	//��������
	void buildPowerGrid();
	//��ӵ����ı�
	void addPowerGridEdge();
	//Prim�㷨����С������
	void costMinByPrim();
	//չʾ���
	void showResult();
	//�����������ϵͳ
	void runPowerGridCostSystem();
private:
	//�������Ķ��������Ƿ��Ѿ�����
	bool isVertexExist(Vector<string>& vertexName);
	//���ָ�������������ı��Ƿ��Ѿ�����
	bool isEdgeExist(Vertex<string, int>* currentVertex, Vertex<string, int>* destVertex);
	//����������еıߵ���Ŀ
	int getMaxAddEdge();

	int currentEdgeNumber = 0;
	Graph<string, int> powerGrid;
	Vector<Edge<string, int>*> result;
};

void PowerGridCostSystem::showMenu()
{
	cout << "**\t\t�������ģ��ϵͳ\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
	cout << "**\t\tA---������������\t\t**" << endl;
	cout << "**\t\tB---��ӵ����ı�\t\t**" << endl;
	cout << "**\t\tC---������С������\t\t**" << endl;
	cout << "**\t\tD---��ʾ��С������\t\t**" << endl;
	cout << "**\t\tE---�˳�����\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void PowerGridCostSystem::buildPowerGrid()
{
	//��ʼ��
	powerGrid.clearGraph();
	powerGrid.clearVertex();
	currentEdgeNumber = 0;
	result.clear();
	//�������
	int vertexNumber = 0;
	//�洢�������ֵ�Vector����
	Vector<string> vertexName;
	cout << "�������������ĸ���:";
	cin >> vertexNumber;
	//��������ĺϷ��ԣ���ǿ����Ľ�׳��
	while (vertexNumber <= 0 || cin.fail())
	{
		cout << "��������ĸ���ֻ����������!" << endl;
		cout << "��������������������:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> vertexNumber;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vertexName.reSize(vertexNumber);
	//���붥�����֣�����Vector
	cout << "������������������������:" << endl;
	for (int i = 0; i < vertexNumber; i++)
	{
		cin >> vertexName[i];
	}
	//�������������Ƿ�����������
	while (isVertexExist(vertexName))
	{
		cout << "�������¶����к����ظ�������!" << endl;
		cout << "������������������������:" << endl;
		for (int i = 0; i < vertexNumber; i++)
		{
			cin >> vertexName[i];
		}
	}
	//�����ͼ�м���Ԫ��
	for (int i = 0; i < vertexNumber; i++)
	{
		powerGrid.insertVertex(vertexName[i]);
	}
}

void PowerGridCostSystem::addPowerGridEdge()
{
	//�߶�Ӧ���������������
	string name1;
	string name2;
	//��������ָ��
	Vertex<string, int>* vertex1 = nullptr;
	Vertex<string, int>* vertex2 = nullptr;
	//�ߵ�Ȩ��
	int weight = 0;
	//����Ҫ����ı���
	int edgeNumber = 0;
	//�����жϣ���ֹҪ��ӵı���Ŀ���࣬��ǿ����׳��
	if (currentEdgeNumber >= getMaxAddEdge())
	{
		cout << "Ŀǰ�ߵĸ����������ֵ���޷�����ӣ�" << endl;
		return;
	}
	cout << "��������ӱߵĸ���:";
	cin >> edgeNumber;
	//����������������������ı���������д���
	while (edgeNumber <= 0 || cin.fail() || edgeNumber > (getMaxAddEdge() - currentEdgeNumber))
	{
		//���������
		if (edgeNumber <= 0 || cin.fail())
		{
			cout << "�ߵĸ���ֻ����������!" << endl;
		}
		//�����������
		else
		{
			cout << "�����ߵ������ᳬ�����ֵ!" << endl;
		}
		cout << "����������߸���:";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> edgeNumber;
	}
	//����ϵͳ�ı�������
	currentEdgeNumber += edgeNumber;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	for (int i = 0; i < edgeNumber; i++)
	{
		//��������������ߵ�Ȩ��
		cout << "�������������㼰��:";
		while (true)
		{
			cin >> name1 >> name2 >> weight;
			vertex1 = powerGrid.findVertexByName(name1);
			vertex2 = powerGrid.findVertexByName(name2);
			//������Ķ�����м�飬���д�����
			if (name1 == name2)
			{
				cout << "���������������ͬ!";
			}
			else if (vertex1 == nullptr)
			{
				cout << "��һ�����㲻����!";
			}
			else if (vertex2 == nullptr)
			{
				cout << "�ڶ������㲻����!";
			}
			else if (weight <= 0 || cin.fail())
			{
				cout << "ÿһ���ߵĻ��ѱ�����������!";
			}
			//�ߺϷ������
			else
			{
				//�����δ���ڣ��Ͳ���㣬����ѭ��
				if (!isEdgeExist(vertex1, vertex2))
				{
					powerGrid.insertEdge(vertex1, vertex2, weight);
					break;
				}
				//���������������Լ����ڱߣ���������
				else
				{
					cout << "����������֮���Ѿ����ڱ�!";
				}
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl;
			cout << "�����������������㼰��:";
		}
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return;
}

void PowerGridCostSystem::costMinByPrim()
{
	//ϵͳ����Ϊ0��ֱ�ӷ���
	if (powerGrid.getVertexTable().getSize() == 0)
	{
		cout << "ϵͳ��û�ж���!" << endl;
		return;
	}
	//ϵͳֻ��һ�����㣬��ζ��û�бߣ�Ҳ����Ҫ��
	else if (powerGrid.getVertexTable().getSize() == 1)
	{
		cout << "ϵͳ��û�б�!" << endl;
		return;
	}
	//�洢�������
	int vertexNumber = powerGrid.getVertexTable().getSize();
	//��¼�Ѿ�����Ķ������
	int count = 1;
	//������������ָ���ݴ���һ�����Լ���С��
	Edge<string, int>* nextEdge = nullptr;
	Edge<string, int>* minEdge = nullptr;
	//��ʼ����(���ڵ�)������
	string init;
	//������С���õĶ�
	Heap<Edge<string, int>*> heap;
	//��ʼ����(���ڵ�)
	Vertex<string, int>* initVertex = nullptr;
	//��սڵ�
	result.clear();
	//��ͼ�еĶ���selectedȫ������Ϊfalse��Ϊ������׼��
	for (int i = 0; i < vertexNumber; i++)
	{
		powerGrid.getVertexTable()[i]->setSelected(false);
	}
	//������ʼ����
	cout << "��������ʼ����:";
	cin >> init;
	//������ʼ����
	initVertex = powerGrid.findVertexByName(init);
	//��������䣬��ǿ����Ľ�׳��
	while (initVertex == nullptr)
	{
		cout << "�˶��㲻��ϵͳ֮��!" << endl;
		cout << "���������룺";
		cin >> init;
		initVertex = powerGrid.findVertexByName(init);
	}
	//��ʼ��������Ϊ��ѡ��
	initVertex->setSelected(true);
	//������δѡ����ɵ�ʱ��ִ��ѭ��
	while (count < vertexNumber)
	{
		//Ѱ������ʼ����������δ��ѡ�е����ж��㣬����������
		nextEdge = initVertex->getHead();
		while (nextEdge != nullptr)
		{
			if (nextEdge->getDestVertex()->getSelected() == false)
			{
				heap.insert(nextEdge);
			}
			nextEdge = nextEdge->getNext();
		}
		//���������û���ҵ�������δ��ѡ�еĶ��㣬˵������ϵͳ��δ��ͨ
		if (heap.getSize() == 0)
		{
			cout << "Ŀǰ�ĵ���ϵͳ��δ��ͨ!" << endl;
			return;
		}
		while (heap.getSize() != 0)
		{
			//ѡ����С�ߣ�����result����
			minEdge = heap.getTop();
			if (minEdge->getDestVertex()->getSelected() == false)
			{
				//��С�߶�Ӧ����һ�붥��selected��Ϊtrue
				minEdge->getDestVertex()->setSelected(true);
				//��һ�����㵱����ʼ�������Ѱ
				initVertex = minEdge->getDestVertex();
				//����result���
				result.pushBack(minEdge);
				//������
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
	cout << "����Prim��С������!" << endl;
	return;
}

void PowerGridCostSystem::showResult()
{
	//����бߵ���ĿС�ڶ���-1���߶�����Ŀ��Ϊ1����С������δ�ɹ�����
	if ((result.getSize() != (powerGrid.getVertexTable().getSize() - 1)) || (powerGrid.getVertexTable().getSize() == 1))
	{
		cout << "��С������δ�ɹ�����!" << endl;
		return;
	}
	cout << "��С�������Ķ��㼰��Ϊ:" << endl;
	//����������
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
	//��ʾ�˵�
	showMenu();
	//�洢��������ʹ��string����cin�Ľ�׳��
	string cmmand;
	while (true)
	{
		cout << endl;
		cout << "��ѡ�������";
		cin >> cmmand;
		switch (cmmand[0])
		{
		case 'A':
			//��������ϵͳ
			buildPowerGrid();
			break;
		case 'B':
			//������ϵͳ���ӱ�
			addPowerGridEdge();
			break;
		case 'C':
			//������С������
			costMinByPrim();
			break;
		case 'D':
			//չʾ���
			showResult();
			break;
		case 'E':
			cout << "�ɹ��˳�ϵͳ��" << endl;
			return;
		default:
			cout << "���������벻��ȷ������������!";
			break;
		}
	}
}

bool PowerGridCostSystem::isVertexExist(Vector<string>& vertexName)
{
	//���Vector�ڲ��Ƿ���������
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
	//���Vector�ڶ���������Ѵ��ڶ�����Ƿ�������
	for (int i = 0; i < vertexName.getSize(); i++)
	{
		if (powerGrid.findVertexByName(vertexName[i]) != nullptr)
		{
			cout << "�����¶���������ϵͳ���Ѵ��ڵĶ��������ظ�!" << endl;
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
		//�Ѿ����˱ߣ�����true
		if (tempCurrentEdge->getDestVertex()->getName() == destVertex->getName())
		{
			return true;
		}
		//�������Ѱ��ֱ����ǰ����������������㶼��Ѱ��
		tempCurrentEdge = tempCurrentEdge->getNext();
	}
	//û���ҵ�������false
	return false;
}

int PowerGridCostSystem::getMaxAddEdge()
{
	//�Ȼ�����Ķ�����
	int vertexNumber = powerGrid.getVertexTable().getSize();
	//����������ȫͼ����ΪmaxEdge
	int maxEdge = (vertexNumber - 1) * vertexNumber / 2;
	return maxEdge;
}


int main()
{
	//�������ϵͳ
	PowerGridCostSystem powerGridCostSystem;
	//���е������ϵͳ
	powerGridCostSystem.runPowerGridCostSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}


