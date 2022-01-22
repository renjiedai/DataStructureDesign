#include <iostream>
#include <random>
#include <ctime>
#include <limits>

using namespace std;

template <typename T>
class SortCompareSystem
{
public:
	//��ӡ�˵�
	void showMenu();
	//��������
	void swapNumber(T& x, T& y);
	//ð������
	void bubbleSort(T tempArray[], int length);
	//ѡ������
	void selectSort(T tempArray[], int length);
	//��������
	void insertSort(T tempArray[], int length);
	//ϣ������
	void shellSort(T tempArray[], int length);
	//��������
	void quickSort(T tempArray[], int left, int right);
	//������
	void heapSort(T tempArray[], int length);
	//�鲢����
	void mergeSort(T tempArray[], int length);
	//��������
	void radixSort(T tempArray[], int length);
	//��������Ƚ�ϵͳ
	void runSortCompareSystem();

private:
	//��������»�����
	void siftDown(T tempArray[], int start, int max);
	//�鲢����ĵݹ麯��
	void smallMergeSort(T tempArray[], int copyArray[], int left, int right);
	//����ϵͳrandom������Χ��С����д����������ĺ�������ΧΪ0-999999999
	int makeSingleRandomNumber();
	//����ָ����Ŀ�����������������
	void makeRandomNumber(int tempArray[], int length);
	
	//�Ƚϴ���
	long long compareNumber = 0;
	//��������
	long long exchangeNumber = 0;
};

template <typename T>
void SortCompareSystem<T>::showMenu()
{
	cout << "**\t\t�����㷨�Ƚ�\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t1---ð������\t\t\t**" << endl;
	cout << "**\t\t2---ѡ������\t\t\t**" << endl;
	cout << "**\t\t3---ֱ�Ӳ�������\t\t**" << endl;
	cout << "**\t\t4---ϣ������\t\t\t**" << endl;
	cout << "**\t\t5---��������\t\t\t**" << endl;
	cout << "**\t\t6---������\t\t\t**" << endl;
	cout << "**\t\t7---�鲢����\t\t\t**" << endl;
	cout << "**\t\t8---��������\t\t\t**" << endl;
	cout << "**\t\t9---�˳�����\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

template<typename T>
void SortCompareSystem<T>::swapNumber(T& x, T& y)
{
	exchangeNumber++;
	T temp = x;
	x = y;
	y = temp;
	return;
}

template<typename T>
void SortCompareSystem<T>::bubbleSort(T tempArray[], int length)
{
	//����Ƿ����˽���
	bool flag = false;
	//����lenth-1������
	for (int i = 0; i < length - 1; i++)
	{
		flag = false;
		for (int j = 0; j < length - i - 1; j++)
		{
			//�Ƚϴ���++
			compareNumber++;
			//����������򣬽��н���������flagΪtrue
			if (tempArray[j] > tempArray[j + 1])
			{
				swapNumber(tempArray[j], tempArray[j + 1]);
				flag = true;
			}
		}
		//���һ������û�з�����������ô�Ѿ���������
		if (flag == false)
		{
			return;
		}
	}
}

template<typename T>
void SortCompareSystem<T>::selectSort(T tempArray[], int length)
{
	//��СԪ�ص�λ��
	int min = 0;
	//length��ѭ��ѡ��length����Сֵ
	for (int i = 0; i < length; i++)
	{
		min = i;
		for (int j = i + 1; j < length; j++)
		{
			compareNumber++;
			//������СԪ�ص�λ��
			if (tempArray[j] < tempArray[min])
			{
				min = j;
			}
		}
		//����Ԫ��λ��
		if (min != i)
		{
			swapNumber(tempArray[i], tempArray[min]);
		}
	}
	return;
}

template<typename T>
void SortCompareSystem<T>::insertSort(T tempArray[], int length)
{
	int i = 0, j = 0;
	T temp = 0;
	//���ν�tempArray[1]-tempArray[length-1]����ǰ�����źõ�����
	for (i = 1; i < length; i++)
	{	
		temp = tempArray[i];
		//�Ӻ���ǰ�Ҳ����λ�ã���tempArray[i]С����ǰ��������ǰ����
		for (j = i; j > 0 && tempArray[j - 1] > temp; j--)
		{
			compareNumber++;
			exchangeNumber++;
			//û�ҵ�λ��ʱ��һֱŲλ��
			tempArray[j] = tempArray[j - 1];
		}
		//��������ߵ�j=0��������һ��forѭ��������tempArray[j - 1] <= temp���Ƚϴ���++
		if (j != 0)
		{
			compareNumber++;
		}
		tempArray[j] = temp;
	}
	return;
}

template<typename T>
void SortCompareSystem<T>::shellSort(T tempArray[], int length)
{
	int gap = 0;
	T temp = 0;
	int j = 0;
	for (gap = length / 2; gap >= 1; gap = gap / 2)
	{
		for (int i = gap; i < length; i++)
		{			
			compareNumber++;
			//��tempArray[i]С����ǰ��������ǰ����
			if (tempArray[i] < tempArray[i - gap])
			{
				temp = tempArray[i];
				for (j = i - gap; j >= 0 && temp < tempArray[j]; j = j - gap)
				{
					compareNumber++;
					exchangeNumber++;
					//û�ҵ�λ��ʱ��һֱŲλ��
					tempArray[j + gap] = tempArray[j];
				}
				//����j<0�����˳�ѭ������Ҫ�������һ�αȽϣ��Ƚ���Ŀ++
				if (temp >= tempArray[j + gap])
				{
					compareNumber++;
				}
				//�ҵ��˲���λ��
				tempArray[j + gap] = temp;
			}
		}
	}
	return;
}

template<typename T>
void SortCompareSystem<T>::quickSort(T tempArray[], int left, int right)
{
	//����ѭ���������׼
	int i = 0, j = 0;
	T pivot = 0;
	if (left >= right)
	{
		return;
	}
	//�Ż���׼��ѡ����ȡ���˵����е���������ѡ���м�ֵ�ŵ�������λ
	compareNumber += 3;
	int middle = (left + right) / 2;
	if (tempArray[right] < tempArray[middle])
	{
		swapNumber(tempArray[right], tempArray[middle]);
	}
	if (tempArray[right] < tempArray[left])
	{
		swapNumber(tempArray[right], tempArray[left]);
	}
	if (tempArray[left] < tempArray[middle])
	{
		swapNumber(tempArray[left], tempArray[middle]);
	}
	//ȡ��׼
	pivot = tempArray[left];
	//�������2�����֣����ϱߵĹ����Ѿ����������3�����ϵ�����ִ���·�����
	if (left + 2 <= right)
	{
		i = left;
		j = right;
		while (true)
		{
			//����pivot���л��֣���Υ��˳������ߣ�Υ���򽻻���ֱ����ɻ���break
			while (tempArray[++i] < pivot)
			{
				compareNumber++;
			}
			compareNumber++;
			while (tempArray[--j] > pivot)
			{
				compareNumber++;
			}
			compareNumber++;
			if (i < j)
			{
				swapNumber(tempArray[i], tempArray[j]);
			}
			else
			{
				break;
			}
		}
		swapNumber(tempArray[j], tempArray[left]);
		quickSort(tempArray, left, j);
		quickSort(tempArray, j + 1, right);
	}
}

template<typename T>
void SortCompareSystem<T>::heapSort(T tempArray[], int length)
{
	int i = 0;
	//��(length - 2) / 2�������Ϊ�󶥶�
	for (i = (length - 2) / 2; i >= 0; i--)
	{
		siftDown(tempArray, i, length - 1);
	}
	//���󶥶ѱ�Ϊ��С�����˳��
	for (i = length - 1; i > 0; i--)
	{
		swap(tempArray[0], tempArray[i]);
		siftDown(tempArray, 0, i - 1);
	}
}

template<typename T>
void SortCompareSystem<T>::mergeSort(T tempArray[], int length)
{
	//����ռ������ݴ�鲢����
	T* copyArray = new T[length];
	for (int i = 0; i < length; i++)
	{
		copyArray[i] = tempArray[i];
		exchangeNumber++;
	}
	//�ݹ���й鲢����
	smallMergeSort(tempArray, copyArray, 0, length - 1);
	delete[] copyArray;
	copyArray = nullptr;
	return;
}

template<typename T>
void SortCompareSystem<T>::radixSort(T tempArray[], int length)
{
	//intΪ32λ������int���Բ��Ϊ3���֣���2048��Ӧ11λ2����
	int radix = 2048;
	int move[3] = { 0,11,22 };
	//����length���Ⱥ�radix���ȵĿռ�洢���������
	int* bucket = new int[length];
	int* count = new int[radix];
	int i = 0, j = 0;
	//��2048�����£�32λint����3��ѭ��
	for (i = 0; i < 3; i++)
	{
		//��ʼ��Ϊ0
		for (j = 0; j < radix; j++)
		{
			count[j] = 0;
		}
		//ͳ�Ʋ�ͬ�������Ŀ
		for (j = 0; j < length; j++)
		{
			count[(tempArray[j] >> move[i]) & 2047]++;
		}
		for (j = 1; j < radix; j++)
		{
			count[j] += count[j - 1];
		}
		//����ռ�
		for (j = length - 1; j >= 0; j--)
		{
			int k = (tempArray[j] >> move[i]) & 2047;
			bucket[count[k] - 1] = tempArray[j];
			exchangeNumber++;
			count[k]--;
		}
		for (j = 0; j < length; j++)
		{
			tempArray[j] = bucket[j];
			exchangeNumber++;
		}
	}
	//�ͷ��ڴ�
	delete[] bucket;
	delete[] count;
}

template<typename T>
void SortCompareSystem<T>::runSortCompareSystem()
{
	//��ʾ�˵�
	showMenu();
	//Ҫ���������������
	int number = 0;
	int choice = 0;
	string sortName = "";
	//���ڼ�ʱ
	clock_t start = 0, end = 0;
	cout << "������Ҫ�����������������";
	cin >> number;
	//��������ǿ����Ľ�׳��
	while (cin.fail() || number <= 0)
	{
		cout << "������ĸ���ӦΪ��������" << endl;
		cout << "���������������������";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> number;
	}
	//���ڴ洢�����������
	int* numberArray = new int[number];
	makeRandomNumber(numberArray, number);
	//����ÿ�δ�numberArray���ƹ�����������
	int* tempArray = new int[number];
	while (true)
	{
		//���鸴��
		for (int i = 0; i < number; i++)
		{
			tempArray[i] = numberArray[i];
		}
		cout << endl;
		cout << "��ѡ�������㷨��" << "\t";
		cin >> choice;
		//��������ǿ����Ľ�׳��
		while (cin.fail())
		{
			cout << "������ĸ���ӦΪ��������" << endl;
			cout << "���������������������";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> choice;
		}
		sortName = "";
		exchangeNumber = 0;
		compareNumber = 0;
		//��ʼ��ʱ
		start = clock();
		//��ͬ����µ�����
		switch (choice)
		{
		case 1:
			bubbleSort(tempArray, number);
			sortName = "ð������";
			break;
		case 2:
			selectSort(tempArray, number);
			sortName = "ѡ������";
			break;
		case 3:
			insertSort(tempArray, number);
			sortName = "ֱ�Ӳ�������";
			break;
		case 4:
			shellSort(tempArray, number);
			sortName = "ϣ������";
			break;
		case 5:
			quickSort(tempArray, 0, number - 1);
			sortName = "��������";
			break;
		case 6:
			heapSort(tempArray, number);
			sortName = "������";
			break;
		case 7:
			mergeSort(tempArray, number);
			sortName = "�鲢����";
			break;
		case 8:
			radixSort(tempArray, number);
			sortName = "��������";
			break;
		default:
			cout << "���ѳɹ��˳�ϵͳ" << endl;
			//�ͷ��ڴ�
			delete[] numberArray;
			delete[] tempArray;
			numberArray = nullptr;
			tempArray = nullptr;
			return;
		}
		end = clock();
		cout << endl;		
		cout << sortName << "����ʱ���ǣ�" << "\t" << end - start << "����" << endl;
		cout << sortName << "���������ǣ�" << "\t" << exchangeNumber << "��" << endl;
		cout << sortName << "�Ƚϴ����ǣ�" << "\t" << compareNumber << "��" << endl;	
	}
	//�ͷ��ڴ�
	delete[] numberArray;
	delete[] tempArray;
	numberArray = nullptr;
	tempArray = nullptr;
	return;
}

template<typename T>
void SortCompareSystem<T>::siftDown(T tempArray[], int start, int max)
{
	//�ӵ�ǰλ�ÿ�ʼ
	int current = start;
	//�Ҵ���
	int bigChild = 2 * current + 1;
	//�ݴ浱ǰλ��
	T temp = tempArray[current];
	while (bigChild <= max)
	{
		if (bigChild < max)
		{
			compareNumber++;
			//���ҵ��ϴ��ӵ��±�
			if (tempArray[bigChild] < tempArray[bigChild + 1])
			{
				bigChild++;
			}
		}
		compareNumber++;
		//���ڵ�Ƚϴ�ĺ��ӽڵ������ѭ��
		if (temp >= tempArray[bigChild])
		{
			break;
		}
		//����ǰ�ڵ��ֵ��ֵΪ�ϴ��ӵ�ֵ�����Ҽ��������ж��Ƿ���϶ѵ�����
		else
		{
			exchangeNumber++;
			tempArray[current] = tempArray[bigChild];
			current = bigChild;
			bigChild = 2 * bigChild + 1;
		}
	}
	//��ԭ����ֵ���ҵ�����ȷλ�ã���ɽ�������
	tempArray[current] = temp;
	return;
}

template<typename T>
void SortCompareSystem<T>::smallMergeSort(T tempArray[], int copyArray[], int left, int right)
{
	//�ݹ���ֹ����
	if (left >= right)
	{
		return;
	}
	//��������·���й鲢����
	int middle = (left + right) / 2;
	smallMergeSort(copyArray, tempArray, left, middle);
	smallMergeSort(copyArray, tempArray, middle + 1, right);
	compareNumber++;
	//����Ϊ��·�鲢�Ĺ���
	int temp1 = left;
	int temp2 = middle + 1;
	int current = left;
	//˫ָ�뷨������������Ƭ�κ�Ϊһ��
	while (temp1 <= middle && temp2 <= right)
	{
		exchangeNumber++;
		compareNumber++;
		if (copyArray[temp1] <= copyArray[temp2])
		{
			tempArray[current++] = copyArray[temp1++];
		}
		else
		{
			tempArray[current++] = copyArray[temp2++];
		}
	}
	//�����໹û���꣬����
	while (temp1 <= middle)
	{
		tempArray[current++] = copyArray[temp1++];
		exchangeNumber++;
	}
	//����Ҳ໹û���꣬����
	while (temp2 <= right)
	{
		tempArray[current++] = copyArray[temp2++];
		exchangeNumber++;
	}
	return;
}

template<typename T>
int SortCompareSystem<T>::makeSingleRandomNumber()
{
	int result = 0;
	//����9λ����ÿһλ�����0-9������
	for (int i = 0; i < 9; i++)
	{
		result *= 10;
		result += rand() % 10;	
	}
	return result;
}

template<typename T>
void SortCompareSystem<T>::makeRandomNumber(int tempArray[], int length)
{
	//����length�������
	for (int i = 0; i < length; i++)
	{
		tempArray[i] = makeSingleRandomNumber();
	}
	return;
}

int main()
{
	//���������
	srand((unsigned)time(NULL));
	//����ϵͳ
	SortCompareSystem<int> sortCompareSystem;
	sortCompareSystem.runSortCompareSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}

