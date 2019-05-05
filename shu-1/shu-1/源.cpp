#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;
struct node{                   /*定义结点结构体*/
	struct node *lchild;
	struct node *rchild;
	char data;
	int ltag, rtag;
};
typedef  struct  node* BTREE;


void Creat1BT(BTREE &T)     /*先序递归创建二叉树*/
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

BTREE Creat2BT()       /*层序非递归建立二叉树*/
{
	BTREE st[100];   /*结点指针数组*/
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
void PrintBT(BTREE T)   /*按行打印一株二叉树*/
{
	cout << "二叉树创建如下:" << endl;
	BTREE Q[100], tmp;                      /*结点指针队列*/
	int front = 0, rear = 0, i = 1, j = 0, k = 1, n, flag = 0;
	if (T != NULL) Q[++rear] = T;
	while (1)
	{
		tmp = Q[++front];
		if (i == pow(2, j))                /*按2的指数每行打印*/
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
		if (tmp != NULL)                 /*父结点不空即可入队*/
		{
			Q[++rear] = tmp->lchild;
			i++;
			Q[++rear] = tmp->rchild;
			i++;
		}
		else{                            /*定义空指针儿子为空*/
			Q[rear + 1] = NULL;
			Q[rear + 2] = NULL;
			rear += 2;
		}
		for (n = front; n <= rear; n++)   /*遍历队列直到队列内部均为NULL终止循环*/
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
BTREE Father(BTREE p, BTREE T)  /*按层序遍历寻找父结点*/
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
		T->ltag = (T->lchild) ? 1 : 0;  /*设置中序线索标志*/
		T->rtag = (T->rchild) ? 1 : 0;
		if (pre1 != NULL){                    /*设置前驱结点的儿子*/
			if (pre1->rtag == 0) pre1->rchild = T;
			if (T->ltag == 0)  T->lchild = pre1;
		}
		pre1 = T;
	}
}
BTREE PostNext(BTREE p, BTREE T) /*中序线索树的后序后继结点*/
{
	BTREE tmp = Father(p, T);        /*寻找父结点*/
	if (tmp == NULL) return NULL;
	if (p->rtag == 0) return p->rchild; 
	else
	{
		if (tmp->rtag == 1)
		{
			if (tmp->rchild == p) return tmp;
			tmp = tmp->rchild;                                    /*若为左孩子且父结点右子树不为空*/
			while (tmp->ltag == 1 || tmp->rtag == 1)              /*遍历父结点最深子结点并返回*/
			{
				if (tmp->ltag == 1) tmp = tmp->lchild;
				if (tmp->rtag == 1) tmp = tmp->rchild;
			}
		}
	}
	return tmp;
}
void PostOrder3(BTREE T)                              /*中序线索树后序遍历*/
{
	cout << "后序线索树遍历:" << endl;
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
		T->ltag = (T->lchild) ? 1 : 0;  /*设置中序线索标志*/
		T->rtag = (T->rchild) ? 1 : 0;
		if (pre != NULL){                    /*设置前驱结点的儿子*/
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
BTREE PreNext(BTREE p)    /*中序线索树中序后继结点*/
{
	if (p->rtag == 0) return p->rchild;
	else{
		if (p->ltag == 1) return p->lchild;
		else return p->rchild;
	}
}
void PrintIn(BTREE T)   /*打印中序线索树线索关系*/
{
	cout <<endl<< "二叉树线索化成功" << endl;
	cout << "线索节点如下:" << endl;
	BTREE Q[100], tmp;
	int front = 0, rear = 0;
	if (T != NULL) Q[++rear] = T;
	while (front != rear)
	{
		tmp = Q[++front];    /*中序线索树结点入队*/
		if (tmp->ltag == 1)
		{
			Q[++rear] = tmp->lchild;
		}
		if (tmp->rtag == 1)
		{
			Q[++rear] = tmp->rchild;
		}
		if (tmp->ltag != 1 || tmp->rtag != 1)  /*判断线索标志并打印*/
		{
			cout << tmp->data << endl;
			if (tmp->ltag != 1)
			{
				if (tmp->lchild != NULL)
				{
					cout << "左线索为:" << tmp->lchild->data << endl;
				}
				else cout << "左线索为:NULL" << endl;
			}
			if (tmp->rtag != 1)
			{
				if (tmp->rchild != NULL)
				{
					cout << "右线索为:" << tmp->rchild->data << endl;
				}
				else cout << "右线索为:NULL" << endl;
			}
		}
	}
}

void PreOrder3(BTREE T)  /*中序线索树先序遍历*/
{
	cout << "先序线索树遍历:" << endl;
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
void PreOrder(BTREE T)  /*二叉树递归先序遍历*/
{
	if (T != NULL)
	{
		cout << T->data;
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}
void PostOrder(BTREE T) /*二叉树递归后序遍历*/
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
	cout << "先序遍历:" << endl;
	PreOrder(T);
	PreOrderTh(T);
	PrintIn(T);
	PreOrder3(T);
	Creat1BT(T1);
	PrintBT(T1);
	cout << "后序遍历:" << endl;
	PostOrder(T1);
	PostOrderTh(T1);
	PrintIn(T1);
	PostOrder3(T1);
}
