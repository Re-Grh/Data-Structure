#include <iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
#define maxlen 100
#pragma warning(disable:4996)
using namespace std;
struct Link
{
	int v;
	Link * next;
};
struct node
{
	char element;
	struct Link* firstedge;
};
struct Adgraph
{
	int n, e;
	node Ad[maxlen];
};
typedef struct Adgraph biao; /*邻接表*/
int DFN[maxlen], LOW[maxlen];
int stack[maxlen], visit[maxlen], xuhao=0, index=-1;
void cre1(biao  *G) /*创建邻接表*/
{
	int k, i, j;
	cout << "输入顶点数及边数" << endl;
	cin >> G->n >> G->e;
	cout << "输入顶点信息" << endl;
	for (k = 0; k<G->n; k++)
	{
		cin >> G->Ad[k].element;
		G->Ad[k].firstedge = NULL;
	}
	cout << "输入边上两顶点的序号" << endl;
	for (k = 0; k<G->e; k++)
	{
		cin >> j >> i;
		Link* p = new Link;
		p->v = i;
		p->next = G->Ad[j].firstedge;
		G->Ad[j].firstedge = p;  /*双插法*/
	}
	cout << "邻接表：" << endl;
	for (i = 0; i<G->n; i++)
	{
		cout << G->Ad[i].element;
		Link *m = G->Ad[i].firstedge;
		while (m != NULL)
		{
			printf("->%c", G->Ad[m->v].element);
			m = m->next;
		}
		cout << "->NULL" << endl;
	}

}
void tarjan(int x, biao *G)
{
	DFN[x] = LOW[x] = ++xuhao;
	stack[++index] = x;
	Link* p; int w;
	visit[x] = 1;
	for (p = G->Ad[x].firstedge; p; p = p->next)
	{
		w = p->v;
		if (DFN[w] == 0) 
		{
			tarjan(w,G);
			LOW[x] = min(LOW[x], LOW[w]);

		}
		else if (visit[w]){  
			LOW[x] = min(LOW[x], DFN[w]);

		}
	}
	if (LOW[x] == DFN[x]) 
	{
		do{
			cout<< G->Ad[stack[index]].element<<"  ";
			visit[stack[index]] = 0;
			index--;

		} while (x != stack[index + 1]);
		cout << endl;
	}
	return;
}
int main()
{
	freopen("1.txt", "r", stdin);
	biao *G = new biao;
	cre1(G);
	cout << "强联通分量: " << endl;
	for (int i = 0; i < G->n; i++)
	{
		if (!DFN[i])  tarjan(i, G);
	}
	fclose(stdin);
	return 0;
}

