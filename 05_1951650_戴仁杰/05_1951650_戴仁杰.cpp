#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class KeywordSearchSystem
{
public:
	//构造函数，用于构建一个关键字检索系统
	KeywordSearchSystem();
	//往文件中写入英文文本
	void inputText();
	//判断查找到的字符串是否是单词
	bool isWord(int position, int keywordLength, const string text);
	//寻找目标单词，返回找到的单词数
	int searchKeyword();
private:
	//写文件所用的文件流
	ofstream ofs;
	//文件的名字
	string filename;
	//读文件所用文件流
	ifstream ifs;
};

KeywordSearchSystem::KeywordSearchSystem()
{
	cout << "关键字检索系统" << endl;
	cout << "请输入文件名：";
	cin >> filename;
	cout << endl;
	//对文件名长度进行简单判断，防止名字为空或者过长
	while (filename.length() <= 4 || filename.length() > 255)
	{
		cout << "文件名长度不符合要求，请重新输入！" << endl;
		cin >> filename;
	}
	//文件名应以.txt结尾
	while (filename.substr(filename.length() - 4, filename.length() - 1) != ".txt")
	{
		cout << "文件名应为.txt结尾，请重新输入！" << endl;
		cin >> filename;
	}
	
	//创建一个名字为filename的文件，以写的方式打开
	ofs.open(filename, ios::out);
	//如果打开失败，则直接退出程序
	if (!ofs.is_open()) 
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
}

void KeywordSearchSystem::inputText()
{
	//暂存输入的字符串
	string text;
	cout << "请输入一段英文：" << endl;
	//利用getchar读取掉上次cin时缓冲区留下的回车
	char temp = getchar();
	//向text中输入字符串
	getline(cin, text);
	//将输入的字符串读入文件
	ofs << text;
	cout << "本段文本已保存在文本文件“" << filename << "”中。" << endl << endl;
	if (text.length() == 0)
	{
		cout << "但请注意，您输入的文本长度为0！" << endl;
	}
	//关闭文件
	ofs.close();
}

bool KeywordSearchSystem::isWord(int position, int keywordLength, const string text)
{
	//表示该单词前后字符（如果存在）
	char prior = '\0';
	char next = '\0';
	//开头单词，特殊处理
	if (position - keywordLength == -1)
	{
		next = text[position + 1];
		//后一个字符不是字母
		if (next < 'A' || next>'z' || (next > 'Z' && next < 'a'))
		{
			return true;
		}
		return false;
	}
	//结尾单词，特殊处理
	if (position == text.length() - 1)
	{
		prior = text[position - keywordLength];
		//前一个字符不是字母
		if (prior < 'A' || prior>'z' || (prior > 'Z' && prior < 'a'))
		{
			return true;
		}
		return false;
	}
	//其它单词，前后字符均不为字母，此时该子串为一个单词
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
	//存储读出的文件数据
	string text;
	//要查找的关键字
	string keyword;
	cout << "请输入要检索的关键字：";
	cin >> keyword;

	ifs.open(filename, ios::in);
	//文件打开失败，退出程序
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		exit(1);
	}
	//暂存读出的字符
	char c = '\0';
	while ((c = ifs.get()) != EOF)
	{
		text += c;
	}
	cout << "显示源文件“ " << filename << " ”：" << endl << endl;
	cout << text << endl << endl;

	//记录关键词的个数
	int keywordNum = 0;
	int* ne = new int[keyword.length()]();
	//求模式串的Next：
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
	//KMP算法匹配子串
	for (int i = 0, j = 0; i <text.length(); i++)
	{
		//遇到不匹配的情况，回退
		while (j > 0 && text[i] != keyword[j])
		{
			j = ne[j - 1];
		}
		//当前字符匹配，继续后移
		if (text[i] == keyword[j])
		{
			j++;
		}
		//出现完全匹配，进行筛选是否是单词
		if (j == keyword.length())
		{
			if (isWord(i, keyword.length(), text))
			{
				keywordNum++;
			}
			j = 0;
		}
	}
	cout << "在源文件中共检索到：" << keywordNum << "个关键字“ " << keyword << " ”" << endl;
	return keywordNum;
}

int main()
{
	//建立关键词匹配系统
	KeywordSearchSystem keywordSearchSystem;
	//写入文件
	keywordSearchSystem.inputText();
	//匹配关键词并计数
	keywordSearchSystem.searchKeyword();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}