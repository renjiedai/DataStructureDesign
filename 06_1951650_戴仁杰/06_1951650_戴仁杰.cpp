#include <iostream>
#include <string>
#include<limits>

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



//家谱树的节点类
template<typename T>
class GenealogicalTreeNode
{
public:
	//默认构造函数
	GenealogicalTreeNode() = default;
	//带有元素值的构造函数
	GenealogicalTreeNode(T& inputData);
	//保持类的封装性，一系列的get函数
	T getData();
	GenealogicalTreeNode<T>* getFirstChild();
	GenealogicalTreeNode<T>* getNextSibling();
	GenealogicalTreeNode<T>* getParent();
	//保持类的封装性，一系列的set函数
	void setData(T& inputData);
	void setFirstChild(GenealogicalTreeNode<T>* inputFirstChild);
	void setNextSibling(GenealogicalTreeNode<T>* inputNextSibling);
	void setParent(GenealogicalTreeNode<T>* inputParent);
private:
	//树中的元素值
	T data;
	//第一个孩子节点指针
	GenealogicalTreeNode<T>* firstChild = nullptr;
	//右兄弟指针
	GenealogicalTreeNode<T>* nextSibling = nullptr;
	//双亲节点指针
	GenealogicalTreeNode<T>* parent = nullptr;
};

template<typename T>
GenealogicalTreeNode<T>::GenealogicalTreeNode(T& inputData)
{
	this->data = inputData;
}

template<typename T>
T GenealogicalTreeNode<T>::getData()
{
	return this->data;
}

template<typename T>
GenealogicalTreeNode<T>* GenealogicalTreeNode<T>::getFirstChild()
{
	return this->firstChild;
}

template<typename T>
GenealogicalTreeNode<T>* GenealogicalTreeNode<T>::getNextSibling()
{
	return this->nextSibling;
}

template<typename T>
GenealogicalTreeNode<T>* GenealogicalTreeNode<T>::getParent()
{
	return this->parent;
}

template<typename T>
void GenealogicalTreeNode<T>::setData(T& inputData)
{
	this->data = inputData;
}

template<typename T>
void GenealogicalTreeNode<T>::setFirstChild(GenealogicalTreeNode<T>* inputFirstChild)
{
	this->firstChild = inputFirstChild;
}

template<typename T>
void GenealogicalTreeNode<T>::setNextSibling(GenealogicalTreeNode<T>* inputNextSibling)
{
	this->nextSibling = inputNextSibling;
}

template<typename T>
void GenealogicalTreeNode<T>::setParent(GenealogicalTreeNode<T>* inputParent)
{
	this->parent = inputParent;
}


template<typename T>
class GenealogicalTree
{
public:
	~GenealogicalTree();
	//寻找家谱树中有没有指定名字的成员
	GenealogicalTreeNode<T>* find(T data);
	//清空家谱树
	void makeEmptyByNode(GenealogicalTreeNode<T>* node);
	//删除node及其孩子兄弟节点，保存被删除的节点到vec中
	void makeEmptyAndSaveByNode(Vector<T>& vec, GenealogicalTreeNode<T>* node);
	//get和set函数
	GenealogicalTreeNode<T>* getRoot();
	void setRoot(GenealogicalTreeNode<T>* inputRoot);
private:
	//寻找node节点及其子孙中指定data的节点并返回，内部递归
	GenealogicalTreeNode<T>* findByNode(T data, GenealogicalTreeNode<T>* node);
	GenealogicalTreeNode<T>* root = nullptr;
};

template<typename T>
GenealogicalTree<T>::~GenealogicalTree()
{
	makeEmptyByNode(root);
}

template<typename T>
GenealogicalTreeNode<T>* GenealogicalTree<T>::find(T data)
{
	return findByNode(data, root);
}

template<typename T>
void GenealogicalTree<T>::makeEmptyByNode(GenealogicalTreeNode<T>* node)
{
	//node为空，返回
	if (node == nullptr)
	{
		return;
	}
	//删除孩子和兄弟节点
	makeEmptyByNode(node->getFirstChild());
	makeEmptyByNode(node->getNextSibling());
	//删除节点
	delete node;
	node = nullptr;
}

template<typename T>
void GenealogicalTree<T>::makeEmptyAndSaveByNode(Vector<T>& vec, GenealogicalTreeNode<T>* node)
{
	//node为空，返回
	if (node == nullptr)
	{
		return;
	}
	//删除并保存孩子和兄弟节点
	makeEmptyAndSaveByNode(vec, node->getFirstChild());
	makeEmptyAndSaveByNode(vec, node->getNextSibling());
	//保存node的data数据
	vec.pushBack(node->getData());
	//删除节点
	delete node;
	node = nullptr;
}

template<typename T>
GenealogicalTreeNode<T>* GenealogicalTree<T>::getRoot()
{
	return root;
}

template<typename T>
void GenealogicalTree<T>::setRoot(GenealogicalTreeNode<T>* inputRoot)
{
	this->root = inputRoot;
}

template<typename T>
GenealogicalTreeNode<T>* GenealogicalTree<T>::findByNode(T data, GenealogicalTreeNode<T>* node)
{
	if (node == nullptr)
	{
		return nullptr;
	}
	//自己就是，直接返回
	if (node->getData() == data)
	{
		return node;
	}
	GenealogicalTreeNode<T>* result = nullptr;
	//寻找node的孩子节点
	result = findByNode(data, node->getFirstChild());
	if (result != nullptr)
	{
		return result;
	}
	//寻找node的兄弟节点
	result = findByNode(data, node->getNextSibling());
	if (result != nullptr)
	{
		return result;
	}
	//孩子和兄弟都没找到，返回nullptr
	return nullptr;
}



//家谱管理系统类
class GenealogicalManagementSystem
{
public:
	//打印菜单栏
	void showMenu();
	//初始化系统
	void initGenealogical();
	//给家谱中的人建立家庭
	void buildFamily();
	//展示一个节点及其孩子节点的信息
	void showFamilyByNode(GenealogicalTreeNode<string>* parent);
	//插入一个家庭成员
	void addFamilyMember();
	//解散家庭
	void removeFamily();
	//给成员更改姓名
	void changeMemberName();
	//运行整个家谱管理系统
	void runGenealogicalManagementSystem();
private:
	//检查要插入的孩子是否重名或者已经在树内部存在
	bool isChildExist(Vector<string>& child);
	//在家谱树中增加孩子，无提示信息版本
	bool addChild(GenealogicalTreeNode<string>* parent, Vector<string>& child);
	//家谱树
	GenealogicalTree<string> genealogicalTree;
};


void GenealogicalManagementSystem::showMenu()
{
	cout << "**\t\t家谱管理系统\t\t\t**" << endl;
	//打印分割线
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA --- 完善家谱\t\t\t**" << endl;
	cout << "**\t\tB --- 添加家庭成员\t\t**" << endl;
	cout << "**\t\tC --- 解散局部家庭\t\t**" << endl;
	cout << "**\t\tD --- 更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE --- 退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

bool GenealogicalManagementSystem::isChildExist(Vector<string>& child)
{
	for (int i = 0; i < child.getSize() - 1; i++)
	{
		for (int j = i + 1; j < child.getSize(); j++)
		{
			if (child[i] == child[j])
			{
				cout << "您输入的孩子存在重名现象！" << endl;
				return true;
			}
		}
	}
	for (int i = 0; i < child.getSize(); i++)
	{
		if (genealogicalTree.find(child[i]) != nullptr)
		{
			cout << "输入的孩子" << child[i] << "与家谱中原有成员存在重名！" << endl;
			return true;
		}
	}
	return false;
}

bool GenealogicalManagementSystem::addChild(GenealogicalTreeNode<string>* parent, Vector<string>& child)
{
	//双亲节点为空或者孩子节点名字为空，返回false
	if (parent == nullptr || child.isEmpty())
	{
		return false;
	}
	//孩子名字不为空，建立第一个孩子
	GenealogicalTreeNode<string>* newChild = new GenealogicalTreeNode<string>(child[0]);
	parent->setFirstChild(newChild);
	newChild->setParent(parent);
	//后续孩子存到第一个孩子的兄弟节点
	for (int i = 1; i < child.getSize(); i++)
	{
		GenealogicalTreeNode<string>* brotherChild = new GenealogicalTreeNode<string>(child[i]);
		newChild->setNextSibling(brotherChild);
		newChild->getNextSibling()->setParent(parent);
		newChild = newChild->getNextSibling();
	}
	return true;
}

void GenealogicalManagementSystem::initGenealogical()
{
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	//建立祖先
	string ancestorName;
	cin >> ancestorName;
	GenealogicalTreeNode<string>* tempRoot = new GenealogicalTreeNode<string>(ancestorName);
	genealogicalTree.setRoot(tempRoot);

	cout << "此家谱的祖先是：" << ancestorName << endl;
}

void GenealogicalManagementSystem::buildFamily()
{
	//孩子数目
	int childNum = 0;
	//双亲节点名字
	string parentName;
	//存储孩子名字的Vector
	Vector<string> child;
	//家谱树中的双亲节点
	GenealogicalTreeNode<string>* parent = nullptr;
	cout << "请输入要建立家庭的人的姓名：";
	cin >> parentName;
	//在AVL树中快速寻找双亲节点的名字
	parent = genealogicalTree.find(parentName);
	//双亲节点为空节点或者已经有孩子
	while (parent == nullptr || parent->getFirstChild() != nullptr)
	{
		if (parent == nullptr)
		{
			cout << "此人不在家谱中！" << endl;
		}
		else
		{
			cout << "此人已经建立家庭！" << endl;
		}
		cout << "请重新输入：";
		cin >> parentName;
		parent = genealogicalTree.find(parentName);
	}
	//输入孩子的个数
	cout << "请输入" << parentName << "的儿女的人数：";
	cin >> childNum;
	//错误处理，增强程序的鲁棒性
	while (cin.fail() || childNum <= 0)
	{
		cout << "请输入一个正整数！" << endl;
		cout << "请重新输入：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> childNum;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//输入孩子的姓名
	cout << "请依次输入" << parentName << "的儿女的姓名：";
	child.reSize(childNum);
	for (int i = 0; i < childNum; i++)
	{
		cin >> child[i];
	}
	//检查输入中是否存在重名
	while (isChildExist(child))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "请重新依次输入" << parentName << "的儿女的姓名：";
		for (int i = 0; i < childNum; i++)
		{
			cin >> child[i];
		}
	}
	//插入孩子
	addChild(parent, child);
	//显示孩子信息
	showFamilyByNode(parent);
	return;
}

void GenealogicalManagementSystem::showFamilyByNode(GenealogicalTreeNode<string>* parentNode)
{
	if (parentNode->getFirstChild() == nullptr)
	{
		cout << parentNode->getData() << "没有子孙！" << endl;
		return;
	}
	else
	{
		cout << parentNode->getData() << "的第一代子孙是：";
		GenealogicalTreeNode<string>* firstChild = parentNode->getFirstChild();
		cout << firstChild->getData() << ' ';
		while (firstChild->getNextSibling() != nullptr)
		{
			firstChild = firstChild->getNextSibling();
			cout << firstChild->getData() << ' ';
		}
		cout << endl;
	}
}

void GenealogicalManagementSystem::addFamilyMember()
{
	//新建元素的双亲节点名字
	string parentName;
	//新元素名字
	string newMember;
	//存储孩子名字的Vector
	Vector<string> newMembers;
	//要插入成员的双亲节点
	GenealogicalTreeNode<string>* parent = nullptr;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> parentName;
	//在家谱树中寻找双亲
	parent = genealogicalTree.find(parentName);
	//没找到双亲重新输入
	while (parent == nullptr)
	{
		cout << "此人不在家谱中！" << endl;
		cout << "请重新输入：";
		cin >> parentName;
		parent = genealogicalTree.find(parentName);
	}
	//输入孩子的名字
	cout << "请输入" << parentName << "新添加儿子（或女儿）的姓名：";
	cin >> newMember;
	newMembers.pushBack(newMember);
	//如果有重名，重新输入
	while (isChildExist(newMembers))
	{
		cout << "请重新输入：";
		cin >> newMember;
	}
	//插入孩子
	addChild(parent, newMembers);
	//显示孩子信息
	showFamilyByNode(parent);
}

void GenealogicalManagementSystem::removeFamily()
{
	string ancestorName;
	Vector<string> deleteNodes;
	//要移除的家族的根节点
	GenealogicalTreeNode<string>* ancestorNode = nullptr;
	cout << "请输入要解散家庭的人的姓名：";
	cin >> ancestorName;
	ancestorNode = genealogicalTree.find(ancestorName);
	//节点为空或者节点为根节点，不能解散
	while (ancestorNode == nullptr || ancestorNode->getData() == genealogicalTree.getRoot()->getData())
	{
		//错误处理，增强程序的健壮性
		if (ancestorNode == nullptr)
		{
			cout << "此人不在家谱中！" << endl;
		}
		else
		{
			cout << "不能解散第一代祖先的家庭！" << endl;
		}
		cout << "请重新输入：";
		cin >> ancestorName;
		ancestorNode = genealogicalTree.find(ancestorName);
	}
	cout << "要解散家庭的人是：" << ancestorNode->getData() << endl;
	showFamilyByNode(ancestorNode);
	if (ancestorNode->getParent() != nullptr)
	{
		//被删除的节点是其双亲节点的第一个孩子，删除后将其兄弟设置为双亲的第一个孩子
		if (ancestorNode->getParent()->getFirstChild() == ancestorNode)
		{
			ancestorNode->getParent()->setFirstChild(ancestorNode->getNextSibling());
		}
		//被删除节点不是其双亲节点的第一个孩子，删除后将该节点的前驱的后继设为自己后继
		else
		{
			GenealogicalTreeNode<string>* current = ancestorNode->getParent()->getFirstChild();
			while (current->getNextSibling() != ancestorNode)
			{
				current = current->getNextSibling();
			}
			current->setNextSibling(ancestorNode->getNextSibling());
		}
	}
	//把解散家庭的根节点存入deleteNodes
	deleteNodes.pushBack(ancestorNode->getData());
	//移除要解散成员的子孙并存入
	genealogicalTree.makeEmptyAndSaveByNode(deleteNodes, ancestorNode->getFirstChild());
	delete ancestorNode;
	ancestorNode = nullptr;
	return;
}

void GenealogicalManagementSystem::changeMemberName()
{
	//存储旧名字和新名字
	string oldName, newName;
	GenealogicalTreeNode<string>* oldMember = nullptr;
	GenealogicalTreeNode<string>* newMember = nullptr;
	cout << "请输入要更改姓名的人的目前姓名：";
	cin >> oldName;
	//寻找此人
	oldMember = genealogicalTree.find(oldName);
	//如果没有找到此人，重新输入
	while (oldMember == nullptr)
	{
		cout << "此人不在家谱中！" << endl;
		cout << "请重新输入：";
		cin >> oldName;
		oldMember = genealogicalTree.find(oldName);
	}
	//已经找到改名的节点
	cout << "请输入更改后的姓名：";
	cin >> newName;
	//检查新名字是否存在重名
	newMember = genealogicalTree.find(newName);
	//如果存在重名则重新输入
	while (newMember != nullptr)
	{
		cout << "此姓名已存在于家谱中！" << endl;
		cout << "请重新输入：";
		cin >> newName;
		newMember = genealogicalTree.find(newName);
	}
	//更改名字
	oldMember->setData(newName);
	cout << oldName << "已更名为" << newName << endl;
	return;
}

void GenealogicalManagementSystem::runGenealogicalManagementSystem()
{
	//打印初始菜单
	showMenu();
	//建立祖先，初始化家谱树
	initGenealogical();
	//输入操作的代号
	string operation;
	while (true)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "请输入要执行的操作：";
		cin >> operation;
		//string类型不能用于switch，用string的第一个字符区分操作
		switch (operation[0])
		{
		case 'A':
			//完善家庭
			buildFamily();
			break;
		case 'B':
			//增加家庭成员
			addFamilyMember();
			break;
		case 'C':
			//解散局部家庭
			removeFamily();
			break;
		case 'D':
			//更改家庭成员姓名
			changeMemberName();
			break;
		case 'E':
			//退出程序
			cout << "成功退出系统！" << endl;
			return;
		default:
			cout << "操作数输入不正确，请重新输入!" << endl;
		}
	}
}

int main()
{
	//建立家谱管理系统
	GenealogicalManagementSystem genealogicalManagementSystem;
	//运行程序
	genealogicalManagementSystem.runGenealogicalManagementSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}
