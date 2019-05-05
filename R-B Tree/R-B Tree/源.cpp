#include <iostream>
#include "RBTree.h"
#include "AVL.h"
#include "double.h"
#include <time.h>
using namespace std;
int main()
{
	clock_t start, stop;
	double s;
	int a[] = { 10, 40, 30, 60, 90, 70, 20, 50, 80,100,46,47,89,97,64,12};
	int i,j,n;
	RBTNode<int>* node;
	PNode root = NULL;
	int ilen = (sizeof(a)) / (sizeof(a[0]));
	char b[][7] = { "Tom", "Jerry", "Alex", "Kiero", "West", "Hardon", "James", "Kawaii", "May", "July", "GG", "Myth", "Jordon", "AI", "FF", "Mike" };
	string c;
	RBTree<int>* tree = new RBTree<int>();
	RBTree<int>* tree1 = new RBTree<int>();
	AVL T=NULL;
	cout << "ԭʼ����: ";
	for (i = 0; i<ilen; i++)
		cout << b[i] << "," << a[i]<<"   ";
	cout << endl;

	for (i = 0; i<ilen; i++)
	{
		tree->insert(a[i],b[i]);		
	}
	tree->print();
	tree->remove(10);
	tree->remove(60);
	tree->print();
	cout << "�����ѯֵ: " << endl;
	cin >> j;
	if ((node=tree->search(j)) != NULL) cout << "��ѯ��ֵ��Ϊ�� "<<node->w << "," <<node->key << endl;
	else cout << " δ�ҵ�: "<<endl;
	cout << "�����޸ļ�ֵ: " << endl;
	cin >> j;
	cin >> c;
	if ((node = tree->search(j)) != NULL) node->w = c;
	else cout << " δ�ҵ�: " << endl;
	cout << "�����ѯֵ: " << endl;
	cin >> j;
	if ((node = tree->search(j)) != NULL) cout << "��ѯ��ֵ��Ϊ�� " << node->w << "," << node->key << endl;
	else cout << " δ�ҵ�: " << endl;
	cout << endl;
	cout << "R-BTree & AVL: " << endl;
	cout << "������R-BTree�ڵ����������Ϣ" << endl;
	int d[101];
	cin >> n;
	for (i = 0; i < n; i++) d[i] = rand() % 100;
	start = clock();
	for (i = 0; i < n; i++) tree1->insert(d[i]);
	stop = clock();
	tree1->print();
	s = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "R-BTree's time is " << s << " s." << endl;
	start = clock();
	T = CreatAVL(T, d);
	stop = clock();
	s = (double)(stop - start) / CLOCKS_PER_SEC;
	PrintBT(T);
	cout << "AVL's time is " << s/1000 << " s." << endl;
	cout << "R-BTree & double: " << endl;
	cout << "����������ڵ����" << endl;
	int e[501];
	cin >> n;
	for (i = 0; i < n; i++) e[i] = i;
	start = clock();
	for (i = 0; i < n; i++) tree1->insert(e[i]);
	stop = clock();
	s = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "R-BTree's time is " << s << " s." << endl;
	start = clock();
	create(&root, e, n);
	stop = clock();
	s = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "double's time is " << s << " s." << endl; 
}