#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class KeywordSearchSystem
{
public:
	//���캯�������ڹ���һ���ؼ��ּ���ϵͳ
	KeywordSearchSystem();
	//���ļ���д��Ӣ���ı�
	void inputText();
	//�жϲ��ҵ����ַ����Ƿ��ǵ���
	bool isWord(int position, int keywordLength, const string text);
	//Ѱ��Ŀ�굥�ʣ������ҵ��ĵ�����
	int searchKeyword();
private:
	//д�ļ����õ��ļ���
	ofstream ofs;
	//�ļ�������
	string filename;
	//���ļ������ļ���
	ifstream ifs;
};

KeywordSearchSystem::KeywordSearchSystem()
{
	cout << "�ؼ��ּ���ϵͳ" << endl;
	cout << "�������ļ�����";
	cin >> filename;
	cout << endl;
	//���ļ������Ƚ��м��жϣ���ֹ����Ϊ�ջ��߹���
	while (filename.length() <= 4 || filename.length() > 255)
	{
		cout << "�ļ������Ȳ�����Ҫ�����������룡" << endl;
		cin >> filename;
	}
	//�ļ���Ӧ��.txt��β
	while (filename.substr(filename.length() - 4, filename.length() - 1) != ".txt")
	{
		cout << "�ļ���ӦΪ.txt��β�����������룡" << endl;
		cin >> filename;
	}
	
	//����һ������Ϊfilename���ļ�����д�ķ�ʽ��
	ofs.open(filename, ios::out);
	//�����ʧ�ܣ���ֱ���˳�����
	if (!ofs.is_open()) 
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
}

void KeywordSearchSystem::inputText()
{
	//�ݴ�������ַ���
	string text;
	cout << "������һ��Ӣ�ģ�" << endl;
	//����getchar��ȡ���ϴ�cinʱ���������µĻس�
	char temp = getchar();
	//��text�������ַ���
	getline(cin, text);
	//��������ַ��������ļ�
	ofs << text;
	cout << "�����ı��ѱ������ı��ļ���" << filename << "���С�" << endl << endl;
	if (text.length() == 0)
	{
		cout << "����ע�⣬��������ı�����Ϊ0��" << endl;
	}
	//�ر��ļ�
	ofs.close();
}

bool KeywordSearchSystem::isWord(int position, int keywordLength, const string text)
{
	//��ʾ�õ���ǰ���ַ���������ڣ�
	char prior = '\0';
	char next = '\0';
	//��ͷ���ʣ����⴦��
	if (position - keywordLength == -1)
	{
		next = text[position + 1];
		//��һ���ַ�������ĸ
		if (next < 'A' || next>'z' || (next > 'Z' && next < 'a'))
		{
			return true;
		}
		return false;
	}
	//��β���ʣ����⴦��
	if (position == text.length() - 1)
	{
		prior = text[position - keywordLength];
		//ǰһ���ַ�������ĸ
		if (prior < 'A' || prior>'z' || (prior > 'Z' && prior < 'a'))
		{
			return true;
		}
		return false;
	}
	//�������ʣ�ǰ���ַ�����Ϊ��ĸ����ʱ���Ӵ�Ϊһ������
	next = text[position + 1];
	prior = text[position - keywordLength];
	if ((prior < 'A' || prior>'z' || (prior > 'Z' && prior < 'a')) && (next < 'A' || next>'z' || (next > 'Z' && next < 'a')))
	{
		return true;
	}
	return false;
}

int KeywordSearchSystem::searchKeyword()
{
	//�洢�������ļ�����
	string text;
	//Ҫ���ҵĹؼ���
	string keyword;
	cout << "������Ҫ�����Ĺؼ��֣�";
	cin >> keyword;

	ifs.open(filename, ios::in);
	//�ļ���ʧ�ܣ��˳�����
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		exit(1);
	}
	//�ݴ�������ַ�
	char c = '\0';
	while ((c = ifs.get()) != EOF)
	{
		text += c;
	}
	cout << "��ʾԴ�ļ��� " << filename << " ����" << endl << endl;
	cout << text << endl << endl;

	//��¼�ؼ��ʵĸ���
	int keywordNum = 0;
	int* ne = new int[keyword.length()]();
	//��ģʽ����Next��
	for (int i = 1, j = 0; i < keyword.length(); i++)
	{
		while (j > 0 && keyword[i] != keyword[j])
		{
			j = ne[j - 1];
		}
		if (keyword[i] == keyword[j])
		{
			j++;
		}
		ne[i] = j;
	}
	//KMP�㷨ƥ���Ӵ�
	for (int i = 0, j = 0; i <text.length(); i++)
	{
		//������ƥ������������
		while (j > 0 && text[i] != keyword[j])
		{
			j = ne[j - 1];
		}
		//��ǰ�ַ�ƥ�䣬��������
		if (text[i] == keyword[j])
		{
			j++;
		}
		//������ȫƥ�䣬����ɸѡ�Ƿ��ǵ���
		if (j == keyword.length())
		{
			if (isWord(i, keyword.length(), text))
			{
				keywordNum++;
			}
			j = 0;
		}
	}
	cout << "��Դ�ļ��й���������" << keywordNum << "���ؼ��֡� " << keyword << " ��" << endl;
	return keywordNum;
}

int main()
{
	//�����ؼ���ƥ��ϵͳ
	KeywordSearchSystem keywordSearchSystem;
	//д���ļ�
	keywordSearchSystem.inputText();
	//ƥ��ؼ��ʲ�����
	keywordSearchSystem.searchKeyword();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}