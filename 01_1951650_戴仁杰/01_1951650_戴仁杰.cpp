#include <iostream>
#include <string>
#include <limits>


using namespace std;

//ѧ���࣬���ڴ��ѧ��������Ϣ
class Student
{
public:
	Student() = default;
	//���ι��캯��
	Student(string inputExamID, string inputName, string inputSex, int inputAge, string inputExamCategory);
	//��ȡ����
	string getExamID();
	//������������������
	friend ostream& operator<<(ostream& out, const Student& stu);
	friend istream& operator>>(istream& in, Student& stu);
	//���صȺ������
	Student& operator=(const Student& stu);

private:
	string examID;
	string name;
	string sex;
	int age = 0;
	string examCategory;

};
Student::Student(string inputExamID, string inputName, string inputSex, int inputAge, string inputExamCategory)
{
	this->examID = inputExamID;
	this->name = inputName;
	this->sex = inputSex;
	this->age = inputAge;
	this->examCategory = inputExamCategory;
}
string Student::getExamID()
{
	return this->examID;
}

ostream& operator<<(ostream& out, const Student& stu)
{
	out << stu.examID << '\t' << stu.name << '\t' << stu.sex << '\t' << stu.age << '\t' << stu.examCategory;

	return out;
}

istream& operator>>(istream& is, Student& stu)
{
	is >> stu.examID >> stu.name >> stu.sex >> stu.age >> stu.examCategory;
	return is;

}

Student& Student::operator=(const Student& stu)
{
	this->examID = stu.examID;
	this->name = stu.name;
	this->sex = stu.sex;
	this->age = stu.age;
	this->examCategory = stu.examCategory;
	return *this;
}

//�ڵ��࣬����˫������
template<typename T>
class Node {
public:
	Node() = default;
	//���ι��캯��
	Node(T& data, Node<T>* prior, Node<T>* next);
	//��ȡ�ڵ�ֵ�Ĳ���
	T getData();
	//��ȡǰ���ڵ㡢��̽ڵ�
	Node<T>* getPrior();
	Node<T>* getNext();
	//�������ݡ�ǰ������̵���������
	void setData(T& data);
	void setPrior(Node<T>* prior);
	void setNext(Node<T>* next);
private:
	//������
	T data;
	//ǰ��ָ����
	Node<T>* prior = nullptr;
	Node<T>* next = nullptr;
};

template<typename T>
Node<T>::Node(T& data, Node<T>* prior, Node<T>* next)
{
	this->data = data;
	this->prior = prior;
	this->next = next;

}
template<typename T>
T Node<T>::getData()
{
	return this->data;
}
template<typename T>
Node<T>* Node<T>::getPrior()
{
	return this->prior;
}
template<typename T>
Node<T>* Node<T>::getNext()
{
	return this->next;
}
template<typename T>
void Node<T>::setData(T& data)
{
	this->data = data;
}
template<typename T>
void Node<T>::setPrior(Node<T>* prior)
{
	this->prior = prior;
}

template<typename T>
void Node<T>::setNext(Node<T>* next)
{
	this->next = next;
}



//ѧ�������࣬�洢ѧ������Ϣ
template<typename T>
class Linklist {
public:
	Linklist();
	~Linklist();
	//��������С
	int getLinkSize();
	//����ѧ������
	Node<T>* findByStudentID(string studentID);
	//ָ��λ������Ԫ��
	bool appendElem(T& data, int position);
	//ɾ��ָ��ѧ�ŵ�Ԫ��
	bool popElem(string studentID);
	//�޸�ָ��ѧ�ŵ�ѧ����Ϣ
	bool changeElem(T& data, string studentID);
	//�����ǰ����ȫ����Ϣ
	void outputLinklist();
private:
	//ͷ����������С
	Node<T>* head;
	int linkSize = 0;
};
template<typename T>
Linklist<T>::Linklist() 
{
	head = new Node<T>;
	linkSize = 0;
}
template<typename T>
Linklist<T>::~Linklist()
{
	while (linkSize != 0)
	{
		head = head->getNext();
		delete head->getPrior();
		linkSize--;
	}
	//ɾ�����һ��ʣ��ڵ�
	delete head;
}
template<typename T>
int Linklist<T>::getLinkSize()
{
	return this->linkSize;
}

template<typename T>
Node<T>* Linklist<T>::findByStudentID(string studentID)
{
	Node<T>* current = head;
	//û���ҵ�Ŀ��ڵ�ʱ��һֱѭ��
	while (current->getNext() != nullptr)
	{
		current = current->getNext();
		//�ҵ��ڵ㷵�ؽڵ�ָ��
		if (current->getData().getExamID() == studentID)
		{
			return current;
		}
	}
	//δ�ҵ�Ŀ��ڵ㣬����nullptr
	return nullptr;
}

template<typename T>
bool Linklist<T>::appendElem(T& data, int position)
{
	//������λ�ò�����ʱ������false
	if (position<1 || position>linkSize + 1)
	{
		return false;
	}
	Node<T>* current = head;
	//δ�ҵ�λ��ʱ��ѭ������
	for (int i = 1; i < position; i++)
	{
		current = current->getNext();
	}
	Node<T>* newNode = new Node<T>(data, current, current->getNext());
	if (current->getNext() != nullptr)
	{
		current->getNext()->setPrior(newNode);
	}
	current->setNext(newNode);
	linkSize++;
	return true;
}

template<typename T>
bool Linklist<T>::popElem(string studentID)
{
	//��ѧ�Ų���ѧ��
	Node<T>* current = findByStudentID(studentID);
	if (current == nullptr)
	{
		return false;
	}
	//ǰ���ڵ�ĺ����Ϊ��ǰ�ĺ��
	current->getPrior()->setNext(current->getNext());
	if (current->getNext() != nullptr)
	{
		current->getNext()->setPrior(current->getPrior());
	}
	delete current;
	linkSize--;
	return true;
}

template<typename T>
bool Linklist<T>::changeElem(T& data, string studentID)
{
	//����ѧ�Ų�ѯѧ��
	Node<T>* current = findByStudentID(studentID);
	//��ѯ����ѧ����Ϣ������false
	if (current == nullptr)
	{
		return false;
	}
	//����ѧ����Ϣ
	current->setData(data);
	return true;
}

template<typename T>
void Linklist<T>::outputLinklist()
{
	Node<T>* current = head;
	//���ڵ㲻Ϊ��ʱ���������
	while (current->getNext() != nullptr)
	{
		current = current->getNext();
		cout << current->getData() << endl;
	}
	return;
}

//ѧ������ϵͳ�࣬Ϊѧ�����������Ӹ�����ʾ��Ϣ
template<typename T>
class StudentManagement
{
public:
	//���·�װ���ຯ�����ḻ������Ľ�����ʾ��Ϣ�����ӽ����Ѻ���
	StudentManagement();
	//��ɾ��ĵ��ĸ�����
	bool appendStudent();
	bool popStudent();
	bool findStudent();
	bool changeStudent();
	//չʾ��ǰϵͳ���ڵ�ѧ����Ϣ
	void displayStudents();
private:
	//�洢ѧ����Ϣ������
	Linklist<T> studentLinklist;
};

template<typename T>
StudentManagement<T>::StudentManagement()
{
	int studentNums = 0;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	cin >> studentNums;
	//��������ǿ����Ľ�׳��
	while (cin.fail() || studentNums <= 0)
	{
		cout << "��������ӦΪ��������" << endl;
		cout << "���������뿼��������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> studentNums;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������!" << endl;
	for (int i = 0; i < studentNums; i++)
	{
		T studentInput;
		cin >> studentInput;
		studentLinklist.appendElem(studentInput, i + 1);
	}

}

template<typename T>
bool StudentManagement<T>::appendStudent()
{
	cout << "��������Ҫ����Ŀ���λ�ã�";
	int position = 0;
	//��������ѧ��λ��
	cin >> position;
	//�ж�λ���Ƿ���ڣ���ǿ�����³����
	while (position <= 0 || position > studentLinklist.getLinkSize() + 1 || cin.fail())
	{
		cout << "����Ƿ�������λ��ӦΪ���������Ҳ�������ǰ���λ��+1��" << endl;
		cout << "�������������λ�ã�";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> position;
	}
	T studentInput;
	cout << "����������Ҫ���뿼���Ŀ��ţ��������Ա����估�������" << endl;
	//����ѧ�ţ����ж������ѧ���Ƿ����ظ�
	cin >> studentInput;
	while (studentLinklist.findByStudentID(studentInput.getExamID()) != nullptr)
	{
		cout << "����ʧ�ܣ��ÿ����ѱ�ʹ�ã�����������" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> studentInput;
	}
	//����
	if (studentLinklist.appendElem(studentInput, position))
	{
		cout << "����ɹ���" << endl;
		return true;
	}
	return false;
}

template<typename T>
bool StudentManagement<T>::popStudent()
{
	string studentID = "";
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�" << endl;
	cin >> studentID;
	//����ѧ�Ų���ѧ��
	Node<T>* student = studentLinklist.findByStudentID(studentID);
	//δ��ѯ��ѧ������������
	while (student == nullptr)
	{
		cout << "�ÿ����Ŷ�Ӧ�Ŀ��������ڣ����������뿼����" << endl;
		cin >> studentID;
		student = studentLinklist.findByStudentID(studentID);
	}
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�" << student->getData() << endl;
	if (studentLinklist.popElem(studentID))
	{
		return true;
	}
	return false;
}

template<typename T>
bool StudentManagement<T>::findStudent()
{
	string studentID = "";
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�" << endl;
	cin >> studentID;
	//��������Ĳ�ѯ����
	Node<T>* student = studentLinklist.findByStudentID(studentID);
	//��ѯʧ�ܣ�����
	if (student == nullptr)
	{
		cout << "δ��ѯ���ÿ�������Ӧ�Ŀ���" << endl;
		return false;
	}
	//��ѯ�ɹ������ѧ����Ϣ
	cout << "��ѯ�ɹ���������Ϣ����" << endl;
	cout << "����\t" << "����\t" << "�Ա�\t" << "����\t" << "�������\t" << endl;
	cout << student->getData() << endl;
	return true;
}

template<typename T>
bool StudentManagement<T>::changeStudent()
{
	string studentID = "";
	cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�" << endl;
	cin >> studentID;
	//��ѯҪ�޸���Ϣ�Ŀ���
	Node<T>* student = studentLinklist.findByStudentID(studentID);
	if (student == nullptr)
	{
		cout << "δ��ѯ���ÿ�������Ӧ�Ŀ���" << endl;
		return false;
	}
	//��ѯ�������������µĿ�����Ϣ
	cout << "�����������޸ĺ�Ŀ��ţ��������Ա����估�������" << endl;
	T changeStudent;
	cin >> changeStudent;
	//�������Ŀ�����Ϣ�Ƿ���ϵͳ�е���Ϣ�ظ�
	if (studentLinklist.findByStudentID(changeStudent.getExamID()) != nullptr)
	{
		cout << "�޸�ʧ�ܣ��ÿ������Ѿ����ڣ���������" << endl;
		return false;
	}
	//�޸�ѧ����Ϣ
	studentLinklist.changeElem(changeStudent, studentID);
	cout << "�޸ĳɹ���" << endl;
	return true;
}

template<typename T>
void StudentManagement<T>::displayStudents()
{
	cout << endl;
	//��ӡ��ͷ
	cout << "����\t" << "����\t" << "�Ա�\t" << "����\t" << "�������\t" << endl;
	//���ѧ����Ϣ
	studentLinklist.outputLinklist();
	return;
}



int main()
{
	//�������Թ���ϵͳ
	StudentManagement<Student> studentManagement;
	studentManagement.displayStudents();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cout << endl;
	//���ݸ�����������ж�Ҫ���еĲ�����������Ӧ����
	while (true)
	{
		cout << "��ѡ����Ҫ���еĲ�����";
		int inputOperator = -1;
		cin >> inputOperator;
		//���������ж��Ƿ�Ϸ�����ǿ����Ľ�׳��
		if (cin.fail() || inputOperator < 0 || inputOperator>5)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "������������������" << endl;
			inputOperator = -1;
		}
		//���������inputOperator���жϽ���ʲô����
		switch (inputOperator)
		{
		case 0:
			cout << "���ѳɹ��˳�ϵͳ" << endl;
# ifdef _WIN32
			system("pause");
# endif
			return 0;
		case 1:
			studentManagement.appendStudent();
			studentManagement.displayStudents();
			break;
		case 2:
			studentManagement.popStudent();		
			studentManagement.displayStudents();
			break;
		case 3:
			studentManagement.findStudent();
			break;
		case 4:
			studentManagement.changeStudent();
			studentManagement.displayStudents();
			break;
		case 5:
			studentManagement.displayStudents();
			break;
		default:
			break;
		}
	}
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}


