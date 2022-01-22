#include <iostream>
#include <string>
#include<limits>

using namespace std;

//AVL���ڵ��࣬�洢AVL���Ľڵ�
template<typename KeyT, typename DataT>
class AVLTreeNode
{
public:
	AVLTreeNode() = default;
	AVLTreeNode(KeyT inputKey, DataT inputData);
	//���ַ�װ�ԣ�����罻��ʹ��get��set����
	void setKey(KeyT inputKey);
	void setData(DataT inputData);
	void setHeight(int inputHeight);
	void setLeft(AVLTreeNode<KeyT, DataT>* inputLeft);
	void setRight(AVLTreeNode<KeyT, DataT>* inputRight);
	KeyT getKey();
	DataT getData();
	int getHeight();
	AVLTreeNode<KeyT, DataT>* getLeft();
	AVLTreeNode<KeyT, DataT>* getRight();
private:
	//�ؼ���key�Լ��洢����data
	KeyT key;
	DataT data;
	//���ĸ߶ȣ�������ƽ��ʹ��
	int height = 0;
	//AVL�������Һ���ָ��
	AVLTreeNode<KeyT, DataT>* left = nullptr;
	AVLTreeNode<KeyT, DataT>* right = nullptr;
};

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>::AVLTreeNode(KeyT inputKey, DataT inputData)
{
	this->key = inputKey;
	this->data = inputData;
}

template<typename KeyT, typename DataT>
void AVLTreeNode<KeyT, DataT>::setKey(KeyT inputKey)
{
	this->key = inputKey;
}

template<typename KeyT, typename DataT>
void AVLTreeNode<KeyT, DataT>::setData(DataT inputData)
{
	this->data = inputData;
}

template<typename KeyT, typename DataT>
void AVLTreeNode<KeyT, DataT>::setHeight(int inputHeight)
{
	this->height = inputHeight;
}

template<typename KeyT, typename DataT>
void AVLTreeNode<KeyT, DataT>::setLeft(AVLTreeNode<KeyT, DataT>* inputLeft)
{
	this->left = inputLeft;
}

template<typename KeyT, typename DataT>
void AVLTreeNode<KeyT, DataT>::setRight(AVLTreeNode<KeyT, DataT>* inputRight)
{
	this->right = inputRight;
}

template<typename KeyT, typename DataT>
KeyT AVLTreeNode<KeyT, DataT>::getKey()
{
	return this->key;
}

template<typename KeyT, typename DataT>
DataT AVLTreeNode<KeyT, DataT>::getData()
{
	return this->data;
}

template<typename KeyT, typename DataT>
int AVLTreeNode<KeyT, DataT>::getHeight()
{
	return this->height;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTreeNode<KeyT, DataT>::getLeft()
{
	return this->left;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTreeNode<KeyT, DataT>::getRight()
{
	return this->right;
}


template<typename KeyT, typename DataT>
class AVLTree
{
public:
	//���캯������������
	AVLTree();
	~AVLTree();
	//�������AVL������
	void makeAllEmpty();
	//��AVL���в������ݣ���Ϊ�ӿ��ṩ���ⲿʹ��
	AVLTreeNode<KeyT, DataT>* insert(KeyT insertKey, DataT insertData);
	//ɾ��ָ��key�Ľڵ�
	AVLTreeNode<KeyT, DataT>* remove(KeyT removeKey);
	//Ѱ��ָ��key�Ľڵ�
	AVLTreeNode<KeyT, DataT>* find(KeyT findKey);
	//�ı�AVL����key��ֵ
	bool change(KeyT changeOldKey, KeyT changeNewKey);
	//get����
	int getSize();
	AVLTreeNode<KeyT, DataT>* getRoot();
private:
	//���ڷ�װһ�����ش�ֵ�ĺ���
	int nodeMax(int x, int y);
	//��node�ڵ�����������µ���һ���ڵ㣬����Ѱ�����������ڵ�
	AVLTreeNode<KeyT, DataT>* findPriorNode(AVLTreeNode<KeyT, DataT>* node);
	//��node�ڵ�����������µ���һ���ڵ㣬����Ѱ������������С�ڵ�
	AVLTreeNode<KeyT, DataT>* findNextNode(AVLTreeNode<KeyT, DataT>* node);
	//RRƽ����ת
	AVLTreeNode<KeyT, DataT>* rotateRR(AVLTreeNode<KeyT, DataT>* node);
	//LLƽ����ת
	AVLTreeNode<KeyT, DataT>* rotateLL(AVLTreeNode<KeyT, DataT>* node);
	//LRƽ����ת
	AVLTreeNode<KeyT, DataT>* rotateLR(AVLTreeNode<KeyT, DataT>* node);
	//RLƽ����ת
	AVLTreeNode<KeyT, DataT>* rotateRL(AVLTreeNode<KeyT, DataT>* node);
	//���node�ڵ㼰����������ڵ㣬�ڲ��ݹ�
	void makeEmptyByNode(AVLTreeNode<KeyT, DataT>* node);
	//����Ԫ�ص�ĳ���ڵ���������ڲ��ݹ�
	AVLTreeNode<KeyT, DataT>* insertByNode(KeyT insertKey, DataT insertData, AVLTreeNode<KeyT, DataT>* node);
	//ɾ��ĳ���ڵ���ָ��keyֵ�Ľڵ㣬�ڲ��ݹ�
	AVLTreeNode<KeyT, DataT>* removeByNode(KeyT removeKey, AVLTreeNode<KeyT, DataT>* node);
	//��ĳ���ڵ��������Ѱ��keyֵΪfindKey��Ԫ�أ��ڲ��ݹ�
	AVLTreeNode<KeyT, DataT>* findByNode(KeyT findKey, AVLTreeNode<KeyT, DataT>* node);
	//���ĳ���ڵ�������߶�
	int getHeightByNode(AVLTreeNode<KeyT, DataT>* node);
	AVLTreeNode<KeyT, DataT>* root = nullptr;
	int size = 0;
};

template<typename KeyT, typename DataT>
AVLTree<KeyT, DataT>::AVLTree()
{
	this->root = nullptr;
	this->size = 0;
}

template<typename KeyT, typename DataT>
AVLTree<KeyT, DataT>::~AVLTree()
{
	makeAllEmpty();
}

template<typename KeyT, typename DataT>
void AVLTree<KeyT, DataT>::makeAllEmpty()
{
	//�����ڵ㼰���������
	makeEmptyByNode(root);
	root = nullptr;
	size = 0;
	return;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::insert(KeyT insertKey, DataT insertData)
{
	root = insertByNode(insertKey, insertData, root);
	size++;
	return root;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::remove(KeyT removeKey)
{
	if (root != nullptr)
	{
		size--;
		root = removeByNode(removeKey, root);
		return root;
	}
	return nullptr;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::find(KeyT findKey)
{
	return findByNode(findKey, root);
}

template<typename KeyT, typename DataT>
bool AVLTree<KeyT, DataT>::change(KeyT changeOldKey, KeyT changeNewKey)
{
	//Ѱ�ҵ�Ҫ��key�Ľڵ�
	AVLTreeNode<KeyT, DataT>* changeNode = findByNode(changeOldKey, root);
	if (changeNode == nullptr)
	{
		return false;
	}
	DataT changeNodeData = changeNode->getData();
	//�����µ�Ԫ��
	root = insertByNode(changeNewKey, changeNodeData, root);
	//ɾ���ɵ�Ԫ��
	root = removeByNode(changeOldKey, root);
	return true;
}

template<typename KeyT, typename DataT>
int AVLTree<KeyT, DataT>::getSize()
{
	return this->size;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::getRoot()
{
	return this->root;
}

template<typename KeyT, typename DataT>
int AVLTree<KeyT, DataT>::nodeMax(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::findPriorNode(AVLTreeNode<KeyT, DataT>* node)
{
	//��ָ��������
	AVLTreeNode<KeyT, DataT>* tempNode = node->getLeft();
	//��������Ϊ��ʱ��һֱָ��������
	if (tempNode != nullptr)
	{
		while (tempNode->getRight() != nullptr)
		{
			tempNode = tempNode->getRight();
		}
	}
	return tempNode;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::findNextNode(AVLTreeNode<KeyT, DataT>* node)
{
	//��ָ��������
	AVLTreeNode<KeyT, DataT>* tempNode = node->getRight();
	//��������Ϊ��ʱ��һֱָ��������
	if (tempNode != nullptr)
	{
		while (tempNode->getLeft() != nullptr)
		{
			tempNode = tempNode->getLeft();
		}
	}
	return tempNode;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateRR(AVLTreeNode<KeyT, DataT>* node)
{
	AVLTreeNode<KeyT, DataT>* tempNode = node->getRight();
	node->setRight(tempNode->getLeft());
	tempNode->setLeft(node);
	//����node�ĸ߶�Ϊ�ϸ������߶�+1
	node->setHeight(nodeMax(getHeightByNode(node->getLeft()), getHeightByNode(node->getRight())) + 1);
	tempNode->setHeight(nodeMax(getHeightByNode(tempNode->getLeft()), getHeightByNode(tempNode->getRight())) + 1);
	//�µĸ��ڵ�ΪtempNode
	return tempNode;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateLL(AVLTreeNode<KeyT, DataT>* node)
{
	AVLTreeNode<KeyT, DataT>* tempNode = node->getLeft();
	node->setLeft(tempNode->getRight());
	tempNode->setRight(node);
	//����node�ĸ߶�Ϊ�ϸ������߶�+1
	node->setHeight(nodeMax(getHeightByNode(node->getLeft()), getHeightByNode(node->getRight())) + 1);
	tempNode->setHeight(nodeMax(getHeightByNode(tempNode->getLeft()), getHeightByNode(tempNode->getRight())) + 1);
	//�µĸ��ڵ�ΪtempNode
	return tempNode;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateLR(AVLTreeNode<KeyT, DataT>* node)
{
	//�����ڵ������������RRƽ����ת
	node->setLeft(rotateRR(node->getLeft()));
	//�����ڵ����LLƽ����ת
	node = rotateLL(node);
	return node;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateRL(AVLTreeNode<KeyT, DataT>* node)
{
	//�����ڵ������������LLƽ����ת
	node->setRight(rotateLL(node->getRight()));
	//�����ڵ����RRƽ����ת
	node = rotateRR(node);
	return node;
}

template<typename KeyT, typename DataT>
void AVLTree<KeyT, DataT>::makeEmptyByNode(AVLTreeNode<KeyT, DataT>* node)
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
	size--;
	return;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::insertByNode(KeyT insertKey, DataT insertData, AVLTreeNode<KeyT, DataT>* node)
{
	//�ҵ���Ҫ����ĵط�������������½��ڵ㣬�������
	if (node == nullptr)
	{
		node = new AVLTreeNode<KeyT, DataT>(insertKey, insertData);
	}
	//�����key�ȵ�ǰ�ڵ��key�󣬲��뵽�Һ��ӽڵ�
	else if (insertKey > node->getKey())
	{
		node->setRight(insertByNode(insertKey, insertData, node->getRight()));
		//������Ҳ�����߶ȸ���2��������AVL��ʧ�⣬����ƽ����ת
		if (getHeightByNode(node->getRight()) - getHeightByNode(node->getLeft()) == 2)
		{
			//���뵽�����������ҽڵ㣬ִ��RRƽ����ת
			if (insertKey > node->getRight()->getKey())
			{
				node = rotateRR(node);
			}
			//���뵽������������ڵ㣬ִ��RLƽ����ת
			else if (insertKey < node->getRight()->getKey())
			{
				node = rotateRL(node);
			}

		}
	}
	//�����key�ȵ�ǰ�ڵ��keyС�����뵽���ӽڵ�
	else if (insertKey < node->getKey())
	{
		node->setLeft(insertByNode(insertKey, insertData, node->getLeft()));
		//����������Ҳ�߶ȸ���2��������AVL��ʧ�⣬����ƽ����ת
		if (getHeightByNode(node->getLeft()) - getHeightByNode(node->getRight()) == 2)
		{
			//���뵽������������ڵ㣬ִ��LLƽ����ת
			if (insertKey < node->getLeft()->getKey())
			{
				node = rotateLL(node);
			}
			//���뵽�����������ҽڵ㣬ִ��LRƽ����ת
			else if (insertKey > node->getLeft()->getKey())
			{
				node = rotateLR(node);
			}
		}
	}
	//�߶�����Ϊ�ϸ������߶�+1
	node->setHeight(nodeMax(getHeightByNode(node->getLeft()), getHeightByNode(node->getRight())) + 1);
	return node;

}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::removeByNode(KeyT removeKey, AVLTreeNode<KeyT, DataT>* node)
{
	//ɾ���Ľڵ�Ϊ�գ����أ���ǿ����Ľ�׳��
	if (node == nullptr)
	{
		return nullptr;
	}
	//����ڵ㼴ΪҪɾ���Ľڵ�
	if (removeKey == node->getKey())
	{
		//AVL���������������ǿ�
		if (node->getLeft() != nullptr && node->getRight() != nullptr)
		{
			//��������������Ҫ�ߣ�����������Ľڵ��滻node�ڵ�
			if (getHeightByNode(node->getLeft()) > getHeightByNode(node->getRight()))
			{
				//�������������Ľڵ��滻node
				AVLTreeNode<KeyT, DataT>* leftMaxNode = findPriorNode(node);
				node->setKey(leftMaxNode->getKey());
				node->setData(leftMaxNode->getData());
				//�ݹ�ɾ�����������ڵ�
				node->setLeft(removeByNode(leftMaxNode->getKey(), node->getLeft()));
			}
			//��������������Ҫ��������������Ľڵ��滻node�ڵ�
			else
			{
				//������������С�Ľڵ��滻node
				AVLTreeNode<KeyT, DataT>* rightMinNode = findNextNode(node);
				node->setKey(rightMinNode->getKey());
				node->setData(rightMinNode->getData());
				//�ݹ�ɾ����������С�ڵ�
				node->setRight(removeByNode(rightMinNode->getKey(), node->getRight()));
			}
		}
		//����������ȫ��
		else
		{
			AVLTreeNode<KeyT, DataT>* tempNode = node;
			//��������Ϊ��
			if (node->getLeft() != nullptr)
			{
				node = node->getLeft();
			}
			//��������Ϊ��
			else if (node->getRight() != nullptr)
			{
				node = node->getRight();
			}
			//������������Ϊ��
			else
			{
				node = nullptr;
			}
			//�ͷű��Ƴ��Ľڵ�
			delete tempNode;
			tempNode = nullptr;
		}
	}
	//����ڵ�key����node�ڵ��key����������ɾ��
	else if (removeKey > node->getKey())
	{
		node->setRight(removeByNode(removeKey, node->getRight()));
		//������������������2���൱�������������뵼��ʧ�⣬����LR��LLƽ����ת
		if (getHeightByNode(node->getLeft()) - getHeightByNode(node->getRight()) == 2)
		{
			//���������ҽڵ��������������ڵ�߶ȣ��൱�������������ҽڵ�����ˣ�Ҫִ��LRƽ����ת
			if (getHeightByNode(node->getLeft()->getRight()) > getHeightByNode(node->getLeft()->getLeft()))
			{
				node = rotateLR(node);
			}
			//���������ҽڵ��������������ڵ�߶ȣ��൱��������������ڵ�����ˣ�Ҫִ��LLƽ����ת
			else
			{
				node = rotateLL(node);
			}
		}
	}
	//����ڵ�keyС��node�ڵ��key����������ɾ��
	else
	{
		node->setLeft(removeByNode(removeKey, node->getLeft()));
		//������������������2���൱�������������뵼��ʧ�⣬����RL��RRƽ����ת
		if (getHeightByNode(node->getRight()) - getHeightByNode(node->getLeft()) == 2)
		{
			//����������ڵ�������������ҽڵ�߶ȣ��൱��������������ڵ�����ˣ�Ҫִ��RLƽ����ת
			if (getHeightByNode(node->getRight()->getLeft()) > getHeightByNode(node->getRight()->getRight()))
			{
				node = rotateRL(node);
			}
			//����������ڵ�������������ҽڵ�߶ȣ��൱�������������ҽڵ�����ˣ�Ҫִ��RRƽ����ת
			else
			{
				node = rotateRR(node);
			}
		}
	}
	return node;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::findByNode(KeyT findKey, AVLTreeNode<KeyT, DataT>* node)
{
	AVLTreeNode<KeyT, DataT>* resultNode = nullptr;
	//����ĸ��ڵ�Ϊnullptr������nullptr
	if (node == nullptr)
	{
		return nullptr;
	}
	//Ŀ��keyС�ڵ�ǰ�ڵ��key��Ѱ������
	if (findKey < node->getKey())
	{
		resultNode = findByNode(findKey, node->getLeft());
		return resultNode;
	}
	//Ŀ��key���ڵ�ǰ�ڵ��key��Ѱ���Һ���
	else if (findKey > node->getKey())
	{
		resultNode = findByNode(findKey, node->getRight());
		return resultNode;
	}
	//Ŀ��keyǡ�õ��ڵ�ǰ�ڵ�key������
	else
	{
		return node;
	}
}

template<typename KeyT, typename DataT>
int AVLTree<KeyT, DataT>::getHeightByNode(AVLTreeNode<KeyT, DataT>* node)
{
	//�ڵ�Ϊ�շ���0
	if (node == nullptr)
	{
		return 0;
	}
	//���򷵻�����
	return node->getHeight();
}




class BsortTreeManagementSystem
{
public:
	//��ʾ�˵�
	void showMenu();
	//�Եݹ麯����װ����ʾ�Ѿ�����õ���Ϣ
	void showSortedNumber();
	//��������������
	void build();
	//���������в���Ԫ��
	void insert();
	//��ѰԪ��
	void search();
	//ִ�ж���������ϵͳ
	void runBsortTreeManagementSystem();
private:
	//��ʾ�Ѿ�����õ���Ϣ���ڲ��ݹ�
	void showSortedNumberByNode(AVLTreeNode<int, int>* node);
	AVLTree<int, int> AVLtree;
};

void BsortTreeManagementSystem::showMenu()
{
	cout << "**\t\t����������\t\t\t**" << endl;
	//��ӡ�ָ���
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
	cout << "**\t\t1 --- ��������������\t\t**" << endl;
	cout << "**\t\t2 --- ����Ԫ��\t\t\t**" << endl;
	cout << "**\t\t3 --- ��ѯԪ��\t\t\t**" << endl;
	cout << "**\t\t4 --- �˳�����\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	return;
}

void BsortTreeManagementSystem::showSortedNumber()
{
	showSortedNumberByNode(AVLtree.getRoot());
}

void BsortTreeManagementSystem::build()
{
	//��������������֮ǰ�������������
	AVLtree.makeAllEmpty();
	int number = -1;
	cout << "Please input key to create Bsort_Tree: " << endl;
	while (true)
	{
		cin >> number;
		//����״̬��������������
		if (cin.fail())
		{
			cout << "������һ��������" << endl;
			cout << "���������룺";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			number = -1;
			continue;
		}
		//��⵽����Ϊ0���˳�
		if (number == 0)
		{
			break;
		}
		//����Ƿ��Ѿ�����
		if (AVLtree.find(number) != nullptr)
		{
			cout << "The input key<" << number << ">is have in!" << endl;
		}
		//��������ڣ������
		else
		{
			AVLtree.insert(number, number);
		}
	}
	//���մ�С�����������������������
	cout << "Bsort_Tree is:" << endl;
	showSortedNumber();
	cout << endl << endl;
}

void BsortTreeManagementSystem::insert()
{
	int insertNumber = -1;
	cout << "Please input key which inserted: ";
	cin >> insertNumber;
	//������
	while (cin.fail())
	{
		cout << "������һ��������" << endl;
		cout << "���������룺";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> insertNumber;
	}
	//����Ƿ��Ѿ�����
	if (AVLtree.find(insertNumber) != nullptr)
	{
		cout << "The input key<" << insertNumber << ">is have in!" << endl;
	}
	//��������ڣ������
	else
	{
		AVLtree.insert(insertNumber, insertNumber);
	}
	//���մ�С�����������������������
	cout << "Bsort_Tree is:" << endl;
	showSortedNumber();
	cout << endl << endl;
	return;
}

void BsortTreeManagementSystem::search()
{
	int searchNumber = -1;
	cout << "Please input key which searched: ";
	cin >> searchNumber;
	//������
	while (cin.fail())
	{
		cout << "������һ��������" << endl;
		cout << "���������룺";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> searchNumber;
	}
	//�����ɹ�
	if (AVLtree.find(searchNumber) != nullptr)
	{
		cout << "search success!" << endl;
	}
	else
	{
		cout << searchNumber << " not exist!" << endl;
	}
	cout << endl;
	return;
}

void BsortTreeManagementSystem::runBsortTreeManagementSystem()
{
	//��ʾ�˵�
	showMenu();
	//��������Ĵ���
	string operation;
	while (true)
	{
		cout << "Please select: ";
		cin >> operation;
		//string���Ͳ�������switch����string�ĵ�һ���ַ����ֲ���
		switch (operation[0])
		{
		case '1':
			//��������������
			build();
			break;
		case '2':
			//����Ԫ��
			insert();
			break;
		case '3':
			//��ѯԪ��
			search();
			break;
		case '4':
			//�˳�����
			cout << "Exit successfully!" << endl;
			return;
		default:
			cout << "���������벻��ȷ������������!" << endl;
		}
	}
	return;
}



void BsortTreeManagementSystem::showSortedNumberByNode(AVLTreeNode<int, int>* node)
{
	if (node == nullptr)
	{
		return;
	}
	//����������
	showSortedNumberByNode(node->getLeft());
	//�����Լ�
	cout << node->getKey() << "->";
	//����������
	showSortedNumberByNode(node->getRight());
	return;
}

int main()
{
	BsortTreeManagementSystem bsortTreeManagementSystem;
	bsortTreeManagementSystem.runBsortTreeManagementSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}


