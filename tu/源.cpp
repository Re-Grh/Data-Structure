#include <iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>
#include <time.h>
#pragma warning(disable:4996)
#define maxlen 100
using namespace std;
#define MAX  10000  
int lowcost[maxlen], visit[maxlen], closest[maxlen],parent[maxlen];
struct matrix_graph
{
	int n, e;
	int mat[maxlen][maxlen];
};
typedef struct matrix_graph juzhen; /*邻接矩阵*/
struct edge{
	int f, l, w;
};

struct Kruscal{
	int n, e;
	edge E[maxlen];
};
bool cmp(const edge &a,const edge &b)
{
	return a.w < b.w;
}
void cre1(juzhen  &G, int n) /*创建邻接矩阵*/
{
	FILE* fstream;
	if (n == 1)
		fstream = fopen("test.txt", "r+");
	else
		fstream = fopen("1.txt", "r+");
	int i, j, x, y, w;
	cout << "输入顶点数及边数" << endl;
	fscanf(fstream, "%d %d", &G.n, &G.e);
	cout << "输入顶点信息" << endl;
	for (i = 1; i <= G.n; i++)
	for (j = 1; j <= G.n; j++)
	{
		G.mat[i][j] = MAX;
	}
	cout << "输入边上两顶点的序号及其权值" << endl;
	for (i = 0; i<G.e; i++)
	{
		fscanf(fstream, "%d %d %d", &x, &y, &w);
		G.mat[x][y] = w;
		G.mat[y][x] = w;
	}
	cout << "邻接矩阵：" << endl;
	for (i = 1; i <= G.n; i++)
	{
		for (j = 1; j <= G.n; j++)
			cout << G.mat[i][j] << " ";
		cout << endl;
	}
	fclose(fstream);
}
void cre2(Kruscal  &G, int n) 
{
	FILE* fstream;
	if (n == 1)
		fstream = fopen("test.txt", "r+");
	else
		fstream = fopen("1.txt", "r+");
	int i;
	cout << "输入顶点数及边数" << endl;
	fscanf(fstream, "%d %d", &G.n, &G.e);
	cout << "输入顶点信息" << endl;
	cout << "输入边上两顶点的序号及其权值" << endl;
	for (i = 0; i<G.e; i++)
	{
		fscanf(fstream, "%d %d %d", &G.E[i].f, &G.E[i].l, &G.E[i].w);
	}
	fclose(fstream);
}
void prim(int start,juzhen G)
{
	int sumweight = 0;
	clock_t sta, stop;
	double s;
	int i, j, k = 0;
	sta = clock();
	for (i = 1; i<=G.n; i++)                                      
	{
		lowcost[i] = G.mat[start][i];
		visit[i] = -1;  
		closest[i] = start;
	}
	visit[start] = 0;                                       
	closest[start] = start;
	for (i = 1; i<G.n; i++)
	{
		int min = MAX;
		int v = -1;
		for (j = 1; j<=G.n; j++)
		{
			if (visit[j] == -1 && lowcost[j]<min)                 
			{
				min = lowcost[j];
				v = j;
			}
		}
		printf("%d  %d  %d\n",closest[v],v, lowcost[v]);
		if (v != -1)
		{
			visit[v] = 0;                                      
			sumweight += lowcost[v];                           
			for (j = 1; j<=G.n; j++)
			{
				if (visit[j] == -1 && G.mat[v][j]<lowcost[j])
				{
					lowcost[j] = G.mat[v][j];                    
					closest[j] = v;
				}
			}
		}
	}
	stop = clock();
	s = (double)(stop - sta) / CLOCKS_PER_SEC;
	printf("the minmum weight is %d\n", sumweight);
	printf("the Prime time is %f\n", s);
}
int unionsearch(int x) 
{
	return x == parent[x] ? x : unionsearch(parent[x]);
}
void kruscal(Kruscal G)
{
	int i,sweight=0,j;
	clock_t start, stop;
	double s;
	start = clock();
	sort(G.E, G.E + G.e, cmp);
	for (i = 0; i < G.n; i++)
	{
	  parent[i] = i;
	}
	for (j = 0; j < G.n - 1; j++)
	{
		for (i = 0; i < G.e; i++)
		{
			if (unionsearch(G.E[i].f) != unionsearch(G.E[i].l))
			{
				printf("%d  %d  %d\n", G.E[i].f, G.E[i].l, G.E[i].w);
				parent[G.E[i].f] = parent[G.E[i].l];
				sweight += G.E[i].w;
				break;
			}
		}
	}
	stop = clock();
	s = (double)(stop - start) / CLOCKS_PER_SEC;
	printf("the minmum weight is %d\n", sweight);
	printf("the Kruscal time is %f\n", s);
}
int main()
{
	juzhen G,G1;
	cre1(G, 1);
	cout << "生成树的边如下: " << endl;
	prim(1, G);
	Kruscal g,g1;
	cre2(g, 1);
	cout << "生成树的边如下: " << endl;
	kruscal(g);
	cre1(G1, 2);
	cout << "生成树的边如下: " << endl;
	prim(1, G1);
	cre2(g1, 2);
	cout << "生成树的边如下: " << endl;
	kruscal(g1);
	return 0;
}
