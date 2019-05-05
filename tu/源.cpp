#include <iostream>
#include <cstdio>
#pragma warning(disable:4996)
#define maxlen 100
#define maxint 10000
using namespace std;
int D[maxlen], P[maxlen], S[maxlen];
int D1[maxlen][maxlen], P1[maxlen][maxlen];
struct matrix_graph
{
	int n, e; 
	int mat[maxlen][maxlen];
};
typedef struct matrix_graph juzhen; /*邻接矩阵*/

void cre1(juzhen  &G) /*创建邻接矩阵*/
{
	FILE* fstream;
	fstream = fopen("2.txt", "r+");
	int i, j, x, y,w;
	cout << "输入顶点数及边数" << endl;
	fscanf(fstream, "%d %d", &G.n, &G.e);
	cout << "输入顶点信息" << endl;
	for (i = 1; i<=G.n; i++)
	for (j = 1; j <=G.n; j++)
	{
		G.mat[i][j] = maxint;
	}
	cout << "输入边上两顶点的序号及其权值" << endl;
	for (i = 0; i<G.e; i++)
	{
		fscanf(fstream, "%d %d %d", &x, &y,&w);
		G.mat[x][y] = w;
	}
	cout << "邻接矩阵：" << endl;
	for (i = 1; i<=G.n; i++)
	{
		for (j = 1; j<=G.n; j++)
			cout << G.mat[i][j] << " ";
		cout << endl;
	}
	fclose(fstream);
}
void Dijkstra(juzhen G, int v,int c)
{
	int i, j,k,min;
	for (i = 1; i <= G.n; i++)
	{
		S[i] = 0;
	}
	for (i = 1; i <= G.n; i++)
	{
		D[i] = G.mat[v][i];
		if (D[i] < maxint) P[i] = v;
		else P[i] = 0;
	}
	P[v] = 0, S[v] = 1;
	for (i = 2; i <= G.n; i++)
	{
		min = maxint;
		for (j = 1; j <= G.n; j++)
		{
			if (D[j] < min&&S[j]==0)
			{
				k = j;
				min = D[k];
			}
		}
		S[k] = 1;
		for (j = 1; j <= G.n; j++)
		{
			if (S[j]==0)
			{
				if (D[j] > D[k] + G.mat[k][j])
				{
					D[j] = D[k] + G.mat[k][j];
					P[j] = k;
				}
			}
		}
	}
	cout << "最短路径长度    最短路径" << endl;
	if (c == 1)
	{
		for (i = 1; i <= G.n; i++)
		{
			if (i != v)
			{
				cout << D[i] << "     " << i;
				k = P[i];
				while (k != 0){
					cout << " <- " << k;
					k = P[k];
				}
				cout << endl;
			}
		}
	}
	else{
		for (i = 1; i <= G.n; i++)
		{
			if (i != v)
			{
				cout << D[i] << "     " << i;
				k = P[i];
				while (k != 0){
					cout << " -> " << k;
					k = P[k];
				}
				cout << endl;
			}
		}
	}
	
}
void Floyd(juzhen G)
{
	int i, j, k;
	for (i = 1; i <= G.n; i++)
	{
		for (j = 1; j <= G.n; j++)
		{
			D1[i][j] = G.mat[i][j];
			P1[i][j] = 0;
		}
	}
	for (k = 1; k <= G.n; k++)
	{
		for (i = 1; i <= G.n; i++)
		{
			for (j = 1; j <= G.n; j++)
			{
				if (D1[i][j] > D1[i][k] + D1[k][j])
				{
					D1[i][j] = D1[i][k] + D1[k][j];
					P1[i][j] = k;
				}
			}
		}
	}
}
int main()
{
	int v,i,j,k,a,c,tep=1;
	juzhen G,g;
	cre1(G);
	while (tep)
	{
		printf("最短路径算法实现如下 \n");
		printf("1——Dijkstra算法输出源点到其他顶点的最短路径\n");
		printf("2——Floyd-Warshall算法输出任意两个顶点间的最短路径\n");
		printf("3——Dijkstra算法输出其他顶点到目标终点的最短路径\n");
		printf("4——Floyd-Warshall算法输出某对顶点最短路径\n");
		printf("6——退出程序\n");
		printf("请输入服务选项（1-6）:");
		cin >> a;
		switch (a)
		{

		case 1:
			system("cls");
			cout << "请输入源点：";
			cin >> v;
			Dijkstra(G, v,1);
			printf("是否继续？（1.YES  2，NO  ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 2:
			system("cls");
			Floyd(G);
			cout << "最短距离矩阵：" << endl;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
					cout << D1[i][j] << " ";
				cout << endl;
			}
			cout << "最短路径矩阵：" << endl;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
					cout << P1[i][j] << " ";
				cout << endl;
			}
			cout << "最短路径长度    最短路径" << endl;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
				{
					if (D1[i][j] < maxint/2&&i!=j)
					{
						cout << D1[i][j] << "   ";
						k = P1[i][j];
						cout << j << " <- ";
						while (k != 0){
							cout << k << " <- ";
							k = P1[k][j];
						}
						cout << i;
						cout << endl;
					}
				}
			}
			printf("是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "请输入终点：";
			cin >> v;
			g.e = G.e, g.n = G.n;
			for (i = 1; i <= G.n; i++)
			{
				for (j = 1; j <= G.n; j++)
					g.mat[i][j] = G.mat[j][i];
			}
			Dijkstra(g, v,2);
			printf("\n是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 4:
			system("cls");
			Floyd(G);
			cout << "输入任意两个顶点： ";
			cin >> i >> j;
			cout << "顶点" << i << " -> " << j << "    ";
			cout << "最短路径长度    最短路径" << endl;
			cout << D1[i][j] << "   ";
			k = P1[i][j];
			cout << j << " <- ";
			while (k != 0){
				cout << k << " <- ";
				k = P1[k][j];
			}
			cout << i;
			cout << endl;
			cout << "顶点" << j << " -> " << i << "    ";
			cout << "最短路径长度    最短路径" << endl;
			cout << D1[j][i] << "   ";
			k = P1[j][i];
			cout << i << " <- ";
			while (k != 0){
				cout << k << " <- ";
				k = P1[k][i];
			}
			cout << j;
			cout << endl;
			printf("\n是否继续？（1.YES  2，NO ）：");
			cin >> c;
			getchar();
			if (c == 1)tep = 1;
			else
				tep = 0;
			system("cls");
			break;
		case 5:
			system("cls");
			
			system("cls");
			break;
		case 6:
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