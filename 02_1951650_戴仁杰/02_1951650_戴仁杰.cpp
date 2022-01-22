#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

//�ڵ��࣬�洢��Ա�ı�ţ����ṩ�����ķ���
template<typename T>
class Node
{
public:
	Node() = default;
	//���ι��캯��
	Node(T numberID, Node<T>* next);
	//��õ�ǰ��Ա���
	T getNumberID();
	//��ȡ��̽ڵ�
	Node<T>* getNext();
	//���õ�ǰ��Ա���
	void setNumberID(T numberID);
	//���ú�̽ڵ�
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

//���ڴ洢��Ա��Ϣ��ѭ������ṹ
template<typename T>
class Linklist
{
public:
	Linklist();
	~Linklist();
	//����numberID�ڵ��ǰһ���ڵ��ָ�룬�����������
	Node<T>* findElemByNumberID(T numberID);
	//�������positionλ�����ӱ��ΪnumberID��Ԫ��
	bool appendElem(T numberID, int position);
	//ɾ��������ָ��numberID��Ԫ��
	bool popElem(T numberID);
	//��ʾ����ǰʣ���Ԫ��numberID
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
	//������λ�ò�����ʱ��ֱ�ӷ���
	if (position<1 || position>size + 1)
	{
		return false;
	}
	//����ѭ����Ҫ����Ľڵ�
	Node<T>* current = head;
	for (int i = 1; i < position; i++)
	{
		current = current->getNext();
	}
	//���ò���Ľڵ��Լ�����һ���ڵ�����޸�nextָ����ɲ������
	Node<T>* newNode = new Node<T>(numberID, current->getNext());
	current->setNext(newNode);
	size++;
	return true;
}

template<typename T>
bool Linklist<T>::popElem(T numberID)
{
	Node<T>* prior = findElemByNumberID(numberID);
	//δ�ҵ�������ɾ��ʧ��
	if (prior == nullptr)
	{
		return false;
	}
	//��ѯ�ɹ���Ŀ��ڵ�ɾ��
	Node<T>* next = prior->getNext()->getNext();
	delete prior->getNext();
	prior->setNext(next);
	//ɾ����ɣ������С��һ
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

//Լɪ����Ϸ�࣬�����������и��õĹ���
class JosephusGame
{
public:
	//��Ĺ��캯������ɳ�ʼ��
	JosephusGame();
	//���������Ϣ
	void insertPerson();
	//���ݱ���ɾ�����
	void killPerson();
	//չʾʣ�������Ϣ
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
	//��ʼ��������ϷҪ���е�N S M K�ȱ���
	int N, S, M, K;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K��Ϊֹ" << endl;
	cout << endl;
	//��ʽ�����Ʒ����������Ϣ�����ֶ���
	cout << left << setw(25) << "������������Ϸ��������N��";
	cin >> N;
	//���������⣬��ǿ����Ľ�׳�ԣ���ͬ
	while (cin.fail() || N <= 0)
	{
		cout << left << setw(25) << "������NӦΪ��������" << endl;
		cout << left << setw(25) << "����������������N��";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> N;
	}
	cout << left << setw(25) << "��������Ϸ��ʼ��λ��S��";
	cin >> S;
	while (cin.fail() || S <= 0)
	{
		cout << left << setw(25) << "��ʼ��λ��SӦΪ��������" << endl;
		cout << left << setw(25) << "���������뿪ʼ��λ��S��";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> S;
	}
	cout << left << setw(25) << "��������������M��";
	cin >> M;
	while (cin.fail() || M <= 0)
	{
		cout << left << setw(25) << "��������MӦΪ��������" << endl;
		cout << left << setw(25) << "������������������M��";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> M;
	}
	cout << left << setw(25) << "������ʣ�����������K��";
	cin >> K;
	while (cin.fail() || K <= 0 || K > N)
	{
		cout << left << setw(25) << "ʣ����������KӦΪ�������Ҳ�����������N��" << endl;
		cout << left << setw(25) << "����������ʣ����������K��";
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
	//���θ�numbers����ұ�ţ���1��numbers��������
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
	//���ҵ���ʼ�Ľڵ�
	for (int i = 1; i < start; i++)
	{
		startNode = startNode->getNext();
		//�����ͷ��㣬��ô������
		if (startNode == linklist.getHead())
		{
			i--;
		}
	}
	//δ�ﵽ����ʣ������ʱ��ִ��ɾ������
	while (linklist.getSize() > live)
	{	
		for (int i = 1; i < death; i++)
		{
			//�����ͷ��㣬��ô������
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
		cout << "��" << deathNumber <<  "�����ߵ�λ���ǣ�\t" << popNodeNumberID << endl;
		//�����ݴ浱ǰ����һ��ָ��
		tempStartNode = startNode->getNext();
		linklist.popElem(popNodeNumberID);
		startNode = tempStartNode;
	}
	cout << endl;
}

void JosephusGame::showLivers()
{
	Node<int>* current = linklist.getHead();
	cout << "���ʣ�£�\t" << linklist.getSize() << "��" << endl;
	cout << "ʣ�������λ��Ϊ��";
	for (int i = 0; i < linklist.getSize(); i++)
	{
		current = current->getNext();
		cout << setw(7) << current->getNumberID();
	}
	cout << endl;
}

int main()
{
	//����Լɪ����Ϸ�ಢ������в��롢ɾ����չʾ����
	JosephusGame game = JosephusGame();
	game.insertPerson();
	game.killPerson();
	game.showLivers();

# ifdef _WIN32
	system("pause");
# endif
	return 0;
}