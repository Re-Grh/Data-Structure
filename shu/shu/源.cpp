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
struct node2{                /*�ǵݹ�ʵ�ֺ����������ṹ��*/
	BTREE ptr;
	int flag;
};

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
		T= new node;
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
				if (Q[k]!=NULL) cout << Q[k]->data << "   ";
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
BTREE PostNext(BTREE p,BTREE T) /*�����������ĺ����̽��*/
{
	BTREE tmp =Father(p,T);        /*Ѱ�Ҹ����*/
	if (tmp == NULL) return NULL;
	if (tmp->rchild == p) return tmp;          /*��Ϊ�Һ��ӷ��ظ����*/
	else if (tmp->rtag == 0 && tmp->lchild == p) return tmp;  /*��Ϊ�����Ҹ����������Ϊ�շ��ظ����*/
	else
	{
		tmp = tmp->rchild;                                    /*��Ϊ�����Ҹ������������Ϊ��*/
		while (tmp->ltag == 1 || tmp->rtag == 1)              /*��������������ӽ�㲢����*/
		{
			if (tmp->ltag == 1) tmp = tmp->lchild;
			if (tmp->rtag == 1) tmp = tmp->rchild;
		}
	}
	return tmp;
}
void PostOrder3(BTREE T)                              /*�����������������*/
{
	cout << "�����������������:" << endl;
	BTREE  tmp = T;
	while (tmp->lchild != NULL)
	{
		tmp = tmp->lchild;
	}
	cout << tmp->data;
	while (1)
	{
		tmp = PostNext(tmp,T);
		cout << tmp->data;
		if (PostNext(tmp, T) == NULL) break;
	}
	cout << endl;
}

BTREE pre = NULL;
void InOrderTh(BTREE &L)           /*����������������*/
{
	BTREE T = L;

	if (T != NULL)
	{
		InOrderTh(T->lchild);            
		T->ltag = (T->lchild) ? 1 : 0;  /*��������������־*/
		T->rtag = (T->rchild) ? 1 : 0;
		if (pre!=NULL){                    /*����ǰ�����Ķ���*/
			if (pre->rtag == 0) pre->rchild = T;
			if (T->ltag == 0)  T->lchild = pre;
		}
		pre = T;
		InOrderTh(T->rchild);
	}
}
BTREE InNext(BTREE p)    /*���������������̽��*/
{
	BTREE tmp=p->rchild;
	if (p->rtag == 1)
	{
		while (tmp->ltag == 1)
			tmp = tmp->lchild;
	}
	return tmp;
}
void InOrder3(BTREE T)  /*�����������������*/
{
	BTREE  tmp=T;
	cout << "�����������������:" << endl;
	while (tmp->lchild != NULL)
	{
		tmp = tmp->lchild;
	}
	cout << tmp->data;
	while (1)
	{
		tmp = InNext(tmp);
		cout << tmp->data;
		if (InNext(tmp) == NULL) break;
	}
	cout << endl;
}
void PrintIn(BTREE T)   /*��ӡ����������������ϵ*/
{
	cout << "�����������ɹ�" << endl;
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
			cout << tmp->data << endl;;
			if (tmp->ltag != 1)
			{
				if (tmp->lchild != NULL)
				{
					cout << "������Ϊ:" << tmp->lchild->data << endl;
				}
				else cout << "������Ϊ:NULL"  << endl;
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
BTREE PreNext(BTREE p)  /*���������������̽��*/
{
	BTREE tmp;
	if (p->ltag == 1) tmp = p->lchild;
	else
	{
		tmp = p;
		while (tmp->rtag == 0)
		{
			tmp = tmp->rchild;
			if (tmp == NULL) goto end;
		}
		tmp = tmp->rchild;
	}
end:	return tmp;
}
void PreOrder3(BTREE T)  /*�����������������*/
{
	cout << "�����������������:" << endl;
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
void InOrder(BTREE T) /*�������ݹ��������*/
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		cout << T->data;
		InOrder(T->rchild);
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
void PreOrder2(BTREE T)  /*�������ǵݹ��������*/
{
	cout << "�������(�ǵݹ�):" << endl;
	BTREE Q[100];
	int top = 0;
	while (top != 0 || T != NULL)
	{
		while (T != NULL)
		{
			cout << T->data;
			Q[++top] = T;
			T = T->lchild;
		}
		if (top != 0)
		{
			T = Q[top--];
			T=T->rchild;
		}
	}
	cout << endl;
}
void InOrder2(BTREE T) /*�������ǵݹ��������*/
{
	cout << "�������(�ǵݹ�):" << endl;
	BTREE Q[100];
	int top = 0;
	while (top != 0 || T != NULL)
	{
		while (T != NULL)
		{
			Q[++top] = T;
			T = T->lchild;
		}
		if (top != 0)
		{
			T = Q[top--];
			cout << T->data;
			T = T->rchild;
		}
	}
	cout << endl;
}
void PostOrder2(BTREE T)  /*�������ǵݹ�������*/
{
	cout << "�������(�ǵݹ�):" << endl;
	int top=-0;
	struct node2 Q[100];
	while ( T!= NULL || top != 0)
	{
		while (T != NULL)
		{
			top++;
			Q[top].ptr = T;
			Q[top].flag = 1;
			T = T->lchild;
		}
		while(top != 0 && Q[top].flag == 2)
		{
			T = Q[top--].ptr;
			cout << T->data;
			if (top == 0)
			{
				goto end;
			}
		}
		if (top != 0)
		{
			Q[top].flag = 2;
			T = Q[top].ptr->rchild;
		}
	}
end: cout << endl;
}
void LeverOrder(BTREE T)  /*�������Ĳ������*/
{
	cout << "�������:" << endl;
	BTREE Q[100], tmp;
	int front = 0,rear=0;
	if (T != NULL) Q[++rear] = T;
	while (front != rear)
	{
		tmp = Q[++front];
		cout << tmp->data;
		if (tmp->lchild != NULL)
		{
			Q[++rear] = tmp->lchild;
		}
		if (tmp->rchild != NULL)
		{
			Q[++rear] = tmp->rchild;
		}
	}
	cout << endl;
}
 
int main()
{
	BTREE T;
	int i=0;
		cout << "��ѡ�񴴽�����������" << endl;
start:	cout << "(1:����ݹ齨��  2:����ǵݹ齨��)" << endl;  
		cin >> i;
		if (i == 1)
		{
			cout << "�밴���������㣬�ռ����#��ʾ" << endl;
			Creat1BT(T);
		}
		else if (i == 2)
		{
			cout << "�밴���������㣬�ռ����#��ʾ" << endl;
			getchar();
			T = Creat2BT();
		}
		else {
			cout << "��ѡ��������,����������" << endl;
			goto start;
		}
		PrintBT(T);
		cout << "�������:" << endl;
		PreOrder(T);
		cout << endl;
		PreOrder2(T);
		cout << "�������: " << endl;
		InOrder(T);
		cout << endl;
		InOrder2(T);
		cout << "�������: " << endl;
		PostOrder(T);
		cout << endl;
		PostOrder2(T);
		LeverOrder(T);
		InOrderTh(T);
		PrintIn(T);
		PreOrder3(T);
		InOrder3(T);
		PostOrder3(T);
	
}
