#include <iostream>
#include <string>
#include<limits>

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



//�������Ľڵ���
template<typename T>
class GenealogicalTreeNode
{
public:
	//Ĭ�Ϲ��캯��
	GenealogicalTreeNode() = default;
	//����Ԫ��ֵ�Ĺ��캯��
	GenealogicalTreeNode(T& inputData);
	//������ķ�װ�ԣ�һϵ�е�get����
	T getData();
	GenealogicalTreeNode<T>* getFirstChild();
	GenealogicalTreeNode<T>* getNextSibling();
	GenealogicalTreeNode<T>* getParent();
	//������ķ�װ�ԣ�һϵ�е�set����
	void setData(T& inputData);
	void setFirstChild(GenealogicalTreeNode<T>* inputFirstChild);
	void setNextSibling(GenealogicalTreeNode<T>* inputNextSibling);
	void setParent(GenealogicalTreeNode<T>* inputParent);
private:
	//���е�Ԫ��ֵ
	T data;
	//��һ�����ӽڵ�ָ��
	GenealogicalTreeNode<T>* firstChild = nullptr;
	//���ֵ�ָ��
	GenealogicalTreeNode<T>* nextSibling = nullptr;
	//˫�׽ڵ�ָ��
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
	//Ѱ�Ҽ���������û��ָ�����ֵĳ�Ա
	GenealogicalTreeNode<T>* find(T data);
	//��ռ�����
	void makeEmptyByNode(GenealogicalTreeNode<T>* node);
	//ɾ��node���亢���ֵܽڵ㣬���汻ɾ���Ľڵ㵽vec��
	void makeEmptyAndSaveByNode(Vector<T>& vec, GenealogicalTreeNode<T>* node);
	//get��set����
	GenealogicalTreeNode<T>* getRoot();
	void setRoot(GenealogicalTreeNode<T>* inputRoot);
private:
	//Ѱ��node�ڵ㼰��������ָ��data�Ľڵ㲢���أ��ڲ��ݹ�
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
	//nodeΪ�գ�����
	if (node == nullptr)
	{
		return;
	}
	//ɾ�����Ӻ��ֵܽڵ�
	makeEmptyByNode(node->getFirstChild());
	makeEmptyByNode(node->getNextSibling());
	//ɾ���ڵ�
	delete node;
	node = nullptr;
}

template<typename T>
void GenealogicalTree<T>::makeEmptyAndSaveByNode(Vector<T>& vec, GenealogicalTreeNode<T>* node)
{
	//nodeΪ�գ�����
	if (node == nullptr)
	{
		return;
	}
	//ɾ�������溢�Ӻ��ֵܽڵ�
	makeEmptyAndSaveByNode(vec, node->getFirstChild());
	makeEmptyAndSaveByNode(vec, node->getNextSibling());
	//����node��data����
	vec.pushBack(node->getData());
	//ɾ���ڵ�
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
	//�Լ����ǣ�ֱ�ӷ���
	if (node->getData() == data)
	{
		return node;
	}
	GenealogicalTreeNode<T>* result = nullptr;
	//Ѱ��node�ĺ��ӽڵ�
	result = findByNode(data, node->getFirstChild());
	if (result != nullptr)
	{
		return result;
	}
	//Ѱ��node���ֵܽڵ�
	result = findByNode(data, node->getNextSibling());
	if (result != nullptr)
	{
		return result;
	}
	//���Ӻ��ֵܶ�û�ҵ�������nullptr
	return nullptr;
}



//���׹���ϵͳ��
class GenealogicalManagementSystem
{
public:
	//��ӡ�˵���
	void showMenu();
	//��ʼ��ϵͳ
	void initGenealogical();
	//�������е��˽�����ͥ
	void buildFamily();
	//չʾһ���ڵ㼰�亢�ӽڵ����Ϣ
	void showFamilyByNode(GenealogicalTreeNode<string>* parent);
	//����һ����ͥ��Ա
	void addFamilyMember();
	//��ɢ��ͥ
	void removeFamily();
	//����Ա��������
	void changeMemberName();
	//�����������׹���ϵͳ
	void runGenealogicalManagementSystem();
private:
	//���Ҫ����ĺ����Ƿ����������Ѿ������ڲ�����
	bool isChildExist(Vector<string>& child);
	//�ڼ����������Ӻ��ӣ�����ʾ��Ϣ�汾
	bool addChild(GenealogicalTreeNode<string>* parent, Vector<string>& child);
	//������
	GenealogicalTree<string> genealogicalTree;
};


void GenealogicalManagementSystem::showMenu()
{
	cout << "**\t\t���׹���ϵͳ\t\t\t**" << endl;
	//��ӡ�ָ���
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
	cout << "**\t\tA --- ���Ƽ���\t\t\t**" << endl;
	cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t\t**" << endl;
	cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t\t**" << endl;
	cout << "**\t\tD --- ���ļ�ͥ��Ա����\t\t**" << endl;
	cout << "**\t\tE --- �˳�����\t\t\t**" << endl;
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
				cout << "������ĺ��Ӵ�����������" << endl;
				return true;
			}
		}
	}
	for (int i = 0; i < child.getSize(); i++)
	{
		if (genealogicalTree.find(child[i]) != nullptr)
		{
			cout << "����ĺ���" << child[i] << "�������ԭ�г�Ա����������" << endl;
			return true;
		}
	}
	return false;
}

bool GenealogicalManagementSystem::addChild(GenealogicalTreeNode<string>* parent, Vector<string>& child)
{
	//˫�׽ڵ�Ϊ�ջ��ߺ��ӽڵ�����Ϊ�գ�����false
	if (parent == nullptr || child.isEmpty())
	{
		return false;
	}
	//�������ֲ�Ϊ�գ�������һ������
	GenealogicalTreeNode<string>* newChild = new GenealogicalTreeNode<string>(child[0]);
	parent->setFirstChild(newChild);
	newChild->setParent(parent);
	//�������Ӵ浽��һ�����ӵ��ֵܽڵ�
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
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";
	//��������
	string ancestorName;
	cin >> ancestorName;
	GenealogicalTreeNode<string>* tempRoot = new GenealogicalTreeNode<string>(ancestorName);
	genealogicalTree.setRoot(tempRoot);

	cout << "�˼��׵������ǣ�" << ancestorName << endl;
}

void GenealogicalManagementSystem::buildFamily()
{
	//������Ŀ
	int childNum = 0;
	//˫�׽ڵ�����
	string parentName;
	//�洢�������ֵ�Vector
	Vector<string> child;
	//�������е�˫�׽ڵ�
	GenealogicalTreeNode<string>* parent = nullptr;
	cout << "������Ҫ������ͥ���˵�������";
	cin >> parentName;
	//��AVL���п���Ѱ��˫�׽ڵ������
	parent = genealogicalTree.find(parentName);
	//˫�׽ڵ�Ϊ�սڵ�����Ѿ��к���
	while (parent == nullptr || parent->getFirstChild() != nullptr)
	{
		if (parent == nullptr)
		{
			cout << "���˲��ڼ����У�" << endl;
		}
		else
		{
			cout << "�����Ѿ�������ͥ��" << endl;
		}
		cout << "���������룺";
		cin >> parentName;
		parent = genealogicalTree.find(parentName);
	}
	//���뺢�ӵĸ���
	cout << "������" << parentName << "�Ķ�Ů��������";
	cin >> childNum;
	//��������ǿ�����³����
	while (cin.fail() || childNum <= 0)
	{
		cout << "������һ����������" << endl;
		cout << "���������룺";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> childNum;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//���뺢�ӵ�����
	cout << "����������" << parentName << "�Ķ�Ů��������";
	child.reSize(childNum);
	for (int i = 0; i < childNum; i++)
	{
		cin >> child[i];
	}
	//����������Ƿ��������
	while (isChildExist(child))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "��������������" << parentName << "�Ķ�Ů��������";
		for (int i = 0; i < childNum; i++)
		{
			cin >> child[i];
		}
	}
	//���뺢��
	addChild(parent, child);
	//��ʾ������Ϣ
	showFamilyByNode(parent);
	return;
}

void GenealogicalManagementSystem::showFamilyByNode(GenealogicalTreeNode<string>* parentNode)
{
	if (parentNode->getFirstChild() == nullptr)
	{
		cout << parentNode->getData() << "û�����" << endl;
		return;
	}
	else
	{
		cout << parentNode->getData() << "�ĵ�һ�������ǣ�";
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
	//�½�Ԫ�ص�˫�׽ڵ�����
	string parentName;
	//��Ԫ������
	string newMember;
	//�洢�������ֵ�Vector
	Vector<string> newMembers;
	//Ҫ�����Ա��˫�׽ڵ�
	GenealogicalTreeNode<string>* parent = nullptr;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> parentName;
	//�ڼ�������Ѱ��˫��
	parent = genealogicalTree.find(parentName);
	//û�ҵ�˫����������
	while (parent == nullptr)
	{
		cout << "���˲��ڼ����У�" << endl;
		cout << "���������룺";
		cin >> parentName;
		parent = genealogicalTree.find(parentName);
	}
	//���뺢�ӵ�����
	cout << "������" << parentName << "����Ӷ��ӣ���Ů������������";
	cin >> newMember;
	newMembers.pushBack(newMember);
	//�������������������
	while (isChildExist(newMembers))
	{
		cout << "���������룺";
		cin >> newMember;
	}
	//���뺢��
	addChild(parent, newMembers);
	//��ʾ������Ϣ
	showFamilyByNode(parent);
}

void GenealogicalManagementSystem::removeFamily()
{
	string ancestorName;
	Vector<string> deleteNodes;
	//Ҫ�Ƴ��ļ���ĸ��ڵ�
	GenealogicalTreeNode<string>* ancestorNode = nullptr;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	cin >> ancestorName;
	ancestorNode = genealogicalTree.find(ancestorName);
	//�ڵ�Ϊ�ջ��߽ڵ�Ϊ���ڵ㣬���ܽ�ɢ
	while (ancestorNode == nullptr || ancestorNode->getData() == genealogicalTree.getRoot()->getData())
	{
		//��������ǿ����Ľ�׳��
		if (ancestorNode == nullptr)
		{
			cout << "���˲��ڼ����У�" << endl;
		}
		else
		{
			cout << "���ܽ�ɢ��һ�����ȵļ�ͥ��" << endl;
		}
		cout << "���������룺";
		cin >> ancestorName;
		ancestorNode = genealogicalTree.find(ancestorName);
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << ancestorNode->getData() << endl;
	showFamilyByNode(ancestorNode);
	if (ancestorNode->getParent() != nullptr)
	{
		//��ɾ���Ľڵ�����˫�׽ڵ�ĵ�һ�����ӣ�ɾ�������ֵ�����Ϊ˫�׵ĵ�һ������
		if (ancestorNode->getParent()->getFirstChild() == ancestorNode)
		{
			ancestorNode->getParent()->setFirstChild(ancestorNode->getNextSibling());
		}
		//��ɾ���ڵ㲻����˫�׽ڵ�ĵ�һ�����ӣ�ɾ���󽫸ýڵ��ǰ���ĺ����Ϊ�Լ����
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
	//�ѽ�ɢ��ͥ�ĸ��ڵ����deleteNodes
	deleteNodes.pushBack(ancestorNode->getData());
	//�Ƴ�Ҫ��ɢ��Ա�����ﲢ����
	genealogicalTree.makeEmptyAndSaveByNode(deleteNodes, ancestorNode->getFirstChild());
	delete ancestorNode;
	ancestorNode = nullptr;
	return;
}

void GenealogicalManagementSystem::changeMemberName()
{
	//�洢�����ֺ�������
	string oldName, newName;
	GenealogicalTreeNode<string>* oldMember = nullptr;
	GenealogicalTreeNode<string>* newMember = nullptr;
	cout << "������Ҫ�����������˵�Ŀǰ������";
	cin >> oldName;
	//Ѱ�Ҵ���
	oldMember = genealogicalTree.find(oldName);
	//���û���ҵ����ˣ���������
	while (oldMember == nullptr)
	{
		cout << "���˲��ڼ����У�" << endl;
		cout << "���������룺";
		cin >> oldName;
		oldMember = genealogicalTree.find(oldName);
	}
	//�Ѿ��ҵ������Ľڵ�
	cout << "��������ĺ��������";
	cin >> newName;
	//����������Ƿ��������
	newMember = genealogicalTree.find(newName);
	//���������������������
	while (newMember != nullptr)
	{
		cout << "�������Ѵ����ڼ����У�" << endl;
		cout << "���������룺";
		cin >> newName;
		newMember = genealogicalTree.find(newName);
	}
	//��������
	oldMember->setData(newName);
	cout << oldName << "�Ѹ���Ϊ" << newName << endl;
	return;
}

void GenealogicalManagementSystem::runGenealogicalManagementSystem()
{
	//��ӡ��ʼ�˵�
	showMenu();
	//�������ȣ���ʼ��������
	initGenealogical();
	//��������Ĵ���
	string operation;
	while (true)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "������Ҫִ�еĲ�����";
		cin >> operation;
		//string���Ͳ�������switch����string�ĵ�һ���ַ����ֲ���
		switch (operation[0])
		{
		case 'A':
			//���Ƽ�ͥ
			buildFamily();
			break;
		case 'B':
			//���Ӽ�ͥ��Ա
			addFamilyMember();
			break;
		case 'C':
			//��ɢ�ֲ���ͥ
			removeFamily();
			break;
		case 'D':
			//���ļ�ͥ��Ա����
			changeMemberName();
			break;
		case 'E':
			//�˳�����
			cout << "�ɹ��˳�ϵͳ��" << endl;
			return;
		default:
			cout << "���������벻��ȷ������������!" << endl;
		}
	}
}

int main()
{
	//�������׹���ϵͳ
	GenealogicalManagementSystem genealogicalManagementSystem;
	//���г���
	genealogicalManagementSystem.runGenealogicalManagementSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}
