#include <iostream>
#include <string>
#include <limits>


using namespace std;

//学生类，用于存放学生各类信息
class Student
{
public:
	Student() = default;
	//带参构造函数
	Student(string inputExamID, string inputName, string inputSex, int inputAge, string inputExamCategory);
	//获取考号
	string getExamID();
	//重载流输入输出运算符
	friend ostream& operator<<(ostream& out, const Student& stu);
	friend istream& operator>>(istream& in, Student& stu);
	//重载等号运算符
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

//节点类，采用双向链表
template<typename T>
class Node {
public:
	Node() = default;
	//带参构造函数
	Node(T& data, Node<T>* prior, Node<T>* next);
	//获取节点值的参数
	T getData();
	//获取前驱节点、后继节点
	Node<T>* getPrior();
	Node<T>* getNext();
	//设置数据、前驱、后继的三个函数
	void setData(T& data);
	void setPrior(Node<T>* prior);
	void setNext(Node<T>* next);
private:
	//数据域
	T data;
	//前后指针域
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



//学生链表类，存储学生的信息
template<typename T>
class Linklist {
public:
	Linklist();
	~Linklist();
	//获得链表大小
	int getLinkSize();
	//根据学号索引
	Node<T>* findByStudentID(string studentID);
	//指定位置增加元素
	bool appendElem(T& data, int position);
	//删除指定学号的元素
	bool popElem(string studentID);
	//修改指定学号的学生信息
	bool changeElem(T& data, string studentID);
	//输出当前链表全部信息
	void outputLinklist();
private:
	//头结点与链表大小
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
	//删除最后一个剩余节点
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
	//没有找到目标节点时，一直循环
	while (current->getNext() != nullptr)
	{
		current = current->getNext();
		//找到节点返回节点指针
		if (current->getData().getExamID() == studentID)
		{
			return current;
		}
	}
	//未找到目标节点，返回nullptr
	return nullptr;
}

template<typename T>
bool Linklist<T>::appendElem(T& data, int position)
{
	//当插入位置不合理时，返回false
	if (position<1 || position>linkSize + 1)
	{
		return false;
	}
	Node<T>* current = head;
	//未找到位置时，循环查找
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
	//用学号查找学生
	Node<T>* current = findByStudentID(studentID);
	if (current == nullptr)
	{
		return false;
	}
	//前驱节点的后继设为当前的后继
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
	//根据学号查询学生
	Node<T>* current = findByStudentID(studentID);
	//查询不到学生信息，返回false
	if (current == nullptr)
	{
		return false;
	}
	//设置学生信息
	current->setData(data);
	return true;
}

template<typename T>
void Linklist<T>::outputLinklist()
{
	Node<T>* current = head;
	//当节点不为空时，依次输出
	while (current->getNext() != nullptr)
	{
		current = current->getNext();
		cout << current->getData() << endl;
	}
	return;
}

//学生管理系统类，为学生链表类增加各类提示信息
template<typename T>
class StudentManagement
{
public:
	//重新封装各类函数，丰富链表类的交互提示信息，增加界面友好性
	StudentManagement();
	//增删查改的四个函数
	bool appendStudent();
	bool popStudent();
	bool findStudent();
	bool changeStudent();
	//展示当前系统存在的学生信息
	void displayStudents();
private:
	//存储学生信息的链表
	Linklist<T> studentLinklist;
};

template<typename T>
StudentManagement<T>::StudentManagement()
{
	int studentNums = 0;
	cout << "首先请建立考生信息系统！" << endl;
	cout << "请输入考生人数：";
	cin >> studentNums;
	//错误处理，增强程序的健壮性
	while (cin.fail() || studentNums <= 0)
	{
		cout << "考生人数应为正整数！" << endl;
		cout << "请重新输入考生人数：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> studentNums;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别!" << endl;
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
	cout << "请输入你要插入的考生位置：";
	int position = 0;
	//输入插入的学生位置
	cin >> position;
	//判断位置是否存在，增强程序的鲁棒性
	while (position <= 0 || position > studentLinklist.getLinkSize() + 1 || cin.fail())
	{
		cout << "输入非法（插入位置应为正整数，且不超过当前最大位置+1）" << endl;
		cout << "请重新输入插入位置：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> position;
	}
	T studentInput;
	cout << "请依次输入要插入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	//输入学号，并判断输入的学号是否有重复
	cin >> studentInput;
	while (studentLinklist.findByStudentID(studentInput.getExamID()) != nullptr)
	{
		cout << "插入失败，该考号已被使用，请重新输入" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> studentInput;
	}
	//插入
	if (studentLinklist.appendElem(studentInput, position))
	{
		cout << "插入成功！" << endl;
		return true;
	}
	return false;
}

template<typename T>
bool StudentManagement<T>::popStudent()
{
	string studentID = "";
	cout << "请输入要删除的考生的考号：" << endl;
	cin >> studentID;
	//依据学号查找学生
	Node<T>* student = studentLinklist.findByStudentID(studentID);
	//未查询到学生，重新输入
	while (student == nullptr)
	{
		cout << "该考生号对应的考生不存在，请重新输入考生号" << endl;
		cin >> studentID;
		student = studentLinklist.findByStudentID(studentID);
	}
	cout << "你删除的考生信息是：" << student->getData() << endl;
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
	cout << "请输入要查找的考生的考号：" << endl;
	cin >> studentID;
	//调用链表的查询函数
	Node<T>* student = studentLinklist.findByStudentID(studentID);
	//查询失败，返回
	if (student == nullptr)
	{
		cout << "未查询到该考号所对应的考生" << endl;
		return false;
	}
	//查询成功，输出学生信息
	cout << "查询成功，考生信息如下" << endl;
	cout << "考号\t" << "姓名\t" << "性别\t" << "年龄\t" << "报考类别\t" << endl;
	cout << student->getData() << endl;
	return true;
}

template<typename T>
bool StudentManagement<T>::changeStudent()
{
	string studentID = "";
	cout << "请输入要修改的考生的考号：" << endl;
	cin >> studentID;
	//查询要修改信息的考生
	Node<T>* student = studentLinklist.findByStudentID(studentID);
	if (student == nullptr)
	{
		cout << "未查询到该考号所对应的考生" << endl;
		return false;
	}
	//查询到考生，输入新的考生信息
	cout << "请依次输入修改后的考号，姓名，性别，年龄及报考类别：" << endl;
	T changeStudent;
	cin >> changeStudent;
	//检查输入的考生信息是否与系统中的信息重复
	if (studentLinklist.findByStudentID(changeStudent.getExamID()) != nullptr)
	{
		cout << "修改失败，该考生号已经存在，请检查输入" << endl;
		return false;
	}
	//修改学生信息
	studentLinklist.changeElem(changeStudent, studentID);
	cout << "修改成功！" << endl;
	return true;
}

template<typename T>
void StudentManagement<T>::displayStudents()
{
	cout << endl;
	//打印表头
	cout << "考号\t" << "姓名\t" << "性别\t" << "年龄\t" << "报考类别\t" << endl;
	//输出学生信息
	studentLinklist.outputLinklist();
	return;
}



int main()
{
	//建立考试管理系统
	StudentManagement<Student> studentManagement;
	studentManagement.displayStudents();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	cout << endl;
	//根据各类输入进行判断要进行的操作，调用相应函数
	while (true)
	{
		cout << "请选择您要进行的操作：";
		int inputOperator = -1;
		cin >> inputOperator;
		//进行输入判断是否合法，增强程序的健壮性
		if (cin.fail() || inputOperator < 0 || inputOperator>5)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "输入有误，请重新输入" << endl;
			inputOperator = -1;
		}
		//根据输入的inputOperator来判断进行什么操作
		switch (inputOperator)
		{
		case 0:
			cout << "您已成功退出系统" << endl;
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


