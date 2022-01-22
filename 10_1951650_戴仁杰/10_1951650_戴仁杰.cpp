#include <iostream>
#include <random>
#include <ctime>
#include <limits>

using namespace std;

template <typename T>
class SortCompareSystem
{
public:
	//打印菜单
	void showMenu();
	//交换函数
	void swapNumber(T& x, T& y);
	//冒泡排序
	void bubbleSort(T tempArray[], int length);
	//选择排序
	void selectSort(T tempArray[], int length);
	//插入排序
	void insertSort(T tempArray[], int length);
	//希尔排序
	void shellSort(T tempArray[], int length);
	//快速排序
	void quickSort(T tempArray[], int left, int right);
	//堆排序
	void heapSort(T tempArray[], int length);
	//归并排序
	void mergeSort(T tempArray[], int length);
	//基数排序
	void radixSort(T tempArray[], int length);
	//运行排序比较系统
	void runSortCompareSystem();

private:
	//堆排序的下滑函数
	void siftDown(T tempArray[], int start, int max);
	//归并排序的递归函数
	void smallMergeSort(T tempArray[], int copyArray[], int left, int right);
	//由于系统random函数范围较小，编写生成随机数的函数，范围为0-999999999
	int makeSingleRandomNumber();
	//生成指定数目的随机数并存入数组
	void makeRandomNumber(int tempArray[], int length);
	
	//比较次数
	long long compareNumber = 0;
	//交换次数
	long long exchangeNumber = 0;
};

template <typename T>
void SortCompareSystem<T>::showMenu()
{
	cout << "**\t\t排序算法比较\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t1---冒泡排序\t\t\t**" << endl;
	cout << "**\t\t2---选择排序\t\t\t**" << endl;
	cout << "**\t\t3---直接插入排序\t\t**" << endl;
	cout << "**\t\t4---希尔排序\t\t\t**" << endl;
	cout << "**\t\t5---快速排序\t\t\t**" << endl;
	cout << "**\t\t6---堆排序\t\t\t**" << endl;
	cout << "**\t\t7---归并排序\t\t\t**" << endl;
	cout << "**\t\t8---基数排序\t\t\t**" << endl;
	cout << "**\t\t9---退出程序\t\t\t**" << endl;
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
	//标记是否发生了交换
	bool flag = false;
	//进行lenth-1轮起泡
	for (int i = 0; i < length - 1; i++)
	{
		flag = false;
		for (int j = 0; j < length - i - 1; j++)
		{
			//比较次数++
			compareNumber++;
			//如果出现逆序，进行交换，并置flag为true
			if (tempArray[j] > tempArray[j + 1])
			{
				swapNumber(tempArray[j], tempArray[j + 1]);
				flag = true;
			}
		}
		//如果一趟起泡没有发生交换，那么已经有序，跳出
		if (flag == false)
		{
			return;
		}
	}
}

template<typename T>
void SortCompareSystem<T>::selectSort(T tempArray[], int length)
{
	//最小元素的位置
	int min = 0;
	//length次循环选出length个最小值
	for (int i = 0; i < length; i++)
	{
		min = i;
		for (int j = i + 1; j < length; j++)
		{
			compareNumber++;
			//更新最小元素的位置
			if (tempArray[j] < tempArray[min])
			{
				min = j;
			}
		}
		//交换元素位置
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
	//依次将tempArray[1]-tempArray[length-1]插入前边已排好的序列
	for (i = 1; i < length; i++)
	{	
		temp = tempArray[i];
		//从后往前找插入的位置，若tempArray[i]小于其前驱，则向前插入
		for (j = i; j > 0 && tempArray[j - 1] > temp; j--)
		{
			compareNumber++;
			exchangeNumber++;
			//没找到位置时，一直挪位置
			tempArray[j] = tempArray[j - 1];
		}
		//如果不是走到j=0跳出的上一个for循环，则是tempArray[j - 1] <= temp，比较次数++
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
			//若tempArray[i]小于其前驱，则向前插入
			if (tempArray[i] < tempArray[i - gap])
			{
				temp = tempArray[i];
				for (j = i - gap; j >= 0 && temp < tempArray[j]; j = j - gap)
				{
					compareNumber++;
					exchangeNumber++;
					//没找到位置时，一直挪位置
					tempArray[j + gap] = tempArray[j];
				}
				//不是j<0导致退出循环，则要加上最后一次比较，比较数目++
				if (temp >= tempArray[j + gap])
				{
					compareNumber++;
				}
				//找到了插入位置
				tempArray[j + gap] = temp;
			}
		}
	}
	return;
}

template<typename T>
void SortCompareSystem<T>::quickSort(T tempArray[], int left, int right)
{
	//定义循环变量与基准
	int i = 0, j = 0;
	T pivot = 0;
	if (left >= right)
	{
		return;
	}
	//优化基准的选择，在取两端点与中点三个点中选择中间值放到数组首位
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
	//取基准
	pivot = tempArray[left];
	//如果至多2个数字，则上边的过程已经完成了排序，3个以上的数据执行下方过程
	if (left + 2 <= right)
	{
		i = left;
		j = right;
		while (true)
		{
			//根据pivot进行划分，不违反顺序继续走，违反则交换，直至完成划分break
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
	//从(length - 2) / 2逐个调整为大顶堆
	for (i = (length - 2) / 2; i >= 0; i--)
	{
		siftDown(tempArray, i, length - 1);
	}
	//将大顶堆变为从小到大的顺序
	for (i = length - 1; i > 0; i--)
	{
		swap(tempArray[0], tempArray[i]);
		siftDown(tempArray, 0, i - 1);
	}
}

template<typename T>
void SortCompareSystem<T>::mergeSort(T tempArray[], int length)
{
	//申请空间用于暂存归并数组
	T* copyArray = new T[length];
	for (int i = 0; i < length; i++)
	{
		copyArray[i] = tempArray[i];
		exchangeNumber++;
	}
	//递归进行归并排序
	smallMergeSort(tempArray, copyArray, 0, length - 1);
	delete[] copyArray;
	copyArray = nullptr;
	return;
}

template<typename T>
void SortCompareSystem<T>::radixSort(T tempArray[], int length)
{
	//int为32位，所以int可以拆分为3部分，而2048对应11位2进制
	int radix = 2048;
	int move[3] = { 0,11,22 };
	//申请length长度和radix长度的空间存储数字与分组
	int* bucket = new int[length];
	int* count = new int[radix];
	int i = 0, j = 0;
	//在2048基数下，32位int进行3次循环
	for (i = 0; i < 3; i++)
	{
		//初始化为0
		for (j = 0; j < radix; j++)
		{
			count[j] = 0;
		}
		//统计不同分组的数目
		for (j = 0; j < length; j++)
		{
			count[(tempArray[j] >> move[i]) & 2047]++;
		}
		for (j = 1; j < radix; j++)
		{
			count[j] += count[j - 1];
		}
		//完成收集
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
	//释放内存
	delete[] bucket;
	delete[] count;
}

template<typename T>
void SortCompareSystem<T>::runSortCompareSystem()
{
	//显示菜单
	showMenu();
	//要产生的随机数个数
	int number = 0;
	int choice = 0;
	string sortName = "";
	//用于计时
	clock_t start = 0, end = 0;
	cout << "请输入要产生的随机数个数：";
	cin >> number;
	//错误处理，增强程序的健壮性
	while (cin.fail() || number <= 0)
	{
		cout << "随机数的个数应为正整数！" << endl;
		cout << "请重新输入随机数个数：";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> number;
	}
	//用于存储产生的随机数
	int* numberArray = new int[number];
	makeRandomNumber(numberArray, number);
	//用于每次从numberArray复制过来测试排序
	int* tempArray = new int[number];
	while (true)
	{
		//数组复制
		for (int i = 0; i < number; i++)
		{
			tempArray[i] = numberArray[i];
		}
		cout << endl;
		cout << "请选择排序算法：" << "\t";
		cin >> choice;
		//错误处理，增强程序的健壮性
		while (cin.fail())
		{
			cout << "随机数的个数应为正整数！" << endl;
			cout << "请重新输入随机数个数：";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> choice;
		}
		sortName = "";
		exchangeNumber = 0;
		compareNumber = 0;
		//开始计时
		start = clock();
		//不同情况下的排序
		switch (choice)
		{
		case 1:
			bubbleSort(tempArray, number);
			sortName = "冒泡排序";
			break;
		case 2:
			selectSort(tempArray, number);
			sortName = "选择排序";
			break;
		case 3:
			insertSort(tempArray, number);
			sortName = "直接插入排序";
			break;
		case 4:
			shellSort(tempArray, number);
			sortName = "希尔排序";
			break;
		case 5:
			quickSort(tempArray, 0, number - 1);
			sortName = "快速排序";
			break;
		case 6:
			heapSort(tempArray, number);
			sortName = "堆排序";
			break;
		case 7:
			mergeSort(tempArray, number);
			sortName = "归并排序";
			break;
		case 8:
			radixSort(tempArray, number);
			sortName = "基数排序";
			break;
		default:
			cout << "您已成功退出系统" << endl;
			//释放内存
			delete[] numberArray;
			delete[] tempArray;
			numberArray = nullptr;
			tempArray = nullptr;
			return;
		}
		end = clock();
		cout << endl;		
		cout << sortName << "所用时间是：" << "\t" << end - start << "毫秒" << endl;
		cout << sortName << "交换次数是：" << "\t" << exchangeNumber << "次" << endl;
		cout << sortName << "比较次数是：" << "\t" << compareNumber << "次" << endl;	
	}
	//释放内存
	delete[] numberArray;
	delete[] tempArray;
	numberArray = nullptr;
	tempArray = nullptr;
	return;
}

template<typename T>
void SortCompareSystem<T>::siftDown(T tempArray[], int start, int max)
{
	//从当前位置开始
	int current = start;
	//找大孩子
	int bigChild = 2 * current + 1;
	//暂存当前位置
	T temp = tempArray[current];
	while (bigChild <= max)
	{
		if (bigChild < max)
		{
			compareNumber++;
			//先找到较大孩子的下标
			if (tempArray[bigChild] < tempArray[bigChild + 1])
			{
				bigChild++;
			}
		}
		compareNumber++;
		//根节点比较大的孩子节点大，跳出循环
		if (temp >= tempArray[bigChild])
		{
			break;
		}
		//否则当前节点的值赋值为较大孩子的值，并且继续往下判断是否符合堆的条件
		else
		{
			exchangeNumber++;
			tempArray[current] = tempArray[bigChild];
			current = bigChild;
			bigChild = 2 * bigChild + 1;
		}
	}
	//将原来的值给找到的正确位置，完成交换调整
	tempArray[current] = temp;
	return;
}

template<typename T>
void SortCompareSystem<T>::smallMergeSort(T tempArray[], int copyArray[], int left, int right)
{
	//递归终止条件
	if (left >= right)
	{
		return;
	}
	//分左右两路进行归并排序
	int middle = (left + right) / 2;
	smallMergeSort(copyArray, tempArray, left, middle);
	smallMergeSort(copyArray, tempArray, middle + 1, right);
	compareNumber++;
	//以下为二路归并的过程
	int temp1 = left;
	int temp2 = middle + 1;
	int current = left;
	//双指针法，将两段有序片段合为一个
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
	//如果左侧还没排完，排完
	while (temp1 <= middle)
	{
		tempArray[current++] = copyArray[temp1++];
		exchangeNumber++;
	}
	//如果右侧还没排完，排完
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
	//对于9位数，每一位用随机0-9来产生
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
	//产生length个随机数
	for (int i = 0; i < length; i++)
	{
		tempArray[i] = makeSingleRandomNumber();
	}
	return;
}

int main()
{
	//随机数种子
	srand((unsigned)time(NULL));
	//排序系统
	SortCompareSystem<int> sortCompareSystem;
	sortCompareSystem.runSortCompareSystem();
# ifdef _WIN32
	system("pause");
# endif
	return 0;
}

