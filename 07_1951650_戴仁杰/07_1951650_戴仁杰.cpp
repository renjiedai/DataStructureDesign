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

//�Զ���ջ�࣬Ϊ˳��ջ���ں�һ��Vector����
template <typename T>
class Stack
{
public:
	//����
	void push(T input);
	//ɾ��ĩβԪ��
	void pop();
	//����ջ��Ԫ��
	T top();
	//�ж��Ƿ�Ϊ��
	bool isEmpty();
	//����ջ�Ĵ�С
	int getSize();
	//���ջ
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



//�������ڵ���
template <typename T>
class BTreeNode
{
public:
	BTreeNode() = default;
	BTreeNode(T inputData, int inputTag);
	//get��set����
	T getData();
	BTreeNode<T>* getLeft();
	BTreeNode<T>* getRight();
	int getTag();
	void setData(T inputData);
	void setLeft(BTreeNode<T>* inputLeft);
	void setRight(BTreeNode<T>* inputRight);
	void setTag(int inputTag);
private:
	//������
	T data;
	//��ǽڵ��Ƿ������ŵı����
	int tag = 0;
	//���Һ���ָ����
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
	//get��set����
	BTreeNode<T>* getRoot();
	void setRoot(BTreeNode<T>* inputRoot);
private:
	//���������ڵ�
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
	//����Ϊ��ָ�룬����
	if (node == nullptr)
	{
		return;
	}
	//��������Ϊ�գ�ɾ��������
	if (node->getLeft() != nullptr)
	{
		makeEmptyByNode(node->getLeft());
	}
	//��������Ϊ�գ�ɾ��������
	if (node->getRight() != nullptr)
	{
		makeEmptyByNode(node->getRight());
	}
	//�ͷ��ڴ�
	delete node;
	node = nullptr;
	return;
}

template<typename T>
void BTree<T>::insertLeft(BTreeNode<T>* parent, T data, int tag)
{
	//���ڵ�Ϊ�գ�����
	if (parent == nullptr)
	{
		return;
	}
	//�½��ڵ㲢����
	BTreeNode<T>* leftChild = new BTreeNode<T>(data, tag);
	parent->setLeft(leftChild);
	return;
}

template<typename T>
void BTree<T>::insertRight(BTreeNode<T>* parent, T data, int tag)
{
	//���ڵ�Ϊ�գ�����
	if (parent == nullptr)
	{
		return;
	}
	//�½��ڵ㲢����
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


//����������ʽת��ϵͳ
class BTreeCalculateSystem
{
public:	
	//����������
	bool buildBTree();
	//����ʽ
	void PNExpression();
	//��׺���ʽ
	void InfixExpression();
	//�沨�����ʽ
	void RPNExpression();
private:
	//���÷��ŵ����ȼ������
	int priority(char symbol);
	//�����ʽ�Ƿ��зǷ��ַ�
	bool isLegal(string inputExpression);
	//����������ʱ
	bool buildBTreeForLeftBrackets(char ch);
	bool buildBTreeForRightBrackets();
	//�����������ʱ
	bool buildBTreeForOperator(char ch);
	//����������ʱ
	int buildBTreeForNumber(string input, int startPosition);
	//�Ѿ���ȫ���룬������ջ�������ջʣ�����ݵ�����������Ƿ�Ƿ�
	bool buildBTreeForLast();
	//���ǰ�к�׺���ʽ
	void preOrderBTree(BTreeNode<string>* node);
	void inOrderBTree(BTreeNode<string>* node);
	void postOrderBTree(BTreeNode<string>* node);
	//�洢���ֵ�ջ
	Stack<BTreeNode<string>*> numberStack;
	//�洢�������ջ
	Stack<BTreeNode<string>*> operatorStack;
	//��ʾ����ʽ�Ķ�����
	BTree<string> calculateBTree;
};


bool BTreeCalculateSystem::buildBTree()
{
	//�洢����ı��ʽ
	string inputExpression;
	cout << "��������ʽ��\t";
	cin >> inputExpression;
	//�жϱ��ʽ�Ƿ�Ϸ�
	while (!isLegal(inputExpression))
	{
		cout << "���ʽ�д���δ����ķ��ţ����������룡" << endl;
		cout << "��������ʽ�� ";
		cin >> inputExpression;
	}
	//��������ı��ʽ
	for (int i = 0; i < inputExpression.length(); i++)
	{
		//���������У�������ջ
		if (inputExpression[i] == '(')
		{
			if (!buildBTreeForLeftBrackets(inputExpression[i]))
			{
				return false;
			}
			continue;
		}
		//���������У�һֱ��ջֱ������������
		if (inputExpression[i] == ')')
		{
			if (!buildBTreeForRightBrackets())
			{
				return false;
			}
			continue;
		}
		//���������ŵ���������ж��Ƿ��ջ
		if (priority(inputExpression[i]))
		{
			if (!buildBTreeForOperator(inputExpression[i]))
			{
				return false;
			}
			continue;
		}
		//û���������������Ϊ���ֻ�С����
		i = buildBTreeForNumber(inputExpression, i);
	}
	//��ջȫ��������������������������ڷǷ��ַ������ش���
	if (!buildBTreeForLast())
	{
		return false;
	}
	cout << endl;
	return true;
}

void BTreeCalculateSystem::PNExpression()
{
	cout << "�������ʽ��\t";
	preOrderBTree(calculateBTree.getRoot());
	cout << endl << endl;
}

void BTreeCalculateSystem::InfixExpression()
{
	cout << "��׺���ʽ��\t";
	inOrderBTree(calculateBTree.getRoot());
	cout << endl << endl;
}

void BTreeCalculateSystem::RPNExpression()
{
	cout << "�沨�����ʽ��\t";
	postOrderBTree(calculateBTree.getRoot());
	cout << endl << endl;
}

int BTreeCalculateSystem::priority(char symbol)
{
	//�Ӽ��ŵ����ȼ�Ϊ6
	if (symbol == '+' || symbol == '-')
	{
		return 6;
	}
	//�˳�ȡģ�������ȼ�Ϊ5
	else if (symbol == '*' || symbol == '/' || symbol == '%')
	{
		return 5;
	}
	//�����������ȼ�Ϊ20
	else if (symbol == '(' || symbol == ')')
	{
		return 20;
	}
	//λ�����ȼ�Ϊ10
	else if (symbol == '&')
	{
		return 10;
	}
	//λ������ȼ�Ϊ11
	else if (symbol == '^')
	{
		return 11;
	}
	//���ֻ���С���㷵��0��������ǰ���������
	else if ((symbol >= '0' && symbol <= '9') || symbol == '.')
	{
		return 0;
	}
	//�����������-1���������������Ƿ��ַ�
	return -1;
}

bool BTreeCalculateSystem::isLegal(string inputExpression)
{
	int judge = 0;
	//��������ַ�����Ƿ�Ϸ�
	for (int i = 0; i < inputExpression.length(); i++)
	{
		judge = priority(inputExpression[i]);
		//����ֵΪ-1����ʾ�Ƿ�
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
		cout << "����ı��ʽ�Ƿ�����������" << endl;
		return false;
	}
	while (operatorStack.top()->getData()[0] != '(')
	{
		//����ջ�����ֲ��㣬˵�����ʽ�Ƿ�
		if (numberStack.getSize() < 2)
		{
			cout << "����ı��ʽ�Ƿ�����������" << endl;
			return false;
		}
		BTreeNode<string>* operatorTop = operatorStack.top();
		calculateBTree.setRoot(operatorTop);
		//��ǰ�����Ԫ����Ϊ���ڵ㣬����ջ��Ԫ��Ϊ���Һ���
		operatorTop->setRight(numberStack.top());
		//��������ջ��Ԫ��
		numberStack.pop();
		//��ǰ�����Ԫ����Ϊ���ڵ㣬����ջ��Ԫ��Ϊ������
		operatorTop->setLeft(numberStack.top());
		//��������ջ��Ԫ��
		numberStack.pop();
		//���������ջ��Ԫ��
		operatorStack.pop();
		//��ԭջ���������ڵ���Ϊ�������ִ�������ջ
		numberStack.push(operatorTop);
		//û���������������ջ�Ѿ�Ϊ�գ�˵������Ƿ�
		if (operatorStack.getSize() == 0)
		{
			cout << "����ı��ʽ�Ƿ�����������" << endl;
			return false;
		}
	}
	if (calculateBTree.getRoot() == nullptr)
	{
		cout << "����ı��ʽ�Ƿ�����������" << endl;
		return false;
	}
	//���˽ڵ���ϱ�ǣ��˽ڵ㼰������Ϊ�����ڵĲ���
	calculateBTree.getRoot()->setTag(1);
	//�����ջ����������
	operatorStack.pop();
	return true;
}

bool BTreeCalculateSystem::buildBTreeForOperator(char ch)
{
	string tempData;
	//�����ջΪ�գ�ֱ�ӽ�ջ
	if (operatorStack.getSize() == 0)
	{
		tempData += ch;
		BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
		operatorStack.push(newNode);
	}
	//ջ���գ��ж�ջ��������뵱ǰ����������ȼ��������Ƿ��ջ
	else
	{
		//ջ�����ȼ����㣬��ջ
		if (priority(operatorStack.top()->getData()[0]) > priority(ch))
		{
			tempData += ch;
			BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
			operatorStack.push(newNode);
		}
		//ջ�����ȼ����ߣ��������ٽ�ջ
		else
		{
			//һֱ������ֱ��ջ�����ȼ����㣬���������ջ��
			while (priority(operatorStack.top()->getData()[0]) <= priority(ch))
			{
				//����ջ�����ֲ��㣬˵�����ʽ�Ƿ�
				if (numberStack.getSize() < 2)
				{
					cout << "����ı��ʽ�Ƿ�����������" << endl;
					return false;
				}
				BTreeNode<string>* operatorTop = operatorStack.top();
				calculateBTree.setRoot(operatorTop);
				//��ǰ�����Ԫ����Ϊ���ڵ㣬����ջ��Ԫ��Ϊ���Һ���
				operatorTop->setRight(numberStack.top());
				//��������ջ��Ԫ��
				numberStack.pop();
				//��ǰ�����Ԫ����Ϊ���ڵ㣬����ջ��Ԫ��Ϊ������
				operatorTop->setLeft(numberStack.top());
				//��������ջ��Ԫ��
				numberStack.pop();
				//���������ջ��Ԫ��
				operatorStack.pop();
				//��ԭջ���������ڵ���Ϊ�������ִ�������ջ
				numberStack.push(operatorTop);
				//�����ջ�Ѿ��գ����ٵ���
				if (operatorStack.getSize() == 0)
				{
					break;
				}
			}
			//��ǰ��������������ջ
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
		//һλһλ��ȡ�õ�����
		tempData += inputExpression[i];
		i++;
	}
	//��ʱӦ�˻����ֵ����һλ
	i--;
	//������ջ
	BTreeNode<string>* newNode = new BTreeNode<string>(tempData, 0);
	numberStack.push(newNode);
	return i;
}

bool BTreeCalculateSystem::buildBTreeForLast()
{
	//����һ�����ֵ���������⴦��
	if (calculateBTree.getRoot() == nullptr && operatorStack.getSize() == 0 && numberStack.getSize() == 1)
	{
		BTreeNode<string>* operatorTop = numberStack.top();
		calculateBTree.setRoot(operatorTop);
	}
	while (operatorStack.getSize() != 0)
	{
		//����ջ�����ֲ��㣬˵�����ʽ�Ƿ�
		if (numberStack.getSize() < 2)
		{
			cout << "����ı��ʽ�Ƿ�����������" << endl;
			return false;
		}
		BTreeNode<string>* operatorTop = operatorStack.top();
		calculateBTree.setRoot(operatorTop);
		//��ǰ�����Ԫ����Ϊ���ڵ㣬����ջ��Ԫ��Ϊ���Һ���
		operatorTop->setRight(numberStack.top());
		//��������ջ��Ԫ��
		numberStack.pop();
		//��ǰ�����Ԫ����Ϊ���ڵ㣬����ջ��Ԫ��Ϊ������
		operatorTop->setLeft(numberStack.top());
		//��������ջ��Ԫ��
		numberStack.pop();
		//���������ջ��Ԫ��
		operatorStack.pop();
		//��ԭջ���������ڵ���Ϊ�������ִ�������ջ
		numberStack.push(operatorTop);
	}
	if (numberStack.getSize() != 1)
	{
		cout << "����ı��ʽ�Ƿ�����������" << endl;
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
	//����������ϵͳ
	BTreeCalculateSystem bTreeCalculateSystem;
	if (bTreeCalculateSystem.buildBTree())
	{
		//�������ʽ
		bTreeCalculateSystem.PNExpression();
		//�����׺���ʽ
		bTreeCalculateSystem.InfixExpression();
		//����沨��ʽ
		bTreeCalculateSystem.RPNExpression();
	}
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}


