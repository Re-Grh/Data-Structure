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
struct node2{                /*非递归实现后序遍历所需结构体*/
	BTREE ptr;
	int flag;
};

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
		T= new node;
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
				if (Q[k]!=NULL) cout << Q[k]->data << "   ";
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
BTREE PostNext(BTREE p,BTREE T) /*中序线索树的后序后继结点*/
{
	BTREE tmp =Father(p,T);        /*寻找父结点*/
	if (tmp == NULL) return NULL;
	if (tmp->rchild == p) return tmp;          /*若为右孩子返回父结点*/
	else if (tmp->rtag == 0 && tmp->lchild == p) return tmp;  /*若为左孩子且父结点右子树为空返回父结点*/
	else
	{
		tmp = tmp->rchild;                                    /*若为左孩子且父结点右子树不为空*/
		while (tmp->ltag == 1 || tmp->rtag == 1)              /*遍历父结点最深子结点并返回*/
		{
			if (tmp->ltag == 1) tmp = tmp->lchild;
			if (tmp->rtag == 1) tmp = tmp->rchild;
		}
	}
	return tmp;
}
void PostOrder3(BTREE T)                              /*中序线索树后序遍历*/
{
	cout << "中序线索树后序遍历:" << endl;
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
void InOrderTh(BTREE &L)           /*二叉树中序线索化*/
{
	BTREE T = L;

	if (T != NULL)
	{
		InOrderTh(T->lchild);            
		T->ltag = (T->lchild) ? 1 : 0;  /*设置中序线索标志*/
		T->rtag = (T->rchild) ? 1 : 0;
		if (pre!=NULL){                    /*设置前驱结点的儿子*/
			if (pre->rtag == 0) pre->rchild = T;
			if (T->ltag == 0)  T->lchild = pre;
		}
		pre = T;
		InOrderTh(T->rchild);
	}
}
BTREE InNext(BTREE p)    /*中序线索树中序后继结点*/
{
	BTREE tmp=p->rchild;
	if (p->rtag == 1)
	{
		while (tmp->ltag == 1)
			tmp = tmp->lchild;
	}
	return tmp;
}
void InOrder3(BTREE T)  /*中序线索树中序遍历*/
{
	BTREE  tmp=T;
	cout << "中序线索树中序遍历:" << endl;
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
void PrintIn(BTREE T)   /*打印中序线索树线索关系*/
{
	cout << "中序线索化成功" << endl;
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
			cout << tmp->data << endl;;
			if (tmp->ltag != 1)
			{
				if (tmp->lchild != NULL)
				{
					cout << "左线索为:" << tmp->lchild->data << endl;
				}
				else cout << "左线索为:NULL"  << endl;
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
BTREE PreNext(BTREE p)  /*中序线索树先序后继结点*/
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
void PreOrder3(BTREE T)  /*中序线索树先序遍历*/
{
	cout << "中序线索树先序遍历:" << endl;
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
void InOrder(BTREE T) /*二叉树递归中序遍历*/
{
	if (T != NULL)
	{
		InOrder(T->lchild);
		cout << T->data;
		InOrder(T->rchild);
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
void PreOrder2(BTREE T)  /*二叉树非递归先序遍历*/
{
	cout << "先序遍历(非递归):" << endl;
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
void InOrder2(BTREE T) /*二叉树非递归中序遍历*/
{
	cout << "中序遍历(非递归):" << endl;
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
void PostOrder2(BTREE T)  /*二叉树非递归后序遍历*/
{
	cout << "后序遍历(非递归):" << endl;
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
void LeverOrder(BTREE T)  /*二叉树的层序遍历*/
{
	cout << "层序遍历:" << endl;
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
		cout << "请选择创建二叉树方法" << endl;
start:	cout << "(1:先序递归建立  2:层序非递归建立)" << endl;  
		cin >> i;
		if (i == 1)
		{
			cout << "请按先序输入结点，空间点用#表示" << endl;
			Creat1BT(T);
		}
		else if (i == 2)
		{
			cout << "请按层序输入结点，空间点用#表示" << endl;
			getchar();
			T = Creat2BT();
		}
		else {
			cout << "所选功能有误,请重新输入" << endl;
			goto start;
		}
		PrintBT(T);
		cout << "先序遍历:" << endl;
		PreOrder(T);
		cout << endl;
		PreOrder2(T);
		cout << "中序遍历: " << endl;
		InOrder(T);
		cout << endl;
		InOrder2(T);
		cout << "后序遍历: " << endl;
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
