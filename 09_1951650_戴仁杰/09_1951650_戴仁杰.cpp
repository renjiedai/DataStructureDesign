#include <iostream>
#include <string>
#include<limits>

using namespace std;

//AVL树节点类，存储AVL树的节点
template<typename KeyT, typename DataT>
class AVLTreeNode
{
public:
	AVLTreeNode() = default;
	AVLTreeNode(KeyT inputKey, DataT inputData);
	//保持封装性，与外界交流使用get和set函数
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
	//关键码key以及存储内容data
	KeyT key;
	DataT data;
	//树的高度，保持树平衡使用
	int height = 0;
	//AVL树的左右孩子指针
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
	//构造函数与析构函数
	AVLTree();
	~AVLTree();
	//清空整个AVL家谱树
	void makeAllEmpty();
	//向AVL树中插入数据，作为接口提供给外部使用
	AVLTreeNode<KeyT, DataT>* insert(KeyT insertKey, DataT insertData);
	//删除指定key的节点
	AVLTreeNode<KeyT, DataT>* remove(KeyT removeKey);
	//寻找指定key的节点
	AVLTreeNode<KeyT, DataT>* find(KeyT findKey);
	//改变AVL树中key的值
	bool change(KeyT changeOldKey, KeyT changeNewKey);
	//get函数
	int getSize();
	AVLTreeNode<KeyT, DataT>* getRoot();
private:
	//类内封装一个返回大值的函数
	int nodeMax(int x, int y);
	//找node节点在中序遍历下的上一个节点，用于寻找左子树最大节点
	AVLTreeNode<KeyT, DataT>* findPriorNode(AVLTreeNode<KeyT, DataT>* node);
	//找node节点在中序遍历下的下一个节点，用于寻找右子树的最小节点
	AVLTreeNode<KeyT, DataT>* findNextNode(AVLTreeNode<KeyT, DataT>* node);
	//RR平衡旋转
	AVLTreeNode<KeyT, DataT>* rotateRR(AVLTreeNode<KeyT, DataT>* node);
	//LL平衡旋转
	AVLTreeNode<KeyT, DataT>* rotateLL(AVLTreeNode<KeyT, DataT>* node);
	//LR平衡旋转
	AVLTreeNode<KeyT, DataT>* rotateLR(AVLTreeNode<KeyT, DataT>* node);
	//RL平衡旋转
	AVLTreeNode<KeyT, DataT>* rotateRL(AVLTreeNode<KeyT, DataT>* node);
	//清空node节点及其所有子孙节点，内部递归
	void makeEmptyByNode(AVLTreeNode<KeyT, DataT>* node);
	//插入元素到某个节点的子树，内部递归
	AVLTreeNode<KeyT, DataT>* insertByNode(KeyT insertKey, DataT insertData, AVLTreeNode<KeyT, DataT>* node);
	//删除某个节点下指定key值的节点，内部递归
	AVLTreeNode<KeyT, DataT>* removeByNode(KeyT removeKey, AVLTreeNode<KeyT, DataT>* node);
	//在某个节点的子树中寻找key值为findKey的元素，内部递归
	AVLTreeNode<KeyT, DataT>* findByNode(KeyT findKey, AVLTreeNode<KeyT, DataT>* node);
	//获得某个节点的子树高度
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
	//将根节点及其子孙清空
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
	//寻找到要改key的节点
	AVLTreeNode<KeyT, DataT>* changeNode = findByNode(changeOldKey, root);
	if (changeNode == nullptr)
	{
		return false;
	}
	DataT changeNodeData = changeNode->getData();
	//插入新的元素
	root = insertByNode(changeNewKey, changeNodeData, root);
	//删除旧的元素
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
	//先指向左子树
	AVLTreeNode<KeyT, DataT>* tempNode = node->getLeft();
	//左子树不为空时候，一直指向右子树
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
	//先指向右子树
	AVLTreeNode<KeyT, DataT>* tempNode = node->getRight();
	//右子树不为空时候，一直指向左子树
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
	//设置node的高度为较高子树高度+1
	node->setHeight(nodeMax(getHeightByNode(node->getLeft()), getHeightByNode(node->getRight())) + 1);
	tempNode->setHeight(nodeMax(getHeightByNode(tempNode->getLeft()), getHeightByNode(tempNode->getRight())) + 1);
	//新的根节点为tempNode
	return tempNode;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateLL(AVLTreeNode<KeyT, DataT>* node)
{
	AVLTreeNode<KeyT, DataT>* tempNode = node->getLeft();
	node->setLeft(tempNode->getRight());
	tempNode->setRight(node);
	//设置node的高度为较高子树高度+1
	node->setHeight(nodeMax(getHeightByNode(node->getLeft()), getHeightByNode(node->getRight())) + 1);
	tempNode->setHeight(nodeMax(getHeightByNode(tempNode->getLeft()), getHeightByNode(tempNode->getRight())) + 1);
	//新的根节点为tempNode
	return tempNode;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateLR(AVLTreeNode<KeyT, DataT>* node)
{
	//将根节点的左子树进行RR平衡旋转
	node->setLeft(rotateRR(node->getLeft()));
	//将根节点进行LL平衡旋转
	node = rotateLL(node);
	return node;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::rotateRL(AVLTreeNode<KeyT, DataT>* node)
{
	//将根节点的左子树进行LL平衡旋转
	node->setRight(rotateLL(node->getRight()));
	//将根节点进行RR平衡旋转
	node = rotateRR(node);
	return node;
}

template<typename KeyT, typename DataT>
void AVLTree<KeyT, DataT>::makeEmptyByNode(AVLTreeNode<KeyT, DataT>* node)
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
	size--;
	return;
}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::insertByNode(KeyT insertKey, DataT insertData, AVLTreeNode<KeyT, DataT>* node)
{
	//找到了要插入的地方，则根据数据新建节点，插入完毕
	if (node == nullptr)
	{
		node = new AVLTreeNode<KeyT, DataT>(insertKey, insertData);
	}
	//插入的key比当前节点的key大，插入到右孩子节点
	else if (insertKey > node->getKey())
	{
		node->setRight(insertByNode(insertKey, insertData, node->getRight()));
		//插入后右侧比左侧高度高了2，则发生了AVL树失衡，进行平衡旋转
		if (getHeightByNode(node->getRight()) - getHeightByNode(node->getLeft()) == 2)
		{
			//插入到了右子树的右节点，执行RR平衡旋转
			if (insertKey > node->getRight()->getKey())
			{
				node = rotateRR(node);
			}
			//插入到了右子树的左节点，执行RL平衡旋转
			else if (insertKey < node->getRight()->getKey())
			{
				node = rotateRL(node);
			}

		}
	}
	//插入的key比当前节点的key小，插入到左孩子节点
	else if (insertKey < node->getKey())
	{
		node->setLeft(insertByNode(insertKey, insertData, node->getLeft()));
		//插入后左侧比右侧高度高了2，则发生了AVL树失衡，进行平衡旋转
		if (getHeightByNode(node->getLeft()) - getHeightByNode(node->getRight()) == 2)
		{
			//插入到了左子树的左节点，执行LL平衡旋转
			if (insertKey < node->getLeft()->getKey())
			{
				node = rotateLL(node);
			}
			//插入到了左子树的右节点，执行LR平衡旋转
			else if (insertKey > node->getLeft()->getKey())
			{
				node = rotateLR(node);
			}
		}
	}
	//高度设置为较高子树高度+1
	node->setHeight(nodeMax(getHeightByNode(node->getLeft()), getHeightByNode(node->getRight())) + 1);
	return node;

}

template<typename KeyT, typename DataT>
AVLTreeNode<KeyT, DataT>* AVLTree<KeyT, DataT>::removeByNode(KeyT removeKey, AVLTreeNode<KeyT, DataT>* node)
{
	//删除的节点为空，返回，增强程序的健壮性
	if (node == nullptr)
	{
		return nullptr;
	}
	//传入节点即为要删除的节点
	if (removeKey == node->getKey())
	{
		//AVL树的左右子树均非空
		if (node->getLeft() != nullptr && node->getRight() != nullptr)
		{
			//左子树比右子树要高，用左子树里的节点替换node节点
			if (getHeightByNode(node->getLeft()) > getHeightByNode(node->getRight()))
			{
				//用左子树里最大的节点替换node
				AVLTreeNode<KeyT, DataT>* leftMaxNode = findPriorNode(node);
				node->setKey(leftMaxNode->getKey());
				node->setData(leftMaxNode->getData());
				//递归删除左子树最大节点
				node->setLeft(removeByNode(leftMaxNode->getKey(), node->getLeft()));
			}
			//左子树比右子树要矮，用右子树里的节点替换node节点
			else
			{
				//用右子树里最小的节点替换node
				AVLTreeNode<KeyT, DataT>* rightMinNode = findNextNode(node);
				node->setKey(rightMinNode->getKey());
				node->setData(rightMinNode->getData());
				//递归删除右子树最小节点
				node->setRight(removeByNode(rightMinNode->getKey(), node->getRight()));
			}
		}
		//左右子树不全满
		else
		{
			AVLTreeNode<KeyT, DataT>* tempNode = node;
			//左子树不为空
			if (node->getLeft() != nullptr)
			{
				node = node->getLeft();
			}
			//右子树不为空
			else if (node->getRight() != nullptr)
			{
				node = node->getRight();
			}
			//左右两个树都为空
			else
			{
				node = nullptr;
			}
			//释放被移除的节点
			delete tempNode;
			tempNode = nullptr;
		}
	}
	//传入节点key大于node节点的key，在右子树删除
	else if (removeKey > node->getKey())
	{
		node->setRight(removeByNode(removeKey, node->getRight()));
		//左子树比右子树高了2，相当于在左子树插入导致失衡，进行LR或LL平衡旋转
		if (getHeightByNode(node->getLeft()) - getHeightByNode(node->getRight()) == 2)
		{
			//左子树的右节点高于左子树的左节点高度，相当于在左子树的右节点插入了，要执行LR平衡旋转
			if (getHeightByNode(node->getLeft()->getRight()) > getHeightByNode(node->getLeft()->getLeft()))
			{
				node = rotateLR(node);
			}
			//左子树的右节点低于左子树的左节点高度，相当于在左子树的左节点插入了，要执行LL平衡旋转
			else
			{
				node = rotateLL(node);
			}
		}
	}
	//传入节点key小于node节点的key，在左子树删除
	else
	{
		node->setLeft(removeByNode(removeKey, node->getLeft()));
		//右子树比左子树高了2，相当于在右子树插入导致失衡，进行RL或RR平衡旋转
		if (getHeightByNode(node->getRight()) - getHeightByNode(node->getLeft()) == 2)
		{
			//右子树的左节点高于右子树的右节点高度，相当于在右子树的左节点插入了，要执行RL平衡旋转
			if (getHeightByNode(node->getRight()->getLeft()) > getHeightByNode(node->getRight()->getRight()))
			{
				node = rotateRL(node);
			}
			//右子树的左节点低于右子树的右节点高度，相当于在右子树的右节点插入了，要执行RR平衡旋转
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
	//传入的根节点为nullptr，返回nullptr
	if (node == nullptr)
	{
		return nullptr;
	}
	//目标key小于当前节点的key，寻找左孩子
	if (findKey < node->getKey())
	{
		resultNode = findByNode(findKey, node->getLeft());
		return resultNode;
	}
	//目标key大于当前节点的key，寻找右孩子
	else if (findKey > node->getKey())
	{
		resultNode = findByNode(findKey, node->getRight());
		return resultNode;
	}
	//目标key恰好等于当前节点key，返回
	else
	{
		return node;
	}
}

template<typename KeyT, typename DataT>
int AVLTree<KeyT, DataT>::getHeightByNode(AVLTreeNode<KeyT, DataT>* node)
{
	//节点为空返回0
	if (node == nullptr)
	{
		return 0;
	}
	//否则返回树高
	return node->getHeight();
}




class BsortTreeManagementSystem
{
public:
	//显示菜单
	void showMenu();
	//对递归函数封装，显示已经排序好的信息
	void showSortedNumber();
	//建立二叉排序树
	void build();
	//向排序树中插入元素
	void insert();
	//搜寻元素
	void search();
	//执行二叉排序树系统
	void runBsortTreeManagementSystem();
private:
	//显示已经排序好的信息，内部递归
	void showSortedNumberByNode(AVLTreeNode<int, int>* node);
	AVLTree<int, int> AVLtree;
};

void BsortTreeManagementSystem::showMenu()
{
	cout << "**\t\t二叉排序树\t\t\t**" << endl;
	//打印分割线
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\t1 --- 建立二叉排序树\t\t**" << endl;
	cout << "**\t\t2 --- 插入元素\t\t\t**" << endl;
	cout << "**\t\t3 --- 查询元素\t\t\t**" << endl;
	cout << "**\t\t4 --- 退出程序\t\t\t**" << endl;
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
	//建立二叉排序树之前，清空已有数据
	AVLtree.makeAllEmpty();
	int number = -1;
	cout << "Please input key to create Bsort_Tree: " << endl;
	while (true)
	{
		cin >> number;
		//输入状态错误则重新输入
		if (cin.fail())
		{
			cout << "请输入一个整数！" << endl;
			cout << "请重新输入：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			number = -1;
			continue;
		}
		//检测到输入为0，退出
		if (number == 0)
		{
			break;
		}
		//检查是否已经存在
		if (AVLtree.find(number) != nullptr)
		{
			cout << "The input key<" << number << ">is have in!" << endl;
		}
		//如果不存在，则插入
		else
		{
			AVLtree.insert(number, number);
		}
	}
	//按照从小到大输出二叉排序树的内容
	cout << "Bsort_Tree is:" << endl;
	showSortedNumber();
	cout << endl << endl;
}

void BsortTreeManagementSystem::insert()
{
	int insertNumber = -1;
	cout << "Please input key which inserted: ";
	cin >> insertNumber;
	//错误检查
	while (cin.fail())
	{
		cout << "请输入一个整数！" << endl;
		cout << "请重新输入：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> insertNumber;
	}
	//检查是否已经存在
	if (AVLtree.find(insertNumber) != nullptr)
	{
		cout << "The input key<" << insertNumber << ">is have in!" << endl;
	}
	//如果不存在，则插入
	else
	{
		AVLtree.insert(insertNumber, insertNumber);
	}
	//按照从小到大输出二叉排序树的内容
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
	//错误检查
	while (cin.fail())
	{
		cout << "请输入一个整数！" << endl;
		cout << "请重新输入：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> searchNumber;
	}
	//搜索成功
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
	//显示菜单
	showMenu();
	//输入操作的代号
	string operation;
	while (true)
	{
		cout << "Please select: ";
		cin >> operation;
		//string类型不能用于switch，用string的第一个字符区分操作
		switch (operation[0])
		{
		case '1':
			//建立二叉排序树
			build();
			break;
		case '2':
			//插入元素
			insert();
			break;
		case '3':
			//查询元素
			search();
			break;
		case '4':
			//退出程序
			cout << "Exit successfully!" << endl;
			return;
		default:
			cout << "操作数输入不正确，请重新输入!" << endl;
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
	//访问左子树
	showSortedNumberByNode(node->getLeft());
	//访问自己
	cout << node->getKey() << "->";
	//访问右子树
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


