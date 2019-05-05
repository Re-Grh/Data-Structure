#include <iostream>
#include <cstring>
#include <time.h>
using namespace std;
#define SIZE 100001
int Num[SIZE];
void Swap(int &i, int &j)
{
	int tmp;
	tmp = i;
	i = j;
	j = tmp;
}
void bubble(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (a[i] > a[j]) Swap(a[i], a[j]);
		}
	}
	cout << "冒泡排序结果： " << endl;
	for (i = 0; i < n; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
}
void Quick(int a[],int left,int right)
{
	if (left < right)
	{
		int i = left, j = right;
		int key = a[left];
		while (i < j)
		{
			while (i < j&&a[j]>=key) j--;
			if (i<j) a[i++] = a[j];
			while (i<j  && a[i]<key) i++;
			if (i<j) a[j--] = a[i];
		}
		a[i] = key;
		Quick(a, left, i - 1);
		Quick(a, i + 1, right);
	}
}
void insert(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		int key = a[i];
		while(a[j]>= key&&j>-1)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
	cout << "插入排序结果： " << endl;
	for (i = 0; i < n; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
}
void xier(int a[], int n)
{
	int i, j,d,key;
	for (d = n / 2; d >= 1; d /= 2)
	{
		for (i = d; i < n; i++)
		{
			j = i - d;
			key = a[i];
			while (key < a[j]&&j>-1){
				a[j+d] = a[j];
				j -= d;
			}
			a[j + d] = key;
		}
	}
	cout << "希尔排序结果： " << endl;
	for (i = 0; i < n; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
}
void xuanze(int a[], int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[k]) k = j;
		}
		if (k != i) Swap(a[k], a[i]);
	}
	cout << "选择排序结果： " << endl;
	for (i = 0; i < n; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
}
void PushDown(int a[] ,int first, int last)
{
	int i = first;
	while (i <= last / 2)
	{
		if (i == last / 2 && last % 2 == 0)
		{
			if (a[i] < a[last]) Swap(a[i], a[last]);
			break;
		}
		else if (a[i] < a[2 * i] && a[2 * i] > a[2 * i + 1])
		{
			Swap(a[i], a[2 * i]);
			i *= 2;
		}
		else if (a[i] < a[2 * i+1] && a[2 * i] <= a[2 * i + 1])
		{
			Swap(a[i], a[2 * i+1]);
			i=i*2+1;
		}
		else break;
	}
}
void HeapSort(int a[], int n)
{
	int i;
	for (i = n; i>=1; i--) a[i] = a[i-1];
	for (i = n / 2; i >= 1; i--) PushDown(a, i, n);
	for (i = n; i >1; i--)
	{
		Swap(a[1], a[i]);
		PushDown(a, 1, i-1);
	}
	for (i = 0; i < n; i++) a[i] = a[i+1];
	cout << "堆排序结果： " << endl;
	for (i = 0; i < n; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;
}
int BinSearch1(int key, int a[],int n)
{
	int low = 0, high = n - 1,mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key > a[mid]) low = mid + 1;
		else if (key < a[mid]) high = mid - 1;
		else return mid;
	} 
	return 0;
}
int BinSearch2(int key, int a[], int i,int j)
{
	if (i>=j) return 0;
	else
	{
		int low = i, high = j - 1, mid = (low + high) / 2;
		if (key == a[mid]) return mid;
		else if (key > a[mid]) return BinSearch2(key, a, mid + 1, j);
		else return BinSearch2(key, a, i, mid);
	}
	return 0;
}

int main()
{
	int i, n, k, j,tep=1,a,c;
	clock_t start, stop;
	double s;
	while (tep)
	{
		printf("查找结构与排序方法的实现如下 \n");
		printf("0——随机生成n个不重复的待排序整数\n");
		printf("1——冒泡排序和快速排序\n");
		printf("2——插入排序和希尔排序\n");
		printf("3——选择排序和堆排序\n");
		printf("4——二分查找（递归）\n");
		printf("5——二分查找（非递归）\n");
		printf("6——退出程序\n");
		printf("请输入服务选项（0-6）:");
		cin >> a;
		switch (a)
		{
		case 0:
			system("cls");
			cout << "输入数字个数： " << endl;
			cin >> n;
			cout << "随机生成整数如下： " << endl;
			for (i = 0; i < n; i++)
			{
				Num[i] = rand() % 100000;
			}
			for (i = 0; i < n; i++)
			{
				cout << Num[i] << "  ";
			}
			printf("\n是否继续？（1.YES  2，NO  ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 1:
			system("cls");
			start = clock();
			bubble(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "冒泡排序所用时间： "<< s<<" s"<<endl;
			start = clock();
			Quick(Num, 0, n - 1);
			cout << "快速排序结果： " << endl;
			for (i = 0; i < n; i++)
			{
				cout << Num[i] << "  ";
			}
			cout << endl;
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "快速排序所用时间： " << s << " s" << endl;
			printf("是否继续？（1.YES  2，NO  ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 2:
			system("cls");
			start = clock();
			insert(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "直接插入排序所用时间： " << s << " s" << endl;
			start = clock();
			xier(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "希尔排序所用时间： " << s << " s" << endl;
			printf("是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 3:
			system("cls");
			start = clock();
			xuanze(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "选择排序所用时间： " << s << " s" << endl;
			start = clock();
			HeapSort(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "堆排序所用时间： " << s << " s" << endl;
			printf("\n是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 4:
			system("cls");
			cout << "输入搜索数字： " << endl;
			cin >> k;
			start = clock();
			j = BinSearch1(k, Num, n);
			if (j == 0) cout << "未找到对应数字。" << endl;
			else cout << "已找到对应数字，所在位置数组下标为：" << j << endl;
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "二分查找所用时间： " << s << " s" << endl;
			printf("\n是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 5:
			system("cls");
			cout << "输入搜索数字： " << endl;
			cin >> k;
			start = clock();
			j = BinSearch2(k, Num, 0, n);
			if (j == 0) cout << "未找到对应数字。" << endl;
			else cout << "已找到对应数字，所在位置数组下标为：" << j << endl;
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "二分查找所用时间： " << s << " s" << endl;
			printf("\n是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 6:
			printf("谢谢使用！");
			tep = 0;
			break;
		default:
			system("cls");
			printf("选择错误！\n");
		}
	}
	return 0;
}