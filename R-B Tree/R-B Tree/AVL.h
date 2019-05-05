#include<iostream>
#include<string>
#include<queue>
#include<cstdlib>
using namespace std;

struct node{
	int element;
	node* lchild;
	node* rchild;
	int height;
};
typedef node* AVL;   /*ƽ������㶨��*/
int Height(AVL T)
{
	return (T == NULL ? 0 : T->height);
}
int Max(int x, int y)
{
	return x > y ? x : y;
}
void PrintBT(AVL T)   /*���д�ӡһ��AVL��*/
{
	cout << "AVL����������: " << endl;
	AVL Q[300], tmp;                      /*���ָ�����*/
	int front = 0, rear = 0, i = 1, j = 0, k = 1, n, flag = 0;
	if (T != NULL) Q[++rear] = T;
	while (1)
	{
		tmp = Q[++front];
		if (i == pow(2, j))                /*��2��ָ��ÿ�д�ӡ*/
		{
			for (k; k <= rear; k++)
			{
				if (Q[k] != NULL) cout << Q[k]->element << "   ";
				else  cout << "N   ";
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
			i += 2;
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
AVL SingleLeft(AVL T) /*������ת����ƽ����*/
{
	AVL x = T;
	AVL y = T->lchild;
	x->lchild = y->rchild;
	y->rchild = x;
	x->height = Max(Height(x->lchild), Height(x->rchild)) + 1;
	y->height = Max(Height(y->lchild), Height(y->rchild)) + 1;
	return y;
}
AVL SingleRight(AVL T)
{
	AVL x = T;
	AVL y = x->rchild;
	x->rchild = y->lchild;
	y->lchild = x;
	x->height = Max(Height(x->lchild), Height(x->rchild)) + 1;
	y->height = Max(Height(y->lchild), Height(y->rchild)) + 1;
	return y;
}
AVL DoubleLeft(AVL T)
{
	AVL G;
	T->lchild = SingleRight(T->lchild);
	G = SingleLeft(T);
	return G;
}
AVL DoubleRight(AVL T)
{
	AVL G;
	T->rchild = SingleLeft(T->rchild);
	G = SingleRight(T);
	return G;
}
AVL Insert(int X, AVL T)
{
	if (T == NULL)
	{
		T = new node;
		T->element = X;
		T->height = 0;
		T->lchild = T->rchild = NULL;

	}
	else if (X<T->element)
	{
		T->lchild = Insert(X, T->lchild);
		if (Height(T->lchild) - Height(T->rchild) == 2)
		{
			if (X < T->lchild->element)
			{
				T = SingleLeft(T);
			}
			else
			{
				T = DoubleLeft(T);
			}
		}
	}
	else if (X>T->element)
	{
		T->rchild = Insert(X, T->rchild);
		if (Height(T->rchild) - Height(T->lchild) == 2)
		{
			if (X < T->rchild->element)
			{
				T = DoubleRight(T);
			}
			else
			{
				T = SingleRight(T);

			}
		}
	}
	T->height = Max(Height(T->lchild), Height(T->rchild) + 1);
	return T;
}
AVL CreatAVL(AVL T,int a[])
{
	cout << "������AVL���ڵ����������Ϣ" << endl;
	int n, i;
	cin >> n;
	for (i = 0; i < n; i++) T = Insert(a[i], T);
	return T;
}

int deletemin(AVL &T) /*Ѱ��������������ڵ�*/
{
	if (T->lchild == NULL)
	{
		int tmp = T->element;
		T = T->rchild;
		return tmp;
	}
	else return deletemin(T->lchild);
}
AVL Delete(int X, AVL T)
{
	if (T == NULL)
	{
		cout << "δ�ҵ�ɾ��Ԫ��" << endl;
		return NULL;
	}

	if (T->element > X)             //��������������ɾ��X
	{
		T->lchild = Delete(X, T->lchild);
		if (Height(T->rchild) - Height(T->lchild) == 2)
		{
			if (Height(T->rchild->lchild) > Height(T->rchild->rchild))
			{
				T = DoubleRight(T);
			}
			else
			{
				T = SingleRight(T);
			}
		}
	}
	else if (T->element < X)        //��������������ɾ��X
	{
		T->rchild = Delete(X, T->rchild);

		if (Height(T->lchild) - Height(T->rchild) == 2)
		{
			if (Height(T->lchild->rchild) > Height(T->lchild->lchild))
			{
				T = DoubleLeft(T);
			}
			else
			{
				T = SingleLeft(T);
			}
		}
	}
	else
	{
		if (T->lchild == NULL)       //���������Ϊ��
		{
			T = T->rchild;
		}
		else if (T->rchild == NULL)  //���������Ϊ��
		{
			T = T->lchild;
		}
		else                          //��������������ǿ�
		{
			T->element = deletemin(T->rchild);
			if (Height(T->lchild) - Height(T->rchild) == 2)
			{
				if (Height(T->lchild->rchild) > Height(T->lchild->lchild))
				{
					T = DoubleLeft(T);
				}
				else
				{
					T = SingleLeft(T);
				}
			}
		}

	}

	if (T != NULL)
	{
		T->height = Max(Height(T->lchild), Height(T->rchild)) + 1;
	}
	return T;
}
AVL DeleteAVL(AVL T)
{
	int X;
	cout << "������ɾ�������Ϣ" << endl;
	cin >> X;
	return Delete(X, T);
}
void SearchAVL(int X, AVL T)
{
	if (T == NULL)
	{
		cout << "δ�ҵ���Ӧ���" << endl;
		return;
	}
	if (X < T->element) SearchAVL(X, T->lchild);
	else if (X>T->element) SearchAVL(X, T->rchild);
	else  cout << "���" << X << "����AVL���б��ҵ�" << endl;
}
void Inorder(AVL T)      /*�и�����ʵ������*/
{
	if (T != NULL)
	{
		Inorder(T->lchild);
		cout << T->element << "   ";
		Inorder(T->rchild);
	}
}
void Inorder2(AVL T)   /*�������*/
{
	if (T != NULL)
	{
		Inorder2(T->rchild);
		cout << T->element << "   ";
		Inorder2(T->lchild);
	}
}