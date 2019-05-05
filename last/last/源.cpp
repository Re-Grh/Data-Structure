#include <iostream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
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
}
void Quick(int a[], int left, int right)
{
	if (left < right)
	{
		int i = left, j = right;
		int key = a[left];
		while (i < j)
		{
			while (i < j&&a[j] >= key) j--;
			if (i<j) a[i++] = a[j];
			while (i<j  && a[i]<key) i++;
			if (i<j) a[j--] = a[i];
		}
		a[i] = key;
		Quick(a, left, i - 1);
		Quick(a, i + 1, right);
	}
}
void Quick1(int a[], int left, int right)
{
	if (left < right)
	{
		int i = left, j = right;
		srand((unsigned)time(NULL));
		int r = i + (rand() % (j - i + 1));
		int key = a[r];
		while (i < j)
		{
			while (i < j&&a[j] >= key) j--;
			if (i<j) a[i++] = a[j];
			while (i<j  && a[i]<key) i++;
			if (i<j) a[j--] = a[i];
		}
		a[i] = key;
		Quick1(a, left, i - 1);
		Quick1(a, i + 1, right);
	}
}
void insert(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		int key = a[i];
		while (a[j] >= key&&j>-1)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
void xier(int a[], int n)
{
	int i, j, d, key;
	for (d = n / 2; d >= 1; d /= 2)
	{
		for (i = d; i < n; i++)
		{
			j = i - d;
			key = a[i];
			while (key < a[j] && j>-1){
				a[j + d] = a[j];
				j -= d;
			}
			a[j + d] = key;
		}
	}
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
}
void PushDown(int a[], int first, int last)
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
		else if (a[i] < a[2 * i + 1] && a[2 * i] <= a[2 * i + 1])
		{
			Swap(a[i], a[2 * i + 1]);
			i = i * 2 + 1;
		}
		else break;
	}
}
void HeapSort(int a[], int n)
{
	int i;
	for (i = n; i >= 1; i--) a[i] = a[i - 1];
	for (i = n / 2; i >= 1; i--) PushDown(a, i, n);
	for (i = n; i >1; i--)
	{
		Swap(a[1], a[i]);
		PushDown(a, 1, i - 1);
	}
	for (i = 0; i < n; i++) a[i] = a[i + 1];
}
int BinSearch1(int key, int a[], int n)
{
	int low = 0, high = n - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key > a[mid]) low = mid + 1;
		else if (key < a[mid]) high = mid - 1;
		else return mid;
	}
	return 0;
}
int BinSearch2(int key, int a[], int i, int j)
{
	if (i >= j) return 0;
	else
	{
		int low = i, high = j - 1, mid = (low + high) / 2;
		if (key == a[mid]) return mid;
		else if (key > a[mid]) return BinSearch2(key, a, mid + 1, j);
		else return BinSearch2(key, a, i, mid);
	}
	return 0;
}
void csort(int A[],int B[],int n)
{

	int C[SIZE] = { 0 };
	for (int j = 0; j < n; j++)
	{
		C[A[j]]++;
	}

	for (int i = 1; i <= SIZE-1; i++)
	{
		C[i] += C[i - 1];
	}

	for (int j = n - 1; j >= 0; j--)
	{
		B[C[A[j]] - 1] = A[j];
		C[A[j]]--;
	}

}
int maxbit(int data[], int n)
{
	int d = 1; //保存最大的位数
	int p = 10;
	for (int i = 0; i < n; ++i)
	{
		while (data[i] >= p)
		{
			p *= 10;
			++d;
		}
	}
	return d;
}
void radixsort(int data[], int n) //基数排序
{
	int d = maxbit(data, n);
	int tmp[SIZE];
	int count[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < n; j++)
		{
			k = (data[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (data[j] / radix) % 10;
			tmp[count[k] - 1] = data[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中
			data[j] = tmp[j];
		radix = radix * 10;
	}
}
int main()
{
	int i, n, k, j, tep = 1, a, c,m;
	int b[SIZE] = { 0 };
	int d[SIZE] = { 0 };
	int e[SIZE] = { 0 };
	int f[SIZE] = { 0 };
	int g[SIZE] = { 0 };
	int h[SIZE] = { 0 };
	int l[SIZE] = { 0 };
	clock_t start, stop;
	double s;
	while (tep)
	{
		printf("查找结构与排序方法的实现如下 \n");
		printf("0——生成n个待排序整数\n");
		printf("1——2种快速排序\n");
		printf("2——插入排序和希尔排序\n");
		printf("3——选择排序和堆排序\n");
		printf("4——2种线性时间排序\n");
		printf("5——二分查找\n");
		printf("6——退出程序\n");
		printf("请输入服务选项（0-6）:");
		cin >> a;
		switch (a)
		{
		case 0:
			system("cls");
			cout << "输入数字个数： " << endl;
			cin >> n;
			cout << "输入数据分布 升序1 降序2 随机3： " << endl;
			cin >> m;
			if (m == 3)
			{
				cout << "随机生成整数如下： " << endl;
				for (i = 0; i < n; i++)
				{
					Num[i] = rand() % 100000 + rand() % 100000;
				}
			}
			if (m == 1)
			{
				cout << "升序生成整数如下： " << endl;
				for (i = 0; i < n; i++)
				{
					Num[i] = i;
				}
			}
			if (m == 2)
			{
				cout << "降序序生成整数如下： " << endl;
				for (i = 0; i < n; i++)
				{
					Num[i] = n-i;
				}
			}
			for (i = 0; i < n; i++)
			{
				b[i] = Num[i];
			}
			for (i = 0; i < n; i++)
			{
				d[i] = Num[i];
			}
			for (i = 0; i < n; i++)
			{
				e[i] = Num[i];
			}
			for (i = 0; i < n; i++)
			{
				f[i] = Num[i];
			}
			for (i = 0; i < n; i++)
			{
				g[i] = Num[i];
			}
			for (i = 0; i < n; i++)
			{
				h[i] = Num[i];
			}
			for (i = 0; i < n; i++)
			{
				l[i] = Num[i];
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
			Quick(Num, 0, n - 1);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "快速排序结果： " << endl;
			cout << "快速排序所用时间： " << s << " s" << endl;
			start = clock();
			Quick1(b, 0, n - 1);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "随机快速排序所用时间： " << s << " s" << endl;
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
			insert(d, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "排序结果： " << endl;
			cout << "直接插入排序所用时间： " << s << " s" << endl;
			start = clock();
			xier(e, n);
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
			xuanze(f, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "排序结果： " << endl;
			cout << "选择排序所用时间： " << s << " s" << endl;
			start = clock();
			HeapSort(g, n);
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
			for (i = 0; i < n; i++)
			{
				b[i] = 0;
			}
			start = clock();
			csort(h, b, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "计数排序所用时间： " << s << " s" << endl;
			start = clock();
			radixsort(l, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "基数排序所用时间： " << s << " s" << endl;
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