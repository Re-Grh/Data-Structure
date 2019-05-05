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
	cout << "ð���������� " << endl;
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
	cout << "������������ " << endl;
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
	cout << "ϣ���������� " << endl;
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
	cout << "ѡ���������� " << endl;
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
	cout << "���������� " << endl;
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
		printf("���ҽṹ�����򷽷���ʵ������ \n");
		printf("0�����������n�����ظ��Ĵ���������\n");
		printf("1����ð������Ϳ�������\n");
		printf("2�������������ϣ������\n");
		printf("3����ѡ������Ͷ�����\n");
		printf("4�������ֲ��ң��ݹ飩\n");
		printf("5�������ֲ��ң��ǵݹ飩\n");
		printf("6�����˳�����\n");
		printf("���������ѡ�0-6��:");
		cin >> a;
		switch (a)
		{
		case 0:
			system("cls");
			cout << "�������ָ����� " << endl;
			cin >> n;
			cout << "��������������£� " << endl;
			for (i = 0; i < n; i++)
			{
				Num[i] = rand() % 100000;
			}
			for (i = 0; i < n; i++)
			{
				cout << Num[i] << "  ";
			}
			printf("\n�Ƿ��������1.YES  2��NO  ����");
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
			cout << "ð����������ʱ�䣺 "<< s<<" s"<<endl;
			start = clock();
			Quick(Num, 0, n - 1);
			cout << "������������ " << endl;
			for (i = 0; i < n; i++)
			{
				cout << Num[i] << "  ";
			}
			cout << endl;
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "������������ʱ�䣺 " << s << " s" << endl;
			printf("�Ƿ��������1.YES  2��NO  ����");
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
			cout << "ֱ�Ӳ�����������ʱ�䣺 " << s << " s" << endl;
			start = clock();
			xier(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "ϣ����������ʱ�䣺 " << s << " s" << endl;
			printf("�Ƿ��������1.YES  2��NO ����");
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
			cout << "ѡ����������ʱ�䣺 " << s << " s" << endl;
			start = clock();
			HeapSort(Num, n);
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "����������ʱ�䣺 " << s << " s" << endl;
			printf("\n�Ƿ��������1.YES  2��NO ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 4:
			system("cls");
			cout << "�����������֣� " << endl;
			cin >> k;
			start = clock();
			j = BinSearch1(k, Num, n);
			if (j == 0) cout << "δ�ҵ���Ӧ���֡�" << endl;
			else cout << "���ҵ���Ӧ���֣�����λ�������±�Ϊ��" << j << endl;
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "���ֲ�������ʱ�䣺 " << s << " s" << endl;
			printf("\n�Ƿ��������1.YES  2��NO ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 5:
			system("cls");
			cout << "�����������֣� " << endl;
			cin >> k;
			start = clock();
			j = BinSearch2(k, Num, 0, n);
			if (j == 0) cout << "δ�ҵ���Ӧ���֡�" << endl;
			else cout << "���ҵ���Ӧ���֣�����λ�������±�Ϊ��" << j << endl;
			stop = clock();
			s = (double)(stop - start) / CLOCKS_PER_SEC;
			cout << "���ֲ�������ʱ�䣺 " << s << " s" << endl;
			printf("\n�Ƿ��������1.YES  2��NO ����");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 6:
			printf("ллʹ�ã�");
			tep = 0;
			break;
		default:
			system("cls");
			printf("ѡ�����\n");
		}
	}
	return 0;
}