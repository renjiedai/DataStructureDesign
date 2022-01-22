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

//自定义栈类，为顺序栈，内含一个Vector数组
template <typename T>
class Stack
{
public:
	//插入
	void push(T input);
	//删除末尾元素
	void pop();
	//返回栈顶元素
	T top();
	//判断是否为空
	bool isEmpty();
	//返回栈的大小
	int getSize();
	//清空栈
	void clear();
private:
	Vector<T> stack;
};

template<typename T>
void Stack<T>::push(T input)
{
	stack.pushBack(input);
}

template<typename T>
void Stack<T>::pop()
{
	stack.popBack();
}

template<typename T>
T Stack<T>::top()
{
	return stack[stack.getSize() - 1];
}

template<typename T>
bool Stack<T>::isEmpty()
{
	return stack.getSize() == 0;
}

template<typename T>
int Stack<T>::getSize()
{
	return stack.getSize();
}

template<typename T>
void Stack<T>::clear()
{
	stack.clear();
}



//二叉树节点类
template <typename T>
class BTreeNode
{
public:
	BTreeNode() = default;
	BTreeNode(T inputData, int inputTag);
	//get与set函数
	T getData();
	BTreeNode<T>* getLeft();
	BTreeNode<T>* getRight();
	int getTag();
	void setData(T inputData);
	void setLeft(BTreeNode<T>* inputLeft);
	void setRight(BTreeNode<T>* inputRight);
	void setTag(int inputTag);
private:
	//数据域
	T data;
	//标记节点是否有括号的标记域
	int tag = 0;
	//左右孩子指针域
	BTreeNode<T>* left = nullptr;
	BTreeNode<T>* right = nullptr;

};

template<typename T>
BTreeNode<T>::BTreeNode(T inputData, int inputTag)
{
	this->data = inputData;
	this->tag = inputTag;
}

template<typename T>
T BTreeNode<T>::getData()
{
	return this->data;
}

template<typename T>
BTreeNode<T>* BTreeNode<T>::getLeft()
{
	return this->left;
}

template<typename T>
BTreeNode<T>* BTreeNode<T>::getRight()
{
	return this->right;
}

template<typename T>
int BTreeNode<T>::getTag()
{
	return this->tag;
}

template<typename T>
void BTreeNode<T>::setData(T inputData)
{
	this->data = inputData;
}

template<typename T>
void BTreeNode<T>::setLeft(BTreeNode<T>* inputLeft)
{
	this->left = inputLeft;
}

template<typename T>
void BTreeNode<T>::setRight(BTreeNode<T>* inputRight)
{
	this->right = inputRight;
}

template<typename T>
void BTreeNode<T>::setTag(int inputTag)
{
	this->tag = inputTag;
}


template<typename T>
class BTree
{
public:
	~BTree();
	void makeEmptyByNode(BTreeNode<T>* node);
	void insertLeft(BTreeNode<T>* parent, T data, int tag);
	void insertRight(BTreeNode<T>* parent, T data, int tag);
	//get和set函数
	BTreeNode<T>* getRoot();
	void setRoot(BTreeNode<T>* inputRoot);
private:
	//二叉树根节点
	BTreeNode<T>* root = nullptr;
};

template<typename T>
BTree<T>::~BTree()
{
	makeEmptyByNode(root);
}

template<typename T>
void BTree<T>::makeEmptyByNode(BTreeNode<T>* node)
{
	//本身为空指针，返回
	if (node == nullptr)
	{
		return;
	}
	//左子树不为空，删除左子树
	if (node->getLeft() != nullptr)
	{
		makeEmptyByNode(node->getLeft());
	}
	//右子树不为空，删除右子树
	if (node->getRight() != nullptr)
	{
		makeEmptyByNode(node->getRight());
	}
	//释放内存
	delete node;
	node = nullptr;
	return;
}

template<typename T>
void BTree<T>::insertLeft(BTreeNode<T>* parent, T data, int tag)
{
	//父节点为空，返回
	if (parent == nullptr)
	{
		return;
	}
	//新建节点并插入
	BTreeNode<T>* leftChild = new BTreeNode<T>(data, tag);
	parent->setLeft(leftChild);
	return;
}

template<typename T>
void BTree<T>::insertRight(BTreeNode<T>* parent, T data, int tag)
{
	//父节点为空，返回
	if (parent == nullptr)
	{
		return;
	}
	//新建节点并插入
	BTreeNode<T>* rightChild = new BTreeNode<T>(data, tag);
	parent->setRight(rightChild);
	return;
}

template<typename T>
BTreeNode<T>* BTree<T>::getRoot()
{
	return this->root;
}

template<typename T>
void BTree<T>::setRoot(BTreeNode<T>* inputRoot)
{
	this->root = inputRoot;
}


//二叉树计算式转换系统
class BTreeCalculateSystem
{
public:	
	//建立二叉树
	bool buildBTree();
	//波兰式
	void PNExpression();
	//中缀表达式
	void InfixExpression();
	//逆波兰表达式
	void RPNExpression();
private:
	//设置符号的优先级并输出
	int priority(char symbol);
	//检查表达式是否含有非法字符
	bool isLegal(string inputExpression);
	//当遇到括号时
	bool buildBTreeForLeftBrackets(char ch);
	bool buildBTreeForRightBrackets();
	//当遇到运算符时
	bool buildBTreeForOperator(char ch);
	//当遇到数字时
	int buildBTreeForNumber(string input, int startPosition);
	//已经完全读入，将数字栈和运算符栈剩余内容弹出，并检测是否非法
	bool buildBTreeForLast();
	//输出前中后缀表达式
	void preOrderBTree(BTreeNode<string>* node);
	void inOrderBTree(BTreeNode<string>* node);
	void postOrderBTree(BTreeNode<string>* node);
	//存储数字的栈
	Stack<BTreeNode<string>*> numberStack;
	//存储运算符的栈
	Stack<BTreeNode<string>*> operatorStack;
	//表示运算式的二叉树
	BTree<string> calculateBTree;
};


bool BTreeCalculateSystem::buildBTree()
{
	//存储输入的表达式
	string inputExpression;
	cout << "请输入表达式：\t";
	cin >> inputExpression;
	//判断表达式是否合法
	while (!isLegal(inputExpression))
	{
		cout << "表达式中存在未定义的符号，请重新输入！" << endl;
		cout << "请输入表达式： ";
		cin >> inputExpression;
	}
	//遍历输入的表达式
	for (int i = 0; i < inputExpression.length(); i++)
	{
		//左括号特判，进符号栈
		if (inputExpression[i] == '(')
		{
			if (!buildBTreeForLeftBrackets(inputExpression[i]))
			{
				return false;
			}
			continue;
		}
		//右括号特判，一直出栈直到遇见左括号
		if (inputExpression[i] == ')')
		{
			if (!buildBTreeForRightBrackets())
			{
				return false;
			}
			continue;
		}
		//遇到除括号的运算符，判断是否进栈
		if (priority(inputExpression[i]))
		{
			if (!buildBTreeForOperator(inputExpression[i]))
			{
				return false;
			}
			continue;
		}
		//没有遇到运算符，即为数字或小数点
		i = buildBTreeForNumber(inputExpression, i);
	}
	//将栈全部弹出，建立二叉树，如果存在非法字符，返回错误
	if (!buildBTreeForLast())
	{
		return false;
	}
	cout << endl;
	return true;
}

void BTreeCalculateSystem::PNExpression()
{
	cout << "波兰表达式：\t";
	preOrderBTree(calculateBTree.getRoot());
	cout << endl << endl;
}

void BTreeCalculateSystem::InfixExpression()
{
	cout << "中缀表达式：\t";
	inOrderBTree(calculateBTree.getRoot());
	cout << endl << endl;
}

void BTreeCalculateSystem::RPNExpression()
{
	cout << "逆波兰表达式：\t";
	postOrderBTree(calculateBTree.getRoot());
	cout << endl << endl;
}

int BTreeCalculateSystem::priority(char symbol)
{
	//加减号的优先级为6
	if (symbol == '+' || symbol == '-')
	{
		return 6;
	}
	//乘除取模运算优先级为5
	else if (symbol == '*' || symbol == '/' || symbol == '%')
	{
		return 5;
	}
	//左又括号优先级为20
	else if (symbol == '(' || symbol == ')')
	{
		return 20;
	}
	//位与优先级为10
	else if (symbol == '&')
	{
		return 10;
	}
	//位异或优先级为11
	else if (symbol == '^')
	{
		return 11;
	}
	//数字或者小数点返回0，表明当前不是运算符
	else if ((symbol >= '0' && symbol <= '9') || symbol == '.')
	{
		return 0;
	}
	//其他情况返回-1，表明出现其他非法字符
	return -1;
}

bool BTreeCalculateSystem::isLegal(string inputExpression)
{
	int judge = 0;
	//对输入的字符检查是否合法
	for (int i = 0; i < inputExpression.length(); i++)
	{
		judge = priority(inputExpression[i]);
		//返回值为-1，表示非法
		if (judge == -1)
		{
			return false;
		}
	}
	return true;
}

bool BTreeCalculateSystem::buildBTreeForLeftBrackets(char ch)
{
	string tempData;
	tempData += ch;
	BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
	operatorStack.push(newNode);
	return true;
}

bool BTreeCalculateSystem::buildBTreeForRightBrackets()
{
	if (operatorStack.getSize() == 0)
	{
		cout << "输入的表达式非法！请检查输入" << endl;
		return false;
	}
	while (operatorStack.top()->getData()[0] != '(')
	{
		//数字栈内数字不足，说明表达式非法
		if (numberStack.getSize() < 2)
		{
			cout << "输入的表达式非法！请检查输入" << endl;
			return false;
		}
		BTreeNode<string>* operatorTop = operatorStack.top();
		calculateBTree.setRoot(operatorTop);
		//当前运算符元素作为根节点，数字栈顶元素为其右孩子
		operatorTop->setRight(numberStack.top());
		//弹出数字栈顶元素
		numberStack.pop();
		//当前运算符元素作为根节点，数字栈顶元素为其左孩子
		operatorTop->setLeft(numberStack.top());
		//弹出数字栈顶元素
		numberStack.pop();
		//弹出运算符栈顶元素
		operatorStack.pop();
		//将原栈顶操作符节点作为广义数字存入数字栈
		numberStack.push(operatorTop);
		//没遇到左括号运算符栈已经为空，说明输入非法
		if (operatorStack.getSize() == 0)
		{
			cout << "输入的表达式非法！请检查输入" << endl;
			return false;
		}
	}
	if (calculateBTree.getRoot() == nullptr)
	{
		cout << "输入的表达式非法！请检查输入" << endl;
		return false;
	}
	//给此节点打上标记，此节点及其子树为括号内的部分
	calculateBTree.getRoot()->setTag(1);
	//运算符栈弹出左括号
	operatorStack.pop();
	return true;
}

bool BTreeCalculateSystem::buildBTreeForOperator(char ch)
{
	string tempData;
	//运算符栈为空，直接进栈
	if (operatorStack.getSize() == 0)
	{
		tempData += ch;
		BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
		operatorStack.push(newNode);
	}
	//栈不空，判断栈顶运算符与当前运算符的优先级，决定是否进栈
	else
	{
		//栈顶优先级不足，进栈
		if (priority(operatorStack.top()->getData()[0]) > priority(ch))
		{
			tempData += ch;
			BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
			operatorStack.push(newNode);
		}
		//栈顶优先级更高，弹出完再进栈
		else
		{
			//一直弹出，直到栈顶优先级不足，或者运算符栈空
			while (priority(operatorStack.top()->getData()[0]) <= priority(ch))
			{
				//数字栈内数字不足，说明表达式非法
				if (numberStack.getSize() < 2)
				{
					cout << "输入的表达式非法！请检查输入" << endl;
					return false;
				}
				BTreeNode<string>* operatorTop = operatorStack.top();
				calculateBTree.setRoot(operatorTop);
				//当前运算符元素作为根节点，数字栈顶元素为其右孩子
				operatorTop->setRight(numberStack.top());
				//弹出数字栈顶元素
				numberStack.pop();
				//当前运算符元素作为根节点，数字栈顶元素为其左孩子
				operatorTop->setLeft(numberStack.top());
				//弹出数字栈顶元素
				numberStack.pop();
				//弹出运算符栈顶元素
				operatorStack.pop();
				//将原栈顶操作符节点作为广义数字存入数字栈
				numberStack.push(operatorTop);
				//运算符栈已经空，不再弹出
				if (operatorStack.getSize() == 0)
				{
					break;
				}
			}
			//当前运算符进入运算符栈
			tempData += ch;
			BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
			operatorStack.push(newNode);
		}
	}
	return true;
}

int BTreeCalculateSystem::buildBTreeForNumber(string inputExpression, int startPosition)
{
	string tempData;
	int i = startPosition;
	while (!priority(inputExpression[i]))
	{
		//一位一位读取得到数字
		tempData += inputExpression[i];
		i++;
	}
	//此时应退回数字的最后一位
	i--;
	//数字入栈
	BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
	numberStack.push(newNode);
	return i;
}

bool BTreeCalculateSystem::buildBTreeForLast()
{
	//仅有一个数字的情况，特殊处理
	if (calculateBTree.getRoot() == nullptr && operatorStack.getSize() == 0 && numberStack.getSize() == 1)
	{
		BTreeNode<string>* operatorTop = numberStack.top();
		calculateBTree.setRoot(operatorTop);
	}
	while (operatorStack.getSize() != 0)
	{
		//数字栈内数字不足，说明表达式非法
		if (numberStack.getSize() < 2)
		{
			cout << "输入的表达式非法！请检查输入" << endl;
			return false;
		}
		BTreeNode<string>* operatorTop = operatorStack.top();
		calculateBTree.setRoot(operatorTop);
		//当前运算符元素作为根节点，数字栈顶元素为其右孩子
		operatorTop->setRight(numberStack.top());
		//弹出数字栈顶元素
		numberStack.pop();
		//当前运算符元素作为根节点，数字栈顶元素为其左孩子
		operatorTop->setLeft(numberStack.top());
		//弹出数字栈顶元素
		numberStack.pop();
		//弹出运算符栈顶元素
		operatorStack.pop();
		//将原栈顶操作符节点作为广义数字存入数字栈
		numberStack.push(operatorTop);
	}
	if (numberStack.getSize() != 1)
	{
		cout << "输入的表达式非法！请检查输入" << endl;
		return false;
	}
	return true;
}

void BTreeCalculateSystem::preOrderBTree(BTreeNode<string>* node)
{
	if (node != nullptr)
	{
		cout << node->getData() << " ";
		preOrderBTree(node->getLeft());
		preOrderBTree(node->getRight());
	}
	return;
}

void BTreeCalculateSystem::inOrderBTree(BTreeNode<string>* node)
{
	if (node != nullptr)
	{	
		if (node->getTag() == 1)
		{
			cout << "( ";
		}
		inOrderBTree(node->getLeft());
		cout << node->getData() << " ";
		inOrderBTree(node->getRight());
		if (node->getTag() == 1)
		{
			cout << ") ";
		}
	}
	return;
}

void BTreeCalculateSystem::postOrderBTree(BTreeNode<string>* node)
{
	if (node != nullptr)
	{
		postOrderBTree(node->getLeft());
		postOrderBTree(node->getRight());
		cout << node->getData() << " ";
	}
	return;
}


int main()
{
	//建立二叉树系统
	BTreeCalculateSystem bTreeCalculateSystem;
	if (bTreeCalculateSystem.buildBTree())
	{
		//输出波兰式
		bTreeCalculateSystem.PNExpression();
		//输出中缀表达式
		bTreeCalculateSystem.InfixExpression();
		//输出逆波兰式
		bTreeCalculateSystem.RPNExpression();
	}
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}


