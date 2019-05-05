#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
#define maxlen 100
using namespace std;
bool visited[maxlen];/*������־����*/
int dfn[maxlen];  /*�����������*/
int xuhao = 1;
int z=0;
char xianshen[maxlen];  /*������С������*/
char xianguang[maxlen];
struct Link
{
	int v;
	int mark;
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
typedef struct Adgraph biao; /*�ڽӱ�*/
struct matrix_graph
{
	int n, e;
	int mat[maxlen][maxlen];
	int mark[maxlen][maxlen];
	char element[maxlen];
};
typedef struct matrix_graph juzhen; /*�ڽӾ���*/
struct EBOX{
	int ivex, jvex;
	struct EBOX*ilink, *jlink;
};
struct VexBox{
	char element;
	EBOX *firstedge;
};
typedef struct{
	VexBox Ad[maxlen];
	int n, e;
} AMLGraph;  /*�ڽӶ��ر�*/
void cre1(juzhen  &G) /*�����ڽӾ���*/
{
	int i, j, x, y;
	cout << "���붥����������" << endl;
	cin >> G.n >> G.e;
	cout << "���붥����Ϣ" << endl;
	for (i = 0; i<G.n; i++)  cin >> G.element[i];
	for (i = 0; i<G.n; i++)
	for (j = 0; j < G.n; j++)
	{
		G.mat[i][j] = 0;
		G.mark[i][j] = 0;
	}
	cout << "�����������������" << endl;
	for (i = 0; i<G.e; i++)
	{
		cin >> x >> y;
		G.mat[x][y] = 1;
		G.mat[y][x] = 1;
	}
	cout << "�ڽӾ���" << endl;
	for (i = 0; i<G.n; i++)
	{
		for (j = 0; j<G.n; j++)
			cout << G.mat[i][j] << " ";
		cout << endl;
	}
}
void cre2(biao  *G) /*�����ڽӱ�*/
{
	int k, i, j;
	cout << "���붥����������" << endl;  
	cin >> G->n >> G->e;
	cout << "���붥����Ϣ" << endl;
	for (k = 0; k<G->n; k++)
	{
		cin >> G->Ad[k].element;
		G->Ad[k].firstedge = NULL;
	}
	cout << "�����������������" << endl;
	for (k = 0; k<G->e; k++)
	{
		cin >> j >> i;
		Link* p = new Link;
		p->v = i;  
		p->next = G->Ad[j].firstedge;
		G->Ad[j].firstedge = p;  /*˫�巨*/
		p = new Link;
		p->v = j;
		p->next = G->Ad[i].firstedge;
		G->Ad[i].firstedge = p;      /*����ͼ*/
		p->mark = 0;
	}
	cout << "�ڽӱ�" << endl;
	for (i = 0; i<G->n; i++)
	{
		cout << G->Ad[i].element;
		Link *m = G->Ad[i].firstedge;
		while (m != NULL)
		{
			printf("->%c", G->Ad[m->v].element);
			m = m->next;
		}
		cout<<"->NULL"<<endl;
	}

}
void cre3(AMLGraph &G)  /*�����ڽӶ��ر�*/
{
	int i, j, k;
	cout << "���붥����������" << endl;
	cin >> G.n >> G.e;
	cout << "���붥����Ϣ" << endl;
	for (k = 0; k<G.n; k++)
	{
		cin >> G.Ad[k].element;
		G.Ad[k].firstedge = NULL;
	}
	cout << "�����������������" << endl;
	for (k = 0; k < G.e; k++)
	{
		cin >>i >> j;
		EBOX* p = new EBOX;
		p->ivex = i, p->jvex = j;
		p->ilink = G.Ad[i].firstedge;
		p->jlink = G.Ad[j].firstedge;
		G.Ad[i].firstedge = p;
		G.Ad[j].firstedge = p; /*˫�巨*/
	}
	cout << "�ڽӶ��ر�" << endl;
	for (i = 0; i<G.n; i++)
	{
		cout << G.Ad[i].element;
		EBOX *m = G.Ad[i].firstedge;
		while (m != NULL)
		{
			if (m->ivex == i)       /*�ж϶����ڱ��ϵ�����λ��*/
			{
				printf("->(%c,%c)", G.Ad[m->ivex].element, G.Ad[m->jvex].element);
				m = m->ilink;
			}
			else
			{
				printf("->(%c,%c)", G.Ad[m->ivex].element, G.Ad[m->jvex].element);
				m = m->jlink;
			}
		}
		cout << "->NULL" << endl;
	}
}
void DFS1(juzhen *G, int i) 
{
	int j;
	cout << G->element[i] << " ";
	visited[i] = true;
	dfn[i] = xuhao;
	xuhao++;
	for (j = 0; j<G->n; j++)
	if (G->mat[i][j] == 1 && !visited[j])
	{
		G->mark[i][j] = 1;
		DFS1(G, j);
	}
}
void DFST1(juzhen G) /*�ڽӾ���ݹ�����*/
{
	int i,j,k=0;
	xuhao = 1;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	cout << "�ڽӾ���DFS��";
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) DFS1(&G, i);
	}
	cout << endl;
	cout << "�����ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout <<dfn[i]<< " ";
	}
	cout << endl;
	cout << "������������Ϣ���£�"<<endl;
	cout << "���ڵ�Ϊ��"<<G.element[0]<<endl;
	cout << "����ʱ���ʵıߣ�";
	for (i = 0; i < G.n; i++)
	{
		for (j = 0; j < G.n; j++)
		{
			if (G.mark[i][j] == 1)
			{
				if (dfn[i] < dfn[j])
					cout << G.element[i] << "-----" << G.element[j]<<"    "  ;	
				xianshen[k] = G.element[i];
				xianshen[k+1] = G.element[j];
				k += 2;
				z+=2;
			}
		}
	}
	z -= 2;
	cout << endl;
}
void DFS2(juzhen *G, int i)
{
	cout << "�ڽӾ���DFS(�ǵݹ�)��" ;
	xuhao = 1;
	int STACK[maxlen];
	int top = maxlen,j;
	STACK[--top] = i;
	while (top != maxlen)
	{
		int k = STACK[top];
		if (!visited[k])
		{
			cout << G->element[k] << " ";
			visited[k] = true;
			dfn[k] = xuhao;
			xuhao++;
		}
		else top++;
		for (j = 0; j<G->n; j++)
		if (G->mat[k][j] == 1 && !visited[j])
		{
			STACK[--top] = j;
			G->mark[k][j] = 1;
			break;
		}

	}
	
}
void DFST2(juzhen G) /*�ڽӾ���ǵݹ�����*/
{
	int i,j;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) DFS2(&G, i);
	}
	cout << endl;
	cout << "�����ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "����(�ǵݹ�)��������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << G.element[0] << endl;
	cout << "����ʱ���ʵıߣ�";
	for (i = 0; i < G.n; i++)
	{
		for (j = 0; j < G.n; j++)
		{
			if (G.mark[i][j] == 1)
			{
				if (dfn[i] < dfn[j])
					cout << G.element[i] << "-----" << G.element[j] << "    ";
			}
		}
	}
	cout << endl;
}
void BFS1(juzhen *G, int i)
{
	cout << "�ڽӾ���BFS��";
	xuhao = 1;
	int Queue[maxlen], front = 0, rear = 0, w;
	visited[i] = true;
	dfn[i] = xuhao++;
	Queue[rear++] = i;
	cout << G->element[i] << " ";
	while (front != rear)
	{
		i= Queue[front++];
		for (w = 0; w<G->n; w++)
		{
			if (!visited[w] && G->mat[i][w]==1)
			{
				cout << G->element[w] << " ";
				G->mark[i][w] = 1;
				visited[w] = true;
				dfn[w] = xuhao++;
				Queue[rear++] = w;
			}
		}
	}
}
void BFST1(juzhen G) /*�ڽӾ������*/
{
	int i,j,k=0;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) BFS1(&G, i);
	}
	cout << endl;
	cout << "�ȹ��ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "�ȹ���������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << G.element[0] << endl;
	cout << "����ʱ���ʵıߣ�";
	for (i = 0; i < G.n; i++)
	{
		for (j = 0; j < G.n; j++)
		{
			if (G.mark[i][j] == 1)
			{
				if (dfn[i] < dfn[j])
					cout << G.element[i] << "-----" << G.element[j] << "    ";
				xianguang[k] = G.element[i];
				xianguang[k + 1] = G.element[j];
				k += 2;
			}
		}
	}
	cout << endl;
}

void DFS3(biao *G, int i)
{
	cout << G->Ad[i].element << " ";
	visited[i] = true;
	dfn[i] = xuhao;
	xuhao++;
	Link *p = G->Ad[i].firstedge;
	while (p != NULL)
	{
		if (!visited[p->v])
		{
			DFS3(G, p->v);
			p->mark = 1;
		}
		p = p->next;
	}
}
void DFST3(biao G) /*�ڽӱ�ݹ�����*/
{
	int i;
	xuhao = 1;
	Link *p=NULL;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	cout << "�ڽӱ�DFS��";
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) DFS3(&G, i);
	}
	cout << endl;
	cout << "�����ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "������������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << G.Ad[0].element << endl;
	cout << "����ʱ���ʵıߣ�";
	for (i = 0; i < G.n; i++)
	{	
		p = G.Ad[i].firstedge;
		while (1)
		{
			if (p->mark == 1)
			{
				if (dfn[i] < dfn[p->v])
					cout << G.Ad[i].element << "-----" << G.Ad[p->v].element << "    ";
			}
			p = p->next;
			if (p == NULL) break;
		}
	}
	cout << endl;
}
void DFS4(biao *G, int i)
{
	cout << "�ڽӱ�DFS(�ǵݹ�)��";
	xuhao = 1;
	int STACK[maxlen];
	int top = maxlen;
	STACK[--top] = i;
	while (top != maxlen)
	{
		int k = STACK[top];
		if (!visited[k])
		{
			cout << G->Ad[k].element << " ";
			visited[k] = true;
			dfn[k] = xuhao;
			xuhao++;
		}
		else top++;
		Link *p = G->Ad[k].firstedge;
		while (p != NULL)
		{
			if (!visited[p->v])
			{
				STACK[--top] = p->v;
				break;
			}
			p = p->next;
		}

	}
	
}
void DFST4(biao G) /*�ڽӱ�ǵݹ�����*/
{
	int i,j;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) DFS4(&G, i);
	}
	cout << endl;
	cout << "�����ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "����(�ǵݹ�)��������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << G.Ad[0].element << endl;
	cout << "����ʱ���ʵıߣ�";
	for (j = 0; j <= z;j+=2)
		cout <<xianshen[j] << "-----" << xianshen[j+1] << "    ";
	cout << endl;

}
void BFS2(biao *G, int i)
{
	cout << "�ڽӱ�BFS��";
	xuhao = 1;
	int Queue[maxlen], front = 0, rear = 0, w;
	visited[i] = true;
	dfn[i] = xuhao++;
	Queue[rear++] = i;
	cout << G->Ad[i].element << " ";
	while (front != rear)
	{
		i = Queue[front++];
		Link *p = G->Ad[i].firstedge;
		while (p != NULL)
		{
			if (!visited[p->v])
			{
				w = p->v;
				p->mark = 1;
				cout <<G->Ad[w].element << " ";
				visited[w] = true;
				dfn[w] = xuhao++;
				Queue[rear++] = w;
			}
			p = p->next;
		}
	}

}
void BFST2(biao G) /*�ڽӱ����*/
{
	int i,j;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) BFS2(&G, i);
	}
	cout << endl;
	cout << "�ȹ��ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "�ȹ���������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << G.Ad[0].element << endl;
	cout << "����ʱ���ʵıߣ�";
	for (j = 0; j <= z; j += 2)
		cout << xianguang[j] << "-----" << xianguang[j + 1] << "    ";
	cout << endl;
}
void DFS5(AMLGraph *G, int i)
{
	cout << G->Ad[i].element << " ";
	visited[i] = true;
	dfn[i] = xuhao;
	xuhao++;
	EBOX *p = G->Ad[i].firstedge;
	while (p != NULL)
	{
		if (p->ivex == i)
		{
			if (!visited[p->jvex])
				DFS5(G, p->jvex);
			p = p->ilink;
		}
		else
		{
			if (!visited[p->ivex])
				DFS5(G, p->ivex);
			p = p->jlink;
		}
	}
}
void DFST5(AMLGraph G) /*�ڽӶ��ر�ݹ�����*/
{
	int i,j;
	xuhao = 1;
	for (i = 0; i < G.n; i++)
		visited[i]=0;
	cout << "�ڽӶ��ر�DFS��";
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) DFS5(&G, i);
	}
	cout << endl;
	cout << "�����ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "������������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << xianshen[0] << endl;
	cout << "����ʱ���ʵıߣ�";
	for (j = 0; j <= z; j += 2)
		cout << xianshen[j] << "-----" << xianshen[j + 1] << "    ";
	cout << endl;
}
void DFS6(AMLGraph *G, int i)
{
	cout << "�ڽӶ��ر�DFS(�ǵݹ�)��";
	xuhao = 1;
	int STACK[maxlen];
	int top = maxlen;
	STACK[--top] = i;
	while (top != maxlen)
	{
		i = STACK[top];
		int k = STACK[top];
		if (!visited[k])
		{
			cout << G->Ad[k].element << " ";
			visited[k] = true;
			dfn[k] = xuhao;
			xuhao++;
		}
		else top++;
		EBOX *p = G->Ad[k].firstedge;
		while (p != NULL)
		{
			if (p->ivex == i)
			{
				if (!visited[p->jvex])
				{
					STACK[--top] = p->jvex;
					break;
				}
				p = p->ilink;
			}
			else
			{
				if (!visited[p->ivex])
				{
					STACK[--top] = p->ivex;
					break;
				}
				p = p->jlink;
			}
		}

	}

}
void DFST6(AMLGraph G) /*�ڽӶ��ر�ǵݹ�����*/
{
	int i,j;
	for (i = 0; i < G.n; i++)
		visited[i] = 0;
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) DFS6(&G, i);
	}
	cout << endl;
	cout << "�����ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "����(�ǵݹ�)��������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << xianshen[0] << endl;
	cout << "����ʱ���ʵıߣ�";
	for (j = 0; j <= z; j += 2)
		cout << xianshen[j] << "-----" << xianshen[j + 1] << "    ";
	cout << endl;
}
void BFS3(AMLGraph *G, int i)
{
	cout << "�ڽӱ�BFS��";
	xuhao = 1;
	int Queue[maxlen], front = 0, rear = 0, w;
	visited[i] = true;
	dfn[i] = xuhao++;
	Queue[rear++] = i;
	cout << G->Ad[i].element << " ";
	while (front != rear)
	{
		i = Queue[front++];
		EBOX *p = G->Ad[i].firstedge;
		while (p != NULL)
		{
			if (p->ivex == i)
			{
				if (!visited[p->jvex])
				{
					w = p->jvex;
					cout << G->Ad[w].element << " ";
					visited[w] = true;
					dfn[w] = xuhao++;
					Queue[rear++] = w;
				}
				p = p->ilink;
			}
			else
			{
				if (!visited[p->ivex])
				{
					w = p->ivex;
					cout << G->Ad[w].element << " ";
					visited[w] = true;
					dfn[w] = xuhao++;
					Queue[rear++] = w;
				}
				p = p->jlink;
			}
		}
	}

}
void BFST3(AMLGraph G) /*�ڽӶ��ر����*/
{
	int i,j;
	for (i = 0; i < G.n; i++)
		visited[i] = false;
	for (i = 0; i < G.n; i++)
	{
		if (!visited[i]) BFS3(&G, i);
	}
	cout << endl;
	cout << "�ȹ��ţ�";
	for (i = 0; i < G.n; i++)
	{
		cout << dfn[i] << " ";
	}
	cout << endl;
	cout << "�ȹ���������Ϣ���£�" << endl;
	cout << "���ڵ�Ϊ��" << xianguang[0] << endl;
	cout << "����ʱ���ʵıߣ�";
	for (j = 0; j <= z; j += 2)
		cout << xianguang[j] << "-----" << xianguang[j + 1] << "    ";
	cout << endl;
}
void MatToList(juzhen g, biao *G) /*�ڽӾ���װ��Ϊ�ڽӱ�*/
{
	int i, j;
	for (i = 0; i<g.n; i++)                  
		G->Ad[i].firstedge = NULL;
	for (i = 0; i<g.n; i++)                  
		G->Ad[i].element =g.element[i];
	for (i = 0; i<g.n; i++)                  
	for (j = g.n - 1; j >= 0; j--)
	if (g.mat[i][j] != 0)      
	{
		Link* p = new Link; 
		p->v = j;
		p->next = G->Ad[i].firstedge;
		G->Ad[i].firstedge = p;
	}
	G->n = g.n; G->e = g.e;
	cout << endl;
	cout << "�ڽӾ���ת��Ϊ�ڽӱ�" << endl;
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
void ListToMat(biao G, juzhen &g) /*�ڽӱ�װ��Ϊ�ڽӾ���*/
{
	int i,j;
	Link *p;
	g.n = G.n; g.e = G.e;
	for (i = 0; i<g.n; i++)
	{
		for (j = 0; j<g.n; j++)
		 g.mat[i][j] =0;
		
	}
	for (i = 0; i<G.n; i++)
		g.element[i]=G.Ad[i].element ;
	for (i = 0; i<G.n; i++)
	{
		p = G.Ad[i].firstedge;
		while (p != NULL)
		{
			g.mat[i][p->v] = 1;
			p = p->next;
		}
	}
	cout << endl;
	cout << "�ڽӱ�ת��Ϊ�ڽӾ���" << endl;
	for (i = 0; i<g.n; i++)
	{
		for (j = 0; j<g.n; j++)
			cout << g.mat[i][j] << " ";
		cout << endl;
	}
}
void ListToAML(biao *g,AMLGraph &G) /*�ڽӱ�װ��Ϊ�ڽӶ��ر�*/
{
	int i, j, k;
	Link *q;
	G.e = g->e, G.n = g->n;
	for (k = 0; k<G.n; k++)
	{
		 G.Ad[k].element=g->Ad[k].element;
		G.Ad[k].firstedge = NULL;
	}
	for (k = 0; k < G.n; k++)
	{
		q = g->Ad[k].firstedge;
		while (q != NULL)
		{
			i = k, j = q->v;
			EBOX* p = new EBOX;
			p->ivex = i, p->jvex = j;
			p->ilink = G.Ad[i].firstedge;
			G.Ad[i].firstedge = p;
			q = q->next;
		}
	}
	cout << endl;
	cout << "�ڽӱ�ת��Ϊ�ڽӶ��ر�" << endl;
	for (i = 0; i<G.n; i++)
	{
		cout << G.Ad[i].element;
		EBOX *m = G.Ad[i].firstedge;
		while (m != NULL)
		{
			if (m->ivex == i)
			{
				printf("->(%c,%c)", G.Ad[m->ivex].element,G.Ad[m->jvex].element);
				m = m->ilink;
			}
			else
			{
				printf("->(%c,%c)", G.Ad[m->ivex].element, G.Ad[m->jvex].element);
				m = m->jlink;
			}
		}
		cout << "->NULL" << endl;
	}
}
void AMLToList(AMLGraph g, biao *G) /*�ڽӶ��ر�װ��Ϊ�ڽӱ�*/
{
	int i,k;
	EBOX *q;
	for (i = 0; i<g.n; i++)
		G->Ad[i].firstedge = NULL;
	for (i = 0; i<g.n; i++)
		G->Ad[i].element = g.Ad[i].element;
	for (k = 0; k < g.n; k++)
	{
		q = g.Ad[k].firstedge;
		while (q != NULL)
		{
			Link * p = new Link;
			if (G->Ad[k].element == g.Ad[q->ivex].element)
			{
				p->v = q->jvex;
				q = q->ilink;
			}
			else  { p->v = q->ivex; 
			q = q->jlink;
			}
			p->next = G->Ad[k].firstedge;
			G->Ad[k].firstedge = p;
		}
	}
	G->n = g.n; G->e = g.e;
	cout << endl;
	cout << "�ڽӶ��ر�ת��Ϊ�ڽӱ�" << endl;
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
int main()
{
	AMLGraph T;
	juzhen g;
	biao G;
	printf("1������ȡ�ļ������ڽӾ���\n");
	printf("2�����ڽӾ������������\n");
	printf("3�����ڽӾ���ת��Ϊ�ڽӱ�\n");
	printf("4�����ڽӱ����������\n");
	printf("5�����ڽӱ�ת��Ϊ�ڽӶ��ر�\n");
	printf("6�����ڽӶ��ر����������\n");
	freopen("1.txt", "r", stdin);
	cre1(g);
	DFST1(g);
	DFST2(g);
	BFST1(g);
	MatToList(g, &G);
	DFST3(G);
	DFST4(G);
	BFST2(G);
	ListToAML(&G, T);
	DFST5(T);
	DFST5(T);
	BFST3(T);
	fclose(stdin);	
	return 0;
}

