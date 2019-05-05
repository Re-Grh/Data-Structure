#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
struct node{                   /*������ṹ��*/
	struct node *lchild;
	struct node *rchild;
	char data;
	int ltag, rtag;
};
typedef  struct  node* BTREE;


void Creat1BT(BTREE &T)     /*����ݹ鴴��������*/
{
	char ch;
	cin >> ch;
	if (ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = new node;
		T->data = ch;
		Creat1BT(T->lchild);
		Creat1BT(T->rchild);
	}
}

BTREE Creat2BT()       /*����ǵݹ齨��������*/
{
	BTREE st[100];   /*���ָ������*/
	int i, j;
	char ch;
	BTREE bt = NULL, p;
	ch = getchar();
	for (i = 0; ch != '\n'; ch = getchar())
	{
		if (ch != '#')
		{
			p = new node;
			p->data = ch;
			p->lchild = NULL;
			p->rchild = NULL;

		}
		else
		{
			p = NULL;
		}
		st[++i] = p;
		if (i == 1) bt = p;
		else {
			j = i / 2;
			if (st[j] != NULL) {
				if (i % 2 == 0) st[j]->lchild = p;
				else st[j]->rchild = p;
			}
		}
	}
	return bt;
}
void PrintBT(BTREE T)   /*���д�ӡһ�������*/
{
	cout << "��������������:" << endl;
	BTREE Q[100], tmp;                      /*���ָ�����*/
	int front = 0, rear = 0, i = 1, j = 0, k = 1, n, flag = 0;
	if (T != NULL) Q[++rear] = T;
	while (1)
	{
		tmp = Q[++front];
		if (i == pow(2, j))                /*��2��ָ��ÿ�д�ӡ*/
		{
			for (k; k <= rear; k++)
			{
				if (Q[k] != NULL) cout << Q[k]->data << "   ";
				else  cout << "NULL   ";
			}
			j++;
			i = 0;
			cout << endl;
		}
		if (tmp != NULL)                 /*����㲻�ռ������*/
		{
			Q[++rear] = tmp->lchild;
			i++;
			Q[++rear] = tmp->rchild;
			i++;
		}
		else{                            /*�����ָ�����Ϊ��*/
			Q[rear + 1] = NULL;
			Q[rear + 2] = NULL;
			rear += 2;
		}
		for (n = front; n <= rear; n++)   /*��������ֱ�������ڲ���ΪNULL��ֹѭ��*/
		{
			if (Q[n] != NULL)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0) break;
		flag = 0;
	}
}
BTREE Father(BTREE p, BTREE T)  /*���������Ѱ�Ҹ����*/
{
	BTREE Q[100], tmp;
	if (p == T) return NULL;
	int front = 0, rear = 0;
	if (T != NULL) Q[++rear] = T;
	while (front != rear)
	{
		tmp = Q[++front];
		if (tmp->lchild == p || tmp->rchild == p) return tmp;
		if (tmp->lchild != NULL)
		{
			Q[++rear] = tmp->lchild;
		}
		if (tmp->rchild != NULL)
		{
			Q[++rear] = tmp->rchild;
		}
	}
	return NULL;
}
BTREE pre1 = NULL;
void PostOrderTh(BTREE &L)
{
	BTREE T = L;
	if (T != NULL)
	{
		PostOrderTh(T->lchild);
		PostOrderTh(T->rchild);
		T->ltag = (T->lchild) ? 1 : 0;  /*��������������־*/
		T->rtag = (T->rchild) ? 1 : 0;
		if (pre1 != NULL){                    /*����ǰ�����Ķ���*/
			if (pre1->rtag == 0) pre1->rchild = T;
			if (T->ltag == 0)  T->lchild = pre1;
		}
		pre1 = T;
	}
}
BTREE PostNext(BTREE p, BTREE T) /*�����������ĺ����̽��*/
{
	BTREE tmp = Father(p, T);        /*Ѱ�Ҹ����*/
	if (tmp == NULL) return NULL;
	if (p->rtag == 0) return p->rchild; 
	else
	{
		if (tmp->rtag == 1)
		{
			if (tmp->rchild == p) return tmp;
			tmp = tmp->rchild;                                    /*��Ϊ�����Ҹ������������Ϊ��*/
			while (tmp->ltag == 1 || tmp->rtag == 1)              /*��������������ӽ�㲢����*/
			{
				if (tmp->ltag == 1) tmp = tmp->lchild;
				if (tmp->rtag == 1) tmp = tmp->rchild;
			}
		}
	}
	return tmp;
}
void PostOrder3(BTREE T)                              /*�����������������*/
{
	cout << "��������������:" << endl;
	BTREE  tmp = T;
	while (tmp->lchild != NULL)
	{
		tmp = tmp->lchild;
	}
	cout << tmp->data;
	while (1)
	{
		tmp = PostNext(tmp, T);
		cout << tmp->data;
		if (PostNext(tmp, T) == NULL) break;
	}
	cout << endl;
}

BTREE pre = NULL;
void PreOrderTh(BTREE &L)        
{
	BTREE T = L;
	if (T != NULL)
	{
		T->ltag = (T->lchild) ? 1 : 0;  /*��������������־*/
		T->rtag = (T->rchild) ? 1 : 0;
		if (pre != NULL){                    /*����ǰ�����Ķ���*/
			if (pre->rtag == 0) pre->rchild = T;
			if (T->ltag == 0)  T->lchild = pre;
		}
		pre = T;
		if (T->ltag==1)
		PreOrderTh(T->lchild);
		if (T->rtag==1)
		PreOrderTh(T->rchild);
	}
}
BTREE PreNext(BTREE p)    /*���������������̽��*/
{
	if (p->rtag == 0) return p->rchild;
	else{
		if (p->ltag == 1) return p->lchild;
		else return p->rchild;
	}
}
void PrintIn(BTREE T)   /*��ӡ����������������ϵ*/
{
	cout <<endl<< "�������������ɹ�" << endl;
	cout << "�����ڵ�����:" << endl;
	BTREE Q[100], tmp;
	int front = 0, rear = 0;
	if (T != NULL) Q[++rear] = T;
	while (front != rear)
	{
		tmp = Q[++front];    /*����������������*/
		if (tmp->ltag == 1)
		{
			Q[++rear] = tmp->lchild;
		}
		if (tmp->rtag == 1)
		{
			Q[++rear] = tmp->rchild;
		}
		if (tmp->ltag != 1 || tmp->rtag != 1)  /*�ж�������־����ӡ*/
		{
			cout << tmp->data << endl;
			if (tmp->ltag != 1)
			{
				if (tmp->lchild != NULL)
				{
					cout << "������Ϊ:" << tmp->lchild->data << endl;
				}
				else cout << "������Ϊ:NULL" << endl;
			}
			if (tmp->rtag != 1)
			{
				if (tmp->rchild != NULL)
				{
					cout << "������Ϊ:" << tmp->rchild->data << endl;
				}
				else cout << "������Ϊ:NULL" << endl;
			}
		}
	}
}

void PreOrder3(BTREE T)  /*�����������������*/
{
	cout << "��������������:" << endl;
	BTREE  tmp = T;
	cout << tmp->data;
	while (1)
	{
		tmp = PreNext(tmp);
		cout << tmp->data;
		if (PreNext(tmp) == NULL) break;
	}
	cout << endl;
}
void PreOrder(BTREE T)  /*�������ݹ��������*/
{
	if (T != NULL)
	{
		cout << T->data;
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}
void PostOrder(BTREE T) /*�������ݹ�������*/
{
	if (T != NULL)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		cout << T->data;
	}
}

int main()
{
	BTREE T,T1;
	Creat1BT(T);
	PrintBT(T);
	cout << "�������:" << endl;
	PreOrder(T);
	PreOrderTh(T);
	PrintIn(T);
	PreOrder3(T);
	Creat1BT(T1);
	PrintBT(T1);
	cout << "�������:" << endl;
	PostOrder(T1);
	PostOrderTh(T1);
	PrintIn(T1);
	PostOrder3(T1);
}
