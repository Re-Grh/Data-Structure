#include<iostream>
#include<string>
#include<queue>
#include<cstdlib>
using namespace std;

struct node{
	int element;
	node* lchild ;
	node* rchild;
	int height;
};
typedef node* AVL;   /*平衡树结点定义*/
int Height(AVL T)
{
	return (T == NULL ? 0 : T->height);
}                    
int Max(int x, int y)
{
	return x > y ? x : y;
}
void PrintBT(AVL T)   /*按行打印一株AVL树*/
{
	AVL Q[50], tmp;                      /*结点指针队列*/
	int front = 0, rear = 0, i = 1, j = 0, k = 1, n, flag = 0;
	if (T != NULL) Q[++rear] = T;
	while (1)
	{
		tmp = Q[++front];
		if (i == pow(2, j))                /*按2的指数每行打印*/
		{
			for (k; k <= rear; k++)
			{
				if (Q[k] != NULL) cout << Q[k]->element << "   ";
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
			i += 2;
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
AVL SingleLeft(AVL T) /*四种旋转调整平衡树*/
{
	AVL x = T;
	AVL y = T->lchild;
	printf("结点%d发生LL旋转： %d的右儿子变为%d的左儿子，%d成为新的父节点，新右儿子为%d\n", x->element, y->element, x->element, y->element, x->element);
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
	printf("结点%d发生RR旋转： %d的左儿子变为%d的右儿子，%d成为新的父节点，新左儿子为%d\n", x->element, y->element, x->element, y->element, x->element);
	x->rchild = y->lchild;
	y->lchild = x;
	x->height = Max(Height(x->lchild), Height(x->rchild) )+ 1;
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
				printf("\n结点%d发生LR旋转：\n", T->element);
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
				printf("\n结点%d发生RL旋转：\n", T->element);
				T =DoubleRight(T);
			}
			else
			{
				T = SingleRight(T);

			}
		}
	}
	T->height = Max(Height(T->lchild),Height( T->rchild) + 1);
	return T;
}
AVL CreatAVL(AVL T)
{
	cout << "请输入AVL树节点个数与结点信息" << endl;
	int a[1001],n,i;
	cin >> n;
	for (i = 0; i < n; i++) cin >> a[i];
	cout << "建立AVL树过程中发生如下旋转" << endl;
	for (i = 0; i < n; i++) T=Insert(a[i],T);
	return T;
}

int deletemin(AVL &T) /*寻找右子树的最左节点*/
{
	if (T->lchild == NULL)
	{
		int tmp = T->element;
		T = T->rchild;
		return tmp;
	}
	else return deletemin(T->lchild);
}
AVL Delete(int X,AVL T)
{
	if (T == NULL)
	{
		cout << "未找到删除元素" << endl;
		return NULL;
	}

	if (T->element > X)             //在树的左子树上删除X
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
	else if (T->element < X)        //在树的右子树上删除X
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
		if (T->lchild == NULL)       //如果左子树为空
		{
			T = T->rchild;
		}
		else if (T->rchild == NULL)  //如果右子树为空
		{
			T = T->lchild;
		}
		else                          //如果左右子树都非空
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
	cout << "请输入删除结点信息" << endl;
	cin >> X;
	return Delete(X, T);
}
void SearchAVL(int X, AVL T)
{
	if (T == NULL)
	{
		cout << "未找到相应结点" << endl;
		return;
	}
	if (X < T->element) SearchAVL(X, T->lchild);
	else if (X>T->element) SearchAVL(X, T->rchild);
	else  cout <<"结点"<<X<< "已在AVL树中被找到" << endl;
}
void Inorder(AVL T)      /*中根遍历实现排序*/
{
	if (T != NULL)
	{
		Inorder(T->lchild);
		cout << T->element << "   ";
		Inorder(T->rchild);
	}
}
void Inorder2(AVL T)   /*反向遍历*/
{
	if (T != NULL)
	{
		Inorder2(T->rchild);
		cout << T->element << "   ";
		Inorder2(T->lchild);
	}
}
int main()
{
	int n, tep = 1,a,c;
	AVL T = NULL;
	while (tep)
	{
		printf("AVL树系统功能如下 \n");
		printf("1——AVL存储结构建立（插入）\n");
		printf("2——AVL树删除操作\n");
		printf("3——AVL树上的查找\n");
		printf("4——利用AVL树的排序\n");
		printf("5——退出程序\n");
		printf("请输入服务选项（1-5）:");
		cin >> a;
		switch (a)
		{
		
		case 1:
			system("cls");
			T = CreatAVL(T);
			cout << "已建立AVL树如下" << endl;
			PrintBT(T);
			printf("是否继续？（1.YES  2.NO  ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 2:
			system("cls");
			T = DeleteAVL(T);
			cout << "删除后新AVL树如下" << endl;
			PrintBT(T);
			printf("是否继续？（1.YES  2.NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "输出查找结点信息" << endl;
			cin >> n;
			SearchAVL(n, T);
			printf("\n是否继续？（1.YES  2.NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 4:
			system("cls");
			cout << "升序排列AVL树结点如下" << endl;
			Inorder(T);
			cout << endl;
			cout << "降序排列AVL树结点如下" << endl;
			Inorder2(T);
			cout << endl;
			printf("\n是否继续？（1.YES  2.NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 5:
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